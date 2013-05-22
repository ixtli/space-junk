//
//  uiManager.h
//  SpaceJunk
//
//  Created by ixtli on 5/21/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiManager__
#define __SpaceJunk__uiManager__

class UILayer;

class UIManager
{
public:
	
	static UIManager* getInstance() { return &_instance; };
	
	bool init();
	
private:
	
	UIManager();
	~UIManager();
	
	static UIManager _instance;
	
};

#endif /* defined(__SpaceJunk__uiManager__) */
