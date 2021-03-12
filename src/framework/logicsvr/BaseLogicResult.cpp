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



#include "BaseLogicResult.h"
#include "BaseLogicPlus.h"
#include "BaseLogicError.h"
#include "Packet.pb.h"
#include "util/tc_common.h"
#include "util/tc_cgi.h"

namespace pccl
{


BaseLogicResult::BaseLogicResult()
{
	reset();
}



BaseLogicResult::~BaseLogicResult()
{
	
}

void BaseLogicResult::reset()
{	
	_sequence.clear();
	_serialize.clear();
}

void BaseLogicResult::setSequence(const std::string& sSeq)
{
	_sequence = sSeq;
}



void BaseLogicResult::success( void )
{	
	success( "" );
}

void BaseLogicResult::success( const std::string& data )
{
	result( 0, "OK", data );	
}

void BaseLogicResult::error( void )
{
	error( BaseLogicError::SERVER_ERROR );
}

void BaseLogicResult::error(int code )
{
	error( code,"OTHER ERROR");
}


void BaseLogicResult::error(int code,const std::string& msg )
{	
	error(code,msg,"");
}

void BaseLogicResult::error(int code , const std::string& msg, const std::string& data)
{	
	if ( this->isError(code) )
	{
		result( code,this->getError(code), data );
	}
	else
	{
		result( code,msg,data );
	}	
}



void BaseLogicResult::result( int code , const std::string& msg, const std::string& data  )
{
	ResponsePacketPb   packet;	
	
	packet.set_version(PacketVersion::V1_VERSION);	
	packet.set_result(code);
	packet.set_msg(msg);
	packet.set_sequence( _sequence );
	packet.set_buffer(data);

	_serialize  =  packet.SerializeAsString();	
}
	

}

