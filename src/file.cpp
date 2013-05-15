//
//  file.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/13/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "environment.h"
#include "file.h"

File::File() : _path(NULL), _contents(NULL), _length(0), _loaded(false)
{}

File::~File()
{
	cleanUp();
}

inline void File::cleanUp()
{
	if (_path) delete [] _path;
	if (_contents) delete [] _contents;
	_path = NULL;
	_contents = NULL;
}

bool File::init(const char* name, const char* ext)
{
	if (_loaded) return false;
	
	cleanUp();
	
	_path = Environment::newPathForFile(name, ext);
	
	if (!_path)
	{
		return false;
	}
		
	// Open file for reading
	FILE* current;
	current = fopen(_path, "r");
	if (!current)
	{
		return false;
	}
	
	// Measure file length
	fseek(current, 0, SEEK_END);
	long fileLen = ftell(current);
	if (fileLen < 1)
	{
		// either an empy file or an error, so either way error
		fclose(current);
		return false;
	}
	
	_length = (size_t)fileLen;
	rewind(current);
	
	// Allocate and check contents
	_contents = new char[_length];
	if (!_contents)
	{
		fclose(current);
		return false;
	}
	
	// attempt read then immediately close the file
	size_t len = fread(_contents, 1, _length, current);
	fclose(current);
	if (len != _length)
	{
		return false;
	}
	
	_loaded = true;
	return true;
}


