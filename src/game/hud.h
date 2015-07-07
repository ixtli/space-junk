//
//  hud.h
//  SpaceJunk
//
//  Created by ixtli on 6/17/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__hud__
#define __SpaceJunk__hud__

#include "../ui/uiColorRectLayer.h"

#include "../engine/Easer.h"

class HUD
{
public:
	
	HUD();
	~HUD();
	
	bool init();
	
	void update(sj_time_t dt);
	
private:
	
	UIColorRectLayer _colorLayer;
	Easer<GLuint> _easer;
	UIColorRectElement* _elt;
};

#endif /* defined(__SpaceJunk__hud__) */
