//
//  Easer.cpp
//  SpaceJunk
//
//  Created by ixtli on 11/17/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#include "easing.h"

#include "Easer.h"

Easer::Easer() :

_totalDuration(0),
_start(0),
_end(0),
_distance(0),
_complete(true)

{ }

Easer::~Easer()
{
	
}

bool Easer::init(sjtime_t duration)
{
	_totalDuration = duration;
	
	return true;
}

void Easer::setStart(int s)
{
	_start = s;
	_end = _distance + _start;
}

void Easer::setDistance(int d)
{
	_distance = d;
	_end = _distance + _start;
}

void Easer::restart()
{
	_timeAccumulator = 0;
	_complete = false;
}

/**
 @param dt milliseconds since last update call
 @return a delta by which the value being eased should be incrimented
 */
int Easer::update(sjtime_t dt)
{
	if (_complete) return 0;
	
	_timeAccumulator += dt;
	
	double delta = easeInOutQuad((double)_timeAccumulator, (double)_totalDuration);
	
	if (_timeAccumulator >= _totalDuration)
		_complete = true;
	
	return (int)round(_distance * delta);
}