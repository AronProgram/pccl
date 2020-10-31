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



#include "BaseLogicRoute.h"
#include "fmt/format.h"
#include "BaseLogicPlus.h"



BaseLogicRoute::BaseLogicRoute()
{


}

BaseLogicRoute::~BaseLogicRoute()
{

	
}



void BaseLogicRoute::bindRoute(int cmd,int subcmd, CALLBACK_FUNC target)
{	
	std::string  route = getRouteId(cmd,subcmd);
	
	if ( _route.count(route) )
	{	
		return;
	}
	
	EXEC_PARAM exec;
	
	exec.cmd      = cmd;
	exec.scmd     = subcmd;
	exec.call     = std::move(target);	
	_route[route] = exec;
}


bool BaseLogicRoute::hasCmd(int cmd,int scmd)
{
	std::string  route = getRouteId(cmd,scmd);

	if ( !_route.count(route) )
	{	
		TLOGERROR("doRoute error, not route:" << route << std::endl);
		return false;
	}

	EXEC_PARAM& exec = _route[route];

	if ( cmd != exec.cmd || scmd != exec.scmd )
	{
		TLOGERROR("doRoute method error, exec route:" << route << std::endl);
		return false;
	}
	
	return true;
	
}


int  BaseLogicRoute::doRoute(int cmd,int scmd )
{	
	std::string  route = getRouteId(cmd,scmd);

	TLOGINFO("doRoute, exec route:" << route << std::endl);

	EXEC_PARAM& exec = _route[route];
	int result       = exec.call();	
	return result;
	
}


std::string BaseLogicRoute::getRouteId(int cmd,int scmd)
{
	std::string routeid = fmt::format("#{0}#{1}", cmd,scmd);
	return routeid;
}


