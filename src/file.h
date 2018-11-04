// read_file() allocates a buffer and reads the content of the file 'path' into 
// the buffer. The file size is returned in 'file_size'. The return value is the
// allocated buffer. The caller must free the return value buffer. If the file could not
// be read, the function returns NULL.
char* mk_read_file(const char* path, size_t* file_size);

// write_file() writes the content in 'output' of size 'output_size' into a new file
// at location 'path'. The return value is 1 if the write succeeds, 0 otherwise.
// The write fails if the file already exists or if it cannot be opened.
int mk_write_file(const char* path, const char* output, size_t output_size);
