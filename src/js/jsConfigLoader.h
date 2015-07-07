//
//  jsConfigLoader.h
//  SpaceJunk
//
//  Created by ixtli on 12/27/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__jsConfigLoader__
#define __SpaceJunk__jsConfigLoader__

#include "./v8Util.h"

class JSConfigLoader
{
public:
	
	JSConfigLoader();
	~JSConfigLoader();
	
	bool init();
	
	static void installConfiguration(v8::Persistent<v8::Context> context);
	
private:
	
	constexpr static const char * CONFIG_NAME = "config";
	
	void processConfigObject();
	
	v8::Persistent<v8::Context> _context;
	
};

#endif /* defined(__SpaceJunk__jsConfigLoader__) */
