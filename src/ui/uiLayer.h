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
	
	UILayer() : _depth(0) {};
	virtual ~UILayer() {};
	
	virtual bool init(uint32_t initialCount) = 0;
	virtual void draw() const = 0;
	virtual void update(sjtime_t dt) = 0;
	virtual void depth(uint32_t d) = 0;
	virtual bool addElement(UIElement* e) = 0;
	virtual bool removeElement(UIElement* e) = 0;
	
	inline uint32_t depth() const { return _depth; };
	
protected:
	
	uint32_t _depth;
	
};

#endif /* defined(__SpaceJunk__uiLayer__) */
