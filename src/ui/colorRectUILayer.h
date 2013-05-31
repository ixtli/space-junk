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

class ColorRectUILayer : public UILayer
{
public:
	
	ColorRectUILayer();
	~ColorRectUILayer();
	
	bool init();
	
private:
	
	ColorRectLayer _layer;
	ColorRect _r;
	
};

#endif /* defined(__SpaceJunk__colorRectUILayer__) */
