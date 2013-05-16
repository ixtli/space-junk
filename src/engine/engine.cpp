//
//  engine.cpp
//  Space Junk
//
//  Created by ixtli on 5/8/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "v8.h"

#include "environment.h"
#include "shader.h"
#include "renderer.h"
#include "version.h"

#include "engine.h"

using namespace v8;

Engine Engine::_instance;

Engine* Engine::getInstance()
{
	return &_instance;
}

Engine::Engine()
{ }

Engine::~Engine()
{
	
}

bool Engine::init()
{
	log("%s v%u.%u", V_DISPLAY_NAME, V_MAJOR, V_MINOR);
	
	// Init the environment wrapper
	Environment::getInstance()->init();
	
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope handle_scope(isolate);
	Persistent<Context> context = Context::New();
	Context::Scope context_scope(context);
	Handle<String> source = String::New("'Hello' + ', World!'");
	Handle<Script> script = Script::Compile(source);
	Handle<Value> result = script->Run();
	context.Dispose(isolate);
	String::AsciiValue ascii(result);
	log("%s", *ascii);
	
	Shader s;
	s.init("solidQuad", POS3F_COL4B);
	
	return true;
}