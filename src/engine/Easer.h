//
//  Easer.h
//  SpaceJunk
//
//  Created by ixtli on 11/17/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__Easer__
#define __SpaceJunk__Easer__

#include "../util/chronoUtil.h"
#include "./easing.h"

template <class T>
class Easer
{
public:
	
	typedef double (*EasingFunction)(double, double, double, double);
	
	Easer() :
	
	_totalDuration(0),
	_start(0),
	_distance(0),
	_complete(true)
	
	{};
	
	~Easer() {};
	
	/**
	 Initialize the easer.
	 @param fxn the function to use to ease
	 */
	bool init(EasingFunction fxn)
	{
		_fxn = fxn;
		return true;
	};
	
#pragma mark -
#pragma mark control functions
	
	/** Restart the animation. Call every time you want to ease. */
	void restart()
	{
		_timeAccumulator = 0;
		_complete = false;
	};
	
	/** Stop the ease. */
	void stop()
	{
		_timeAccumulator = _totalDuration;
		_complete = true;
	};
	
	/**
	 @param dt milliseconds since last update call
	 @return a delta by which the value being eased should be incrimented
	 */
	inline int update(sj_time_t dt)
	{
		if (_complete) return 0;
		
		_timeAccumulator += dt;
		
		if (_timeAccumulator >= _totalDuration)
			_complete = true;
		
		return (T) _fxn((double)_timeAccumulator,
										(double)_totalDuration,
										(double)_start,
										(double)_distance);
	};
	
#pragma mark -
#pragma mark Setters
	
	/**
	 Set the duration of the animation
	 @param duration the time in milliseconds
	 */
	inline void setDuration(sj_time_t duration) { _totalDuration = duration; };
	
	/**
	 Set the start location of the animation
	 @param s the start location
	 */
	inline void setStart(T s) { _start = s; };
	
	/**
	 Set the distance to be traveled over the duration
	 @param d the distance to be eased over
	 */
	inline void setDistance(T d) { _distance = d; };
	
#pragma mark -
#pragma mark Getters
	
	/**
	 Get the computed end location of the animation. The property being eased
	 should generally be set to this value once isComplete() is true
	 @return the end value of the animation
	 */
	inline int getEnd() const { return _start + _distance; };
	
	/** @return true if the ease is complete, otherwise false */
	inline bool isComplete() const { return _complete; };
	
private:
	
	/** The total amount of time the ease should take. */
	sj_time_t _totalDuration;
	
	/** Amount of time that has passed since the start */
	sj_time_t _timeAccumulator;
	
	/** The distance from start to end */
	T _distance;
	
	/** The ease's starting point */
	T _start;
	
	/** True if the ease is complete */
	bool _complete;
	
	/** The easing function to use */
	EasingFunction _fxn;
	
};

#endif /* defined(__SpaceJunk__Easer__) */
