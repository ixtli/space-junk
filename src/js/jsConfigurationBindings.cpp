//
//  jsConfigurationBindings.cpp
//  SpaceJunk
//
//  Created by ixtli on 12/23/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "jsConfigurationBindings.h"

void setPort(const FunctionCallbackInfo<Value> &info)
{
	
}

void getPort(const FunctionCallbackInfo<Value> &info)
{
	info.GetReturnValue().Set(Integer::New(5));
}