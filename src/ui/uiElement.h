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
	
	UIElement& operator=(const UIElement& e);
	
	// set functions
	inline void width(GLuint width) { _rect.bounds.width = width; makeDirty(); };
	inline void height(GLuint height) {_rect.bounds.height = height; makeDirty(); };
	inline void top(GLuint top) { _rect.position.y = top; makeDirty(); };
	inline void left(GLuint left) { _rect.position.x = left; makeDirty(); };
	inline void index(GLuint i) { _index = i; makeDirty(); };
	inline void makeDirty() { _dirty = true; };
	inline void makeClean() { _dirty = false; };
	
	// Getters
	inline const RectI* rect() const { return &_rect; };
	inline const Size2I* size() const { return &_rect.bounds; };
	inline const Point2I* position() const { return &_rect.position; };
	inline GLuint index() const { return _index; };
	inline bool dirty() const { return _dirty; };
	
protected:
	
	RectI _rect;
	GLuint _index;
	bool _dirty;
	
};

#endif /* defined(__SpaceJunk__uiElement__) */
