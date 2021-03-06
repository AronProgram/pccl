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

#include "BaseHttpRequestParams.h"
#include "util/tc_epoll_server.h"
#include "util/tc_common.h"
#include "util/tc_cgi.h"
#include "json.h"
#include "BaseHttpPlus.h"
#include "BaseRandom.h"
#include <algorithm>


namespace pccl
{


BaseHttpRequestParams::BaseHttpRequestParams(void) : 
_bodyType(HTTP_BODY_NOTHING)
{
	
}


BaseHttpRequestParams::~BaseHttpRequestParams(void)
{

}


void BaseHttpRequestParams::setBuffer(std::vector<char>* inBuffer, std::vector<char>* outBuffer)
{
	_inBuffer  = inBuffer;
	_outBuffer = outBuffer;
}



std::vector<char>& BaseHttpRequestParams::getOutBuffer(void)
{
	return *_outBuffer;
}


void BaseHttpRequestParams::reset()
{
	_bodyType = HTTP_BODY_NOTHING;	
	_sequence.clear();
	_route.clear();
	_params.clear();	
	_doc.clear();	
	tars::TC_HttpRequest::reset();
	
}






int BaseHttpRequestParams::parse(void)
{
	int result = parseHttpPacket();
	if ( pccl::STATE_SUCCESS != result )
	{
		return pccl::STATE_ERROR;
	}

	result  = parseHttpBody();

	// 构建染色ID，用于日志的数据链条的追踪
	_sequence = BaseRandom::alpha(12);


	// 获取HTTP路由
	_route = this->getRequestUrl();

	dump();

	return result;
}

std::string& BaseHttpRequestParams::getSequence(void)
{
	return _sequence;	
}


int BaseHttpRequestParams::parseHttpPacket(void)
{	
	std::vector<char>& inBuffer = *_inBuffer;

	TLOGDEBUG("parse http packet:" << std::string( (const char*) &inBuffer[0], inBuffer.size() ) << "\n" );
	
	bool status = this->decode(  (const char*) &inBuffer[0] , inBuffer.size() );
	if ( !status )
	{	
		TLOGERROR( "parse http packet error" << std::endl );
		return pccl::STATE_ERROR;  
	}

	//解析http query stirng 的参数
	parseQueryHeader();
	

	return pccl::STATE_SUCCESS;
	
}

int BaseHttpRequestParams::parseHttpBody(void)
{	

	_doc.clear();

	std::string header = this->getHeader("Content-Type");

	if ( header.find("application/json") ) 
	{
		parseJsonBody();
		return pccl::STATE_SUCCESS;
	}	
	
	parseQueryBody();

	return pccl::STATE_SUCCESS;
}


int BaseHttpRequestParams::parseJsonBody(void)
{
	// 解析body: json
	std::string content = this->getContent();	

	Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader( builder.newCharReader() );
	
	JSONCPP_STRING  err;
	bool status = reader->parse(content.c_str(), content.c_str() + content.length() , &_doc, &err);	
    if ( status ) 
	{
     	_bodyType = HTTP_BODY_JSON;
    }	

	return pccl::STATE_SUCCESS;
	
}


void BaseHttpRequestParams::parseQueryHeader(void)
{
	std::string request = getRequest();
		
	split(request);	

	_bodyType = HTTP_BODY_QUERY;
}

void BaseHttpRequestParams::parseQueryBody(void)
{
	std::string content = this->getContent();	

	split(content);		
}


void    BaseHttpRequestParams::split(const std::string& sQuery)
{

	std::vector<std::string> query = tars::TC_Common::sepstr<std::string>(sQuery,"&");
	
	for( std::size_t i = 0; i < query.size(); i++ )
	{	
		{
			std::vector<std::string> params;

			params.clear();
			
			params = tars::TC_Common::sepstr<std::string>(query[i],"=",true);
			if ( 2 == params.size() )
			{
				_params[ params[0] ] = tars::TC_Cgi::decodeURL(params[1]);
			}
		}
	}

}


const std::string& BaseHttpRequestParams::getRoute()
{
	return _route;
}




void	BaseHttpRequestParams::putParams(const std::string& sKey, const std::string& sValue )
{
	_params[ sKey ] =  sValue ;
}



std::string BaseHttpRequestParams::getRemoteIp(void)
{	
	//const http_header_type& header =  getHeaders();

	if ( !this->getHeader("X-real-ip").empty() )
	{
		return this->getHeader("X-real-ip");
	}
	else if ( !this->getHeader("X-Forwarded-For").empty() )
	{
		return this->getHeader("X-Forwarded-For");
	}
	else
	{
		return "127.0.0.1";
	}

}


void		BaseHttpRequestParams::dump(void)
{
	dumpParams();
}


void		BaseHttpRequestParams::dumpParams(void)
{		
	
	TLOGDEBUG( "dumpParams, " << _sequence << std::endl );
	for( auto it = _params.begin(); it != _params.end(); it++ )
	{
		TLOGDEBUG( "dumpParams, " << _sequence << ", key:" <<it->first << ",value:" << it->second << std::endl);
	}
	
	
}


}



