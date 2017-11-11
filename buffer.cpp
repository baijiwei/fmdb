#include "buffer.h"

size_t Buffer_t::SpaceAvailable()
{
	return max_size - (cursor - head);
}

int Buffer_t::WriteBytesToBuffer(char* source, size_t len)
{
	if (SpaceAvailable() < len) {
		fwrite(head, 1, cursor - head, fd_data);
		cursor = head;
	}
	memcpy(cursor, source, len);
	return 0;
}

Buffer_t::Buffer_t(FILE* fddata, size_t len):fd_data(fddata), max_size(len), head(NULL), cursor(NULL)
{
	if (NULL == fddata || len == 0) {
		return;
	}
    head = (char* ) malloc(len);
	 if (NULL == head) {
		 fprintf(stderr, "Memory has been exhausted");
		 return;
	 }
	 cursor = head;
}
Buffer_t::~Buffer_t()
{
     if (NULL != head) {
		 free(head);
		 head = cursor = NULL;
	 }
}


