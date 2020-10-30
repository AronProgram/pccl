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


#include "BaseHttpController.h"
#include "BaseHttpRouteFactory.h"
#include "BaseApiHandler.h"
#include <string>
#include <memory>



namespace pccl
{


class BaseHttpApiController : public BaseHttpController
{


public:
	
	
	/**
	*
	*  构造函数
	*/
	BaseHttpApiController();
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseHttpApiController();

	/**
	*
	* 清空环境
	*/
	virtual void reset();
	

	/**
	*
	* 初始化路由，统一处理处接口
	*/ 
	virtual void initRoute(void);



protected:	

	/**
	*
	* 统一错误码
	*/	
	virtual void initErrorCode(void);

	
	/**
	*  处理入口
	*/
	virtual int entrance(void);
	

private:
	/**
	*   注册api handler 函数
	*  @parmams: sApi ，API名称
	*  @params:  httpMethod, POST,GET,DELETE
	*  @params:  handler,  BaseBpiHandler 
	*  @params:  isAuth,   是否要鉴权
	*
	*/
	void    regiterRoute(const std::string& sApi,BaseApiHandler* handler, int      method,  bool isAuth = false );

private:
	/*
	* api handler 工厂
	*/
	RegisterRouteHandlerFactory 	_factory;

	
	
};


}



