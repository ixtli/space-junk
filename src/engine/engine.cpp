//
//  engine.cpp
//  Space Junk
//
//  Created by ixtli on 5/8/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include <math.h>

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

_hud(NULL),
_previousUpdate(0),
_maxFPS(60),
_minClocksPerFrame(0)

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
	
	// Configure maximum frames per second
	info("Max FPS: %lu", _maxFPS);
	setMaxFPS(_maxFPS);
	
	UIManager::getInstance()->init();
	
	HUD* h = new HUD();
	h->init();
	
	// Initialize the scene
	CubeManager::getInstance()->init();
	
	_previousUpdate = clock();
	
	return true;
}

void Engine::setMaxFPS(clock_t frameCount)
{
	_maxFPS = frameCount;
	_minClocksPerFrame = CLOCKS_PER_SEC / _maxFPS / 1000;
	
	info("%d\t%lu", CLOCKS_PER_SEC, _minClocksPerFrame);
	
	info("Clocks before frame: %lu", _minClocksPerFrame);
}

void Engine::update()
{
	clock_t t = clock();
	clock_t delta = t - _previousUpdate;
	
	if (delta < _minClocksPerFrame) return;
	
	_previousUpdate = t;
	
	UIManager::getInstance()->update(delta);
	CubeManager::getInstance()->update(delta);
	
	
}
