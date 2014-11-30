//
//  textureManager.h
//  SpaceJunk
//
//  Created by ixtli on 11/30/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__textureManager__
#define __SpaceJunk__textureManager__

#import <queue>

#import "texture.h"

class TextureManager
{
public:
	
	inline static TextureManager* getInstance() { return &_instance; };

	// Returns true if the texture unit is newly bound
	inline static bool bind(Texture* t)
	{
		// Is it already bound?
		if (t->textureUnit() >= 0)
		{
			t->bind(t->textureUnit());
			return false;
		}
		
		// Is there free space in the queue?
		if (_instance._unitsUsed < _instance._textureUnits)
		{
			// If so, simply occupy another unit
			t->bind(_instance._unitsUsed);
			_instance._unitsUsed++;
		} else {
			// If not, we must evict
			Texture* evicted = _instance._textureUnitQueue.front();
			_instance._textureUnitQueue.pop();
			t->bind(evicted->textureUnit());
			evicted->clear();
			_instance._evictions++;
		}
		
		_instance._textureUnitQueue.push(t);
		return true;
	}
	
	bool init();
	
	// Metrics
	inline GLint unitsUsed() const { return _unitsUsed; };
	inline size_t evictions() const { return _evictions; };
	inline void clearEvictions() { _evictions = 0; };
	
private:
	
	TextureManager();
	~TextureManager();
	
	GLint _textureUnits;
	GLint _unitsUsed;
	size_t _evictions;
	
	std::queue<Texture*> _textureUnitQueue;
	
	static TextureManager _instance;
	
};

#endif /* defined(__SpaceJunk__textureManager__) */
