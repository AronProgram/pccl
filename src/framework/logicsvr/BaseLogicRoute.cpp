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

namespace pccl
{


std::string BaseLogicRoute::getRouteId(int cmd,int scmd)
{
	std::string routeid = fmt::format("#{0}#{1}", cmd,scmd);
	return routeid;
}



BaseLogicRoute::BaseLogicRoute()
{


}

BaseLogicRoute::~BaseLogicRoute()
{

	
}



void BaseLogicRoute::bindRoute(const std::string& sRouteId, CALLBACK_FUNC target)
{		
	if ( _route.count(sRouteId) )
	{	
		TLOGERROR("bindRoute error,routeid:" << sRouteId << std::endl);
		return;
	}
	
	EXEC_PARAM exec;	
	exec.route       = sRouteId;
	exec.call        = std::move(target);	
	
	_route[sRouteId] = exec;
}


bool BaseLogicRoute::hasRoute(const std::string& sRouteId)
{
	if ( !_route.count(sRouteId) )
	{	
		TLOGERROR("doRoute error, not route:" << sRouteId << std::endl);
		return false;
	}	
	
	return true;
	
}


int  BaseLogicRoute::doRoute(const std::string& sRouteId )
{	

	TLOGINFO("doRoute, exec route:" << sRouteId << std::endl);

	EXEC_PARAM& exec = _route[sRouteId];
	int result       = exec.call();	
	return result;
	
}



}

