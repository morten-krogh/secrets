


#include "keyak.h"

int mk_encrypt(const char* key, size_t key_size, const char* input, size_t input_size,
			   char* output, size_t* output_size)
{

	output[0] = 'a';
	output[1] = 'b';

	*output_size = 2;

	return 1;
}

int mk_decrypt(const char* key, size_t key_size, const char* input, size_t input_size,
			   char* output, size_t* output_size)
{

	output[0] = 'm';

	*output_size = 1;

	return 1;
}
