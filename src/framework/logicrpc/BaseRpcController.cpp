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



#include "BaseRpcController.h"
#include "BaseRpcPlus.h"
#include "util/tc_common.h"
#include "util/tc_cgi.h"
#include <string>


namespace pccl
{


#if 0
BaseRpcController::BaseRpcController(void) : _status(false)
{
	
}


BaseRpcController::~BaseRpcController()
{
	
}



tars::TC_NetWorkBuffer::PACKET_TYPE BaseRpcController::checkRpcPacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out)
{
	return tars::TC_NetWorkBuffer::PACKET_FULL;
}

tars::TC_NetWorkBuffer::PACKET_TYPE BaseRpcController::ignoreRpcPacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out)
{
	return tars::TC_NetWorkBuffer::PACKET_ERR;	
}


void BaseRpcController::reset()
{
	BaseRpcRequestParams::reset();	
}


void BaseRpcController::initialization(void)
{	
	initErrorCode();
	
	initRoute();	
	
}


int BaseRpcController::doProcess(void)
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


int BaseRpcController::doProcessParse(void)
{
	if ( !this->_status )
	{
		initialization();
		
		this->_status = true;
	}

	return  parse();
}


int BaseRpcController::doProcessRoute(void)
{

	// 调用处理过程
	int                result   = pccl::STATE_SUCCESS;
	
	const std::string& sRoute   = this->getRoute();
	
	TLOGDEBUG("doProcess , sequence:" <<  this->getSequence() <<  ",route:" << sRoute  << std::endl);		
		
	//处理url:是否登录，授权	
	if (  this->hasAuth(sRoute) )
	{		
		TLOGDEBUG( "authorize route:" << sRoute << std::endl);

		result = this->doProcessAuth();
		if ( pccl::STATE_SUCCESS != result )
		{
			this->forbid("AUTH ERROR"); 
			return pccl::STATE_ERROR;
		}
	}
	

	//路由存在
	if (  !this->hasMethod(sRoute) )
	{
		this->error(ROUTER_ERROR);		
		return pccl::STATE_ERROR;
	}

	//处理业务逻辑
	return this->doRoute(sRoute);		

	
}


int BaseRpcController::doProcessAuth(void)
{
	
	return pccl::STATE_SUCCESS;
}
#endif


}


