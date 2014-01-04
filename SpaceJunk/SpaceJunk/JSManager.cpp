//
//  JSManager.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/3/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "v8Util.h"

#include "JSManager.h"

#include "jsConfigLoader.h"

JSManager JSManager::_instance;

JSManager::JSManager()
{}

JSManager::~JSManager()
{
	
}

bool JSManager::init()
{
	// This is safe to call because if ICU support was not compiled in this
	// function exists, but is empty.
	v8::V8::InitializeICU();
	
	JSConfigLoader config;
	
	if (!config.init())
		return false;
	
	return true;
}

