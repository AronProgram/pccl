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
class BaseApiResult : public tars::TC_HttpResponse, public BaseErrorCode
{

public:		
	/**
	*
	*  构造函数
	*/
	BaseApiResult(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseApiResult();
	

public:

	/**
	*  重置
	* 
	*/
	void reset();

	void setSequence(const std::string& sSeq);
	

	/**
	*  返回成功的消息
	* 
	*/
	void success( void );	
	void success( const std::string& data );
	void success( Json::Value& data );


	/*
	*
	* 返回失败的消息
	*/
	void error( void );
	void error(int code );
	void error(int code,const std::string& msg );
	void error(Json::Value& data,int code,const std::string& msg);


	/*
	* 跳转
	*/
	void redirect(const std::string& sUrl); 
	void redirect(const std::string& sUrl, const std::vector<std::string>& cookieHeader);
	void redirect(const std::map<std::string,std::string>& httpHeader,const std::vector<std::string>& cookieHeader);

	/**
	*  鉴权错误
	*
	*/
	void forbid(const std::string& sMsg);


private:

	/**
	* 设置返回信息
	*
	*/
	void result( const std::string& data);
	void result( Json::Value& data);
	void result( Json::Value& data, int code, const std::string& msg);
	void result(const std::map<std::string,std::string>& httpHeader,  int httpStutus, const std::string& about , const std::string& body );
	void result(const std::map<std::string,std::string>& httpHeader,  const std::vector<std::string >& cookieHeader, int httpStutus, const std::string& about , const std::string& body );



	/** 
	*  json反序列化
	*
	*/
	std::string serialize(Json::Value& data ,int code,const std::string& msg);


protected:
	std::string   _sequence;
      
	
};



}

