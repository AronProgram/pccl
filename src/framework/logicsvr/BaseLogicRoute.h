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
#include "json.h"
#include <map>
#include <string>

using namespace tars;



/**
 *
 *
 */
class BaseLogicRoute 
{

public:
	typedef std::function<int(void)> CALLBACK_FUNC;	
    

public:

	/**
	*
	*  构造函数
	*/
	BaseLogicRoute(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseLogicRoute();

	
public:
	/*
	* 
	*  绑定路由处理函数
	*
	*/	
	virtual void initRoute(void) = 0;
	
	/**
	* 绑定路由处理函数
	* @ cmd : 模块标识
	* @ scmd: 模块子命令
	* @ target 子模块处理函数
	*/
	void bindRoute(int cmd,int subcmd,CALLBACK_FUNC target) ;

	/**
	*
	* 处理路由
	*/
	int  doRoute(int cmd,int scmd);

	/**
	*
	*  判断模块处理命令是否一致
	*/
	bool hasCmd(int cmd,int scmd);


	/** 
	*	获取路由ID
	* @ cmd : 模块标识
	* @ scmd: 模块子命令
	*/	
	std::string getRouteId(int cmd,int scmd);


	/**
	*  设置路由完成
	*  @params: bool state , 状态
	*  @return: nothing
	*/
	void setFininsh(bool state = true);


	/**
	* 获取路由设置状态 
	*
	*/
	bool getFinish();

private:
	/*
	* 路由调用参数
	*/
	struct EXEC_PARAM
	{	
		/**
		* 模块标识
		*/
		int 			cmd;

		/*
		* 子模块命令
		*/
		int				scmd;

		/*
		* 回调函数
		*/
		CALLBACK_FUNC   call;
	};


	/*
	* 路由
	*/
	std::map<std::string,EXEC_PARAM >  _route;


	/**
	* 默认处理函数
	* 
	*/
	CALLBACK_FUNC                      _func;


	/*
	* 路由设置是否完成
	*/
	bool                _fininsh; 

};
