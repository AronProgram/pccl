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


#include "BaseLogicApiController.h"
#include "BaseLogicApiHandler.h"
#include "BaseLogicPlus.h"



namespace pccl
{


BaseLogicApiController::BaseLogicApiController(void)
{	
	
}


BaseLogicApiController::~BaseLogicApiController()
{
	
}


void BaseLogicApiController::reset()
{
	BaseLogicController::reset();
}


void BaseLogicApiController::initRoute(void) 
{	
	//todo
	//详细使用，请参考example目录下面的UserApi
	//regiterRoute("/api/helloworld",  new BaseApiHandler(), 0, true );
}

void BaseLogicApiController::initErrorCode(void) 
{	

}

void   BaseLogicApiController::regiterRoute(int cmd, int subCmd, BaseLogicApiHandler* handler  )
{	
	std::string route = BaseLogicRoute::getRouteId(cmd,subCmd);
	this->bindRoute( route,  std::bind(&BaseLogicApiController::handle, this)  );
	_factory.bindRoute( route, handler );
}


int BaseLogicApiController::handle(void)
{

	int result = pccl::STATE_SUCCESS;

	//获取的api handler
	BaseLogicApiHandler* pHandler  = _factory.createHandler( this->getRoute() );
	

	//处理前准备
	pHandler->reset();
	pHandler->setBasePointer(this);
	pHandler->setSequence( this->getSequence() );

	//逻辑处理
	result = pHandler->doProcessApi();		
	
	return result;	
}



}



