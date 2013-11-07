//
//  JSManager.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/3/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//


#include "v8.h"

#include "JSManager.h"

using namespace v8;

JSManager JSManager::_instance;

JSManager::JSManager()
{}

JSManager::~JSManager()
{
	
}

/** @param dt the time in fractions of a second since last update */
void JSManager::update(uint32_t dt)
{
	
}

bool JSManager::init()
{
	// Initialize V8 hello world
	// @TODO: Put this somewhere else
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope handle_scope(isolate);
	Handle<Context> context = Context::New(isolate);
	Persistent<Context> persistent_context(isolate, context);
	Context::Scope context_scope(context);
	Handle<String> source = String::New("'Hello' + ', World!'");
	Handle<Script> script = Script::Compile(source);
	Handle<Value> result = script->Run();
	persistent_context.Dispose();
	String::AsciiValue ascii(result);
	info("%s", *ascii);
	
	return true;
}

