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
#include "util/tc_network_buffer.h"
#include "json.h"
#include "BaseLogicRoute.h"
#include "BaseLogicProcess.h"
#include "BaseLogicParams.h"


#include <map>
#include <string>

using namespace tars;




/**
 *
 *
 */
class BaseLogicController : public BaseLogicProcess, public BaseLogicRoute, public BaseLogicParams  
{
public:
    /**
     * 解析报文：
     * @return :  1 : PACKET_FULL , -1: PACKET_ERR, 0: PACKET_LESS
     */
	static tars::TC_NetWorkBuffer::PACKET_TYPE checkPacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out);

    /**
     * 忽略解析报文：
     * @return :  1 : PACKET_FULL , -1: PACKET_ERR, 0: PACKET_LESS
     */
	static tars::TC_NetWorkBuffer::PACKET_TYPE checkIgnorePacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out);


public:
	
	/**
	*
	*  构造函数
	*/
	BaseLogicController(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseLogicController();

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
	virtual int initialization(void);


	/**
	*
	* 初始化路由，绑定路由处理函数
	*/ 
	virtual void initRoute(void) = 0;	
	


    /**
     * 处理路由请求
     * @return :  0 : success , 非0: error
     */
     virtual int doProcess(void);


	 

public:
	/** 
	* 设置返回信息: 纯Json数据
	* 
	*
	*/	
	void toJson(Json::Value& data, const std::string& msg = "success", int result = 0 );
	void toJsonSuccess(void);
	void toJsonError(void);
	/**
	* 设置返回信息: string数据打包
	*
	*/
	void toBin(const std::string& data, const std::string& msg = "success", int result = 0  );
	void toBin(const std::string& data, int result );
	void toBinSuccess(void);
	void toBinError(void);

	/** 
	* 设置返回信息: json数据打包
	*
	*/
	void toStr(Json::Value& data, const std::string& msg = "success", int result = 0 );


protected:
	
	/** 
	* 处理初始化
	*/
	int doProcessInit(void);
	
	/** 
	* 处理路由
	*/
	int doProcessRoute(void);		

	/*
	*  Document 转成 string
	*/
	std::string doc2Str(Json::Value& data);

	/**
	* 设置成功返回消息
	*/
	void success(const std::string& msg);


	/*
	* 设置错误返回消息
	*/
	void error(const std::string& msg, int result = 100);

};

