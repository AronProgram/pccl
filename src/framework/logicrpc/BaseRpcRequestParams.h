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
#include "BaseRpcHttpPacket.h"
#include "json.h"
#include "BaseRandom.h"
#include <algorithm>
#include <map>
#include <string>
#include <vector>



namespace pccl
{

template<class RpcPacket>
class BaseRpcRequestParams 
{		

public:
	/**
	*
	*  构造函数
	*/
	BaseRpcRequestParams(void) {}
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseRpcRequestParams(void){}

	/**
	*
	*
	*/
	void setBuffer(std::vector<char>* inBuffer, std::vector<char>* outBuffer)	
	{
		_inBuffer  = inBuffer;
		_outBuffer = outBuffer;
	}

	std::vector<char>& getOutBuffer(void)
	{
		return *_outBuffer;
	}

	/*
	*
	*  清空变量
	*
	*/
	virtual void reset()	
	{
		_sequence = "";
		_route	  = "";
		_params.clear();	
		_doc.clear();	
		
	}



	/*
	*  请求序列号,用于日志染色,追踪数据链条
	*/
	std::string& getSequence(void)	
	{
		return _sequence;	
	}

	
	/*
	*
	*  获取路由
	*/
	const std::string&		getRoute()	
	{
		return _route;
	}

  
	/*
	*
	*  获取http body json数据参数
	*/
	Json::Value&           getDoc (void)     { return _doc; }

	
	/**
	* 获取http请求的header/body的后面序列化后的参数列表,
	* 
	*/
	REQUEST_PARAMS& 	getParams(void) 
	{ 
		return _params; 
	}
	
	std::string&    	getParams(const std::string& sKey) 
	{ 
		return _params[sKey]; 
	}
	
	void                putParams(const std::string& sKey, const std::string& sValue )
	{
		_params[ sKey ] =  sValue ;
	}



protected:
	
	/*
	*
	*  解析报文
	*  @return  : 0:success, !0: error
	*/
	int parse(void)
	{
		// 构建染色ID，用于日志的数据链条的追踪
		_sequence = BaseRandom::alpha(12);

		
		int result = parseRpcPacket();
		if ( pccl::STATE_SUCCESS != result )
		{
			TLOGERROR("parse packet error" << "\n" );
			return pccl::STATE_ERROR;
		}	


	 	dump();

		return result;
	}

	
	/**
	*	解析整个http报文
	*	@return  : success: OK, error: error
	*/
	virtual int parseRpcPacket(void)
	{		
		RpcPacket packet;

		int result =  packet.parse( *_inBuffer  );
		if ( pccl::STATE_SUCCESS != result )
		{
			return pccl::STATE_ERROR;
		}

		_route  = packet.getRoute();
		_params = packet.getParams();
		_doc    = packet.getDocument();
		
		return pccl::STATE_ERROR;
	}



private:	
	void       dump(void)		
	{
		dumpParams();
	}
	
	/*
	* 打印参数
	*/
	void 		dumpParams(void)
	{		
		
		TLOGDEBUG( "dumpParams, " << _sequence << std::endl );
		for( auto it = _params.begin(); it != _params.end(); it++ )
		{
			TLOGDEBUG( "dumpParams, " << _sequence << ", key:" <<it->first << ",value:" << it->second << std::endl);
		}
		
		
	}


	
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
	* 路由
	*/
	std::string             _route;
	
	/*
	* http参数：
	* 1. http 协议header/body query string参数
	* 2. 鉴权用户信息的参数（ 鉴权权可以写入进来）
	*/
	REQUEST_PARAMS			_params;

	
	/*
	* http报文解析后json
	*/
	Json::Value				_doc; 

};


}

