//
//  uiColorRectElement.h
//  SpaceJunk
//
//  Created by Ixtli on 6/2/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiColorRectElement__
#define __SpaceJunk__uiColorRectElement__

#include "color.h"
#include "uiElement.h"

class UIColorRectElement : public UIElement
{
public:
	
	UIColorRectElement();
	
	UIColorRectElement& operator=(const UIColorRectElement& c);
	
	const Color4u* color() const { return &_color; };
	
	// Setters
	inline void red(GLubyte r) { _color.r = r; makeDirty(); };
	inline void green(GLubyte g) { _color.g = g; makeDirty(); };
	inline void blue(GLubyte b) { _color.b = b; makeDirty(); };
	inline void alpha(GLubyte a) { _color.a = a; makeDirty(); };
	void rgba(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	
	void updateVerts(GLfloat baseDepth, ColorVertex* verts) const;
	
private:
	
	Color4u _color;
	
};

#endif /* defined(__SpaceJunk__uiColorRectElement__) */
