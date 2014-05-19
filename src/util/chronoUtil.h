//
//  chronoUtil.h
//  SpaceJunk
//
//  Created by ixtli on 5/18/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef SpaceJunk_chronoUtil_h
#define SpaceJunk_chronoUtil_h

#include <chrono>
#include <cstdint>

#define kSJClock std::chrono::steady_clock
#define kSJTimePoint std::chrono::time_point<kSJClock>
#define kSJTimeUnit std::chrono::milliseconds

#define TIME_SINCE_EPOCH() \
	std::chrono::duration_cast<kSJTimeUnit> \
	(std::chrono::system_clock::now().time_since_epoch()).count()

typedef kSJTimeUnit::rep sj_time_t;

#endif
