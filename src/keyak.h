#include <stddef.h>


int mk_encrypt(const char* key, size_t key_size, const char* input, size_t input_size,
			   char* output, size_t* output_size);

int mk_decrypt(const char* key, size_t key_size, const char* input, size_t input_size,
			   char* output, size_t* output_size);


