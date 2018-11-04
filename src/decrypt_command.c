#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "crypto.h"

void usage(const char* cmd)
{
	const char* fmt =
		"Usage: %s [-h] -k string -i input -o output\n"
		"  -h, --help    display this message\n"
		"  -k, --key     symmetric key for the authentiated encryption\n"
		"  -i --input    file path of data to decrypt\n"
		"  -o --output   file path of decrypted data\n";
	printf(fmt, cmd);
}

int main(int argc, char** argv)
{
	static struct option longopts[] = {
             { "help", no_argument, NULL, 'h' },
			 { "key", required_argument, NULL, 'k' },
			 { "input", required_argument, NULL, 'i' },
			 { "output", required_argument, NULL, 'o' },
             { NULL, 0, NULL, 0}
	};
	const char* optstring = "hk:i:o:";

	int ch;
	const char* key = NULL;
	const char* inpath = NULL;
	const char* outpath = NULL;

	while ((ch = getopt_long(argc, argv, optstring, longopts, NULL)) != -1) {
		switch (ch) {
			case 'h':
				usage(argv[0]);
				return 0;
			case 'k':
				key = optarg;
				break;
			case 'i':
				inpath = optarg;
				break;
			case 'o':
				outpath = optarg;
				break;
			default:
				usage(argv[0]);
				return 1;
		}
	}
	assert(ch == -1);
	if (!key || !inpath || !outpath) {
		usage(argv[0]);
		return 1;
	}

	size_t input_size;
	char* input = mk_read_file(inpath, &input_size);
	if (!input) {
		printf("The input file '%s' could not be read\n", inpath);
		return 1;
	}

	char* output = malloc(input_size);
	size_t output_size;

	int rc = mk_decrypt(key, strlen(key), input, input_size, output, &output_size);
	free(input);
	if (!rc) {
		free(output);
		printf("The input in '%s' is unauthenticated\n", inpath);
		return 1;
	}
	assert(output_size == input_size - mk_crypt_prefix_size);

	rc = mk_write_file(outpath, output, output_size);
	free(output);
	if (!rc) {
		printf("The file '%s' already exists or could not be opened for writing\n", outpath);
		return 1;
	}

	return 0;
}
