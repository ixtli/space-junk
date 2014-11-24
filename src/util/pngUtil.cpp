//
//  pngUtil.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/24/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "png.h"
#include "log.h"
#include "pngUtil.h"

void logPNGVersionInfo()
{
	info("libpng %s, using %s.", PNG_LIBPNG_VER_STRING, png_libpng_ver);
}
