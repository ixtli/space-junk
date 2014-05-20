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

_isolate(NULL),
_serverWorkQueue()

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

bool JSManager::pushScript(const char *script, size_t length)
{
	if (!length || !script)
		return false;
	
	// We need to save the work for later
	char* newWork = new char[length + 1];
	memcpy(newWork, script, length + 1);
	
	// Push it to the stack
	bool ret = _serverWorkQueue.push(newWork);
	
	if (!ret)
	{
		delete [] newWork;
	}
	
	return ret;
}

bool JSManager::processScriptQueue()
{
	V8_OPEN_SCOPE();
	
	// Make a new object template for global
	Local<ObjectTemplate> global = ObjectTemplate::New(isolate);
	Local<ObjectTemplate> sj = ObjectTemplate::New(isolate);
	sj->Set(V8_NEW_STRING("log"), FunctionTemplate::New(isolate, v8Log));
	global->Set(V8_NEW_STRING("spacejunk"), sj);
	
	unsigned int scriptsRun = 0;
	char* text = NULL;
	
	while (_serverWorkQueue.pop(text))
	{
		HandleScope secondScope(isolate);
		
		// Create the context in which to run the script
		Local<Context> context = Context::New(isolate, NULL, global);
		
		// Enter the context so operations happen in it
		Context::Scope context_scope(context);

		Local<String> source = V8_NEW_STRING(text);
		Local<Script> script = Script::Compile(source);
		Local<Value> ret = script->Run();
		
		info("Script result: %s", V8StrToCStr(String::Utf8Value(ret)));
		
		delete [] text;
		scriptsRun++;
	}
	
//	V8::ContextDisposedNotification();
	
	return (scriptsRun > 0);
}

void JSManager::initIsolateGlobals()
{
	V8_OPEN_SCOPE();
	
	// Create persistent handles to strings that we're going to use but never
	// expose directly to the user as modifable values
	_globalName.Reset(isolate, V8_NEW_STRING("spacejunk"));
	_logFunctionName.Reset(isolate, V8_NEW_STRING("log"));
}

Local<Value> JSManager::runScriptFile(const char *name)
{
	V8_OPEN_ESCAPABLE_SCOPE();
	
	Local<Value> ret;
	File f;
	
	if (!f.init(name, JSManager::JS_EXTENSION))
	{
		ret = Local<Boolean>::New(isolate, Boolean::New(isolate, false));
	} else {
		Local<String> source = V8_NEW_STRING(f.contents());
		Local<Script> script = Script::Compile(source);
		ret = script->Run();
	}
	
	return handleScope.Escape(ret);
}

Local<Object> JSManager::getGlobalObject(Handle<Context>& context)
{
	V8_OPEN_ESCAPABLE_SCOPE();
	
	Local<String> str = Local<String>::New(isolate, _globalName);
	return handleScope.Escape(context->Global()->Get(str)->ToObject());
}

Local<ObjectTemplate> JSManager::newGlobalTemplate()
{
	V8_OPEN_ESCAPABLE_SCOPE();
	
	Local<ObjectTemplate> global = ObjectTemplate::New(isolate);
	Local<ObjectTemplate> sj = ObjectTemplate::New(isolate);
	
	sj->Set(V8_NEW_STRING("log"), FunctionTemplate::New(isolate, v8Log));
	global->Set(V8_NEW_STRING("spacejunk"), sj);
	
	return handleScope.Escape(global);
}
