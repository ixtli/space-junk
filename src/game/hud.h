//
//  hud.h
//  SpaceJunk
//
//  Created by ixtli on 6/17/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__hud__
#define __SpaceJunk__hud__

#include "uiColorRectLayer.h"

class HUD
{
public:
	
	HUD();
	~HUD();
	
	bool init();
	
private:
	
	UIColorRectLayer _colorLayer;
	
};

#endif /* defined(__SpaceJunk__hud__) */
