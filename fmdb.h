#ifndef FMDB_H
#define FMDB_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "buffer.h"

#define DFT_BUF_SIZE 1024
struct FmdbObj_t {
	short        fd_data;
	short        fd_log;
	Buffer_t*    write_buf;

};
typedef struct FmdbObj_t FmdbObj_t;

#endif
