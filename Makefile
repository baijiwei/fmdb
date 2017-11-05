all: fmdb client

fmdb: server.c httpd.c
	rm -f fmdb
	gcc -W -Wall -lpthread -o fmdb server.c httpd.c buffer.h buffer.c fmdb.h fmdb.c

client: client.c
	rm -f client
	gcc -W -Wall -lpthread -o client client.c
clean:
	rm fmdb client
