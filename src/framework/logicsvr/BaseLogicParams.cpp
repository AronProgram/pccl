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



#include "BaseLogicParams.h"
#include "BaseLogicPlus.h"
#include "util/tc_common.h"
#include <string>


BaseLogicParams::BaseLogicParams(void) 
{
	
}


BaseLogicParams::~BaseLogicParams(void)
{

}


void BaseLogicParams::setBuffer(std::vector<char>* inBuffer, std::vector<char>* outBuffer)
{
	_inBuffer  = inBuffer;
	_outBuffer = outBuffer;
}


void BaseLogicParams::clean()
{
	_packtes.Clear();
}


int BaseLogicParams::initParse(void)
{		
	return  parse();
}


int BaseLogicParams::parse(void)
{	
	std::vector<char>& inBuffer = *_inBuffer;
	
	bool status =_packtes.ParseFromArray( &(inBuffer[0]), inBuffer.size() );
	if ( !status )
	{	
		TLOGERROR("parse request packet error" << std::endl);
		return pccl::STATE_ERROR;
	}

	// debug
	dumpParams();
	
	return pccl::STATE_SUCCESS;
}

RequestPacketPb&   BaseLogicParams::getPackets(void)
{
	return _packtes;
}


const  std::string& BaseLogicParams::getSequence(void)
{
	return _packtes.sequence();	
}

int 		BaseLogicParams::getCmd(void)
{
	return _packtes.cmd();
}


int 		BaseLogicParams::getSubCmd(void)
{
	return _packtes.subcmd();
}

const std::string& BaseLogicParams::getBuffer(void)
{
	return _packtes.buffer();
}

#if 0
const std::map<std::string,std::string>& BaseLogicParams::getContext(void)
{
	return _packtes.context();
}

const std::map<std::string,std::string>& BaseLogicParams::getStatus(void)
{
	return _packtes.status();
}
#endif 


void 		BaseLogicParams::dumpParams(void)
{	
	std::string dump =  _packtes.DebugString();
	
	TLOGDEBUG("BaseLogicParams dumpParams:" << dump << std::endl);
}





