//
//  IComponent.h
//  SpaceJunk
//
//  Created by ixtli on 11/3/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef SpaceJunk_IComponent_h
#define SpaceJunk_IComponent_h

#include <stdlib.h>

class IComponent
{
public:
	virtual ~IComponent() {};
	virtual bool init() = 0;
	virtual void update(uint32_t dt) = 0;
};

#endif
