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

#include "BaseRpcRequestParams.h"
#include "util/tc_http.h"
#include "json.h"
#include "BaseRpcPlus.h"
#include "BaseRandom.h"
#include <algorithm>


namespace pccl
{

#if 0
BaseRpcRequestParams::BaseRpcRequestParams(void) 
{
	
}


BaseRpcRequestParams::~BaseRpcRequestParams(void)
{

}


void BaseRpcRequestParams::setBuffer(std::vector<char>* inBuffer, std::vector<char>* outBuffer)
{
	_inBuffer  = inBuffer;
	_outBuffer = outBuffer;
}



std::vector<char>& BaseRpcRequestParams::getOutBuffer(void)
{
	return *_outBuffer;
}


void BaseRpcRequestParams::reset()
{
	_sequence = "";
	_route    = "";
	_params.clear();	
	_doc.clear();	
	
}






int BaseRpcRequestParams::parse(void)
{
	// 构建染色ID，用于日志的数据链条的追踪
	_sequence = BaseRandom::alpha(12);

	
	int result = parseRpcPacket();
	if ( pccl::STATE_SUCCESS != result )
	{
		TLOGERROR("parse packet error" << "\n" );
		return pccl::STATE_ERROR;
	}	


 	dump();

	return result;
}

std::string& BaseRpcRequestParams::getSequence(void)
{
	return _sequence;	
}


int BaseRpcRequestParams::parseRpcPacket(void)
{	
	
	return pccl::STATE_SUCCESS;	
}

#if _XXX_
int BaseRpcRequestParams::parsetHttpPacket()
{
	// input data : std::vector<char>
	std::vector<char>& inBuffer = *_inBuffer;

	// http packet
	tars::TC_HttpRequest packet;
	
	bool status = packet.decode(  (const char*) &inBuffer[0] , inBuffer.size() );
	if ( !status )
	{
		TLOGERROR( "parse http packet error" << std::endl );
		return pccl::STATE_ERROR;  
	}
	
	
	// 路由
	_route = packet.getRequest();


	// content
	const std::string& content = packet.getContent();

	Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader( builder.newCharReader() );
	
	JSONCPP_STRING  err;
	status = reader->parse(content.c_str(), content.c_str() + content.length() , &_doc, &err);	
    if ( !status ) 
	{
		TLOGERROR("parse rpc  packet error:" << content << "\n" );
		return pccl::STATE_ERROR;
    }	

	return pccl::STATE_SUCCESS;

}


int BaseRpcRequestParams::parsetJsonPacket()
{
	// input data : std::vector<char>
	std::vector<char>& inBuffer = *_inBuffer;

	
	// 解析body: json
	std::string content( (const char*) &inBuffer[0], inBuffer.size()  );	

	TLOGDEBUG("parse rpc  packet:" << content << "\n" );


	Json::CharReaderBuilder builder;
	const std::unique_ptr<Json::CharReader> reader( builder.newCharReader() );
	
	JSONCPP_STRING	err;
	bool status = reader->parse(content.c_str(), content.c_str() + content.length() , &_doc, &err); 
	if ( !status ) 
	{
		TLOGERROR("parse rpc  packet error:" << content << "\n" );
		return pccl::STATE_ERROR;
	}	

	
	if ( !_doc.isMember("method")  || !_doc["method"].isString() )
	{
		TLOGERROR("not method" << content << "\n" );
		return pccl::STATE_ERROR;		
	}

	if ( !_doc.isMember("params") )
	{
		TLOGERROR("not params" << content << "\n" );
		return pccl::STATE_ERROR;		
	}
	
	_route = _doc["method"].asString();

	return pccl::STATE_SUCCESS;

	
}

#endif

const std::string& BaseRpcRequestParams::getRoute()
{
	return _route;
}




void	BaseRpcRequestParams::putParams(const std::string& sKey, const std::string& sValue )
{
	_params[ sKey ] =  sValue ;
}




void		BaseRpcRequestParams::dump(void)
{
	dumpParams();
}


void		BaseRpcRequestParams::dumpParams(void)
{		
	
	TLOGDEBUG( "dumpParams, " << _sequence << std::endl );
	for( auto it = _params.begin(); it != _params.end(); it++ )
	{
		TLOGDEBUG( "dumpParams, " << _sequence << ", key:" <<it->first << ",value:" << it->second << std::endl);
	}
	
	
}

#endif
}



