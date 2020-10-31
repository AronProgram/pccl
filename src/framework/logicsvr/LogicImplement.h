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


#include "servant/Application.h"
#include "BaseLogicPlus.h"



using namespace tars;



/**
 *
 *
 */
template<typename Controller>
class LogicImplement : public Servant {
public:
    /**
     * 构造函数
     */
	LogicImplement(void) {} 
	
	
    /**
     * 析构函数
     */
    virtual ~LogicImplement() {}

    /**
     * 初始化
     */
    virtual void initialize() {}

    /**
     * 释放资源 
     */
    virtual void destroy() {}

    /**
     * 处理处辑层协议请求
     * @param TarsCurrentPtr : current
     * @param vector<char>   : buffer
     * @return :  true : is exist , false: not exist
     */
    int doRequest(TarsCurrentPtr current, std::vector<char>& outBuffer)
	{	
		const std::vector<char>& inBuffer = current->getRequestBuffer();
		
		try
		{
			_controller.clean();
			_controller.setBuffer( (std::vector<char>*)&inBuffer,&outBuffer);
			_controller.doProcess();
			
			TLOGDEBUG( "LogicSvr doRequest response outBuffer size:" << outBuffer.size() << std::endl );
		}
		catch(exception &ex)
		{
			TLOGERROR("[PCCL]LogicImplement::doRequest error: " << ex.what() << endl);
		}
		catch(...)
		{
			TLOGERROR("[PCCL]LogicImplement::doRequest unknown error" << endl);
		}

		
		return pccl::STATE_SUCCESS;
	}


private:
	Controller _controller;


};




