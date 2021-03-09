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



namespace pccl
{

class BaseHttpRequestParams: public tars::TC_HttpRequest
{
		typedef std::map<std::string,std::string> PARAMS;
		
		enum BodyType
		{	
			HTTP_BODY_NOTHING,		
			HTTP_BODY_QUERY,
			HTTP_BODY_JSON,
			//todo ...

			//todo ...
			HTTP_BODY_MAX
		};


public:
	/**
	*
	*  构造函数
	*/
	BaseHttpRequestParams(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseHttpRequestParams(void);

	/**
	*
	*
	*/
	void setBuffer(std::vector<char>* inBuffer, std::vector<char>* outBuffer);

	std::vector<char>& getOutBuffer(void);

	/*
	*
	*  清空变量
	*
	*/
	virtual void reset();
	



	/*
	*  请求序列号,用于日志染色,追踪数据链条
	*/
	std::string& getSequence(void);

	/**
	*
	*  获取客户端IP
	*/
	std::string getRemoteIp(void);

  
	/*
	*
	*  获取http body json数据参数
	*/
	Json::Value&    getJsonParams (void)     { return _doc; }

	/**
	* 获取http请求的header/body的后面序列化后的参数列表,
	* 
	*/
	PARAMS&     		getParams(void) { return _params; };
	std::string&    	getParams(const std::string& sKey) { return _params[sKey]; }
	void                putParams(const std::string& sKey, const std::string& sValue );



protected:
	
	/*
	*
	*  解析报文
	*  @return  : 0:success, !0: error
	*/
	int parse(void);



private:
	void       split(const std::string& sQuery);
	void       dump(void);
	
	/*
	* 打印参数
	*/
	void 		dumpParams(void);

	
private:


		
	/**
	*	解析整个http报文
	*	@return  : success: OK, error: error
	*/
	int parseHttpPacket(void);

	/**
	*	http api query string 的后面序列化后的参数列表
	*/
	void parseQueryHeader(void);
	
	/*
	*  解析 http body
	*  @return  : success: OK, error: error
	*/
	int parseHttpBody(void);

	/*
	*  解析 http json body
	*  @return  : success: OK, error: error
	*/
	int parseJsonBody(void);
	
	/*
	*  解析 http query body
	*/
	void parseQueryBody(void);
	
protected:
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
	* body的格式：querystirng, json
	*/
	BodyType				_bodyType;   

	/*
	* http参数：
	* 1. http 协议header/body query string参数
	* 2. 鉴权用户信息的参数（ 鉴权权可以写入进来）
	*/
	PARAMS 					_params;

	
	/*
	* http报文解析后json
	*/
	Json::Value				_doc; 
	

};


}

