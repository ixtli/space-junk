//
//  simpleVector.h
//  SpaceJunk
//
//  Created by ixtli on 12/20/13.
//  Copyright (c) 2013 ixtli. All rights reserved.
//

#ifndef SpaceJunk_simpleVector_h
#define SpaceJunk_simpleVector_h

#include <stdlib.h>
#include <cassert>

template <typename T, bool dynamic>
class SimpleVector
{
public:
	
	SimpleVector() :
	_size(0),
	_capacity(0),
	_list(NULL)
	{};
	
	~SimpleVector()
	{
		if (_list) delete [] _list;
	};
	
	void init(size_t initialSize = 0);
	
	// Constant Accessors
	inline size_t size() const { return _size; };
	inline size_t capacity() const { return _capacity; };
	inline size_t bytes() const { return sizeof(T) * _capacity; };
	
	inline T& operator[] (const size_t index) const
	{
		assert(index < _size);
		return _list[index];
	};
	
	// Mutating accessors
	size_t push(T elt);
	T pop();
	
	size_t insertAtIndex(size_t index, T elt);
	T removeFromIndex(size_t index);
	size_t removeElement(const T& elt);
	void empty();
	
private:
	
	bool grow();
	
	size_t _size;
	size_t _capacity;
	
	T* _list;
};

/**
 * Completely empty the array
 */
template <typename T, bool dynamic>
void SimpleVector<T, dynamic>::empty()
{
	_size = 0;
};

/**
 * Removes all instances of the element from the array
 * @param elt the element to be removed
 * @return the amount of elements removed
 */
template <typename T, bool dynamic>
size_t SimpleVector<T, dynamic>::removeElement(const T& elt)
{
	size_t initialSize = size();
	
	if (!initialSize) return initialSize;
	
	for (size_t i = 0; i < initialSize; i++)
	{
		if (_list[(initialSize - 1) - i] != elt) continue;
		removeFromIndex((initialSize - 1) - i);
	}
	
	return initialSize - size();
};

/**
 * Remove the element at the target index from the vector
 * @param index the index of the element to remove
 * @return the value removed
 */
template <typename T, bool dynamic>
T SimpleVector<T, dynamic>::removeFromIndex(size_t index)
{
	assert(dynamic);
	assert(index < size());
	
	T ret = _list[index];
	
	_size--;
	
	if (!size() || index == size())
		return ret;
	
	for (size_t i = index; i < _size; i++)
		_list[i] = _list[i + 1];
	
	return ret;
};

/**
 * Insert an element at the index specified. The inserted element
 * becomes that index and the rest of the elements in the array
 * are pushed down one place.
 * @param index the index to insert at
 * @param elt the element to insert
 * @return the new size of the array
 */
template <typename T, bool dynamic>
size_t SimpleVector<T, dynamic>::insertAtIndex(size_t index, T elt)
{
	assert(index < size());
	
	if (capacity() == size())
	{
		if (!grow()) return size();
	}
	
	for (size_t i = _size; i > index; i--)
	{
		_list[i] = _list[i - 1];
	}
	
	_list[index] = elt;
	
	_size++;
	return size();
};

/**
 * Grow the array by 2x its current size OR to 1 if the current capacity is 0
 * @return true if the grow operation was successful
 */
template <typename T, bool dynamic>
bool SimpleVector<T, dynamic>::grow()
{
	assert(dynamic);
	
	size_t newCapacity  = capacity() ? capacity() * 2 : 1;
	T* newList = NULL;
	newList = new T[newCapacity];
	
	if (!newList) return false;
	
	// Save the new capacity
	_capacity = newCapacity;
	
	for (size_t i = 0; i < _size; i++)
	{
		newList[i] = _list[i];
	}
	
	// Start using the newly created list and clean up the old one
	delete [] _list;
	_list = newList;
	
	return true;
};

/**
 * initialize the vector
 * @param initialSize the initial size of the vector. optional if dynamic.
 */
template <typename T, bool dynamic>
void SimpleVector<T, dynamic>::init(size_t initialSize)
{
	// You shouldn't be able to create an fixed vector with no size
	assert(!(!dynamic && initialSize == 0));
	
	_size = initialSize;
	_capacity = initialSize;
	
	if (initialSize)
		_list = new T[capacity()];
};

/**
 * Push a new element on to the end of the array. Only works if dynamic.
 * @param elt the element to push
 * @return the new size of the array
 */
template <typename T, bool dynamic>
size_t SimpleVector<T, dynamic>::push(T elt)
{
	assert(dynamic);
	
	if (size() == capacity())
	{
		bool success = grow();
		if (!success) return size();
	}
	
	_list[size()] = elt;
	_size++;
	
	return size();
};

/**
 * Pop an element from the tail of the vector.
 * @return the popped element
 */
template <typename T, bool dynamic>
T SimpleVector<T, dynamic>::pop()
{
	assert(dynamic);
	assert(size() > 0);
	
	_size--;
	T ret = _list[0];
	
	// Only do this if there are elements left to shift
	if (size())
	{
		for (size_t i = 0; i < _size; i++)
			_list[i] = _list[i + 1];
	}
	
	return ret;
};

#endif
