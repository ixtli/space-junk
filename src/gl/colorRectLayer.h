//
//	colorRectLayer.h
//	SpaceJunk
//
//	Created by Ixtli on 5/24/13.
//	Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__colorRectLayer__
#define __SpaceJunk__colorRectLayer__

#include "rectLayer.h"

struct ColorRect
{
	ColorRect(const RectI* r, const Color4u* c, GLfloat d) :
		rect(r), color(c), depthOffset(d), index(0) {}
	
	const RectI* rect;
	const Color4u* color;
	
	GLfloat depthOffset;
	GLuint index;
};

class ColorRectLayer : public RectLayer
{
public:
	
	ColorRectLayer(bool dynamic = true);
	~ColorRectLayer();
	
	bool init(GLfloat depth, GLuint rectCount);
	
	// "CRUD" functions
	bool addRect(ColorRect* r); // bwa: O(1)
	bool removeRect(const ColorRect& r); // w: O(n), n == (_usedRects - 1)
	void updateRect(const ColorRect& r);
	
	virtual void commit();
	
private:
	
	inline void updateVertsForIndex(GLuint index);
	inline void listChanged() { _dirty = true; };
	
	bool initLayer();
	
	ColorRect** _list;
	ColorVertex* _verts;
	
	bool _dirty;
	bool _initialized;
	
};

#endif /* defined(__SpaceJunk__colorRectLayer__) */
