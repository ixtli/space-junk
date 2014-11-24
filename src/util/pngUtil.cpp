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

#include "png.h"

void logPNGVersionInfo()
{
	info("libpng %s, using %s.", PNG_LIBPNG_VER_STRING, png_libpng_ver);
}

void readPNGInit(const char* fileName)
{
	char* path = Environment::newPathForFile(fileName, "png");
	
	if (!path)
	{
		error("Couldn't open file: %s", fileName);
		return;
	}
	
	// Open file for reading
	FILE* current = NULL;
	current = fopen(path, "rb");
	
	if (!current)
	{
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
	
	// Clean up
CLEANUP:
	if (current) fclose(current);
	if (path) delete [] path;
}
