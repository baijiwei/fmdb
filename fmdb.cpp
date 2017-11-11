#include "fmdb.h"

FmdbObj::FmdbObj():fd_data(NULL), fd_log(NULL), fd_oplog(NULL), write_buf(NULL)
{
	fd_data = fopen(data_file_full_path, "w+");
	if (NULL == fd_data) {
		fprintf(stderr, "Failed to open data file");
		return;
	}
	fd_oplog = fopen(oplog_file_full_path, "w+");
	if (NULL == fd_oplog) {
		fprintf(stderr, "Failed to open oplog file");
		return;
	}
	fd_log = fopen(log_file_full_path, "w+");
	if (NULL == fd_log) {
		fprintf(stderr, "Failed to open log file");
		return;
	}
	write_buf = new Buffer_t(fd_data, DFT_BUF_SIZE);
}

FmdbObj::~FmdbObj()
{
	if (NULL != fd_data) {
		fclose(fd_data);
    }
	if (NULL != fd_oplog) {
		fclose(fd_oplog);
    }
	if (NULL != fd_log) {
		fclose(fd_log);
    }
	if (NULL != write_buf) {
		delete write_buf;
	}
}

void FmdbObj::AppendOplog(char type, char* key, char* val)
{
	switch (type) {
		case 'I':
		    fprintf(fd_oplog, "I,%s,%s", key, val) ;
			break;
		case 'D':
			assert(NULL == val);
		    fprintf(fd_oplog, "D,%s", key) ;
			break;
		case 'F':
			assert(NULL == val);
		    fprintf(fd_oplog, "F,%s", key) ;
			break;
		case 'U':
		    fprintf(fd_oplog, "U,%s,%s", key, val) ;
			break;
		default:
		    fprintf(fd_log, "Invalid oplog type %c", type);
			break;
	}

}

Result FmdbObj::InsertOneValue(char* key, char* val) 
{
	printf("begin to handle insert key\n");

	AppendOplog('I', key, val);

     return RESULT_OK;
}

Result FmdbObj::DeleteOneValue(char* key)
{
	printf("begin to handle delete key\n");
	AppendOplog('D', key, NULL);
	return RESULT_OK;
}

Result FmdbObj::FindOneValue(char* key)
{
	printf("begin to handle find key\n");
	AppendOplog('F', key, NULL);
	return RESULT_OK;
}

Result FmdbObj::UpdateOneValue(char* key, char* val)
{
	printf("begin to handle update key\n");
	AppendOplog('U', key, val);
	return RESULT_OK;
}

void FmdbObj::HandleInputCommand()
{
	char type[16];
    char key[64];
	char val[64];
	while (1) {
		
		printf("Input type:");
		scanf("%s",type);
		if (0 == strcmp(type, "insert")) {
		    printf("Input K/V pair:");
			scanf("%s=%s", key, val);
			InsertOneValue(key, val);
		}
		else if (0 == strcmp(type, "delete")) {
		    printf("Input key:");
			scanf("%s", key);
			DeleteOneValue(key);
		}
		else if (0 == strcmp(type, "find")) {
		    printf("Input key:");
			scanf("%s", key);
			FindOneValue(key);
		}
		else if (0 == strcmp(type, "update")) {
		    printf("Input K/V pair:");
			scanf("%s=%s", key, val);
			UpdateOneValue(key, val);
		}

		else {
			fprintf(stderr, "Invalid key:%s\n", key);
		}
	}

}


