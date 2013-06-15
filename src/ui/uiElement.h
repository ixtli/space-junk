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

class UIElement
{
public:
	
	UIElement();
	UIElement(const Rect2Di& rect);
	UIElement(const Rect2Di& rect, GLfloat depth);
	
	~UIElement();
	
	virtual void update() = 0;
	
	// set functions
	inline void width(GLuint width) { _rect.bounds.width = width; };
	inline void height(GLuint height) { _rect.bounds.height = height; };
	inline void top(GLuint top) { _rect.position.y = top; };
	inline void left(GLuint left) { _rect.position.x = left; };
	inline void depth(GLfloat d) { _depth = d; };
	
	// Getters
	inline const Rect2Di* rect() const { return &_rect; };
	inline const Size2Di* size() const { return &_rect.bounds; };
	inline const Point2Di* position() const { return &_rect.position; };
	inline const GLfloat depth() const { return _depth; };
	
protected:
	
	Rect2Di _rect;
	GLfloat _depth;
	
};

#endif /* defined(__SpaceJunk__uiElement__) */
