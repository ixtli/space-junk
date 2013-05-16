//
//  environment.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include <sys/utsname.h>

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
		log("Error calling the uname() functino.");
		return false;
	}
	
	log("%s v%s %s @%s", name.sysname, name.release, name.machine, name.nodename);
	log("%s", name.version);
	
	return true;
}

char* Environment::newPathForFile(const char *name, const char *type)
{
	
	NSString* n = [[NSString alloc] initWithCString:name
																				 encoding:NSASCIIStringEncoding];
	
	NSString* t = [[NSString alloc] initWithCString:type
																				 encoding:NSASCIIStringEncoding];
	
	NSString* p = [[NSBundle mainBundle] pathForResource:n ofType:t];
	
	// Copy to a buffer and return it
	char* ret = new char[[p length]];
	if (!ret) return NULL;
	strcpy(ret, [p cStringUsingEncoding:NSASCIIStringEncoding]);
	return ret;
}

