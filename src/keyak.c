


#include "keyak.h"

void mk_keyak_encrypt(const char* key, size_t key_size, const char* input, size_t input_size,
			   char* output, size_t* output_size)
{

	output[0] = 'a';
	output[1] = 'b';

	*output_size = 2;
}


int mk_keyak_decrypt(const char* key, size_t key_size, const char* input, size_t input_size,
			   char* output, size_t* output_size)
{

	output[0] = 'm';

	*output_size = 1;

	return 1;
}

const size_t mk_keyak_tag_size = 32;
