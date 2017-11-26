#ifndef FMDB_H
#define FMDB_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "buffer.h"
#include "ffShr.h"
#include<string>
#include<vector>
#include "catalog.h"

#define DFT_BUF_SIZE 1024

using  namespace std;

enum Result {
	RESULT_OK          = 0,
	RESULT_FAIL        = 1,
	RESULT_DEPLICATED  = 2,
	RESULT_NO_FOUND    = 3,
};
typedef enum Result Result;

struct kvValue {
	string   key;
	string   val;
};
typedef struct kvValue kvValue;

struct fmdbBlkLayout {
	off_t   offset;
	uint_T  len;
};

class ffwSession {
public:
    ffwSession();
	~ffwSession();
private:
    std::vector<kvValue*> kv_arr;
	uint_T  curr_size;
};

class ffwDataBlk {
public:
    ffwDataBlk();
	~ffwDataBlk();
private:
	fmdbBlkLayout* layout;
};

class ffwChainBlk {
public:
	ffwChainBlk();
	~ffwChainBlk();
private:
    fmdbXTag  begin_xtag;
	fmdbXTag  close_xtag;
	fmdbBlkLayout* data_layout_arr;
};


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
	std::map<string, fmdbDatabase*>  db_manager;
};

#endif
