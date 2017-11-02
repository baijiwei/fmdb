#ifndef BUFFER_H
#define BUFFER_H

#include<stdio.h>
struct Buffer_t {
	short    fd_data;
	size_t   max_size;
	char*    cursor;
	char*    head;
};
typedef struct Buffer_t Buffer_t;

size_t SpaceAvailable(Buffer_t* buf);
int WriteBytesToBuffer(Buffer_t* buf, char* source, size_t len);
#endif
