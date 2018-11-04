#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* mk_read_file(const char* path, size_t* file_size)
{
	FILE* file = fopen(path, "r");
	if (!file)
		return NULL;

	int rc = fseek(file, 0, SEEK_END);
	if (rc == -1) {
		fclose(file);
		return NULL;
	}

	size_t size = ftell(file);
	rc = fseek(file, 0, SEEK_SET);
	if (rc == -1) {
		fclose(file);
		return NULL;
	}

	char* buf = malloc(size);
	if (!buf) {
		fclose(file);
		return NULL;
	}

	size_t nread = fread(buf, 1, size, file);
	fclose(file);

	if (nread != size) {
		free(buf);
		return NULL;
	}

	*file_size = size;
	return buf;
}

int mk_write_file(const char* path, const char* output, size_t output_size)
{
	FILE* file = fopen(path, "wx");
	if (!file)
		return 0;

	size_t nwritten = fwrite(output, 1, output_size, file);
	fclose(file);

	return (nwritten == output_size) ? 1 : 0;
}
