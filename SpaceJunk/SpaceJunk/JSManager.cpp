//
//  JSManager.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/3/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//


#include "v8.h"
#include "file.h"
#include "JSManager.h"

#include "jsConfigurationBindings.h"

using namespace v8;

JSManager JSManager::_instance;

JSManager::JSManager()
{}

JSManager::~JSManager()
{
	
}

static const char * V8UTF8ToCString(const String::Utf8Value& val)
{
	return *val ? *val : "<V8 String Conversion Failed>";
}

static void v8Log(const FunctionCallbackInfo<Value> &args)
{
	int length = args.Length();
	HandleScope handleScope(args.GetIsolate());
	for (int i = 0; i < length; i++)
	{
		String::Utf8Value str(args[i]);
		info("%s", V8UTF8ToCString(str));
	}
};

bool JSManager::init()
{
	// Create the configuration global template
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope handle_scope(isolate);
	
	// Config object
	Handle<ObjectTemplate> config = ObjectTemplate::New();
	config->SetAccessor(String::New("port"),
											FunctionTemplate::New(getPort),
											FunctionTemplate::New(setPort));
	
	// Expose some globals to the config file
	
	Handle<ObjectTemplate> global = ObjectTemplate::New();
	global->Set(String::New("log"), FunctionTemplate::New(v8Log));
	Handle<Context> context = Context::New(isolate, NULL, global);
	Context::Scope context_scope(context);
	
	// Run our loaded config script in the contents
	File f;
	if (!f.init("config", "js"))
		return false;
	
	Handle<String> source = String::New(f.contents());
	Handle<Script> script = Script::Compile(source);
	Handle<Value> result = script->Run();
	Local<Boolean> b = result->ToBoolean();
	
	return b->Value();
}

