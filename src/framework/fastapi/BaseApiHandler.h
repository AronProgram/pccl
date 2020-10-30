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


#include "BaseHttpResponse.h"
#include "BaseHttpController.h"
#include <iostream>
#include <string>
#include <map>


namespace pccl
{


class BaseApiHandler: public BaseHttpResponse
{
public:
	/*
	* 构造函数
	*/
	BaseApiHandler(void);
	
    /**
     * 析构函数
     **/
    virtual ~BaseApiHandler(void);


	/**
	* 重置
	*/
	virtual void reset() ;
	
	

	void  setBasePointer(BaseHttpController* pBase);
	

	BaseHttpController&  getBasePointerRef();
	
	

public:
	/**
	* 业务逻辑处理入口 
	* 
	*/
	virtual int  doProcessApi(void)    ;

protected:
	/**
	*  检查参数
	**/
	virtual int  doCheckParams(void);
	

	/**
	* 业务处理
	**/
	virtual int  doProcessWork(void);

	
	
protected:
	BaseHttpController*  _pBase;

};


}

