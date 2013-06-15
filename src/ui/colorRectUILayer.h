//
//  colorRectUILayer.h
//  SpaceJunk
//
//  Created by ixtli on 5/31/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__colorRectUILayer__
#define __SpaceJunk__colorRectUILayer__

#include "colorRectLayer.h"
#include "uiLayer.h"
#include "uiColorRectElement.h"

class ColorRectUILayer : public UILayer
{
public:
	
	ColorRectUILayer();
	~ColorRectUILayer();
	
	bool init();
	
	void addElement(UIElement* e);
	void removeElement(UIElement* e);
	
private:
	
	ColorRectLayer _layer;
	
	ColorRectUIElement _r;
	
};

#endif /* defined(__SpaceJunk__colorRectUILayer__) */
