//
//  jsConfigurationBindings.h
//  SpaceJunk
//
//  Created by ixtli on 12/23/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__jsConfigurationBindings__
#define __SpaceJunk__jsConfigurationBindings__

#include "v8.h"

using namespace v8;

void setPort(Local<String> property,
						 Local<Value> value,
						 const PropertyCallbackInfo<void>& info);
void getPort(Local<String> property,
						 const PropertyCallbackInfo<Value>& info);

#endif /* defined(__SpaceJunk__jsConfigurationBindings__) */
