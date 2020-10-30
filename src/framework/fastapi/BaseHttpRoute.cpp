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



#include "BaseHttpRoute.h"
#include "BaseHttpPlus.h"

namespace pccl
{


BaseHttpRoute::BaseHttpRoute():_fininsh(false)
{


}

BaseHttpRoute::~BaseHttpRoute()
{

	
}

void BaseHttpRoute::bindGetRoute(const std::string& sUrl,CALLBACK_FUNC target,bool bAuthorize)
{
	bindRoute(sUrl,target,HTTP_REQUEST_GET,bAuthorize);
}

void BaseHttpRoute::bindPostRoute(const std::string& sUrl,CALLBACK_FUNC target,bool bAuthorize)
{
	bindRoute(sUrl,target,HTTP_REQUEST_POST,bAuthorize);
}  

void BaseHttpRoute::bindDeleteRoute(const std::string& sUrl,CALLBACK_FUNC target,bool bAuthorize)
{
	bindRoute(sUrl,target,HTTP_REQUEST_DELETE,bAuthorize);
} 


void BaseHttpRoute::bindRoute(const std::string& sUrl,CALLBACK_FUNC target,int method,bool bAuthorize)
{

	if ( _route.count(sUrl) )
	{	
		return;
	}
	
	EXEC_PARAM exec;
	
	exec.method    = method;
	exec.authorize = bAuthorize;
	exec.call      = std::move(target);	
	_route[sUrl] = exec;
}


bool BaseHttpRoute::hasAuth(const std::string& sUrl)
{
	if ( !_route.count(sUrl) )
	{	
		TLOGERROR("no route , url:" << sUrl << std::endl);
		return false;
	}

	EXEC_PARAM& exec = _route[sUrl];

	if ( exec.authorize )
	{
		TLOGDEBUG("the url is authorization, url:" << sUrl << std::endl);
		return true;
	}

	return false;

}


bool BaseHttpRoute::hasMethod(const std::string& sUrl,int method)
{

	if ( !_route.count(sUrl) )
	{	
		TLOGERROR("no route , url:" << sUrl << std::endl);
		return false;
	}

	EXEC_PARAM& exec = _route[sUrl];

	if ( method != exec.method )
	{
		TLOGERROR("doRoute method error, exec method:" << exec.method << std::endl);
		return false;
	}
	
	return true;
	
}


int  BaseHttpRoute::doRoute(const std::string& sUrl )
{	

	TLOGINFO("doRoute, exec url:" << sUrl << std::endl);

	EXEC_PARAM& exec = _route[sUrl];
	int result = exec.call();	
	return result;
	
}


void BaseHttpRoute::setFininsh(bool state )
{
	_fininsh = state;
}

bool BaseHttpRoute::getFinish()
{
	return _fininsh;
}


}


