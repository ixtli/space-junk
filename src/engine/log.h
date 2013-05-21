//
//  log.h
//  SpaceJunk
//
//  Created by ixtli on 5/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __SpaceJunk__log__
#define __SpaceJunk__log__

#include <string.h>

#define ERRORMETA "ERROR: "
#define WARNMETA "WARNING: "
#define LOGMETA "[%s(%s:%u)] "

// stackoverflow.com/questions/8487986/file-macro-shows-full-path
#define FILENAME (strrchr(__FILE__,'/') ? strrchr(__FILE__,'/') + 1 : __FILE__)

// with help from 21st Century C by O'Reilly
#ifdef DEBUG

#define log(fmt, ...)																													\
	logToLog(LOGMETA fmt "\n",																									\
	__FUNCTION__,	FILENAME, __LINE__, ##__VA_ARGS__)

__attribute__ ((__format__ (__printf__, 1, 2)))
void logToLog(const char* format, ...);

#else
#define log(fmt, ...) {}
#endif

#define warn(fmt, ...)																												\
	warnToLog(WARNMETA LOGMETA fmt "\n",																				\
	__FUNCTION__,	FILENAME, __LINE__, ##__VA_ARGS__)

__attribute__ ((__format__ (__printf__, 1, 2)))
void warnToLog(const char* format, ...);

#define error(fmt, ...)																												\
	errorToLog(ERRORMETA LOGMETA fmt "\n",																			\
	__FUNCTION__,	FILENAME, __LINE__, ##__VA_ARGS__)

__attribute__ ((__format__ (__printf__, 1, 2)))
void errorToLog(const char* format, ...);

#endif /* defined(__SpaceJunk__log__) */

#ifdef __cplusplus
}
#endif

