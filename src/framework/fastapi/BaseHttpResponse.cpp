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



#include "BaseHttpResponse.h"
#include "BaseHttpPlus.h"
#include "util/tc_common.h"

namespace pccl
{


BaseHttpResponse::BaseHttpResponse():_result(pccl::STATE_SUCCESS)
{
	reset();
}



BaseHttpResponse::~BaseHttpResponse()
{
	
}

void BaseHttpResponse::reset()
{	
	_result    =  pccl::STATE_SUCCESS;
	_message.clear();
	_redirect.clear();
	_sequence.clear();
	_doc.clear();
}

void	BaseHttpResponse::setResult(int result)
{
	_result = result;
}
void	BaseHttpResponse::setErrMsg(const std::string& message, int result )
{	
	_message = message;
	_result  = result;
}
void	BaseHttpResponse::setErrMsg(const char* message, int result )
{
	_message = message;
	_result  = result;
}	

void   BaseHttpResponse::setSequence(const std::string& sequence)
{
	_sequence = sequence;
}

std::string 	BaseHttpResponse::getSeqMsg(void)
{
	std::string seqMsg = "sequence:" + _sequence;
	return seqMsg;
}


}

