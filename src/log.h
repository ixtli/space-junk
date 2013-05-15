//
//  log.h
//  SpaceJunk
//
//  Created by ixtli on 5/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__log__
#define __SpaceJunk__log__

#define LOGMETA "[%s(%s:%u)] "

// stackoverflow.com/questions/8487986/file-macro-shows-full-path
#define FILENM (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// with help from 21st Century C by O'Reilly
#ifdef DEBUG

#define log(fmt, ...)																								\
	Logger::getInstance()->write(Logger::LOG_INFO, LOGMETA fmt "\n",	\
	__FUNCTION__,	FILENM, __LINE__, ##__VA_ARGS__)

#define warn(fmt, ...)																							\
	Logger::getInstance()->write(Logger::LOG_WARN, LOGMETA fmt "\n",	\
	__FUNCTION__,	FILENM, __LINE__, ##__VA_ARGS__)

#else
#define log(fmt, ...) {}
#endif

#define error(fmt, ...)																							\
	Logger::getInstance()->write(Logger::LOG_ERROR, LOGMETA fmt "\n",	\
	__FUNCTION__,	FILENM, __LINE__, ##__VA_ARGS__)

class Logger
{
public:
	
	typedef enum
	{
		LOG_ERROR,
		LOG_WARN,
		LOG_INFO
	} LogLevels;
	
	inline static Logger* getInstance() { return &_instance; };
	
	__attribute__ ((__format__ (__printf__, 3, 4)))
	void write(LogLevels level, const char* format, ...);
	
private:
	
	Logger();
	~Logger();
	
	static Logger _instance;
	
};

#endif /* defined(__SpaceJunk__log__) */
