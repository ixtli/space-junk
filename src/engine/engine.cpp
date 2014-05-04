//
//  engine.cpp
//  Space Junk
//
//  Created by ixtli on 5/8/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "JSManager.h"
#include "server.h"
#include "environment.h"
#include "version.h"
#include "configuration.h"

#include "engine.h"

Engine Engine::_instance;

/** Construct the engine wrapper */
Engine::Engine() :

_lastUpdate(0)

{ }

/** Destroy the engine. */
Engine::~Engine()
{
	
}

/**
 Initialize the engine
 @return true if successful
 */
bool Engine::init()
{
	info("%s v%u.%u", V_DISPLAY_NAME, V_MAJOR, V_MINOR);
	
	// Start components
	initComponents();
	
	// Start the server
	Server::getInstance()->run();
	
	// Do this last so the gap isn't too great
	_lastUpdate = Environment::currentTime();
	
	return true;
}

/** Initialize managers that implement IComponent */
bool Engine::initComponents()
{
	if (!JSManager::getInstance()->init())
		return false;
	
	if (!Server::getInstance()->init())
		return false;
	
	return true;
}

/** Update game components */
void Engine::update(sjtime_t now)
{
	_lastUpdate = now - _lastUpdate;
	
	
	_lastUpdate = now;
}
