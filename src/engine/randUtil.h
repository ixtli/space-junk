//
//  randUtil.h
//  SpaceJunk
//
//  Created by ixtli on 12/18/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef SpaceJunk_randUtil_h
#define SpaceJunk_randUtil_h

#include <random>

#define RAND_BETWEEN(X,Y,T) SJRandomEngine::getRandomBetween<T>(X, Y)
#define RAND_NORMAL(T) SJRandomEngine::getRandomNormal<T>()

#define RAND_FLOAT() RAND_NORMAL(float)
#define RAND_DOUBLE() RAND_NORMAL(double)
#define RAND_INT(X, Y) RAND_BETWEEN(X, Y, int)
#define RAND_UINT(X, Y) RAND_BETWEEN(X, Y, unsigned int)
#define RAND_BYTE(X, Y) RAND_BETWEEN(X, Y, GLubyte)

// Use a custom namespace to obscure globals
namespace SJRandomEngine
{
	static std::default_random_engine defaultRandomEngine(std::random_device{}());
	
	template<typename T>
	T getRandomBetween(T min, T max)
	{
		std::uniform_int_distribution<T> dis(min, max);
		return dis(defaultRandomEngine);
	}
	
	template<typename T>
	T getRandomNormal()
	{
		std::uniform_real_distribution<T> dis(0.0, 1.0);
		return dis(defaultRandomEngine);
	}
}

#endif
