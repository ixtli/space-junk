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

#define V8_NEW_STRING(STRING) \
	v8::String::NewFromUtf8(isolate, STRING)

#define V8GETVAL(ISOLATE, OBJECT, NAME) \
	OBJECT->Get(V8_NEW_STRING(NAME))

#define V8_OPEN_CUSTOM_SCOPE(ISOLATE, HANDLE) \
	v8::Isolate* ISOLATE = JSManager::getIsolate(); \
	v8::HandleScope HANDLE(ISOLATE)

#define V8_OPEN_SCOPE() V8_OPEN_CUSTOM_SCOPE(isolate, handleScope)

#define V8_OPEN_ESCAPABLE_SCOPE() \
	v8::Isolate* isolate = JSManager::getIsolate(); \
	v8::EscapableHandleScope handleScope(isolate)

inline const char * V8StrToCStr(const v8::String::Utf8Value& val)
{
	return *val ? *val : "<V8 String Conversion Failed>";
}

inline bool V8_V_TO_UINT32(const v8::Value* val, unsigned int &target)
{
	if (!val->IsUint32()) return false;
	target = val->ToUint32()->Value();
	return true;
}

inline bool V8_V_TO_INT32(const v8::Value* val, int &target)
{
	if (!val->IsInt32()) return false;
	target = val->ToInt32()->Value();
	return true;
}

inline bool V8_V_TO_BOOL(const v8::Value* val, bool &target)
{
	if (!val->IsBoolean()) return false;
	target = val->ToBoolean()->Value();
	return true;
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
