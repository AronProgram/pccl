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


#include <map>
#include <string>


namespace pccl
{


/**
 *
 * 随机生成类
 */
class BaseRandom 
{

public:
    /**
     * 生成数字和字母
     *
     * @param int $len 长度
     * @return string
     */
	 static std::string alnum(int len = 6);


	 /**
     * 仅生成字符
     *
     * @param int $len 长度
     * @return string
     */
	static std::string alpha(int len = 6);
	 
	/**
     * 生成指定长度的随机数字
     *
     * @param int $len 长度
     * @return string
     */
	static std::string numric(int len = 6);

	/**
     * 数字和字母组合的随机字符串
     *
     * @param int $len 长度
     * @return string
     */
	static std::string nozero(int len = 6);


};


}

