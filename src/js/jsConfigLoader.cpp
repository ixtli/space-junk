//
//  jsConfigLoader.cpp
//  SpaceJunk
//
//  Created by ixtli on 12/27/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "file.h"
#include "configuration.h"
#include "jsConfigLoader.h"
#include "JSManager.h"

#include <wchar.h>
#include <locale>

using namespace v8;

JSConfigLoader::JSConfigLoader()
{
	
}

JSConfigLoader::~JSConfigLoader()
{
	_context.Reset();
}

void JSConfigLoader::installConfiguration(Persistent<Context> context)
{
	
}

void JSConfigLoader::processConfigObject()
{
	V8_OPEN_SCOPE();
	
	Local<Context> ctx = Local<Context>::New(isolate, _context);
	Local<Object> globalInstance = JSManager::getInstance()->getGlobalObject(ctx);
	
	Local<Value> port = V8GETVAL(isolate, globalInstance, "port");
	
	if (!V8_V_TO_UINT32(*port, Configuration::getInstance()->_serverPort))
	{
		warn("Port not a uint. Ignoring.");
	}
	
	Local<Value> blah = V8GETVAL(isolate, globalInstance, "blah");
	String::Utf8Value example(blah);
	info("Blah: %s", V8StrToCStr(example));
}

bool JSConfigLoader::init()
{
	V8_OPEN_SCOPE();
	
	// Get a new object template for the global object
	Local<ObjectTemplate> global = JSManager::getInstance()->newGlobalTemplate();
	
	// Create the context in which to run the script
	Local<Context> context = Context::New(isolate, NULL, global);
	
	// Save the context so we can operate on it later
	_context.Reset(isolate, context);
	
	// Enter the context so operations happen in it
	Context::Scope context_scope(context);
	
	// Run the script itself by name
	Local<Value> ret = JSManager::runScriptFile(CONFIG_NAME);
	
	bool result = false;
	if (!V8_V_TO_BOOL(*ret, result))
	{
		error("Configuration did not return a boolean.");
		return false;
	}
	
	if (!result)
	{
		error("Configuration did not return true.");
		return false;
	}
	
	processConfigObject();
	
	return true;
}
