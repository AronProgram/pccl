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



#include "BaseControllerParams.h"
#include "servant/Application.h"
#include "utils/PcclCommon.h"
#include "utils/Random.h"
#include "util/tc_epoll_server.h"
#include "util/tc_common.h"
#include <string>
#include <algorithm>



BaseControllerParams::BaseControllerParams(void) : 
_bodyType(BODY_NOTHING)
{
	
}


BaseControllerParams::~BaseControllerParams(void)
{

}


void BaseControllerParams::setBuffer(std::vector<char>* inBuffer, std::vector<char>* outBuffer)
{
	_inBuffer  = inBuffer;
	_outBuffer = outBuffer;
}


void BaseControllerParams::clean()
{
	_bodyType = BODY_NOTHING;	
	_sequence = "";
	_doc.clear();
	_account.clear();
	
	tars::TC_HttpRequest::reset();
	
}




int BaseControllerParams::initParse(void)
{		
	return  parse();
}



int BaseControllerParams::parse(void)
{
	int result = parseHttpPacket();
	if ( pccl::STATE_SUCCESS != result )
	{
		return pccl::STATE_ERROR;
	}

	result  = parseHttpBody();

	// 构建染色ID，用于日志的数据链条的追踪
	_sequence = Random::alpha(12);


	dumpParams();

	return result;
}

std::string& BaseControllerParams::getSequence(void)
{
	return _sequence;	
}


int BaseControllerParams::parseHttpPacket(void)
{	
	std::vector<char>& inBuffer = *_inBuffer;

	TLOGDEBUG("parse http packet:" << std::string( (const char*) &inBuffer[0], inBuffer.size() ) << "\n" );
	
	bool status = this->decode(  (const char*) &inBuffer[0] , inBuffer.size() );
	if ( !status )
	{	
		TLOGERROR( "parse http packet error" << std::endl );
		return pccl::STATE_ERROR;  
	}

	return pccl::STATE_SUCCESS;
	
}

int BaseControllerParams::parseHttpBody(void)
{	

	_doc.clear();

	std::string header = this->getHeader("Content-Type");

	if ( std::string::npos == header.find("application/json") ) 
	{
		TLOGINFO( "head is " << header << std::endl );
		return pccl::STATE_SUCCESS;
	}
	


	// 解析body: json
	std::string content = this->getContent();	
	
	Json::Reader reader;

	bool status = reader.parse(content,_doc);
	if ( status )
	{
		_bodyType = BODY_JSON;
	}
	else
	{
		_bodyType = BODY_QUERY;
	}	

	return pccl::STATE_SUCCESS;
	
}

std::string BaseControllerParams::getRemoteIp(void)
{	
	if ( !_httpURL.headerParams("X-real-ip").empty() )
	{
		return _httpURL.headerParams("X-real-ip");
	}
	else if ( !_httpURL.headerParams("X-Forwarded-For").empty() )
	{
		return _httpURL.headerParams("X-Forwarded-For");
	}
	else
	{
		return "127.0.0.1";
	}

}

void		BaseControllerParams::dumpParams(void)
{
	PARAMS&    headerParams = this->getQueryParams();

	
	TLOGDEBUG( "dumpParams, " << _sequence << ",header query string " << std::endl );
	for( auto it = headerParams.begin(); it != headerParams.end(); it++ )
	{
		TLOGDEBUG( "dumpParams, " << _sequence << ", key:" <<it->first << ",value:" << it->second << std::endl);
	}
	
	
	PARAMS&    bodyParams = this->getBodyParams();
	
	TLOGDEBUG( "dumpParams, " << _sequence << ",body params, bodytype :" << _bodyType << std::endl );
	for( auto it = bodyParams.begin(); it != bodyParams.end(); it++ )
	{
		TLOGDEBUG( "dumpParams, " << _sequence << ",key:" <<it->first << ",value:" << it->second << ",length:" << it->second.length() << std::endl);
	}

	TLOGDEBUG( "dumpParams, " << _sequence << ",body params json:" <<  Json::FastWriter().write(_doc) << std::endl );
	
}

void	BaseControllerParams::dumpAccount(void)
{
	TLOGDEBUG( "dumpAccount:" <<  std::endl );
	for( auto it = _account.begin(); it != _account.end(); it++ )
	{
		TLOGDEBUG( "account, key:" << it->first << ",value:" << it->second << ",length:" << it->second.length() << std::endl);
	}

}


