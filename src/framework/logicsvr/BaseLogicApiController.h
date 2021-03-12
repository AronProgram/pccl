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


#include "BaseLogicController.h"
#include "BaseLogicRouteFactory.h"
#include "BaseLogicApiHandler.h"
#include <string>
#include <memory>



namespace pccl
{


class BaseLogicApiController : public BaseLogicController
{


public:
	
	
	/**
	*
	*  构造函数
	*/
	BaseLogicApiController(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseLogicApiController();

	/**
	*
	* 清空环境
	*/
	virtual void reset();	


protected:
	/**
	*
	* 初始化路由，统一处理处接口
	*/ 
	virtual void initRoute(void) override;

	/**
	*
	* 初始化错误码
	*/	
	virtual void initErrorCode(void);

	
	/**
	*	注册api handler 函数
	*  @parmams: sApi ，API名称
	*  @params:  httpMethod, POST,GET,DELETE
	*  @params:  handler,  BaseBpiHandler 
	*  @params:  isAuth,   是否要鉴权
	*
	*/
	void	   regiterRoute(int cmd, int subCmd, BaseLogicApiHandler* handler  );

	
	/**
	*  http协议路由处理总入口
	*/
	int 		handle(void);
	


private:
	/*
	* api handler 工厂
	*/
	RegisterRouteHandlerFactory 	_factory;

	
	
};


}



