//
//  httpRequestHeaders.h
//  SpaceJunk
//
//  Created by ixtli on 5/9/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__httpRequestHeaders__
#define __SpaceJunk__httpRequestHeaders__

#include "uthash.h"

class HTTPRequestHeaders
{
public:
	
	HTTPRequestHeaders();
	~HTTPRequestHeaders();
	
	bool init(char* request);
	const char* header(const char* name) const;
	const char* startLine() const { return _startLine; };
	
private:
	
	typedef struct HeaderField
	{
		char* fieldName = NULL;
		char* fieldContent = NULL;
		
		HeaderField(const char* name, const char* content);
		~HeaderField();
		
		// Make the structure hashable under UT.
		UT_hash_handle hh;
		
	} HeaderField;
	
	char* _startLine;
	HeaderField* _hashHead;
	size_t _count;
	HeaderField** _list;
};

#endif /* defined(__SpaceJunk__httpRequestHeaders__) */
