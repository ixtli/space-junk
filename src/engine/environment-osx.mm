//
//  environment.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include <sys/utsname.h>

#include "renderer.h"
#include "engine.h"
#include "imageData.h"
#include "environment.h"

Environment Environment::_instance;

Environment::Environment()
{}

Environment::~Environment()
{
	destroy();
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
	
	char *p = NULL;
	if ((p = getenv("SCREEN_GAMMA")) != NULL)
	{
		_currentGamma = atof(p);
	} else {
		_currentGamma = 2.2;
	}
	
	info("Gamma: %f", _currentGamma);
	
	if (!Renderer::getInstance()->init())
		return false;
	
	// Init the engine
	if (!Engine::getInstance()->init())
		return false;
	
	return true;
}

void Environment::destroy()
{
	Renderer::getInstance()->destroy();
	Engine::getInstance()->destroy();
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

unsigned int Environment::defaultFBO()
{
	// Use zero for the default FBO. N.B.: Not appropriate for iOS
	return 0;
}

void Environment::updateRenderables()
{
	Renderer::getInstance()->update(TIME_SINCE_EPOCH());
}

void Environment::render()
{
	Renderer::getInstance()->render();
}

void Environment::viewResize(unsigned int w, unsigned int h)
{
	Renderer::getInstance()->resize(Size2I(w, h));
}
