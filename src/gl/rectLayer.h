//
//  rectLayer.h
//  SpaceJunk
//
//  Created by ixtli on 5/30/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__rectLayer__
#define __SpaceJunk__rectLayer__

#include "quadLayer.h"

class RectLayer
{
public:
	
	static const GLuint MAX_RECTS = 0xFFF0;
	
	RectLayer(bool dynamic = false);
	~RectLayer();
	
	bool init(GLfloat depth, GLuint rectCount);
	
	// Inline render functions
	inline void draw() const { _quadLayer.draw(); };
	
	// Inline getters and setters
	inline GLuint used() const { return _usedRects; };
	
protected:
	
	GLfloat _depth;
	GLuint _maxRects;
	GLuint _usedRects;
	
	QuadLayer _quadLayer;
	
};

#endif /* defined(__SpaceJunk__rectLayer__) */
