/**
 * PCCL is pleased to support the open source community by making Tars available.
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
#include "util/tc_http.h"
#include "BaseErrorCode.h"
#include <string>



namespace pccl
{



/**
 *
 *
 */
class BaseRpcResult            : public BaseErrorCode
{

public:		
	/**
	*
	*  构造函数
	*/
	BaseRpcResult(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseRpcResult();
	

public:

	/**
	*  重置
	* 
	*/
	void reset();

	void setSequence(const std::string& sSeq);

	void               setResponse(const std::string& sRsp);
	const std::string& getResponse();

	
	

	/**
	*  返回成功的消息
	* 
	*/
	void success( void );	
	void success( const std::string& data );
	void success( const Json::Value& data );

	
	/*
	*
	* 返回失败的消息
	*/
	void error( void );
	void error(int code );
	void error(int code,const std::string& msg );
	void error(const Json::Value& data,int code,const std::string& msg);

	/**
	* http result
	*/
	void http(Json::Value& data);
	void http(int code, const std::string& msg);
	void http( Json::Value& data, int code, const std::string& msg );



	/**
	*  鉴权错误
	*
	*/
	virtual void forbid(const std::string& sMsg);


private:

	/**
	* 设置返回信息
	*
	*/
	void result( const std::string& data);
	void result( const Json::Value& data);
	void result( const Json::Value& data, int code, const std::string& msg);	
	void result(const std::map<std::string,std::string>& httpHeader,  const std::vector<std::string>& cookieHeader, int httpStutus, const std::string& about , const std::string& body	);

	/** 
	*  json反序列化
	*
	*/
	void        serialize(const Json::Value& data ,int code,const std::string& msg);
	void        serialize(const std::string& data ,int code,const std::string& msg);
	std::string tostring(const Json::Value& data ,int code,const std::string& msg);
	std::string tostring(const std::string& data,int code,const std::string& msg);


protected:
	std::string   _sequence;
	std::string   _response;
      
	
};



}

