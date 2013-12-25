//
//  jsConfigurationBindings.cpp
//  SpaceJunk
//
//  Created by ixtli on 12/23/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "jsConfigurationBindings.h"

void setPort(Local<String> property,
						 Local<Value> value,
						 const PropertyCallbackInfo<void>& info)
{
	
}

void getPort(Local<String> property,
						 const PropertyCallbackInfo<Value>& info)
{
	info.GetReturnValue().Set(Integer::New(5));
}