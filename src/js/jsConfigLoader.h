//
//  jsConfigLoader.h
//  SpaceJunk
//
//  Created by ixtli on 12/27/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__jsConfigLoader__
#define __SpaceJunk__jsConfigLoader__

class JSConfigLoader
{
public:
	
	JSConfigLoader();
	~JSConfigLoader();
	
	bool init();
	
private:
	
	constexpr static const char * CONFIG_NAME = "config";
	
};

#endif /* defined(__SpaceJunk__jsConfigLoader__) */
