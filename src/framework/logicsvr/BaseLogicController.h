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
#include "BaseLogicResult.h"


#include <map>
#include <string>

namespace pccl
{


/**
 *
 *
 */
class BaseLogicController : public BaseLogicProcess, public BaseLogicRoute, public BaseLogicParams,  public BaseLogicResult
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
	static tars::TC_NetWorkBuffer::PACKET_TYPE ignorePacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out);


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
	virtual void reset();

	
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

	

protected:
	
	/** 
	* 处理初始化
	*/
	int doProcessInit(void);
	
	/** 
	* 处理路由
	*/
	int doProcessRoute(void);		


private:
	/**
	*  状态标志
	*/
	bool _status;


};


}

