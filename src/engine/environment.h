//
//  environment.h
//  SpaceJunk
//
//  Created by ixtli on 5/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__environment__
#define __SpaceJunk__environment__

#include <stdlib.h>

#include "../util/chronoUtil.h"

class ImageData;

class Environment
{
public:
	
	bool init();
	void destroy();
	
	// Static functionality
	inline static Environment* getInstance() { return &_instance; };
	static char* newPathForFile(const char* name, const char* type);
	
	static void updateRenderables();
	static void render();
	static void viewResize(unsigned w, unsigned h);
	static unsigned int defaultFBO();
	
	static float getHeightOfStringWithWidth(const char* str, float width);
	static void renderString(const char* str, unsigned char* buffer, float w, float h);
	
	double gamma();
	
private:
	
	Environment();
	~Environment();
	
	static Environment _instance;
	
	double _currentGamma;
	
};

#endif /* defined(__SpaceJunk__environment__) */
