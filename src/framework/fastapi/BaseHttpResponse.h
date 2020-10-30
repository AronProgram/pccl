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
#include <string>


namespace pccl
{



/**
 *
 *
 */
class BaseHttpResponse
{

public:		
	/**
	*
	*  构造函数
	*/
	BaseHttpResponse(void);
	
    /**
     *
     * 析构函数
     */
    virtual ~BaseHttpResponse();

public:
	void                 reset(void);
	int                  getResult(void)       { return _result; }
	void                 setResult(int result);
	
	const std::string&   getErrMsg(void)      { return _message; }
	void                 setErrMsg(const std::string& message, int result = 500 );
	void                 setErrMsg(const char* message,int result = 500);
	std::string          getRedirect() { return _redirect; }
	void                 setRedirect(const std::string& sUrl) { _redirect = sUrl; }
	bool                 hasRedirect() { return _redirect.empty() ? false : true ; }
	

	Json::Value&         getDoc() { return _doc;}
	
	
	void                 setSequence(const std::string& sequence);	
	std::string          getSeqMsg(void);

	
	
	
private:
	int          _result;
	std::string  _redirect;
	std::string  _sequence;	
	std::string  _message;
	Json::Value  _doc;        
	
};



}

