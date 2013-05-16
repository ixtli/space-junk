//
//  engine.h
//  Space Junk
//
//  Created by ixtli on 5/8/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __Space_Junk__engine__
#define __Space_Junk__engine__

class Engine
{
public:
	
	static Engine* getInstance();
	
	bool init();
	
private:
	
	Engine();
	~Engine();
	
	static Engine _instance;
	
};

#endif /* defined(__Space_Junk__engine__) */
