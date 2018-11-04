#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/time.h>

#include "crypto.h"
#include <LakeKeyak.h>

// Adds a nonce of 32 bytes.
static void add_nonce(char* buf)
{
	struct timeval tv;
	int rc = gettimeofday(&tv, NULL);
	assert(!rc);
	uint64_t time = 1000000 * tv.tv_sec + tv.tv_usec;
	*(uint64_t*)buf = time;
	arc4random_buf(buf + 8, 24);
}

void mk_encrypt(const char* key, size_t key_size, const char* input, size_t input_size,
				char* output, size_t* output_size)
{
	add_nonce(output);
	const unsigned char* nonce = (const unsigned char*)output;
	const size_t nonce_size = 32;
	assert(nonce_size <= LakeKeyak_MaxNoncelength);

	unsigned char* tag = (unsigned char*)output + 32;
	unsigned char* cipher_text = (unsigned char*)output + 48;

	LakeKeyak_Instance instance;
	int rc = LakeKeyak_Initialize(&instance, (const unsigned char*)key, key_size, nonce,
								  nonce_size, 0, 0, 0, 0);
	assert(rc == 1);
	rc = LakeKeyak_Wrap(&instance, (const unsigned char*)input, cipher_text, input_size,
						NULL, 0, tag, 0, 0);
	assert(rc == 1);
	*output_size = 48 + input_size;
}

int mk_decrypt(const char* key, size_t key_size, const char* input, size_t input_size,
			   char* output, size_t* output_size)
{
	if (input_size < 48)
		return 0;

	const unsigned char* nonce = (const unsigned char*)input;
	const size_t nonce_size = 32;

	unsigned char* tag = (unsigned char*)input + 32;
	const unsigned char* cipher_text = (const unsigned char*)input + 48;
	unsigned char* plain_text = (unsigned char*)output;

	LakeKeyak_Instance instance;
	int rc = LakeKeyak_Initialize(&instance, (const unsigned char*)key, key_size, nonce,
								  nonce_size, 0, 0, 1, 0);
	assert(rc == 1);
	rc = LakeKeyak_Wrap(&instance, cipher_text, plain_text, input_size - 48,
						NULL, 0, tag, 1, 0);
	if (rc != 1)
		return 0;

	*output_size = input_size - 48;
	return 1;
}

// The nonce is 8 bytes for the time since the epoch in microseconds plus 24
// random bytes. The tag is 16 bytes.
const size_t mk_crypt_prefix_size = 48;
