//
//  uiColorRectLayer.h
//  SpaceJunk
//
//  Created by ixtli on 5/31/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiColorRectLayer__
#define __SpaceJunk__uiColorRectLayer__

#include "colorRectLayer.h"
#include "uiLayer.h"
#include "uiColorRectElement.h"

class UIColorRectLayer : public UILayer
{
public:
	
	UIColorRectLayer();
	~UIColorRectLayer();
	
	bool init();
	
	void addElement(UIElement* e);
	void removeElement(UIElement* e);
	
private:
	
	ColorRectLayer _layer;
	
	ColorRectUIElement _r;
	
};

#endif /* defined(__SpaceJunk__uiColorRectLayer__) */
