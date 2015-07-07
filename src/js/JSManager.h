//
//  JSManager.h
//  SpaceJunk
//
//  Created by ixtli on 11/3/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__JSManager__
#define __SpaceJunk__JSManager__

#include "./v8Util.h"
#include "../engine/ringBuffer.h"

#include "./jsContext.h"

using namespace v8;

class JSManager
{
public:
	
	/** @return the singleton instance */
	static inline JSManager* getInstance() { return &_instance; };
	
	/** @return the current isolate for the main thread */
	static inline Isolate* getIsolate() { return _instance._isolate; };
	
	/** Run a script by name in a given context */
	static Local<Value> runScriptFile(const char* name);
	
	/** Retrieve the global object from a context */
	Persistent<ObjectTemplate>& globalObjectTemplate() {return _globalTemplate;};
	
	/** Make a new context in your current handle scope. */
	Local<Context> newContext();
	
	/** Get a reference to the global object from a given context */
	Local<Object> getGlobalObject(Handle<Context>& context);
	
	bool init();
	void destroy();
	bool pushScriptFromServer(const char* script, size_t length, int fd);
	unsigned int processScriptQueue();
	
private:
	
	/** The size of the server work queue */
	constexpr static const unsigned int WORK_QUEUE_SIZE = 32;
	
	/** The javaScript file extension, with '.' in front */
	constexpr static const char * JS_EXTENSION = ".js";
	
	JSManager();
	~JSManager();
	
	Isolate* _isolate;
	
	class ServerWork
	{
	public:
		
		ServerWork(const char* s, size_t len, int f)
		{
			script = new char[len + 1];
			memcpy(script, s, len);
			script[len] = '\0';
			fd = f;
		}
		
		~ServerWork()
		{
			if (script) delete [] script;
		}
		
		char* script;
		
		int fd;
	};
	
	/** The HTTP server thread pushes work here and we dequeue it */
	RingBuffer<ServerWork*, WORK_QUEUE_SIZE> _serverWorkQueue;
	
	// Create objects that will be presented to every running script
	void initIsolateGlobals();
	
	// Store some UTF8 strings globally so that we dont recreate them needlessly
	Persistent<ObjectTemplate> _globalTemplate;
	
	/** The singleton instance */
	static JSManager _instance;
	
};

#endif /* defined(__SpaceJunk__JSManager__) */
