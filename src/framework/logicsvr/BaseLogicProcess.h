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


/**
 *
 *
 */
class BaseLogicProcess
{


public:

	/**
	*
	*  构造函数
	*/
	BaseLogicProcess(void) {}

	
    /**
     *
     * 析构函数
     */
    virtual ~BaseLogicProcess(void) {}

	
public:
	/**
	*
	* 初始化
	*/
	virtual int initialization(void) = 0;

	
	
	/**
	*  处理流程
	*
	*/
	virtual int doProcess(void)    = 0;
	


};
