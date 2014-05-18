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
	destroy();
}

bool JSManager::init()
{
	// This is safe to call because if ICU support was not compiled in this
	// function exists, but is empty.
	V8::InitializeICU();
	
	// This is the top level isolate scope
	_isolate = Isolate::New();
	_isolate->Enter();
	
	initIsolateGlobals();
	
	JSConfigLoader config;
	
	if (!config.init())
		return false;
	
	return true;
}

void JSManager::destroy()
{
	if (!_isolate) return;
	
	// Clear all persistent handles
	_globalName.Reset();
	_logFunctionName.Reset();
	
	_isolate->Exit();
	_isolate = NULL;
}

void JSManager::initIsolateGlobals()
{
	Isolate* isolate = getIsolate();
	HandleScope handle_scope(isolate);
	
	// Create persistent handles to strings that we're going to use but never
	// expose directly to the user as modifable values
	_globalName.Reset(isolate, String::NewFromUtf8(isolate, "spacejunk"));
	_logFunctionName.Reset(isolate, String::NewFromUtf8(isolate, "log"));
}

Local<Value> JSManager::runScript(const char *name)
{
	Isolate* isolate = getIsolate();
	EscapableHandleScope scope(isolate);
	
	// Run our loaded config script in the contents
	File f;
	if (!f.init(name, JSManager::JS_EXTENSION))
	{
		return Boolean::New(isolate, false);
	}
	
	Local<String> source = String::NewFromUtf8(isolate, f.contents());
	Local<Script> script = Script::Compile(source);
	
	return scope.Escape(script->Run());
}

Local<Object> JSManager::getGlobalObject(Handle<Context> context)
{
	Isolate* isolate = getIsolate();
	EscapableHandleScope scope(isolate);
	Local<String> str = Local<String>::New(isolate, _globalName);
	return scope.Escape(context->Global()->Get(str)->ToObject());
}

Local<ObjectTemplate> JSManager::newGlobalTemplate()
{
	Isolate* isolate = Isolate::GetCurrent();
	EscapableHandleScope scope(isolate);
	
	Local<ObjectTemplate> global = ObjectTemplate::New(isolate);
	Local<ObjectTemplate> sj = ObjectTemplate::New(isolate);
	
	sj->Set(Local<String>::New(isolate, _logFunctionName),
					FunctionTemplate::New(isolate, v8Log));
	
	// Add the spacejunk object 
	global->Set(Local<String>::New(isolate, _globalName), sj);
	
	return scope.Escape(global);
}
