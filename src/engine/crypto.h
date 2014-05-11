//
//  crypto.h
//  SpaceJunk
//
//  Created by ixtli on 5/8/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#ifndef __SpaceJunk__crypto__
#define __SpaceJunk__crypto__

bool SHA1String(const unsigned char* input, size_t len, unsigned char* output);
void base64Encode(const unsigned char* input, int len, char* outBuffer);

size_t SHA1DigestLength();

#endif /* defined(__SpaceJunk__crypto__) */
