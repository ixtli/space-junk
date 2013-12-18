//
//  environment.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include <sys/time.h>
#include <sys/utsname.h>

#include "renderer.h"
#include "engine.h"

#include "environment.h"

Environment Environment::_instance;

Environment::Environment()
{}

Environment::~Environment()
{
	
}

bool Environment::init()
{
	utsname name;
	
	if (uname(&name))
	{
		warn("Error calling the uname() function.");
		return false;
	}
	
	info("%s v%s %s @%s", name.sysname, name.release, name.machine, name.nodename);
	info("%s", name.version);
	
	if (!Renderer::getInstance()->init())
		return false;
	
	// Init the engine
	if (!Engine::getInstance()->init())
		return false;
	
	return true;
}

/**
 Return the full path for a file of a given name and extension
 @param name the name of the file in the bundle
 @param type the type of the file in the bundle
 @return The full path to the file or null if not found
 */
char* Environment::newPathForFile(const char *name, const char *type)
{
	
	NSString* n = [[NSString alloc] initWithCString:name
																				 encoding:NSASCIIStringEncoding];
	
	NSString* t = [[NSString alloc] initWithCString:type
																				 encoding:NSASCIIStringEncoding];
	
	NSString* p = [[NSBundle mainBundle] pathForResource:n ofType:t];
	
	if (!p)
	{
		error("Could not find file %s of type %s.", name, type);
		return NULL;
	}
	
	// Copy to a buffer and return it
	char* ret = new char[[p length]];
	if (!ret) return NULL;
	strcpy(ret, [p cStringUsingEncoding:NSASCIIStringEncoding]);
	return ret;
}

/**
 @return the current time in milliseconds
 */
sjtime_t Environment::currentTime()
{
	timeval ct;
	gettimeofday(&ct, NULL);
	
	// Remember: there are 1000 milliseconds in a second
	// 1000 microseconds in a millisecond
	// so 1,000,000 microseconds in a second
	return (ct.tv_sec * 1000) + ((sjtime_t)round(ct.tv_usec * 0.001));
}

unsigned int Environment::defaultFBO()
{
	// Use zero for the default FBO. N.B.: Not appropriate for iOS
	return 0;
}

void Environment::updateGameEvent(void* ctx)
{
	Engine::getInstance()->update(currentTime());
}

void Environment::updateRenderables()
{
	Renderer::getInstance()->update(currentTime());
}

void Environment::render()
{
	Renderer::getInstance()->render();
}

void Environment::viewResize(unsigned int w, unsigned int h)
{
	Renderer::getInstance()->resize(Size2I(w, h));
}
