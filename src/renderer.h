//
//  renderer.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__renderer__
#define __SpaceJunk__renderer__

#include "geometry.h"

class Renderer
{
public:
	
	inline static Renderer* getInstance() { return &_instance; };
	
	bool initialize(GLuint defaultFBO);
	void resize(const Size2D& newBounds);
	void render();
	
private:
	
	Renderer();
	~Renderer();
	
	Size2D bounds;
	GLuint defaultFBOName;
	
	void resetGL();
	
	static Renderer _instance;
	
};

#endif /* defined(__SpaceJunk__renderer__) */
