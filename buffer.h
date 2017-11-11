#ifndef BUFFER_H
#define BUFFER_H

#include "sys.h"

class Buffer_t {
public:
    Buffer_t(FILE* fd_data, size_t len);
	~Buffer_t();
	int    WriteBytesToBuffer(char* source, size_t len);
	size_t SpaceAvailable();
private:
	FILE*    fd_data;
	size_t   max_size;
	char*    head;
	char*    cursor;
};

#endif
