#include<stdio.h>
#include "fmdb.h"

int main(/*int argc, char** argv*/)
{
	FmdbObj* obj = new FmdbObj();
	if (NULL == obj) {
		printf("Failed to create Fmdb object");
		return -1;
	}
	obj->HandleInputCommand();
	return 0;
}
