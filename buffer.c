#include "buffer.h"

size_t SpaceAvailable(Buffer_t* buf)
{
	return buf->max_size - (buf->cursor - buf->head);
}

int WriteBytesToBuffer(Buffer_t* buf, char* source, size_t len)
{
	if (SpaceAvailable(len) < len) {
		write(buf->fd_data, buf->head, buf->cursor - buf->head);
		buf->cursor = buf->head;
	}
	memcpy(buf->cursor, source, len);
	return 0;
}

