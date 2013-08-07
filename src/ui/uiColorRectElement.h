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
	
	inline void red(GLubyte r) { _color.r = r; };
	inline void green(GLubyte g) { _color.g = g; };
	inline void blue(GLubyte b) { _color.b = b; };
	inline void alpha(GLubyte a) { _color.a = a; };
	
	void rgba(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	
	virtual void update() {};
	
	ColorRect* layerRect() { return &_layerRect; };
	
private:
	
	Color4u _color;
	ColorRect _layerRect;
	
};

#endif /* defined(__SpaceJunk__uiColorRectElement__) */
