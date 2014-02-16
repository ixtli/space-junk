//
//  JSManager.h
//  SpaceJunk
//
//  Created by ixtli on 11/3/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__JSManager__
#define __SpaceJunk__JSManager__

#include "v8Util.h"

using namespace v8;

class JSManager
{
public:
	
	/** @return the singleton instance */
	static inline JSManager* getInstance() { return &_instance; };
	
	/** @return the current isolate */
	static inline Isolate * isolate() { return _instance._isolate; };
	
	/** Run a script by name in a given context */
	static Local<Value> runScript(const char* name);
	
	/** Install the global object in a given context */
	Local<ObjectTemplate> newGlobalTemplate();
	
	/** Retrieve the global object from a context */
	Local<Object> getGlobalObject(Handle<Context> context);
	
	// IComponent implementation
	bool init();
	
private:
	
	/** The javaScript file extension, with '.' in front */
	constexpr static const char * JS_EXTENSION = ".js";
	
	JSManager();
	~JSManager();
	
	void initIsolateGlobals();
	
	v8::Isolate* _isolate;
	
	v8::Persistent<v8::String> _globalName;
	v8::Persistent<v8::String> _logFunctionName;
	
	/** The singleton instance */
	static JSManager _instance;
	
};

#endif /* defined(__SpaceJunk__JSManager__) */
