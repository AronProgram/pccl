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



#include "BaseLogicController.h"
#include "BaseLogicPlus.h"
#include "util/tc_common.h"
#include "Packet.pb.h"
#include <string>


namespace pccl
{


BaseLogicController::BaseLogicController(void):_status(false)
{
	
}


BaseLogicController::~BaseLogicController()
{


}



tars::TC_NetWorkBuffer::PACKET_TYPE BaseLogicController::checkPacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out)
{

	RequestPacketPb packet;

	std::string  content = in.getBuffersString();

	bool status = packet.ParseFromString(content);
	if ( !status )
	{	
		TLOGERROR("checkPacket the packet check error" << std::endl);
		return tars::TC_NetWorkBuffer::PACKET_LESS;
	}

	if ( PacketVersion::V1_VERSION != packet.version() 
		//|| packet.sequence().empty() 
		)
	{
		TLOGERROR("checkPacket  error,version:" << packet.version()  << std::endl);
		return tars::TC_NetWorkBuffer::PACKET_LESS;
	}
	
	// 两步必须不能少
    out = in.getBuffers();
    in.clearBuffers();
	
	TLOGDEBUG("checkPacket success,cmd:" << packet.cmd() << ",subcmd:" << packet.subcmd() << std::endl);
	
	return tars::TC_NetWorkBuffer::PACKET_FULL;

}

tars::TC_NetWorkBuffer::PACKET_TYPE BaseLogicController::ignorePacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out)
{
	return tars::TC_NetWorkBuffer::PACKET_ERR;
}



void BaseLogicController::reset()
{
	BaseLogicParams::reset();	
}


int BaseLogicController::initialization(void)
{	
	//初始化路由
	if ( !this->_status ) 
	{
		initRoute();			
		this->_status = true;
	}	 
	
	
	//解析
	int result = parse();
	
	return result;
}


int BaseLogicController::doProcess(void)
{
	int result = pccl::STATE_SUCCESS;
	
	// 初始化
	result = doProcessInit();
	if ( pccl::STATE_ERROR == result )
	{	
		return pccl::STATE_SUCCESS;
	}	

	//todo
	//限制策略: 频率，ip,黑名单
	

	// 处理路由
	result = doProcessRoute();	

	return result;
	
}


int BaseLogicController::doProcessInit(void)
{
	// 初始化
	int result = initialization();
	if ( pccl::STATE_SUCCESS != result )
	{	
		this->error ( BaseLogicError::PARSE_ERROR );
		return pccl::STATE_ERROR;
	}	

	// todo

	return pccl::STATE_SUCCESS;
}


int BaseLogicController::doProcessRoute(void)
{	

	std::string route = BaseLogicRoute::getRouteId( this->getCmd(), this->getSubCmd() );
	
	TLOGDEBUG("doProcess , sequence:" <<  this->getSequence() << ",route:" <<  route  << std::endl );
		
	if (  !this->hasRoute( route ) )
	{
		this->error( BaseLogicError::ROUTER_ERROR );		
		return pccl::STATE_ERROR;
	}

	//todo 
	//处理url:是否登录，授权	

	
	// 回调函数
	int result = this->doRoute(route);
	
	
	return result;	
	
}


}



