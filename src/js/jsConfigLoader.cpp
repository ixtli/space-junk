//
//  jsConfigLoader.cpp
//  SpaceJunk
//
//  Created by ixtli on 12/27/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "v8Util.h"
#include "file.h"
#include "configuration.h"
#include "jsConfigLoader.h"
#include "JSManager.h"

using namespace v8;

JSConfigLoader::JSConfigLoader()
{
	
}

JSConfigLoader::~JSConfigLoader()
{
	
}

static V8GETTER(portGetter, property, info)
{
	info.GetReturnValue().Set(Integer::New(Configuration::getInstance()->_serverPort));
}

static V8SETTER(portSetter, prop, value, info)
{
	Local<Int32> port = value->ToInt32();
	Configuration::getInstance()->_serverPort = port->Value();
}

bool JSConfigLoader::init()
{
	
	// Create the configuration global template
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope handle_scope(isolate);
	
	// Expose some globals to the config file
	Handle<ObjectTemplate> global = ObjectTemplate::New();
	Handle<ObjectTemplate> sj = ObjectTemplate::New();
	
	sj->Set(String::NewFromUtf8(isolate, "log"), FunctionTemplate::New(v8Log));
//	sj->SetAccessor(String::NewFromUtf8(isolate, "port"), portGetter, portSetter);
	
	Handle<String> sjName = String::NewFromUtf8(isolate, "spacejunk");
	global->Set(sjName, sj);
	Handle<Context> context = Context::New(isolate, NULL, global);
	Context::Scope context_scope(context);
	
	// Run our loaded config script in the contents
	File f;
	if (!f.init(CONFIG_NAME, JSManager::JS_EXTENSION))
		return false;
	
	Handle<String> source = String::NewFromUtf8(isolate, f.contents());
	Handle<Script> script = Script::Compile(source);
	Handle<Value> result = script->Run();
	
	Handle<Object> blah = context->Global()->Get(sjName)->ToObject();
	Handle<Value> port = blah->Get(String::NewFromUtf8(isolate, "port"));
	
	String::Utf8Value portAsStr(port);
	info("port: %s", V8StrToCStr(portAsStr));
	
	return result->ToBoolean()->Value();
}
