//
//  jsContext.h
//  SpaceJunk
//
//  Created by ixtli on 5/19/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__jsContext__
#define __SpaceJunk__jsContext__

#include "./v8util.h"

class JSContext
{
public:
	
	JSContext();
	~JSContext();
	
	bool runScript(const char* script);
	
private:
	
	v8::Persistent<v8::Context> _context;
	
};

#endif /* defined(__SpaceJunk__jsContext__) */
