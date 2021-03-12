/**
 * PCCL is pleased to support the open source community by making Tars available.
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



#include "BaseApiResult.h"
#include "BaseHttpPlus.h"
#include "util/tc_common.h"
#include "util/tc_cgi.h"

namespace pccl
{


BaseApiResult::BaseApiResult()
{
	reset();
}



BaseApiResult::~BaseApiResult()
{
	
}

void BaseApiResult::reset()
{	
	_sequence.clear();
	tars::TC_HttpResponse::reset();
}

void BaseApiResult::setSequence(const std::string& sSeq)
{
	_sequence = sSeq;
}



void BaseApiResult::success( void)
{	
	Json::Value data;
	result(data,STATE_SUCCESS, "OK");
}

void BaseApiResult::success( const std::string& data )
{
	result(data);	
}


void BaseApiResult::success(Json::Value& data)
{	
	result(data,STATE_SUCCESS, "OK");
}

void BaseApiResult::error( void )
{
	error( BaseErrorCode::SERVER_ERROR );
}

void BaseApiResult::error(int code )
{
	error( code,"OTHER ERROR");
}


void BaseApiResult::error(int code,const std::string& msg )
{	
	Json::Value data;
	error(data,code,msg);
}

void BaseApiResult::error(Json::Value& data, int code,const std::string& msg)
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

void BaseApiResult::redirect(const std::string& sUrl)
{
	std::map<std::string,std::string> header;
	const std::vector<std::string>    cookie;
		
	header["Content-Type"]   = "text/html";
	header["Location"]       = tars::TC_Cgi::decodeURL(sUrl);
	
	redirect( header,cookie );
}


void BaseApiResult::redirect(const std::string& sUrl, const std::vector<std::string>& cookieHeader)
{
	
	std::map<std::string,std::string> header;
	header["Content-Type"]   = "text/html";
	header["Location"]       = tars::TC_Cgi::decodeURL(sUrl);
	
	redirect( header,cookieHeader );

}

void BaseApiResult::redirect(const std::map<std::string,std::string>& httpHeader,const std::vector<std::string>& cookie)
{
	result( httpHeader,cookie,302 ,"Found","" );
}




void BaseApiResult::forbid(const std::string& sMsg)
{	
	std::map<std::string,std::string> header;	
	Json::Value                       doc;
	std::string sRsp = serialize(doc,403,sMsg);	
	result( header,403, "Forbidden", sRsp );
}	


void BaseApiResult::result( const std::string& data)
{
	std::map<std::string,std::string> header;	

	header["Content-Type"]  = "application/json;charset=utf-8";		
	result(header, 200,  "OK", data );
}


void BaseApiResult::result( Json::Value& data)
{
	int code        = 0;
	std::string msg = "OK";
	result(data,code,msg);
}


void BaseApiResult::result( Json::Value& data, int code, const std::string& msg )
{	
	std::map<std::string,std::string> header;	

	header["Content-Type"]  = "application/json;charset=utf-8";	
	std::string sBody       = serialize(data,code,msg);
	
    result(header, 200,  "OK", sBody );
}





void BaseApiResult::result(const std::map<std::string,std::string>& httpHeader, int httpStutus, const std::string& about, const std::string& body   )
{
	std::vector<std::string> cookie;
	result(httpHeader,cookie,httpStutus,about,body);

}


void BaseApiResult::result(const std::map<std::string,std::string>& httpHeader,  const std::vector<std::string>& cookieHeader, int httpStutus, const std::string& about , const std::string& body	)
{
	// http header
	if ( httpHeader.empty() )
	{	
		this->setHeader("Content-Type","application/json;charset=utf-8");
	}
	else
	{
		for( auto it = httpHeader.begin(); it != httpHeader.end(); it++ )
		{
			this->setHeader(it->first, it->second);
		}
	}

	// http cookie
	for( auto it = cookieHeader.begin(); it != cookieHeader.end(); it++ )
	{
		this->setSetCookie(*it);
	}

	this->setResponse(httpStutus,about,body);
	
	//rsp.encode(outBuffer);

}


std::string BaseApiResult::serialize( Json::Value& data ,int code,const std::string& msg)
{

	Json::Value      root;
	
	root["code"]      = code;
	root["msg"]       = msg;
	root["data"]      = data;
	root["sequence"]  = _sequence;	
	
	Json::StreamWriterBuilder builder;
    std::string jsonBuf = Json::writeString(builder, root);

	return jsonBuf;

}


}

