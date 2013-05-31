//
//  uiLayer.h
//  SpaceJunk
//
//  Created by ixtli on 5/30/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__uiLayer__
#define __SpaceJunk__uiLayer__

class UILayer
{
public:
	
	UILayer();
	~UILayer();
	
	bool init(unsigned elementCount);
	
private:
	
	unsigned _elementCount;
	
};

#endif /* defined(__SpaceJunk__uiLayer__) */
