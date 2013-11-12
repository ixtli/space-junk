//
//  JSManager.h
//  SpaceJunk
//
//  Created by ixtli on 11/3/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__JSManager__
#define __SpaceJunk__JSManager__

#include "IComponent.h"

class JSManager : public IComponent
{
public:
	
	/** @return the singleton instance */
	static inline JSManager* getInstance() { return &_instance; };
	
	// IComponent implementation
	void update(sjtime_t dt);
	bool init();
	
private:
	
	JSManager();
	virtual ~JSManager();
	
	/** The singleton instance */
	static JSManager _instance;
	
};

#endif /* defined(__SpaceJunk__JSManager__) */
