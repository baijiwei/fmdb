#ifndef FMDB_H
#define FMDB_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "buffer.h"

#define DFT_BUF_SIZE 1024
struct FmdbObj_t {
	FILE*        fd_data;
	FILE*        fd_log;
	FILE*        fd_oplog;
	char*        data_file_full_path;
	char*       oplog_file_full_path;
	char*        log_file_full_path;
	Buffer_t*    write_buf;

};
typedef struct FmdbObj_t FmdbObj_t;

#endif
