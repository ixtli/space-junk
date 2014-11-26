//
//  pngUtil.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/24/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include <stdio.h>

#include "environment.h"
#include "log.h"
#include "pngUtil.h"

#define IF_PNG_ERROR() if(setjmp(png_jmpbuf(png_ptr)))


PNGWrapper::PNGWrapper() :

_hasBackground(false),
_bgRed(0),
_bgGreen(0),
_bgBlue(0),

_width(0),
_height(0),
_bitDepth(0),
_colorType(0),
_interlaceMethod(0),
_compressionMethod(0),
_filterMethod(0),
_channels(0),
_data(NULL)

{}

PNGWrapper::~PNGWrapper()
{
	if (_data) delete [] _data;
}

void PNGWrapper::logPNGVersionInfo()
{
	info("libpng %s, using %s.", PNG_LIBPNG_VER_STRING, png_libpng_ver);
}

bool PNGWrapper::init(const char *fileName)
{
	// Define everything at top so that initialization is never skipped.
	// This is why you never use gotos.
	bool success = false;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	
	char* path = Environment::newPathForFile(fileName, "png");
	
	if (!path)
	{
		error("Couldn't get path: %s", fileName);
		return false;
	}
	
	// Open file for reading
	FILE* current = NULL;
	current = fopen(path, "rb");
	
	if (!current)
	{
		error("Couldn't open file: %s", fileName);
		goto CLEANUP;
	}
	
	// Read the signature
	unsigned char sig[8];
	fread(sig, 1, 8, current);
	
	if (!png_check_sig(sig, 8))
	{
		error("Invalid PNG signature: %s", fileName);
		goto CLEANUP;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	
	if (!png_ptr)
	{
		error("Out of memory.");
		goto CLEANUP;
	}
	
	info_ptr = png_create_info_struct(png_ptr);
	
	if (!info_ptr)
	{
		error("Out of memory.");
		goto CLEANUP;
	}

	// It gets a little... odd from here. For more information, check out
	// http://www.libpng.org/pub/png/book/chapter13.html it's pretty interesting.
	IF_PNG_ERROR()
	{
		error("Unknown PNG error.");
		goto CLEANUP;
	}
	
	if (!readMeta(current, png_ptr, info_ptr))
	{
		goto CLEANUP;
	}

	// Apparntly the PNG file format has the ability to specify a background
	if (!readBackground(png_ptr, info_ptr))
	{
		goto CLEANUP;
	}
	
	if (!readData(current, png_ptr, info_ptr))
	{
		goto CLEANUP;
	}
	
	success = true;
	
CLEANUP:
	delete [] path;
	fclose(current);
	
	if (png_ptr && !info_ptr)
		png_destroy_read_struct(&png_ptr, NULL, NULL);
	else if (png_ptr && info_ptr)
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	
	return success;
}

bool PNGWrapper::readBackground(png_structp png_ptr, png_infop info_ptr)
{
	
	IF_PNG_ERROR()
	{
		return false;
	}
	
	// Does it have an info chunk for defining bg color?
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_bKGD))
	{
		_hasBackground = true;
		png_color_16p pBackground = NULL;
		png_get_bKGD(png_ptr, info_ptr, &pBackground);
		
		if (_bitDepth == 16)
		{
			_bgRed = pBackground->red >> 8;
			_bgGreen = pBackground->green >> 8;
			_bgBlue = pBackground->blue >> 8;
		} else if (_colorType == PNG_COLOR_TYPE_GRAY && _bitDepth < 8) {
			if (_bitDepth == 1)
				_bgRed = _bgBlue = _bgGreen = pBackground->gray ? 255 : 0;
			else if (_bitDepth == 2)
				_bgRed = _bgBlue = _bgGreen = (unsigned char)((255/3) * pBackground->gray);
			else // bit depth == 4
				_bgRed = _bgBlue = _bgGreen = (unsigned char)((255/15) * pBackground->gray);
		} else {
			_bgRed = (unsigned char)pBackground->red;
			_bgGreen = (unsigned char)pBackground->green;
			_bgBlue = (unsigned char)pBackground->blue;
		}
	}
	
	return true;
}

bool PNGWrapper::readData(FILE *f, png_structp png_ptr, png_infop info_ptr)
{
	IF_PNG_ERROR()
	{
		if (_data) delete [] _data;
		return false;
	}
	
	// Handle multiple types of color
	if (_colorType == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);
	if (_colorType == PNG_COLOR_TYPE_GRAY && _bitDepth < 8)
		png_set_expand_gray_1_2_4_to_8(png_ptr);
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);

	// It's possible to provide 16 and 24-bit rgb, but we want to ignore these
	// possibilities, and the library give us a way to do that.
	if (_bitDepth == 16)
		png_set_strip_16(png_ptr);
	if (_colorType == PNG_COLOR_TYPE_GRAY ||
			_colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
		png_set_gray_to_rgb(png_ptr);
	
	// Retrieve system gamma
	double screen_gamma = Environment::getInstance()->gamma();
	
	// According to various tutorials, this is the least harmful way to
	// potentially override the gamma and to be nice of the image tries to
	// set its own gamma settings.
	double gamma;
	if (png_get_gAMA(png_ptr, info_ptr, &gamma))
		png_set_gamma(png_ptr, screen_gamma, gamma);
	
	png_bytep row_pointers[_height];
	
	png_read_update_info(png_ptr, info_ptr);
	
	size_t rowbytes = png_get_rowbytes(png_ptr, info_ptr);
	_channels = (unsigned int)png_get_channels(png_ptr, info_ptr);
	
	_data = new unsigned char[rowbytes * _height];
	
	if (!_data)
	{
		error("Couldn't allocate memory.");
		return false;
	}
	
	// The file is read by pointers to rows of data which allows for some
	// convenience, should you do things like interlacing or whatever. But for
	// now, they're just pointers to our big contiguous chunk we just allocated
	for (size_t i = 0; i < _height; i++)
	{
		row_pointers[i] = _data + i * rowbytes;
	}
	
	png_read_image(png_ptr, row_pointers);
	
	png_read_end(png_ptr, NULL);
	
	return true;
}

bool PNGWrapper::readMeta(FILE *f, png_structp png_ptr, png_infop info_ptr)
{
	IF_PNG_ERROR()
	{
		return false;
	}
	
	// Finally, read the actual PNG
	png_init_io(png_ptr, f);
	png_set_sig_bytes(png_ptr, 8);
	png_read_info(png_ptr, info_ptr);
	
	// Get image metrics
	png_get_IHDR(png_ptr, info_ptr, &_width, &_height, &_bitDepth, &_colorType,
							 &_interlaceMethod, &_compressionMethod, &_filterMethod);
	
	return true;
}



