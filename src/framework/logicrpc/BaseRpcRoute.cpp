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



#include "BaseRpcRoute.h"
#include "BaseRpcPlus.h"

namespace pccl
{


BaseRpcRoute::BaseRpcRoute()
{


}

BaseRpcRoute::~BaseRpcRoute()
{

	
}


void BaseRpcRoute::bindGetRoute(const std::string& sUrl,CALLBACK_FUNC target,bool bAuthorize)
{
	bindRoute(sUrl,target,HTTP_REQUEST_GET,bAuthorize);
}

void BaseRpcRoute::bindPostRoute(const std::string& sUrl,CALLBACK_FUNC target,bool bAuthorize)
{
	bindRoute(sUrl,target,HTTP_REQUEST_POST,bAuthorize);
}  

void BaseRpcRoute::bindDeleteRoute(const std::string& sUrl,CALLBACK_FUNC target,bool bAuthorize)
{
	bindRoute(sUrl,target,HTTP_REQUEST_DELETE,bAuthorize);
} 


void BaseRpcRoute::bindRoute(const std::string& sUrl,CALLBACK_FUNC target,RpcRouteRquestType method,bool bAuthorize)
{

	if ( _route.count(sUrl) )
	{	
		return;
	}
	
	EXEC_PARAM exec;

	
	exec.method    = method;
	exec.authorize = bAuthorize;
	exec.call      = std::move(target);	
	_route[sUrl]   = exec;
}


bool BaseRpcRoute::hasAuth(const std::string& sRoute)
{
	if ( !_route.count(sRoute) )
	{	
		TLOGERROR("no route , url:" << sRoute << std::endl);
		return false;
	}

	EXEC_PARAM& exec = _route[sRoute];

	if ( exec.authorize )
	{
		TLOGDEBUG("the url is authorization, route:" << sRoute << std::endl);
		return true;
	}

	return false;

}


bool BaseRpcRoute::hasMethod(const std::string& sRoute)
{

	if ( !_route.count(sRoute) )
	{	
		TLOGERROR("no route , route:" << sRoute << std::endl);
		return false;
	}

	return true;
	
}


int  BaseRpcRoute::doRoute(const std::string& sRoute )
{	

	TLOGINFO("doRoute, exec route:" << sRoute << std::endl );

	EXEC_PARAM& exec = _route[sRoute];
	int result       = exec.call();	
	
	return result;
	
}


}


