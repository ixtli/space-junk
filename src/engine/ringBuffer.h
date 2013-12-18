//
//  ringBuffer.h
//  SpaceJunk
//
//  Created by ixtli on 11/18/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__ringBuffer__
#define __SpaceJunk__ringBuffer__

#include <assert.h>

/**
 A lock-free multiproducer, multiconsumer queue implemented as a ring buffer.
 Please make sure to always define Q_SIZE as a power of two
 */
template<class T, unsigned Q_SIZE>
class RingBuffer
{
public:
	
	RingBuffer()
	{
		
	};
	
	void push(T* x);
	T* pop();
	
private:
	
	static const unsigned Q_MASK = Q_SIZE - 1;
	
	T* _array[Q_SIZE];
	unsigned _head;
	unsigned _tail;
	
	// The following conditionals are required because in the case that either
	// of them are true, their associated ops must wait
	bool _isEmpty;
	bool _isFull;
	
};

#endif /* defined(__SpaceJunk__ringBuffer__) */
