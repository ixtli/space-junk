//
//  Easer.h
//  SpaceJunk
//
//  Created by ixtli on 11/17/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__Easer__
#define __SpaceJunk__Easer__

class Easer
{
public:
	
	Easer();
	~Easer();
	
	bool init(sjtime_t duration);
	
	// Control
	void restart();
	void stop();
	virtual int update(sjtime_t dt);
	
	// Setters
	void setStart(int s);
	void setDistance(int d);
	
	// Getters
	inline int getEnd() const { return _end; };
	inline bool isComplete() const { return _complete; };
	
private:
	
	/**
	 If the difference between the current value and _end is smaller than this
	 value, the Easer will change state to _completed = true;
	 */
	static constexpr const float END_THRESHOLD = 0.001f;
	
	/** The total amount of time the ease should take. */
	sjtime_t _totalDuration;
	
	/** Amount of time that has passed since the start */
	sjtime_t _timeAccumulator;
	
	/** The distance from start to end */
	int _distance;
	
	/** The ease's starting point */
	int _start;
	
	/** A precomputed end point */
	int _end;
	
	/** True if the ease is complete */
	bool _complete;
	
};

#endif /* defined(__SpaceJunk__Easer__) */
