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
#include "BaseRpcRequestParams.h"
#include "BaseRpcRoute.h"
#include "BaseRpcProcess.h"
#include "BaseRpcResult.h"
#include <map>
#include <string>
#include <vector>


using namespace tars;


namespace pccl
{


template<class RpcPacket >
class BaseRpcController : public pccl::BaseRpcProcess,  public pccl::BaseRpcRoute, public pccl::BaseRpcRequestParams<RpcPacket>, public  pccl::BaseRpcResult
{

public:
	/**
	* parse http packet
	* @param in
	* @param out
	*
	* @return int
	*/
	static tars::TC_NetWorkBuffer::PACKET_TYPE checkRpcPacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out)
	{
		return tars::TC_NetWorkBuffer::PACKET_FULL;
	}
	
	static tars::TC_NetWorkBuffer::PACKET_TYPE ignoreRpcPacket(tars::TC_NetWorkBuffer& in, std::vector<char>& out)	
	{
		return tars::TC_NetWorkBuffer::PACKET_ERR;	
	}


public:
	
	/**
	*
	*  构造函数
	*/
	BaseRpcController(void) { }
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseRpcController() { }

	/*
	*
	*  清空变量
	*
	*/
	virtual void reset()
	{
		BaseRpcRequestParams<RpcPacket>::reset();	
	}

	
	/**
	*
	* 初始化
	*/
	void initialization(void)	
	{	
		initErrorCode();
		
		initRoute();	
		
	}


	/**
	*
	* 初始化路由，绑定路由处理函数
	*/ 
	virtual void initRoute(void)             = 0;    

	

	/**
	* 初始化错误码，统一错误码处理
	*  
	*/
	virtual void initErrorCode(void)         = 0;
	


    /**
     * 处理RPC路由请求
     * @return :  0 : success , 非0: error
     */
    virtual int doProcess(void)
	{
		int result = pccl::STATE_SUCCESS;

		
		TLOGDEBUG( "doProcessParse" << std::endl );
		
		// 初始化
		result = doProcessParse();
		if ( pccl::STATE_ERROR == result )
		{	
			this->error(BaseErrorCode::PARSE_ERROR);
			return pccl::STATE_SUCCESS;
		}	

		TLOGDEBUG( "doProcessRoute" << std::endl );

		//todo
		//限制策略: 频率，ip,黑名单

		// 处理路由
		result = doProcessRoute();
		
		TLOGDEBUG( "doProcess finish, result:" << result << std::endl );

		return result;
		
	}	



protected:	
	
	/** 
	* 处理RPC协议报文的处理
	*/
	int doProcessParse(void)
	{
		return pccl::STATE_SUCCESS;
	}
	
	/** 
	* 处理路由
	*/
	int doProcessRoute(void)
	{
		return pccl::STATE_SUCCESS;
	}

	
	/** 
	* 处理鉴权: jwt,authorize,token等等鉴权模式
	* reutrn int , 0：success ，返回200; 非0 ： 失败,返回403
	*/
	virtual int doProcessAuth(void)
	{
		return pccl::STATE_SUCCESS;
	}



private:
	bool 		_status;

	
};


}



