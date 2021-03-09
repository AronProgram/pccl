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



#include "BaseHttpController.h"
#include "BaseHttpPlus.h"
#include "util/tc_common.h"
#include "util/tc_cgi.h"
#include <string>


namespace pccl
{


BaseHttpController::BaseHttpController(void) 
{
	initialization();
}


BaseHttpController::~BaseHttpController()
{

}



tars::TC_NetWorkBuffer::PACKET_TYPE BaseHttpController::checkHttpPacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out)
{
	return in.parseHttp(in,out);
}



void BaseHttpController::reset()
{
	BaseHttpRequestParams::reset();	
}


void BaseHttpController::initialization(void)
{	
	initRoute();	
}


int BaseHttpController::doProcess(void)
{
	int result = pccl::STATE_SUCCESS;

	
	TLOGDEBUG( "doProcessParse" << std::endl );
	
	// 初始化
	result = doProcessParse();
	if ( pccl::STATE_ERROR == result )
	{	
		this->error(BaseErrorCode::PARSE_ERROR);
		return pccl::STATE_SUCCESS;
	}	

	TLOGDEBUG( "doProcessRoute" << std::endl );

	//todo
	//限制策略: 频率，ip,黑名单

	// 处理路由
	result = doProcessRoute();
	
	TLOGDEBUG( "doProcess finish, result:" << result << std::endl );

	return result;
	
}


int BaseHttpController::doProcessParse(void)
{
	return  parse();
}


int BaseHttpController::doProcessRoute(void)
{

	// 调用处理过程
	int result       = pccl::STATE_SUCCESS;
	std::string sUrl = this->getRequestUrl();
	int method       = this->requestType();
	
	TLOGDEBUG("doProcess , sequence:" <<  this->getSequence() << ",method: " <<  method << ",url:" << sUrl  << std::endl);

	// 处理option/head命令
	if ( this->isOPTIONS() || this->isHEAD() )
	{
		this->success();
		return pccl::STATE_SUCCESS;
	}

	//处理url:是否登录，授权	
	if (  this->hasAuth(sUrl) )
	{		
		TLOGDEBUG( "authorize url:" << sUrl << std::endl);

		result = this->doProcessAuth();
		if ( pccl::STATE_SUCCESS != result )
		{
			this->forbid("AUTH ERROR");	
			return pccl::STATE_ERROR;
		}
	}

	
	TLOGDEBUG( "hasMethod, url: " << sUrl << std::endl);

	//处理业务逻辑
	if (  !this->hasMethod(sUrl,method) )
	{
		this->error(ROUTER_ERROR);		
		return pccl::STATE_ERROR;
	}

	
	result = this->doRoute(sUrl);	
	

	return result;	
	
}



int BaseHttpController::doProcessAuth(void)
{

	return pccl::STATE_SUCCESS;
}




}


