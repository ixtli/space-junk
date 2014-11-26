//
//  pngUtil.h
//  SpaceJunk
//
//  Created by ixtli on 11/24/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__pngUtil__
#define __SpaceJunk__pngUtil__

#include <stdlib.h>

#include "png.h"

class PNGWrapper
{
public:
	
	static void logPNGVersionInfo();
	
	PNGWrapper();
	~PNGWrapper();
	
	bool init(const char* fileName);
	
	inline uint_fast32_t width() const { return _width; };
	inline uint_fast32_t height() const { return _height; };
	inline unsigned int channels() const { return _channels; };
	inline int bitDepth() const { return _bitDepth; };
	inline const unsigned char* data() const { return _data; };
	
private:
	
	bool readMeta(FILE* f, png_structp png_ptr, png_infop info_ptr);
	bool readData(FILE* f, png_structp png_ptr, png_infop info_ptr);
	bool readBackground(png_structp png_ptr, png_infop info_ptr);
	
	// background
	bool _hasBackground;
	unsigned char _bgRed;
	unsigned char _bgGreen;
	unsigned char _bgBlue;
	
	// File metrics
	uint_fast32_t _width;
	uint_fast32_t _height;
	int _bitDepth;
	int _colorType;
	int _interlaceMethod;
	int _compressionMethod;
	int _filterMethod;
	
	unsigned int _channels;
	
	// Contents
	unsigned char* _data;
};

void readPNGInit(const char* fileName);

#endif /* defined(__SpaceJunk__pngUtil__) */
