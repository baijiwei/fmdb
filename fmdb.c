#include "fmdb.h"

static void AllocBuffer(FmdbObj_t *obj, size_t len)
{
	if (NULL == obj || len == 0) {
		return;
	}
     Buffer_t* buf = (Buffer_t* ) malloc(len+sizeof(Buffer_t));
	 if (NULL == buf) {
		 fprintf(stderr, "Memory has been exhausted");
		 return;
	 }
	 buf->max_size = len;
	 buf->head = (char*)buf + sizeof(Buffer_t);
	 buf->cursor = buf->head;
	 buf->fd_data = obj->fd_data;
	 obj->write_buf = buf;
}
FmdbObj_t* ConstructFmDB()
{
	FmdbObj_t* obj = (FmdbObj_t*) calloc(1, sizeof(FmdbObj_t));
	if (NULL == obj) {
		fprintf(stderr, "Memory has been exhausted");
		return NULL;
	}
	AllocBuffer(obj, DFT_BUF_SIZE);

	return obj;
}
