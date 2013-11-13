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
	UIElement(const RectI& rect);
	UIElement(const RectI& rect, GLfloat depth);
	
	~UIElement();
	
	virtual void update(sjtime_t dt) = 0;
	
	/** Call this after you write the state to the gfx card. */
	inline void hasComitted() { setClean(); };
	
	// set functions
	inline void width(GLuint width) { _rect.bounds.width = width; makeDirty(); };
	inline void height(GLuint height) {_rect.bounds.height = height; makeDirty();};
	inline void top(GLuint top) { _rect.position.y = top; makeDirty(); };
	inline void left(GLuint left) { _rect.position.x = left; makeDirty(); };
	inline void depth(GLfloat d) { _depth = d; makeDirty(); };
	inline void makeDirty() { _dirty = true; };
	
	// Getters
	inline const RectI* rect() const { return &_rect; };
	inline const Size2I* size() const { return &_rect.bounds; };
	inline const Point2I* position() const { return &_rect.position; };
	inline const GLfloat depth() const { return _depth; };
	inline bool dirty() const { return _dirty; };
	
protected:
	
	void setClean() { _dirty = false; };
	
	RectI _rect;
	GLfloat _depth;
	bool _isAnimating;
	
private:
	
	bool _dirty;
	
};

#endif /* defined(__SpaceJunk__uiElement__) */
