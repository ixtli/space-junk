//
//  log.h
//  SpaceJunk
//
//  Created by ixtli on 5/14/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__log__
#define __SpaceJunk__log__

// with help from 21st Century C by O'Reilly
#define log(fmt, ...)																						\
	Logger::getInstance()->write(Logger::LOG_INFO,								\
	__FUNCTION__,	__FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define warn(fmt, ...)																					\
	Logger::getInstance()->write(Logger::LOG_WARN,								\
	__FUNCTION__,	__FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define error(fmt, ...)																					\
	Logger::getInstance()->write(Logger::LOG_ERROR,								\
	__FUNCTION__,	__FILE__, __LINE__, fmt, ##__VA_ARGS__)

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
	
	__attribute__((__format__ (__printf__, 6, 7)))
	void write(LogLevels level,
						 const char* function,
						 const char* file,
						 unsigned int line,
						 const char* format,
						 ...);
	
private:
	
	Logger();
	~Logger();
	
	static Logger _instance;
	
};

#endif /* defined(__SpaceJunk__log__) */
