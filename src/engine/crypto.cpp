//
//  crypto.cpp
//  SpaceJunk
//
//  Created by ixtli on 5/8/14.
//  Copyright (c) 2014 ixtli. All rights reserved.
//

#include "crypto.h"

#include <math.h>
#include <openssl/sha.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

// I would prefer not to depend on CDSA directly here, for portability.
#pragma clang diagnostics push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
bool SHA1String(const unsigned char* input, size_t len, unsigned char* output)
{
	SHA1(input, len, output);
	
	return true;
}
#pragma clang diagnostics pop

size_t SHA1DigestLength()
{
	return SHA_DIGEST_LENGTH;
}

void base64Encode(const unsigned char* input, int len, char* outBuffer)
{
	BIO *bio, *b64;
	
	b64 = BIO_new(BIO_f_base64());
	bio = BIO_new(BIO_s_mem());
	bio = BIO_push(b64, bio);
	
	// Strips out newlines from the ouput.
	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
	BIO_write(bio, input, len);
	BIO_flush(bio);
	
	BUF_MEM* bufferPtr;
	BIO_get_mem_ptr(bio, &bufferPtr);
	memcpy(outBuffer, bufferPtr->data, bufferPtr->length);
	outBuffer[bufferPtr->length] = '\0';

	BIO_set_close(bio, BIO_CLOSE);
	BIO_free_all(bio);
}
