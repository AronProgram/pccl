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
#include "BaseControllerRoute.h"
#include "BaseControllerProcess.h"

#include <map>
#include <string>

using namespace tars;



/**
 *
 *
 */
class BaseControllerParams : public tars::TC_HttpRequest  
{

public:
		typedef std::map<std::string,std::string> PARAMS;
		
		enum BodyType
		{	
			BODY_NOTHING,		
			BODY_QUERY,
			BODY_JSON,
			//todo ...

			//todo ...
			BODY_MAX
		};


public:
	/**
	*
	*  构造函数
	*/
	BaseControllerParams(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseControllerParams(void);

	/**
	*
	*
	*/
	void setBuffer(std::vector<char>* inBuffer, std::vector<char>* outBuffer);

	/*
	*
	*  清空变量
	*
	*/
	virtual void clean();
	

	/**
	*
	* 初始化
	*/
	int initParse(void);


	/*
	*  请求序列号,用于日志染色,追踪数据链条
	*/
	std::string& getSequence(void);

	/**
	*
	*  获取客户端IP
	*/
	std::string getRemoteIp(void);

    /**
     * @brief 获取http请求的url，不包括Host,
     *        例如http://www.qq.com/abc?a=b, 则为:/abc?a=b
     * @return http请求的url
     */
	std::string  getQueryString() { return this->getRequest(); }


	/**
     * @brief 获取http请求的url的后面序列化后的参数列表，不包括Host,
     *        例如http://www.qq.com/abc?a=b&c=d, 则为: map<a>=b,map<c>=d;
     * @return http请求的url
     */
	PARAMS&      getQueryParams(void) { return _httpURL.headerParams(); }
	std::string& getQueryParams(const std::string& sKey) { return _httpURL.headerParams(sKey); }
	

	/*
	*
	*  获取http body json数据参数
	*/
	Json::Value&    getBodyJsonParams (void)     { return _doc; }
	//std::string getBodyJsonParams(const std::string& sKey) { return _doc[StringRef(sKey.c_str(),sKey.length())]; }

	/**
	* 获取http请求的body的后面序列化后的参数列表,
	* 
	*/
	PARAMS&      getBodyParams(void) { return this->bodyParams(); };
	std::string& getBodyParams(const std::string& sKey) { return bodyParams(sKey); }

	/**
	* 获取鉴权用户信息
	*/
	std::map<std::string,std::string>& getAccount(void) { return _account; }
	std::string& getAccount(const std::string& sKey) { return _account[sKey]; }

	/*
	* 打印参数
	*/
	void 		dumpParams(void);


	void        dumpAccount(void);

private:


	/*
	*
	*  解析报文
	*  @return  : 0:success, !0: error
	*/
	int parse(void);
		
	/**
	*	解析整个http报文
	*	@return  : success: OK, error: error
	*/
	int parseHttpPacket(void);

	/*
	*  解析 http body
	*  @return  : success: OK, error: error
	*/
	int parseHttpBody(void);

	
protected:
	/*
	* body的格式：querystirng, json
	*/
	BodyType				_bodyType;   
	
	/*
	* http报文解析后json
	*/
	Json::Value				_doc; 
	
	/*
	* 输入buffer
	*/
	std::vector<char>*      _inBuffer;
	
	/*
	* 输出buffer
	*/
	std::vector<char>* 		_outBuffer;  


	/*
	* 序列号
	*/
	std::string             _sequence;

	/*
	* 鉴权用户信息
	*/
	std::map<std::string,std::string> _account;

};

