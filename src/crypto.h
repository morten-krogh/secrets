#include <stddef.h>

// The functions mk_keyak_encrypt() and mk_keyak_decrypt() performs
// authenticated encryption and decryption using the Keyak AEAD. The key of
// size 'key_size' is supplied in 'key'. The input of size 'input_size' is
// supplied in 'input'. The output is placed in 'output'. The size of output is
// placed in 'output_size'. The caller must ensure that output is large enough
// to hold the result.
//
// Encryption always succeeds. Decryption fails if the input is unauthentic.
// mk_keyak_decrypt() returns 1 on success and 0 on authentication failure.  In
// case of authentication failure, the output should not be used.
//
// Internally, the output of mk_keyak_encrypt() is calculated by processing the
// input with Keyak, and concatenating the cipher text with the tag.
// mk_keyak_decrypt() performs the reverse operation.
//
// The size of the decrypted data is equal to the size of the encrypted data
// plus the size of a prefix. The prefix size is given in mk_keyak_prefix_size
// and is equal to 48. The prefix consists of a nonce and a tag. The nonce
// consists of the time since the epoch in microseconds encoded in 8 bytes
// followed by 24 random bytes. The tag is 16 bytes.

void mk_encrypt(const char* key, size_t key_size, const char* input,
					  size_t input_size, char* output, size_t* output_size);

int mk_decrypt(const char* key, size_t key_size, const char* input, size_t input_size,
					 char* output, size_t* output_size);

const size_t mk_crypt_prefix_size;
