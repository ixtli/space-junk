//
//  environment.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include <sys/time.h>
#include <sys/utsname.h>
#include <dispatch/dispatch.h>

#include "renderer.h"
#include "engine.h"

#include "environment.h"

// Some good 'ol c style file-level globals
static dispatch_semaphore_t _global_locks[Environment::NUM_LOCKS];

Environment Environment::_instance;

Environment::Environment()
{}

Environment::~Environment()
{
	for (size_t i = 0; i < NUM_LOCKS; i++)
		_global_locks[i] = NULL;
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
	
	// Initialize locks
	for (size_t i = 0; i < NUM_LOCKS; i++)
	{
		_global_locks[i] = dispatch_semaphore_create(0);
		
		if (!_global_locks[i])
		{
			error("Could not create semaphore index %lu.", i);
			return false;
		}
	}
	
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

/**
 Signal a semaphore. Similar to releasing a lock.
 @param name the SemaphoreNames enum id for the semaphore to lock
 */
void Environment::releaseLock(LockNames name)
{
	long ret = dispatch_semaphore_signal(_global_locks[name]);
	
	if (ret)
	{
		info("Lock awoke a thread.");
	}
}

/**
 Take a named lock
 @param name the name of the lock
 @param wait if true, wait for the lock, else just try
 @return true if the lock was obtained, false otherwise
 */
bool Environment::requestLock(LockNames name, bool wait)
{
	long ret = dispatch_semaphore_wait(_global_locks[name],
			wait ? DISPATCH_TIME_FOREVER : DISPATCH_TIME_NOW);
	
	return (ret == 0) ? true : false;
}

/**
 Wait for given amount milliseconds before giving up waiting for the lock
 @param name the name of the lock to wait on
 @param time the amount of time to wait in milliseconds
 @return
 */
bool Environment::waitOnLock(LockNames name, sjtime_t time)
{
	// 1000 microseconds in a millisecond
	// the unit is in nanoseconds
	dispatch_time_t timeToWait = time * 1000 * NSEC_PER_USEC;
	
	long ret = dispatch_semaphore_wait(_global_locks[name], timeToWait);
	
	return (ret == 0) ? true : false;
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


