//
//	colorRectLayer.h
//	SpaceJunk
//
//	Created by Ixtli on 5/24/13.
//	Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__colorRectLayer__
#define __SpaceJunk__colorRectLayer__

#include "quadLayer.h"

struct ColorRect
{
	ColorRect() :
		rect(), color(), depthOffset(0.0f), index(0xFFFF) {};
	
	ColorRect(const Rect2Di& r) :
		rect(r), color(), depthOffset(0.0f), index(0xFFFF) {};
	
	ColorRect(const Color4u& c) :
		color(c), rect(), depthOffset(0.0f), index(0xFFFF) {};
	
	ColorRect(const Rect2Di& r, const Color4u& c) :
		rect(r), color(c), depthOffset(0.0f), index(0xFFFF) {};
	
	Rect2Di rect;
	Color4u color;
	GLfloat depthOffset;
	GLuint index;
};

class ColorRectLayer
{
public:
	
	static const GLuint MAX_RECTS = 0xFFF0;
	
	ColorRectLayer(bool dynamic = true);
	~ColorRectLayer();
	
	bool init(GLfloat depth, GLuint rectCount);
	
	// "CRUD" functions
	bool addRect(ColorRect* r); // bwa: O(1)
	bool removeRect(const ColorRect& r); // w: O(n), n == _usedRects - r->index
	void updateRect(const ColorRect& r);
	
	void commit();
	
	// Inline render functions
	inline void draw() const { _quadLayer.draw(); };
	
	// Inline getters and setters
	inline GLuint used() const { return _usedRects; };
	
private:
	
	inline void updateVertsForIndex(GLuint index);
	inline void listChanged() { _dirty = true; };
	
	bool initLayer();
	
	GLfloat _depth;
	GLuint _maxRects;
	GLuint _usedRects;
	
	ColorRect** _list;
	ColorVertex* _verts;
	
	bool _dirty;
	bool _initialized;
	QuadLayer _quadLayer;
	
};

#endif /* defined(__SpaceJunk__colorRectLayer__) */
