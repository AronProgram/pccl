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
#include "BaseLogicError.h"
#include <string>



namespace pccl
{



/**
 *
 *
 */
class BaseLogicResult :  public BaseLogicError
{

public:		
	/**
	*
	*  构造函数
	*/
	BaseLogicResult(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseLogicResult();
	

public:

	/**
	*  重置
	* 
	*/
	void reset();

	void setSequence( const std::string& sSeq );
	

	/**
	*  返回成功的消息
	* 
	*/
	void success( void );	
	void success( const std::string& data );


	/*
	*
	* 返回失败的消息
	*/
	void error( void );
	void error( int code );
	void error( int code,const std::string& msg );
	void error( int code , const std::string& msg, const std::string& data );
	

private:

	/**
	* 设置返回信息
	*
	*/
	void result( int code , const std::string& msg, const std::string& data );



protected:
	std::string   _sequence;
	std::string   _serialize;
      
	
};



}

