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
#include "BaseErrorCode.h"
#include "BaseHttpRequestParams.h"
#include "BaseHttpRoute.h"
#include "BaseHttpProcess.h"
#include <map>
#include <string>
#include <vector>


using namespace tars;


namespace pccl
{



class BaseHttpController : public BaseHttpProcess, public BaseHttpRoute, public BaseHttpRequestParams, public BaseErrorCode
{

public:
	/**
	* parse http packet
	* @param in
	* @param out
	*
	* @return int
	*/
	static tars::TC_NetWorkBuffer::PACKET_TYPE checkHttpPacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out);


public:
	
	/**
	*
	*  构造函数
	*/
	BaseHttpController(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseHttpController();

	/*
	*
	*  清空变量
	*
	*/
	virtual void reset();

	
	/**
	*
	* 初始化
	*/
	void initialization(void);


	/**
	*
	* 初始化路由，绑定路由处理函数
	*/ 
	virtual void initRoute(void)       =  0 ;	
	


    /**
     * 处理http路由请求
     * @return :  0 : success , 非0: error
     */
     virtual int doProcess(void);


	/**
	*  返回成功的消息
	* 
	*/
	void success( const std::string& data );
	void success( int code = (int)BaseErrorCode::SUCCESS, const std::string& msg="success" );
	void success( Json::Value& data, int code = (int)BaseErrorCode::SUCCESS, const std::string& msg="success" );


	/*
	*
	* 返回失败的消息
	*/
	void error(int code=(int)BaseErrorCode::PARAMS_ERROR,const std::string& msg="error" );
	void error(Json::Value& data,int code = (int)BaseErrorCode::PARAMS_ERROR,const std::string& msg="error");


	/*
	* 跳转
	*/
	void redirect(const std::string& sUrl);	
	void redirect(const std::string& sUrl, const std::vector<std::string>& cookieHeader);
	void redirect(const std::map<std::string,std::string>& httpHeader,const std::vector<std::string>& cookieHeader);
	void auth(const std::string& sMsg);

	


protected:
	
	/**
	* 设置返回信息
	*
	*/
	void result( const std::string& data);
	void result( Json::Value& data);
	void result( Json::Value& data, int code, const std::string& msg);
	void result(const std::map<std::string,std::string>& httpHeader,  int httpStutus, const std::string& about , const std::string& body );
	void result(const std::map<std::string,std::string>& httpHeader,  const std::vector<std::string >& cookieHeader, int httpStutus, const std::string& about , const std::string& body	);

	/** 
	*  json反序列化
	*
	*/
	std::string serialize(Json::Value& data ,int code,const std::string& msg);




protected:

	
	
	/** 
	* 处理HTTP协议报文的处理
	*/
	int doProcessParse(void);
	
	/** 
	* 处理路由
	*/
	int doProcessRoute(void);
	
		
	/** 
	* 处理鉴权: jwt,authorize,token等等鉴权模式
	* reutrn int , 0：success ，返回200; 非0 ： 失败,返回403
	*/
	virtual int doProcessAuth(void);

	
};


}



