//
//  JSManager.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/3/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "JSManager.h"
#include "file.h"
#include "jsConfigLoader.h"

#include <locale>

using namespace v8;

JSManager JSManager::_instance;

JSManager::JSManager() :

_isolate(NULL)

{}

JSManager::~JSManager()
{
	// Clear all persistent handles
	_globalName.Reset();
	_logFunctionName.Reset();
}

bool JSManager::init()
{
	// This is safe to call because if ICU support was not compiled in this
	// function exists, but is empty.
	V8::InitializeICU();
	
	// This is per-thread and in this engine all interaction with v8 should happen
	// on one thread because their changes must be synchronized and messaged to
	// the graphics and server threads as well.
	_isolate = Isolate::GetCurrent();
	
	initIsolateGlobals();
	
	JSConfigLoader config;
	
	if (!config.init())
		return false;
	
	return true;
}

void JSManager::initIsolateGlobals()
{
	HandleScope handle_scope(_isolate);
	
	// Create persistent handles to strings that we're going to use but never
	// expose directly to the user as modifable values
	_globalName.Reset(_isolate, String::NewFromUtf8(_isolate, "spacejunk"));
	_logFunctionName.Reset(_isolate, String::NewFromUtf8(_isolate, "log"));
}

Local<Value> JSManager::runScript(const char *name)
{
	// Run our loaded config script in the contents
	File f;
	if (!f.init(name, JSManager::JS_EXTENSION))
	{
		return Boolean::New(_instance._isolate, false);
	}
	
	Local<String> source = String::NewFromUtf8(_instance._isolate, f.contents());
	Local<Script> script = Script::Compile(source);
	
	return script->Run();
}

Local<Object> JSManager::getGlobalObject(Handle<Context> context)
{
	return context->Global()->Get(Local<String>::New(_isolate, _globalName))->ToObject();
}

Local<ObjectTemplate> JSManager::newGlobalTemplate()
{
	Handle<ObjectTemplate> global = ObjectTemplate::New(_isolate);
	Handle<ObjectTemplate> sj = ObjectTemplate::New(_isolate);
	
	sj->Set(Local<String>::New(_isolate, _logFunctionName),
					FunctionTemplate::New(_instance.isolate(), v8Log));
	
	// Add the spacejunk object 
	global->Set(Local<String>::New(_isolate, _globalName), sj);
	
	return global;
}
