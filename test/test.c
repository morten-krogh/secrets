#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../src/crypto.h"
#include "../src/file.h"
#include "../src/password.h"

static void test_file()
{
	const char content[] = "Something";
	size_t content_size = sizeof content - 1;
	char path[] = "/tmp/mktest.XXXXXXXXX";
	assert(mktemp(path));
	int rc = mk_write_file(path, content, content_size);
	assert(rc == 1);
	
	size_t file_size;
	char* content2 = mk_read_file(path, &file_size);
	assert(content2);
	assert(content_size == file_size);
	assert(memcmp(content2, content, content_size) == 0);
	free(content2);
}

static void test_password()
{
	char out[40];
	const char* prefix = "Prefix";
	mk_generate_password(prefix, out);
	assert(strlen(out) == strlen(prefix) + 24);
	assert(memcmp(out, prefix, strlen(prefix)) == 0);
}

static void test_crypto()
{
	const char* key = "Key";
	size_t key_size = 3;
	const char* input = "Input";
	size_t input_size = 5;
	char encrypted[64];
	size_t encrypted_size;
	mk_encrypt(key, key_size, input, input_size, encrypted, &encrypted_size);
	assert(encrypted_size == input_size + mk_crypt_prefix_size);

	char decrypted[10];
	size_t decrypted_size;
	int rc = mk_decrypt(key, key_size, encrypted, encrypted_size, decrypted, &decrypted_size);
	assert(rc == 1);
	assert(decrypted_size == input_size);
	assert(memcmp(decrypted, input, input_size) == 0);

	// Too short encrypted data.
	rc = mk_decrypt(key, key_size, encrypted, 40, decrypted, &decrypted_size);
	assert(rc == 0);

	// Manipulate the encrypted data.
	encrypted[50] = encrypted[50] == 0 ? 1 : 0;
	rc = mk_decrypt(key, key_size, encrypted, encrypted_size, decrypted, &decrypted_size);
	assert(rc == 0);
}

int main(void)
{
	test_file();
	test_password();
	test_crypto();
	printf("All tests passed\n");
	return 0;
}
