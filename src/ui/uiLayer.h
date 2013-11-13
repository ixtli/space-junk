//
//  uiLayer.h
//  SpaceJunk
//
//  Created by ixtli on 5/30/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiLayer__
#define __SpaceJunk__uiLayer__

#include "uiElement.h"
#include "rectLayer.h"

class UILayer
{
public:
	
	UILayer(RectLayer* layer);
	~UILayer();
	
	inline void draw() const { _layer->draw(); };
	
	void update(sjtime_t dt);
	void depth(uint32_t d);
	
	inline uint32_t depth() const { return _depth; };
	
	bool addElement(UIElement* e);
	bool removeElement(UIElement* e);
	
protected:
	
	UIElement** _elementList;
	size_t _elementCount;
	
	uint32_t _depth;
	
private:
	
	RectLayer* _layer;
	
};

#endif /* defined(__SpaceJunk__uiLayer__) */
