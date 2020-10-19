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
#include "BaseLogicRoute.h"
#include "BaseLogicProcess.h"
#include "Packet.pb.h"
#include <map>
#include <string>

using namespace tars;



/**
 *
 *
 */
class BaseLogicParams 
{

public:
	/**
	*
	*  构造函数
	*/
	BaseLogicParams(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseLogicParams(void);

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

	RequestPacketPb&   getPackets(void);


	/*
	*  请求序列号,用于日志染色,追踪数据链条
	*/
	const std::string& getSequence(void);

	/*
	* 模识标识
	*/
	int 		getCmd(void);

	/*
	* 模块子命令
	*/
	int  		getSubCmd(void);

	/*
	* 获取数据段缓存的数据
	*/
	const std::string& getBuffer(void);

	/**
	* 获取上下文环境参数
	*/
	const std::map<std::string,std::string>& getContext(void);
	
	const std::map<std::string,std::string>& getStatus(void);
	
	/*
	* 打印参数
	*/
	void 		dumpParams(void);


private:
	/*
	*
	*  解析报文
	*  @return  : 0:success, !0: error
	*/
	int parse(void);
		
	

	
protected:	
	/*
	* 输入buffer
	*/
	std::vector<char>*      _inBuffer;
	
	/*
	* 输出buffer
	*/
	std::vector<char>* 		_outBuffer;  
	
	/**
	* 数据报文
	*/
	RequestPacketPb         _packtes;
	

};

