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
	log("Opening log.");
}

Logger::~Logger()
{
	log("Closing log.");
}

void Logger::write(LogLevels level,
								const char * function,
								const char * file,
								unsigned int line,
								const char * format,
								...)
{
	// stackoverflow.com/questions/8487986/file-macro-shows-full-path
	const char* last = strrchr(file, '/') ? strrchr(file, '/') + 1 : file;
	
	// 21st century c
	printf("%s (%s:%u) ", function, last, line);
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
	printf("\n");
}