//
//  stringUtil.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/9/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "stringUtil.h"

size_t trimmedString(const char* str, const char* &start)
{
	if (!str)
		return 0;
	
	start = str;
	size_t position = 0;
	const char* lastGood = NULL;
	
	while (str[position] != '\0')
	{
		switch (str[position])
		{
			case ' ':
			case '\t':
			case '\r':
			case '\n':
				break;
				
			default:
				if (!lastGood)
				{
					start = str + position;
				}
				
				lastGood = str + position;
				break;
		}
		
		position++;
	}
	
	if (!lastGood)
		return 0;
	
	return lastGood - start + 1;
}
