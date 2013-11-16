//
//  uiColorRectLayer.h
//  SpaceJunk
//
//  Created by ixtli on 5/31/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiColorRectLayer__
#define __SpaceJunk__uiColorRectLayer__

#include "rectLayer.h"
#include "uiLayer.h"
#include "uiColorRectElement.h"

class UIColorRectLayer : public UILayer
{
public:
	
	UIColorRectLayer();
	virtual ~UIColorRectLayer();
	
	virtual bool init(uint32_t initialCount);
	
	virtual void draw() const { _layer.draw(); };
	virtual void depth(uint32_t d) { _depth = d; };
	virtual void update(sjtime_t dt);
	virtual bool addElement(UIElement* e) { return false; };
	virtual bool removeElement(UIElement* e) { return false; };
	
private:
	
	void randomRect();
	
	RectLayer<UIColorRectElement, ColorVertex> _layer;
	
};

#endif /* defined(__SpaceJunk__uiColorRectLayer__) */
