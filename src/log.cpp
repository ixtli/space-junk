//
//  log.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include <stdio.h>
#include <stdarg.h>

#include "log.h"

void logToLog(const char* format, ...)
{
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
}

void warnToLog(const char* format, ...)
{
	// TODO: handle non-debug case
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
}

void errorToLog(const char* format, ...)
{
	// TODO: handle non-debug case
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
}