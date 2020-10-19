/**
 * pccl is pleased to support the open source community by making Tars available.
 *
 * Copyright (C) 2016THL A29 Limited, a Tencent company. All rights reserved.
 *
 * Licensed under the BSD 3-Clause License (the "License"); you may not use this file except 
 * in compliance with the License. You may obtain a copy of the License at
 *
 * https://opensource.org/licenses/BSD-3-Clause
 *
 * Unless required by applicable law or agreed to in writing, software distributed 
 * under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
 * CONDITIONS OF ANY KIND, either express or implied. See the License for the 
 * specific language governing permissions and limitations under the License.
 */



#include "BaseController.h"
#include "servant/Application.h"
#include "optional/optional.h"
#include "util/tc_epoll_server.h"
#include "util/tc_common.h"
#include "util/tc_cgi.h"
#include <string>




BaseController::BaseController(void) 
{
	
}


BaseController::~BaseController()
{

}



tars::TC_NetWorkBuffer::PACKET_TYPE BaseController::checkHttpPacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out)
{
	return in.parseHttp(in,out);
}



void BaseController::clean()
{
	BaseControllerParams::clean();	
}


int BaseController::initialization(void)
{	
	// 设置路由
	if ( !this->getFinish() )
	{
		initError();
		
		initRoute();		
		
		this->setFininsh(true);
	}
	
	// 
	int result = initParse();
	
	return result;
}

void BaseController::success(int code,const std::string& msg)
{
	Json::Value doc;
	success(doc,code,msg);
}

void BaseController::success(Json::Value& data,int code,const std::string& msg )
{
	result(data,code,msg);
}

void BaseController::error(int code,const std::string& msg )
{	
	Json::Value doc;
	error(doc,code,msg);
}

void BaseController::error(Json::Value& data, int code,const std::string& msg)
{	
	if ( this->isError(code) )
	{
		result(data,code,this->getError(code) );
	}
	else
	{
		result(data,code,msg);
	}

}

void BaseController::rediect(const std::string& sUrl)
{
	std::map<std::string,std::string> header;
	const std::vector<std::string>    cookie;
		
	header["Content-Type"]   = "text/html";
	header["Location"]       = tars::TC_Cgi::decodeURL(sUrl);
	
	rediect( header,cookie );
}


void BaseController::rediect(const std::string& sUrl, const std::vector<std::string>& cookieHeader)
{
	
	std::map<std::string,std::string> header;
	header["Content-Type"]   = "text/html";
	header["Location"]       = tars::TC_Cgi::decodeURL(sUrl);
	
	rediect( header,cookieHeader );

}

void BaseController::rediect(const std::map<std::string,std::string>& httpHeader,const std::vector<std::string>& cookie)
{
	result( httpHeader,cookie,302 ,"Found","" );
}




void BaseController::authorize(const std::string& sMsg)
{	
	std::map<std::string,std::string> header;	
	Json::Value                       doc;
	std::string sRsp = serialize(doc,403,sMsg);	
	result( header,403, "Forbidden", sRsp );
}	

void BaseController::result( Json::Value& data)
{
	int code        = 0;
	std::string msg = "OK";
	result(data,code,msg);
}


void BaseController::result( Json::Value& data, int code, const std::string& msg )
{	
	std::map<std::string,std::string> header;	

	header["Content-Type"]  = "application/json;charset=utf-8";	
	std::string sBody       = serialize(data,code,msg);
	
    result(header, 200,  "OK", sBody );
}


void BaseController::result(const std::map<std::string,std::string>& httpHeader, int httpStutus, const std::string& about, const std::string& body   )
{
	std::vector<std::string> cookie;
	result(httpHeader,cookie,httpStutus,about,body);

}


void BaseController::result(const std::map<std::string,std::string>& httpHeader,  const std::vector<std::string>& cookieHeader, int httpStutus, const std::string& about , const std::string& body	)
{

	tars::TC_HttpResponse rsp;	
	std::vector<char>& outBuffer = *_outBuffer;


	if ( httpHeader.empty() )
	{	
		rsp.setHeader("Content-Type","application/json;charset=utf-8");
	}
	else
	{
		for( auto it = httpHeader.begin(); it != httpHeader.end(); it++ )
		{
			rsp.setHeader(it->first, it->second);
		}
	}

	for( auto it = cookieHeader.begin(); it != cookieHeader.end(); it++ )
	{
		rsp.setSetCookie(*it);
	}

	rsp.setResponse(httpStutus,about,body);
	rsp.encode(outBuffer);

}



std::string BaseController::serialize( Json::Value& data ,int code,const std::string& msg)
{

	Json::Value      doc;
	
	doc["code"]      = code;
	doc["msg"]       = msg;
	doc["data"]      = data;
	doc["sequence"]  = _sequence;	
	
	std::string buffer = Json::FastWriter().write(doc);

	return buffer;

}


int BaseController::doProcess(void)
{
	int result = pccl::STATE_SUCCESS;

	// clean
	//clean();

	
	TLOGDEBUG( "doProcessInit" << std::endl );
	
	// 初始化
	result = doProcessInit();
	if ( pccl::STATE_ERROR == result )
	{	
		return pccl::STATE_SUCCESS;
	}	

	TLOGDEBUG( "doProcessRoute" << std::endl );

	//todo
	//限制策略: 频率，ip,黑名单

	// 处理路由
	result = doProcessRoute();
	if ( pccl::STATE_ERROR == result )
	{	
		return pccl::STATE_SUCCESS;
	}

	TLOGDEBUG( "doProcess finish " << std::endl );

	return result;
	
}


int BaseController::doProcessInit(void)
{
	// 初始化
	int result = initialization();
	if ( pccl::STATE_SUCCESS != result )
	{	
		//todo 
		this->error();
		return pccl::STATE_ERROR;
	}	

	// todo

	return pccl::STATE_SUCCESS;
}


int BaseController::doProcessRoute(void)
{

	// 调用处理过程
	int result       = pccl::STATE_SUCCESS;
	std::string sUrl = this->getRequestUrl();
	int method       = this->requestType();
	
	TLOGDEBUG("doProcess , sequence:" <<  this->getSequence() << ",method: " <<  method << ",url:" << sUrl  << std::endl);

	// 处理option/head命令
	if ( this->isOPTIONS() || this->isHEADS() )
	{
		this->success();
		return pccl::STATE_SUCCESS;
	}

	//处理url:是否登录，授权	
	if (  this->hasAuthorize(sUrl) )
	{		
		TLOGDEBUG( "authorize url:" << sUrl << std::endl);

		result = this->doProcessAuthorize();
		if ( pccl::STATE_SUCCESS != result )
		{
			this->authorize("AUTH ERROR");	
			return pccl::STATE_ERROR;
		}
	}

	
	TLOGDEBUG( "has mothod, url: " << sUrl << std::endl);

	//处理业务逻辑
	if (  !this->hasMethod(sUrl,method) )
	{
		this->error(METHOD_ERROR);		
		return pccl::STATE_ERROR;
	}

	
	TLOGDEBUG( "do ruote, url: " << sUrl << std::endl);
	
	result = this->doRoute(sUrl);
	if ( pccl::STATE_SUCCESS != result )
	{
		this->error(ROUTER_ERROR);		
		return pccl::STATE_ERROR;
	}

	TLOGDEBUG( "do ruote finish, url: " << sUrl << std::endl);

	return pccl::STATE_SUCCESS;	
	
}



int BaseController::doProcessAuthorize(void)
{

	return pccl::STATE_SUCCESS;
}



