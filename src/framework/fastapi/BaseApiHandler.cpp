/**
 * Minzea is pleased to support the open source community by making Tars available.
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


#include "BaseApiHandler.h"
#include "BaseHttpPlus.h"


namespace pccl
{



BaseApiHandler::BaseApiHandler(void) :        _pBase(NULL)
{

}


BaseApiHandler::~BaseApiHandler(void)
{

}

void BaseApiHandler::reset() 
{ 
	_pBase = NULL;
	BaseHttpResponse::reset();
}


void  BaseApiHandler::setBasePointer(BaseHttpController* pBase)
{
	_pBase =  pBase;
}


BaseHttpController&  BaseApiHandler::getBasePointerRef()
{
	return *_pBase;
}
	



int BaseApiHandler::doProcessApi(void)
{
	int result = pccl::STATE_SUCCESS;

	result = doCheckParams();
	if ( pccl::STATE_SUCCESS != result )
	{
		return pccl::STATE_ERROR;
	}
	
	result = doProcessWork();
	if ( pccl::STATE_SUCCESS != result )
	{
		return pccl::STATE_ERROR;
	}


	return result;
	
	
}

int BaseApiHandler::doCheckParams(void)
{

	return pccl::STATE_SUCCESS;	
	
}

int BaseApiHandler::doProcessWork(void)
{

	return pccl::STATE_SUCCESS;	
	
}



}

