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

#include "BaseRpcApiController.h"
#include "RpcConfig.h"
#include <string>


using namespace pccl;

/**
 *
 *
 */
class HelloApi : public pccl::BaseRpcApiController<RPC_PACKET>
{


public:
	
	
	/**
	*
	*  构造函数
	*/
	HelloApi(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~HelloApi();

	/**
	*
	* 清空环境
	*/
	virtual void reset();

protected:

	/**
	*
	* 初始化路由，绑定路由处理函数
	*/ 
	virtual void initRoute(void);


	/**
	* 初始化错语码
	*/
	virtual void initErrorCode(void);
	

	

	
};

