//
//  imageData.h
//  SpaceJunk
//
//  Created by ixtli on 11/23/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__imageData__
#define __SpaceJunk__imageData__

class ImageData
{
public:
	
	ImageData(unsigned w, unsigned h);
	~ImageData();
	
	bool init();
	
	inline unsigned height() const { return _height; };
	inline unsigned width() const { return _width; };
	inline unsigned char* data() { return _data; };
	
private:
	
	unsigned _width;
	unsigned _height;
	unsigned char* _data;
};

#endif /* defined(__SpaceJunk__imageData__) */
