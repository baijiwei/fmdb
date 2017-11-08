#include "fmdb.h"

enum Result {
	RESULT_OK          = 0,
	RESULT_FAIL        = 1,
	RESULT_DEPLICATED  = 2,
	RESULT_NO_FOUND    = 3,
};
typedef enum Result Result;

static FmdbObj_t* obj = NULL;
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
		fprintf(stderr, "Memory has been exhausted\n");
		return NULL;
	}


	obj->fd_data = fopen(obj->data_file_full_path, "w+");
	if (NULL == obj->fd_data) {
		fprintf(stderr, "Failed to open data file");
		DestructFmdb(obj);
		return NULL;
	}
	obj->fd_oplog = fopen(obj->oplog_file_full_path, "w+");
	if (NULL == obj->fd_oplog) {
		fprintf(stderr, "Failed to open oplog file");
		DestructFmdb(obj);
		return NULL;
	}
	obj->fd_log = fopen(obj->log_file_full_path, "w+");
	if (NULL == obj->fd_log) {
		fprintf(stderr, "Failed to open log file");
		DestructFmdb(obj);
		return NULL;
	}
	AllocBuffer(obj, DFT_BUF_SIZE);

	return obj;
}

void DestructFmdb(FmdbObj_t* obj)
{
	if (NULL != obj->fd_data) {
		fclose(obj->fd_data);
    }
	if (NULL != obj->fd_oplog) {
		fclose(obj->fd_oplog);
    }
	if (NULL != obj->fd_log) {
		fclose(obj->fd_log);
    }

    free(obj);
	obj = NULL;
}

void AppendOplog(char type, char* key, char* val)
{
	switch (type) {
		case 'I':
		    fprintf(obj->fd_oplog, "I,%s,%s", key, val) ;
			break;
		case 'D':
			assert(NULL == val);
		    fprintf(obj->fd_oplog, "D,%s", key) ;
			break;
		case 'F':
			assert(NULL == val);
		    fprintf(obj->fd_oplog, "F,%s", key) ;
			break;
		case 'U':
		    fprintf(obj->fd_oplog, "U,%s,%s", key, val) ;
			break;
		default:
		    fprintf(obj->fd_log, "Invalid oplog type %c", type);
			break;
	}

}

Result InsertOneValue(char* key, char* val) 
{
	printf("begin to handle insert key\n");

	AppendOplog('I', key, val);

     return RESULT_OK;
}

Result DeleteOneValue(char* key)
{
	printf("begin to handle delete key\n");
	AppendOplog('D', key, NULL);
	return RESULT_OK;
}

Result FindOneValue(char* key)
{
	printf("begin to handle find key\n");
	AppendOplog('F', key, NULL);
	return RESULT_OK;
}

Result UpdateOneValue(char* key, char* val)
{
	printf("begin to handle update key\n");
	AppendOplog('U', key, val);
	return RESULT_OK;
}

void HandleInputCommand()
{
	obj = ConstructFmDB();
	if (NULL == obj) {
		fprintf(stderr, "Failed to create FmdbObj_t object");
		return;
	}
	char type[16];
    char key[64];
	char val[64];
	while (1) {
		
		printf("Input type:");
		scanf("%s",&type);
		if (0 == strcmp(type, "insert")) {
		    printf("Input K/V pair:");
			scanf("%s=%s", &key, &val);
			InsertOneValue(key, val);
		}
		else if (0 == strcmp(type, "delete")) {
		    printf("Input key:");
			scanf("%s", &key);
			DeleteOneValue(key);
		}
		else if (0 == strcmp(type, "find")) {
		    printf("Input key:");
			scanf("%s", &key);
			FindOneValue(key);
		}
		else if (0 == strcmp(type, "update")) {
		    printf("Input K/V pair:");
			scanf("%s=%s", &key, &val);
			UpdateOneValue(key, val);
		}

		else {
			fprintf(stderr, "Invalid key:%s\n", key);
		}
	}

}


