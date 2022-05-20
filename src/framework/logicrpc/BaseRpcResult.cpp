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



#include "BaseRpcResult.h"
#include "util/tc_common.h"
#include "util/tc_cgi.h"
#include "BaseRpcPlus.h"
#include <map>


namespace pccl
{


BaseRpcResult::BaseRpcResult()
{
	reset();
}



BaseRpcResult::~BaseRpcResult()
{
	
}

void BaseRpcResult::reset()
{	
	_sequence.clear();	
}

void BaseRpcResult::setSequence(const std::string& sSeq)
{
	_sequence = sSeq;
}

void	BaseRpcResult::setResponse(const std::string& sRsp)
{
	_response = sRsp;
}

const std::string&  BaseRpcResult::getResponse()
{
	return _response;
}




void BaseRpcResult::success( void)
{	
	Json::Value data;
	result(data,STATE_SUCCESS, "OK");
}

void BaseRpcResult::success( const std::string& data )
{
	result(data);	
}


void BaseRpcResult::success(const Json::Value& data)
{	
	result(data,STATE_SUCCESS, "OK");
}

void BaseRpcResult::error( void )
{
	error( BaseErrorCode::SERVER_ERROR );
}

void BaseRpcResult::error(int code )
{
	error( code,"OTHER ERROR");
}


void BaseRpcResult::error(int code,const std::string& msg )
{	
	Json::Value data;
	error(data,code,msg);
}

void BaseRpcResult::error(const Json::Value& data, int code,const std::string& msg)
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



void BaseRpcResult::result( const std::string& data)
{
	serialize(data, STATE_SUCCESS, "OK");	
}


void BaseRpcResult::result( const Json::Value& data)
{
	serialize(  data , STATE_SUCCESS, "OK");
}


void BaseRpcResult::result( const Json::Value& data, int code, const std::string& msg )
{	
	serialize(data,code,msg);	
}

void BaseRpcResult::http(Json::Value& data)
{	
	http(data,0,"OK");
}

void BaseRpcResult::http(int code, const std::string& msg)
{
	Json::Value data;
	http(data,code,msg);

}

void BaseRpcResult::http( Json::Value& data, int code, const std::string& msg )
{	
	std::map<std::string,std::string> header;
	std::vector<std::string>          cookie;

	header["Content-Type"]  = "application/json;charset=utf-8";	

	Json::Value root;
	root["code"]      = code;
	root["msg"]       = msg;
	root["data"]      = data;
	root["sequence"]  = _sequence;	

	Json::StreamWriterBuilder builder;
    std::string sBody = Json::writeString(builder, root);
	
    result(header, cookie, 200,  "OK", sBody );
}


void BaseRpcResult::result(const std::map<std::string,std::string>& httpHeader,  const std::vector<std::string>& cookieHeader, int httpStutus, const std::string& about , const std::string& body	)
{	
	tars::TC_HttpResponse response;

	// http header
	if ( httpHeader.empty() )
	{	
		response.setHeader("Content-Type","application/json;charset=utf-8");
	}
	else
	{
		for( auto it = httpHeader.begin(); it != httpHeader.end(); it++ )
		{
			response.setHeader(it->first, it->second);
		}
	}

	// http cookie
	for( auto it = cookieHeader.begin(); it != cookieHeader.end(); it++ )
	{
		response.setSetCookie(*it);
	}

	response.setResponse(httpStutus,about,body);

	_response = response.encode();

}


void BaseRpcResult::serialize( const Json::Value& data ,int code,const std::string& msg)
{
	Json::Value      root;
	
	root["code"]      = code;
	root["msg"]       = msg;
	root["data"]      = data;
	root["sequence"]  = _sequence;	
	
	Json::StreamWriterBuilder builder;
    _response = Json::writeString(builder, root);
}

void BaseRpcResult::serialize(const std::string& data ,int code,const std::string& msg)
{
	Json::Value      root;
	
	root["code"]      = code;
	root["msg"]       = msg;
	root["data"]      = data;
	root["sequence"]  = _sequence;	

	Json::StreamWriterBuilder builder;
    _response = Json::writeString(builder, root);	
	
}

std::string BaseRpcResult::tostring( const Json::Value& data ,int code,const std::string& msg)
{

	Json::Value      root;
	
	root["code"]      = code;
	root["msg"]       = msg;
	root["data"]      = data;
	root["sequence"]  = _sequence;		

	
	Json::StreamWriterBuilder builder;
    std::string  jsonBuf = Json::writeString(builder, root);	

	return jsonBuf;

}

std::string BaseRpcResult::tostring(const std::string& data,int code,const std::string& msg)
{

	Json::Value      root;
	
	root["code"]      = code;
	root["msg"]       = msg;
	root["data"]      = data;
	root["sequence"]  = _sequence;		

	
	Json::StreamWriterBuilder builder;
    std::string  jsonBuf = Json::writeString(builder, root);	

	return jsonBuf;

}


void BaseRpcResult::forbid(const std::string& sMsg)
{	
	std::map<std::string,std::string> header;	
	std::vector<std::string>          cookie;	
	Json::Value                       doc;
	std::string sRsp = tostring(doc,403,sMsg);	
	result( header,cookie , 403, "Forbidden", sRsp );
}	


}

