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

#include "uiManager.h"

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
	_globalTemplate.Reset();
	
	_isolate->Exit();
	_isolate = NULL;
}

bool JSManager::pushScriptFromServer(const char *script, size_t length, int fd)
{
	if (!length || !script)
		return false;
	
	// We need to save the work for later
	ServerWork* unit = new ServerWork(script, length, fd);
	
	// Push it to the stack
	bool ret = _serverWorkQueue.push(unit);
	
	// If the queue is full it has not been added. The naive solution is to simply
	// ignore this work unit by deleting it.
	if (!ret)
	{
		delete unit;
	}
	
	return ret;
}

unsigned int JSManager::processScriptQueue()
{
	V8_OPEN_SCOPE();

	unsigned int scriptsRun = 0;
	ServerWork* unit = NULL;
	
	while (_serverWorkQueue.pop(unit))
	{
		HandleScope secondScope(isolate);
		
		// Create the context in which to run the script
		Local<Context> context = newContext();
		
		// Enter the context so operations happen in it
		Context::Scope context_scope(context);

		Local<String> source = V8_NEW_STRING(unit->script);
		Local<Script> script = Script::Compile(source);
		script->Run();
		
		delete unit;
		unit = NULL;
		
		scriptsRun++;
	}
	
	V8::ContextDisposedNotification();
	
	return scriptsRun;
}

inline void makeRandomThing(const v8::FunctionCallbackInfo<v8::Value> &args)
{
	UIManager::getInstance()->makeRandomRect();
}

void JSManager::initIsolateGlobals()
{
	V8_OPEN_SCOPE();
	
	// Make a new object template for global
	Handle<ObjectTemplate> global = ObjectTemplate::New(isolate);
	Local<ObjectTemplate> sj = ObjectTemplate::New(isolate);
	
	sj->Set(V8_NEW_STRING("log"), FunctionTemplate::New(isolate, v8Log));
	sj->Set(V8_NEW_STRING("makeRect"), FunctionTemplate::New(isolate, makeRandomThing));
	
	global->Set(V8_NEW_STRING("spacejunk"), sj);
	
	_globalTemplate.Reset(isolate, global);
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

Local<Context> JSManager::newContext()
{
	V8_OPEN_ESCAPABLE_SCOPE();
	
	// You have to make a scoped reference from the persistent one
	Handle<ObjectTemplate> global =
		Local<ObjectTemplate>::New(isolate, _globalTemplate);
	
	Local<Context> ctx = Context::New(isolate, NULL, global);
	
	return handleScope.Escape(ctx);
}

Local<Object> JSManager::getGlobalObject(Handle<Context>& context)
{
	V8_OPEN_ESCAPABLE_SCOPE();
	Local<String> str = Local<String>::New(isolate, V8_NEW_STRING("spacejunk"));
	return handleScope.Escape(context->Global()->Get(str)->ToObject());
}


