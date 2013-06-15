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

class ColorRectUIElement : public UIElement
{
public:
	
	ColorRectUIElement();
	ColorRectUIElement(const Rect2Di& rect, GLfloat depth);
	ColorRectUIElement(const Rect2Di& rect, const Color4u& color, GLfloat depth);
	~ColorRectUIElement();
	
	const Color4u* color() const { return &_color; };
	
	inline void red(GLushort r) { _color.r = r; };
	inline void green(GLushort g) { _color.g = g; };
	inline void blue(GLushort b) { _color.b = b; };
	inline void alpha(GLushort a) { _color.a = a; };
	
	void rgba(GLushort r, GLushort g, GLushort b, GLushort a);
	
	virtual void update() {};
	
	ColorRect* layerRect() { return &_layerRect; };
	
private:
	
	Color4u _color;
	ColorRect _layerRect;
	
};

#endif /* defined(__SpaceJunk__uiColorRectElement__) */
