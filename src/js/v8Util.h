//
//  v8Util.h
//  SpaceJunk
//
//  Created by ixtli on 12/27/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef SpaceJunk_v8Util_h
#define SpaceJunk_v8Util_h

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#include "v8.h"
#pragma clang diagnostic pop

#define V8GETTER(X, PROP, INFO) void X(\
	v8::Local<v8::String> PROP,\
	const v8::PropertyCallbackInfo<v8::Value>& INFO)

#define V8SETTER(X, PROP, VAL, INFO) void X(\
	v8::Local<v8::String> PROP,\
	v8::Local<v8::Value> VAL,\
	const v8::PropertyCallbackInfo<void>& INFO)

inline const char * V8StrToCStr(const v8::String::Utf8Value& val)
{
	return *val ? *val : "<V8 String Conversion Failed>";
}


inline void v8Log(const v8::FunctionCallbackInfo<v8::Value> &args)
{
	int length = args.Length();
	v8::HandleScope handleScope(args.GetIsolate());
	for (int i = 0; i < length; i++)
	{
		v8::String::Utf8Value str(args[i]);
		info("%s", V8StrToCStr(str));
	}
};

#endif
