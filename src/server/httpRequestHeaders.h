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
	inline size_t headerCount() const { return _headerCount; };
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
	
	size_t _headerCount;
	HeaderField* _hashHead;
	HeaderField** _headerList;
};

#endif /* defined(__SpaceJunk__httpRequestHeaders__) */
