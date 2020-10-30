/**
 * pccl is pleased to support the open source community by making Tars available.
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



#include "BaseRandom.h"
#include "effolkronium/random.hpp"


using RandomEk = effolkronium::random_static;

namespace pccl
{


std::string BaseRandom::alnum(int len )
{

	std::array<std::string,52> ALNUM   = { "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };
	std::string pool;

	for( int i = 0; i < len ; i++ )
	{	
		auto result = RandomEk::get( ALNUM.begin(), ALNUM.end() );
		pool.append( *result );
	}

	return pool;

}

std::string BaseRandom::alpha(int len )
{

	std::array<std::string,62> ALPHA   = { "0","1","2","3","4","5","6","7","8","9","a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
	std::string pool;

	for( int i = 0; i < len ; i++ )
	{	
		auto result = RandomEk::get( ALPHA.begin(), ALPHA.end() );
		pool.append( *result );
	}

	return pool;

}

std::string BaseRandom::numric(int len )
{

	std::array<std::string,10> NUMRIC  = { "0","1","2","3","4","5","6","7","8","9"};
	std::string pool;

	for( int i = 0; i < len ; i++ )
	{	
		auto result = RandomEk::get( NUMRIC.begin(), NUMRIC.end() );
		pool.append( *result );
	}

	return pool;

}


std::string BaseRandom::nozero(int len )
{

	std::array<std::string,9>  NOZERO  = { "1","2","3","4","5","6","7","8","9"};
	std::string pool;

	for( int i = 0; i < len ; i++ )
	{	
		auto result = RandomEk::get( NOZERO.begin(), NOZERO.end() );
		pool.append( *result );
	}

	return pool;

}



}



