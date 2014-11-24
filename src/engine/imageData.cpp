//
//  imageData.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/23/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "imageData.h"

ImageData::ImageData(unsigned w, unsigned h) :

_width(w),
_height(h),
_data(NULL)

{}

ImageData::~ImageData()
{
	if (_data)
	{
		delete [] _data;
		_data = NULL;
	}
}

bool ImageData::init()
{
	_data = new unsigned char[_width * _height];
	
	return (_data != NULL);
}
