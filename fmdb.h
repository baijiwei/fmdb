#ifndef FMDB_H
#define FMDB_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "buffer.h"

#define DFT_BUF_SIZE 1024

enum Result {
	RESULT_OK          = 0,
	RESULT_FAIL        = 1,
	RESULT_DEPLICATED  = 2,
	RESULT_NO_FOUND    = 3,
};
typedef enum Result Result;

class FmdbObj {
public:
    FmdbObj();
	~FmdbObj();
	void     AppendOplog(char type, char* key, char* val);
	void     HandleInputCommand();
	Result   InsertOneValue(char* key, char* val);
	Result   UpdateOneValue(char* key, char* val);
	Result   FindOneValue(char* key);
	Result   DeleteOneValue(char* key);

private:
    void   ConstructFmDB();
	FILE*        fd_data;
	FILE*        fd_log;
	FILE*        fd_oplog;
	char*        data_file_full_path;
	char*       oplog_file_full_path;
	char*        log_file_full_path;
	Buffer_t*    write_buf;

};

#endif
