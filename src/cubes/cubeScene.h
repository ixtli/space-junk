//
//  cubescene.h
//  SpaceJunk
//
//  Created by ixtli on 8/11/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__cubeScene__
#define __SpaceJunk__cubeScene__

class CubeScene
{
public:
	
	inline static CubeScene* instance() { return &_instance; };
	
	bool init();
	
private:
	
	CubeScene();
	~CubeScene();
	
	static CubeScene _instance;
	
};

#endif /* defined(__SpaceJunk__cubescene__) */
