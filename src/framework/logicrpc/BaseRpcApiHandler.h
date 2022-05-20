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

#include "BaseRpcPlus.h"
#include "BaseRpcController.h"
#include "BaseRpcResult.h"
#include "BaseErrorCode.h"
#include <iostream>
#include <string>
#include <map>


namespace pccl
{

template<class RpcPacket >
class BaseRpcApiHandler: public BaseRpcResult
{
public:
	/*
	* 构造函数
	*/
	BaseRpcApiHandler(void):        _pBase(NULL) { }
	
    /**
     * 析构函数
     **/
    virtual ~BaseRpcApiHandler(void) { }


	/**
	* 重置
	*/
	virtual void reset()	
	{ 
		_pBase = NULL;
		BaseRpcResult::reset();
	}
	
	
 	
	void  setBasePointer(BaseRpcController<RpcPacket>* pBase)
	{
		_pBase =  pBase;
	}
	

	BaseRpcController<RpcPacket>&  getBasePointerRef()
	{
		return *_pBase;
	}
	
	

public:
	/**
	* 业务逻辑处理入口 
	* 
	*/
	virtual int  doProcessApi(void)
	{
		
		return pccl::STATE_SUCCESS;				
	
	}
	

protected:
	/**
	*  检查参数
	**/
	virtual int  doCheckParams(void)
	{
		return pccl::STATE_SUCCESS;		
	}
	

	/**
	* 业务处理
	**/
	virtual int  doProcessWork(void)
	{
		return pccl::STATE_SUCCESS;		
	}


	/**
	*	输出
	*/
	virtual void doProcessEnd(void)	
	{
		std::vector<char>& buffer	= _pBase->getOutBuffer();
		const std::string& response = getResponse();
		
		buffer.clear();
		buffer.resize( response.length() );
		memcpy( buffer.data(), response.c_str(), response.length() );		
	}

	
	
protected:
	BaseRpcController<RpcPacket>*  _pBase;

};

template<class RpcPacket >
class BaseRpcHttpApiHandler: public BaseRpcApiHandler<RpcPacket>
{
public:
	/*
	* 构造函数
	*/
	BaseRpcHttpApiHandler(void);
	
    /**
     * 析构函数
     **/
    virtual ~BaseRpcHttpApiHandler(void);

	

public:
	

};


}

