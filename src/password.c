#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "password.h"

static char generate_lower_case_letter()
{
	uint32_t ran = arc4random_uniform(26);
	return 'a' + (char)ran;
}

static char generate_upper_case_letter()
{
	uint32_t ran = arc4random_uniform(26);
	return 'A' + (char)ran;
}

static char generate_digit()
{
	uint32_t ran = arc4random_uniform(10);
	return '0' + (char)ran;
}

static char generate_punctuation_character()
{
	static char chars[] = "!@#$%^&*()-_+={}:;,.<>?/";
	assert(sizeof chars == 25);
	uint32_t ran = arc4random_uniform(24);
	return chars[ran];
}

int mk_generate_password(const char* prefix, char* out)
{
	size_t prefix_len = strlen(prefix);
	memcpy(out, prefix, prefix_len);

	size_t pos = prefix_len;

	for (int i = 0; i < 6; ++i) {
		out[pos++] = generate_punctuation_character();
		out[pos++] = generate_lower_case_letter();
		out[pos++] = generate_upper_case_letter();
		out[pos++] = generate_digit();
	}

	out[pos] = '\0';

	return pos;
}
