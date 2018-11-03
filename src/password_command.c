#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "password.h"

void usage(const char* cmd)
{
	const char* fmt =
		"Usage: %s [-h] [-p string]\n"
		"  -h, --help    display this message\n"
		"  -p, --prefix  prefix for the password(max length 50)\n";
	printf(fmt, cmd);
}




int main(int argc, char** argv)
{
	static struct option longopts[] = {
             { "help", no_argument, NULL, 'h' },
             { "prefix", required_argument, NULL, 'p' },
             { NULL, 0, NULL, 0}
     };
	const char* optstring = "hp:";

	int ch;
	const char* prefix = "";
	while ((ch = getopt_long(argc, argv, optstring, longopts, NULL)) != -1) {
		switch (ch) {
			case 'h':
				usage(argv[0]);
				return 0;
			case 'p':
				prefix = optarg;
				break;
			default:
				usage(argv[0]);
				return 1;
		}
	}
	assert(ch == -1);
	size_t prefix_len = strlen(prefix);
	if (prefix_len > 50) {
		usage(argv[0]);
		return 1;
	}

	// 128 bytes is more than enough.
	char password[128];

	int password_len = mk_generate_password(prefix, password);
	assert(password_len < 128);

	printf("%s\n", password);

	return 0;
}
