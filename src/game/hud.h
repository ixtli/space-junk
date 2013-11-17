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

#include "Easer.h"

class HUD
{
public:
	
	HUD();
	~HUD();
	
	bool init();
	
	void update(sjtime_t dt);
	
private:
	
	UIColorRectLayer _colorLayer;
	Easer _easer;
	UIColorRectElement* _elt;
};

#endif /* defined(__SpaceJunk__hud__) */
