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

#include "util/tc_http.h"
#include "util/tc_network_buffer.h"
#include "json.h"
#include "BaseControllerRoute.h"
#include "BaseControllerProcess.h"
#include "BaseControllerParams.h"


#include <map>
#include <string>
#include <vector>

using namespace tars;




/**
 *
 *
 */
class BaseControllerError  
{

public:
	typedef enum _ErrCode_
	{
		SUCCESS                 = 0,		
		METHOD_ERROR			= 100,
		ROUTER_ERROR			= 101,
		PARAMS_ERROR            = 110,		
		AUTHOR_ERROR            = 403,
		
		ERROR_MAX
			
	}ErrorCode;

public:
	
	/**
	*
	*  构造函数
	*/
	BaseControllerError(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseControllerError();

	/*
	*
	*  清空变量
	*
	*/
	virtual void 	reset();

	const std::string& getError(int code );

	virtual void	initError();

	void            addError(int code, const std::string& msg);
	bool            isError(int code);

private:
	std::map<int,std::string> _error;
	std::string               _empty;
		


};

