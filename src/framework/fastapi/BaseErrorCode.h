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

#include "json.h"
#include <map>
#include <string>
#include <vector>



namespace pccl
{



/**
 *
 *
 */
class BaseErrorCode 
{

public:
	typedef enum _ErrCode_
	{
		SUCCESS                 = 0,		
		METHOD_ERROR			= 100,
		ROUTER_ERROR			= 101,
		PARSE_ERROR		        = 102,
		PARAMS_ERROR            = 110,		
		AUTHOR_ERROR            = 403,
		
		ERROR_MAX
			
	}ErrorCode;

public:
	
	/**
	*
	*  构造函数
	*/
	BaseErrorCode(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseErrorCode();

	/*
	*
	*  清空变量
	*
	*/
	virtual void 	reset();

	/**
	*  获取错误
	*  @params: int code , 错误码
	*  @return: string
	**/
	const std::string& getError(int code );

	
	/**
	*  增加错误码和错误内容
	*  @params: int    code , 错误码
	*  @params: string msg  , 错误内容
	*  @return: 
	**/
	void            addError(int code, const std::string& msg);

	/**
	*  检查错误码
	*  @params: int code , 错误
	*  @return: true,false
	**/
	bool            isError(int code);

private:	
	void	    	initError();

private:
	std::map<int,std::string> _error;
	std::string               _empty;
		


};


}


