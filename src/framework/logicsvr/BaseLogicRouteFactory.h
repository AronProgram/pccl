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

#pragma once

#include "BaseLogicApiHandler.h"
#include <string>
#include <map>
#include <memory>


namespace pccl
{




class BaseLogicRouteFactory
{

public:
	BaseLogicRouteFactory() 
	{ 	
		
	}
	
	~BaseLogicRouteFactory()
	{
		
	}

public:
	BaseLogicApiHandler* createHandler(const   std::string& api)
	{	
		if ( _contain.count(api) > 0 )
		{
			return _contain[api].get();
		}

		return NULL;
		
	}
	

protected:
	std::map<std::string,std::unique_ptr<BaseLogicApiHandler> > _contain;	
	
};



class RegisterRouteHandlerFactory : public BaseLogicRouteFactory
{

public:
	RegisterRouteHandlerFactory() 	
	{ 
		
	}
	
	~RegisterRouteHandlerFactory() 
	{
		
	}


public:
	
	void addApiHandle( const std::string& route, BaseLogicApiHandler* handler)
	{	
		std::unique_ptr<BaseLogicApiHandler> ptr(handler); 
		_contain[route]   = std::move(ptr) ;
	}
	
};




}


