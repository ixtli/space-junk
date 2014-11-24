//
//  engine.cpp
//  Space Junk
//
//  Created by ixtli on 5/8/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include <thread>
#include <chrono>
#include <functional>

#include "JSManager.h"
#include "server.h"
#include "environment.h"
#include "version.h"
#include "configuration.h"

#include "pngUtil.h"

#include "engine.h"

std::thread* engineThread = NULL;

Engine Engine::_instance;

bool Engine::_shouldTerminate = true;

/** Construct the engine wrapper */
Engine::Engine()

{ }

/** Destroy the engine. */
Engine::~Engine()
{
	destroy();
}

void Engine::threadMain()
{
	info("%s v%u.%u", V_DISPLAY_NAME, V_MAJOR, V_MINOR);
	
	logPNGVersionInfo();
	readPNGInit("grass");
	
	// Start components
	initComponents();
	
	// Start the server
	Server::getInstance()->run(Configuration::getInstance()->_serverPort);
	
	// @TODO: Calculate this from target FPS
	const kSJTimeUnit sleepDuration(16);
	const std::chrono::nanoseconds sdns = std::chrono::duration_cast<std::chrono::nanoseconds>(sleepDuration);
	
	kSJTimePoint lastUpdate = kSJClock::now();
	kSJTimePoint now, updateTime;
	
	std::chrono::nanoseconds sleepFor;
	
	while (!_shouldTerminate)
	{
		// Calculate the diff between last entry into this loop and now
		now = kSJClock::now();
		auto dt = now - lastUpdate;
		sj_time_t diff = (sj_time_t)dt.count();
		lastUpdate = now;
		
		// Do the update
		update(diff);
		
		// How long did it take?
		updateTime = kSJClock::now();
		
		// What was the delta between update start and update end?
		sleepFor = std::chrono::duration_cast<std::chrono::nanoseconds>(now - lastUpdate);
		
		// Sleep until the next interval
		std::this_thread::sleep_for(sdns - sleepFor);
	}
	
	// Clean up anything we started at the beginning of thread execution
	Server::getInstance()->stop();
}

/**
 Initialize the engine
 @return true if successful
 */
bool Engine::init()
{
	if (isRunning())
		return false;
	
	_shouldTerminate = false;
	engineThread = new std::thread(&Engine::threadMain, this);
	
	return true;
}

void Engine::destroy()
{
	if (!isRunning())
		return;
	
	_shouldTerminate = true;
	
	if (engineThread->joinable())
	{
		engineThread->join();
	}
	
	delete engineThread;
	engineThread = NULL;
	
	// Clean up and exit
	JSManager::getInstance()->destroy();
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
void Engine::update(sj_time_t dt)
{
	// Tell the JSManager to execute all scripts delivered to it by other threads
	JSManager::getInstance()->processScriptQueue();
}

bool Engine::isRunning() const
{
	return (engineThread != NULL);
}

