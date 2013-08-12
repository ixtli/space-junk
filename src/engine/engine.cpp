//
//  engine.cpp
//  Space Junk
//
//  Created by ixtli on 5/8/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "v8.h"

#include "uiManager.h"
#include "environment.h"
#include "renderer.h"
#include "version.h"

#include "hud.h"
#include "cubeManager.h"

#include "engine.h"

using namespace v8;

Engine Engine::_instance;

Engine::Engine() :

_hud(NULL)

{ }

Engine::~Engine()
{
	if (_hud) delete _hud;
}

bool Engine::init()
{
	info("%s v%u.%u", V_DISPLAY_NAME, V_MAJOR, V_MINOR);
	
	// Init the environment wrapper
	Environment::getInstance()->init();
	
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
	
	UIManager::getInstance()->init();
	
	HUD* h = new HUD();
	h->init();
	
	// Initialize the scene
	const Size3U mapSize(1, 1, 1);
	CubeManager::instance()->init(mapSize, SOLID_CUBE_SHADER);
	
	return true;
}

void Engine::update()
{
	time_t t = time(0);
	
	UIManager::getInstance()->update(t);
}
