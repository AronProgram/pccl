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




BaseLogicController::BaseLogicController(void) 
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

tars::TC_NetWorkBuffer::PACKET_TYPE BaseLogicController::checkIgnorePacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out)
{
	return tars::TC_NetWorkBuffer::PACKET_ERR;
}



void BaseLogicController::clean()
{
	BaseLogicParams::clean();	
}


int BaseLogicController::initialization(void)
{	
	//设置路由
	
	
	initRoute();		
	
	
	//解析
	int result = initParse();
	
	return result;
}

void BaseLogicController::toJson(Json::Value& data, const std::string& msg, int result )
{

	std::vector<char>&       outBuffer = *_outBuffer;
	Json::Value              doc;
	
	doc["code"]     = result;
	doc["msg"]       = msg;
	doc["data"]      = data;
	doc["sequence"]  = getSequence();	
	
	std::string buffer = Json::FastWriter().write(doc);
	outBuffer.resize( buffer.length() );
    memcpy(&outBuffer[0], buffer.c_str(), buffer.length());

}

void BaseLogicController::toJsonSuccess(void)
{	
	Json::Value doc;
	toJson(doc);
}
void BaseLogicController::toJsonError(void)
{
	Json::Value doc;
	toJson(doc,"error",100);
}

void BaseLogicController::toBin(const std::string& data, int result )
{
	std::string msg = "success";

	if ( result != 0 )
	{
		msg = "error";
	}

	toBin(data,msg, result);
}

void BaseLogicController::toBin(const std::string& data, const std::string& msg, int result   )
{
	ResponsePacketPb   packet;	
	std::vector<char>& outBuffer = *_outBuffer;
	
	packet.set_version(PacketVersion::V1_VERSION);	
	packet.set_result(result);
	packet.set_msg(msg);
	packet.set_sequence(this->getSequence());
	packet.set_buffer(data);

	std::string buffer =  packet.SerializeAsString();
	outBuffer.resize( buffer.length() );
    memcpy(&outBuffer[0], buffer.c_str(), buffer.length());

	
	TLOGDEBUG("response result:" << result << ",msg:" << msg <<",size:" << buffer.length() << std::endl );
}



void BaseLogicController::toBinSuccess(void)
{
	toBin("");
}

void BaseLogicController::toBinError(void  )
{
	toBin("","error",100);
}


void BaseLogicController::toStr(Json::Value& data, const std::string& msg, int result )
{
	std::string        str       = doc2Str(data);
	toBin(str,msg,result);
}


void BaseLogicController::success(const std::string& data)
{
	toBin(data,"success",0);
}
void BaseLogicController::error(const std::string& msg,int result )
{
	std::string data;
	toBin(data,msg,result);
}

std::string BaseLogicController::doc2Str(Json::Value& data)
{	
	return Json::FastWriter().write(data);
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
	if ( pccl::STATE_ERROR == result )
	{	
		return pccl::STATE_SUCCESS;
	}

	return result;
	
}


int BaseLogicController::doProcessInit(void)
{
	// 初始化
	int result = initialization();
	if ( pccl::STATE_SUCCESS != result )
	{	
		//todo 
		this->error("params error");
		return pccl::STATE_ERROR;
	}	

	// todo

	return pccl::STATE_SUCCESS;
}


int BaseLogicController::doProcessRoute(void)
{

	// 调用处理过程
	int cmd    = this->getCmd();
	int subcmd = this->getSubCmd();
	
	TLOGDEBUG("doProcess , sequence:" <<  this->getSequence() << ",cmd:" <<  cmd << ",subcmd:" << subcmd  << std::endl);
	
		
	if (  !this->hasCmd(cmd,subcmd) )
	{
		this->error("method error");		
		return pccl::STATE_ERROR;
	}

	//todo 
	//处理url:是否登录，授权	

	
	// 回调函数
	int result = this->doRoute(cmd,subcmd);
	if ( pccl::STATE_SUCCESS != result )
	{
		this->error("params error");		
		return pccl::STATE_ERROR;
	}

	return pccl::STATE_SUCCESS;	
	
}






