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

Logger Logger::_instance;

Logger::Logger()
{
	log("Opening log. %f", 0.5f);
}

Logger::~Logger()
{
	log("Closing log.");
}

void Logger::write(LogLevels level, const char* format, ...)
{
	// 21st century c
	va_list ap;
	va_start(ap, format);
	vfprintf(level == LOG_ERROR ? stderr : stdout, format, ap);
	va_end(ap);
}