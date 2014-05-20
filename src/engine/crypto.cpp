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
	
	BIO *b64 = BIO_new(BIO_f_base64());
	
	// Strips out newlines from the ouput.
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	
	BIO *bmem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bmem);
	
	// Do the b64 encode
	BIO_write(b64, input, len);
	BIO_flush(b64);
	
	// Make a pointer to mem and copy the string out
	BUF_MEM* bufferPtr;
	BIO_get_mem_ptr(b64, &bufferPtr);
	memcpy(outBuffer, bufferPtr->data, bufferPtr->length);
	outBuffer[bufferPtr->length] = '\0';

	BIO_free_all(b64);
}
