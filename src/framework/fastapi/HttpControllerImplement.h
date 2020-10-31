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


#include "BaseHttpPlus.h"
#include "util/tc_http.h"


using namespace tars;

namespace pccl
{


/**
 *
 *
 */
template<typename Controller>
class ControllerImplement : public Servant {
public:
    /**
     * 构造函数
     */
	ControllerImplement(void) {} 
	
	
    /**
     * 析构函数
     */
    virtual ~ControllerImplement() {}

    /**
     * 初始化
     */
    virtual void initialize() {}

    /**
     *  资源释放
     */
    virtual void destroy() {}

    /**
     * 处理http请求
     * @param TarsCurrentPtr : current
     * @param vector<char>   : buffer
     * @return :  true : is exist , false: not exist
     */
    int doRequest(TarsCurrentPtr current, std::vector<char>& outBuffer)
	{
		const std::vector<char>& inBuffer = current->getRequestBuffer();

		try
		{
			_controller.reset();
			_controller.setBuffer( (std::vector<char>*)&inBuffer,&outBuffer);
			_controller.doProcess();
			
			TLOGDEBUG( "[PCCL] FastApi response outBuffer size:" << outBuffer.size() << std::endl );
		}
		catch(exception &ex)
		{
			TLOGERROR("[PCCL]ControllerImplement::doRequest error: " << ex.what() << endl);
		}
		catch(...)
		{
			TLOGERROR("[PCCL]ControllerImplement::doRequest unknown error" << endl);
		}

		return pccl::STATE_SUCCESS;
	}


private:
	Controller _controller;


};

}


