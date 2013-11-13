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
#include "colorRectLayer.h"

class UIColorRectElement : public UIElement
{
public:
	
	UIColorRectElement();
	UIColorRectElement(const RectI& rect, GLfloat depth);
	UIColorRectElement(const RectI& rect, const Color4u& color, GLfloat depth);
	~UIColorRectElement();
	
	const Color4u* color() const { return &_color; };
	
	inline void red(GLubyte r) { _color.r = r; makeDirty(); };
	inline void green(GLubyte g) { _color.g = g; makeDirty(); };
	inline void blue(GLubyte b) { _color.b = b; makeDirty(); };
	inline void alpha(GLubyte a) { _color.a = a; makeDirty(); };
	
	void rgba(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	
	virtual void update(sjtime_t dt);
	
	ColorRect* layerRect() { return &_layerRect; };
	
private:
	
	Color4u _color;
	ColorRect _layerRect;
	
};

#endif /* defined(__SpaceJunk__uiColorRectElement__) */
