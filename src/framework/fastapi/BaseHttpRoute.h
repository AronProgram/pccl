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

namespace pccl
{


/**
 *
 *
 */
class BaseHttpRoute 
{

public:
	typedef std::function<int(void)> CALLBACK_FUNC;
	
    /**
     * @brief 请求协议类型,这里借鉴了tc_httpRequest的类型
     */
    enum HttpRquestType
    {
        HTTP_REQUEST_GET,
        HTTP_REQUEST_POST,
        HTTP_REQUEST_OPTIONS,
        HTTP_REQUEST_HEAD,
        HTTP_REQUEST_PUT,
        HTTP_REQUEST_DELETE,
        HTTP_REQUEST_PATCH,
    };

public:

	/**
	*
	*  构造函数
	*/
	BaseHttpRoute(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseHttpRoute();

	
public:
	/*
	* 
	*  绑定路由处理函数
	*
	*/	
	virtual void initRoute(void) = 0;
	
	/**
	* 绑定路由处理函数
	*
	*/
	void bindRoute(const std::string& sUrl,CALLBACK_FUNC target, int method = HTTP_REQUEST_GET,bool bAuthorize = false) ;

	/**
	* 绑定GET方法路由处理函数
	*
	*/	
	void bindGetRoute(const std::string& sUrl,CALLBACK_FUNC target,bool bAuthorize = false) ;

	/**
	* 绑定POST方法路由处理函数
	*
	*/
	void bindPostRoute(const std::string& sUrl,CALLBACK_FUNC target,bool bAuthorize = false) ;

	/**
	* 绑定DELETE方法路由处理函数
	*
	*/
	void bindDeleteRoute(const std::string& sUrl,CALLBACK_FUNC target,bool bAuthorize = false) ;

	/**
	*
	* 处理路由
	*/
	int  doRoute(const std::string& sUrl);

	
	/**
	*
	*  判断url是否需要授权
	*/
	bool hasAuth(const std::string& sUrl);

	/**
	*
	*  判断url的处方法与设置的是否一致
	*/
	bool hasMethod(const std::string& sUrl,int method);



private:
	/*
	* 路由调用参数
	*/
	struct EXEC_PARAM
	{	
		/**
		* REQUEST_GET,REQUEST_POST
		*  http 请求类型：get,post,option,delete,head
		*/
		int 			method;    

		/**
		* 授权
		*/
		bool            authorize;

		/*
		* 回调函数
		*/
		CALLBACK_FUNC   call;
	};


	/*
	* 路由
	*/
	std::map<std::string,EXEC_PARAM >  _route;
	

};


}

