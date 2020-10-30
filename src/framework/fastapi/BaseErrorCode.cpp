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


#include "BaseErrorCode.h"


namespace pccl
{



BaseErrorCode::BaseErrorCode() 
{
	initError();
}

BaseErrorCode::~BaseErrorCode()
{


}


void BaseErrorCode::initError()
{
	_error[ BaseErrorCode::METHOD_ERROR ]    = "method error";
	_error[ BaseErrorCode::ROUTER_ERROR ]    = "router error";
	_error[ BaseErrorCode::PARSE_ERROR ]     = "parse http packet error";
	_error[ BaseErrorCode::PARAMS_ERROR ]    = "params error";
	_error[ BaseErrorCode::AUTHOR_ERROR ]    = "auth error";
}


void BaseErrorCode::reset()
{
	
	
}


const std::string& BaseErrorCode::getError(int code )
{
	if ( _error.count(code)  > 0 )
		return _error[code];

	return _empty;

}

void	BaseErrorCode::addError(int code, const std::string& msg)
{
	if ( _error.count(code)  > 0 )
		return ;
	
	_error[ code ] = msg;

}


bool BaseErrorCode::isError(int code)
{
	
	if ( _error.count(code)  > 0 )
		return true;

	return false;
}



}


