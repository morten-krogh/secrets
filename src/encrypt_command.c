#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "keyak.h"

void usage(const char* cmd)
{
	const char* fmt =
		"Usage: %s [-h] -k string -i input -o output\n"
		"  -h, --help    display this message\n"
		"  -k, --key     symmetric key for the authentiated encryption\n"
		"  -i --input    file path of data to encrypt\n"
		"  -o --output   file path of encypted data\n";
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
	const char* input = NULL;
	const char* output = NULL;

	while ((ch = getopt_long(argc, argv, optstring, longopts, NULL)) != -1) {
		switch (ch) {
			case 'h':
				usage(argv[0]);
				return 0;
			case 'k':
				key = optarg;
				break;
			case 'i':
				input = optarg;
				break;
			case 'o':
				output = optarg;
				break;
			default:
				usage(argv[0]);
				return 1;
		}
	}
	assert(ch == -1);
	if (!key || !input || !output) {
		usage(argv[0]);
		return 1;
	}

	FILE* infile = fopen(input, "r");
	if (!infile) {
		printf("The file '%s' could not be opened for reading\n", input);
		return 1;
	}

	FILE* outfile = fopen(output, "wx");
	if (!outfile) {
		printf("The file '%s' already exists or could not be opened for writing\n", output);
		return 1;
	}

	int rc = fseek(infile, 0, SEEK_END);
	if (rc == -1) {
		printf("Error reading '%s'\n", input);
		return 1;
	}
	long insize = ftell(infile);
	rc = fseek(infile, 0, SEEK_SET);
	if (rc == -1) {
		printf("Error reading '%s'\n", input);
		return 1;
	}
	
	char* inbuf = malloc(insize);
	assert(inbuf);

	size_t nread = fread(inbuf, 1, insize, infile);
	assert(nread == insize);

	char* outbuf = malloc(insize + 100);

	size_t outsize = mk_encrypt(key, strlen(key), inbuf, insize, outbuf);
	assert(outsize < insize + 100);

	size_t nwritten = fwrite(outbuf, 1, outsize, outfile);
	if (nwritten != outsize) {
		printf("The encrypted data could not be written into file '%s'\n", output);
		return 1;
	}

	// Buffers are freed and files closed automatically by exiting the process.
	return 0;
}
