//
//  file.h
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__file__
#define __SpaceJunk__file__

#include <stddef.h>

class File
{
public:
	
	File();
	~File();
	
	bool init(const char* name, const char* ext);
	
	// Accessors
	inline const char* contents() const { return _contents; };
	inline size_t lenght() const { return _length; };
	inline bool loaded() const { return _loaded; };
	
private:
	
	char* _path;
	char* _contents;
	size_t _length;
	bool _loaded;
	
	void cleanUp();
	
};

#endif /* defined(__SpaceJunk__file__) */
