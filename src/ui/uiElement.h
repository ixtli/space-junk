//
//  uiElement.h
//  SpaceJunk
//
//  Created by ixtli on 5/31/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiElement__
#define __SpaceJunk__uiElement__

#include "geometry.h"

#include "glutil.h"

class UIElement
{
public:
	
	UIElement();
	~UIElement();
	
	UIElement& operator=(const UIElement& e);
	
	// set functions
	inline void width(GLuint width) { _rect.bounds.width = width; };
	inline void height(GLuint height) {_rect.bounds.height = height; };
	inline void top(GLuint top) { _rect.position.y = top; };
	inline void left(GLuint left) { _rect.position.x = left; };
	inline void depth(GLfloat d) { _depthOffset = d; };
	inline void index(GLuint i) { _index = i; };
	
	// Getters
	inline const RectI* rect() const { return &_rect; };
	inline const Size2I* size() const { return &_rect.bounds; };
	inline const Point2I* position() const { return &_rect.position; };
	inline const GLfloat depth() const { return _depthOffset; };
	inline GLuint index() const { return _index; };
	
protected:
	
	RectI _rect;
	GLuint _index;
	GLfloat _depthOffset;
	
};

#endif /* defined(__SpaceJunk__uiElement__) */
