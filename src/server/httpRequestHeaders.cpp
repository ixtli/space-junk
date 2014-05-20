//
//  httpRequestHeaders.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/9/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include <string.h>

#include "stringUtil.h"

#include "httpRequestHeaders.h"

HTTPRequestHeaders::HTTPRequestHeaders() :

_hashHead(NULL),
_startLine(NULL)

{ }

HTTPRequestHeaders::~HTTPRequestHeaders()
{
	if (!_hashHead)
		return;
	
	HeaderField* el, *tmp;
	HASH_ITER(hh, _hashHead, el, tmp)
	{
		if (el == _hashHead) continue;
		if (el) delete el;
	}
	
	HASH_CLEAR(hh, _hashHead);
	delete _hashHead;
	_hashHead = NULL;
	
	if (_startLine)
	{
		delete [] _startLine;
	}
}

HTTPRequestHeaders::HeaderField::HeaderField(const char* name,
																						 const char* content)
{
	size_t nameLength = strlen(name);
	
	// Abort if no name to copy
	if (!nameLength)
	{
		return;
	}
	
	fieldName = new char[nameLength + 1];
	strcpy(fieldName, name);
	
	// There doesn't necessarily have to be content
	if (!content) return;
	
	const char* start = NULL;
	size_t contentLength = trimmedString(content, start);
	
	// It could be all whitespace!
	if (!contentLength) return;
	
	fieldContent = new char[contentLength + 1];
	memcpy(fieldContent, start, contentLength);
	fieldContent[contentLength] = '\0';
}

HTTPRequestHeaders::HeaderField::~HeaderField()
{
	if (fieldName)
		delete [] fieldName;
	
	if (fieldContent)
		delete [] fieldContent;
	
	fieldContent = NULL;
	fieldName = NULL;
}

bool HTTPRequestHeaders::init(char* request)
{
	char* lineSavePtr, *fieldSavePtr;
	char* line = strtok_r(request, "\n", &lineSavePtr);
	
	// Copy the start line ( GET /chat HTTP/1.1, etc. )
	size_t sll = strlen(line);
	_startLine = new char[sll + 1];
	strcpy(_startLine, line);
	_startLine[sll] = '\0';
	
	// Process the fields
	while ((line = strtok_r(NULL, "\n", &lineSavePtr)) != NULL)
	{
		char* fieldName = strtok_r(line, ":", &fieldSavePtr);
		char* fieldContent = strtok_r(NULL, ":", &fieldSavePtr);
		HeaderField* n = new HeaderField(fieldName, fieldContent);
		
		// If it's a bad line, ignore it.
		if (!n->fieldName)
		{
			delete n;
			continue;
		}
		
		// Add it to the hash for quick lookup
		HASH_ADD_KEYPTR(hh, _hashHead, n->fieldName, strlen(n->fieldName), n);
	}
	
	return true;
}

const char* HTTPRequestHeaders::header(const char* name) const
{
	HeaderField* found = NULL;
	HASH_FIND(hh, _hashHead, name, strlen(name), found);
	return found ? found->fieldContent : NULL;
}

