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


#include "BaseHttpApiController.h"
#include "BaseApiHandler.h"
#include "BaseHttpPlus.h"



namespace pccl
{


BaseHttpApiController::BaseHttpApiController()
{
	
}


BaseHttpApiController::~BaseHttpApiController()
{
	
}


void BaseHttpApiController::reset()
{
	BaseHttpController::reset();
}


void BaseHttpApiController::initRoute(void)
{	
	regiterRoute("/api/helloworld",  new BaseApiHandler(), 0, true );
}


void   BaseHttpApiController::regiterRoute(const std::string& sApi,     BaseApiHandler* handler, int method, bool isAuth )
{
	this->bindRoute( sApi,  std::bind(&BaseHttpApiController::entrance, this), method , isAuth );
	_factory.bindRoute( sApi, handler );
}


int BaseHttpApiController::entrance(void)
{

	int result = pccl::STATE_SUCCESS;

	//获取的api handler
	std::string          reqUrl    =  this->getRequestUrl();
	BaseApiHandler*      pHandler  = _factory.createHandler(reqUrl);

	//处理前准备
	pHandler->reset();
	pHandler->setBasePointer(this);
	pHandler->setSequence( this->getSequence() );

	//逻辑处理
	result = pHandler->doProcessApi();	
	if ( pccl::STATE_SUCCESS != result )
	{	
		this->error(  pHandler->getResult(), pHandler->getErrMsg() );
		return pccl::STATE_SUCCESS;
	}

	// 是否有302跳转
	if ( pHandler->hasRedirect() )
	{
		this->redirect(  pHandler->getRedirect() );
		return pccl::STATE_SUCCESS;
	}
	
	// 返回数据
	this->success( pHandler->getDoc() );
	
	return pccl::STATE_SUCCESS;	
}



}



