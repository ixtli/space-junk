//
//  jsContext.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/19/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "./jsContext.h"

JSContext::JSContext() :

_context()

{}


JSContext::~JSContext()
{
	_context.Reset();
}
