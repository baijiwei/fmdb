all: fmdb client

fmdb: server.c httpd.c
	gcc -W -Wall -lpthread -o fmdb server.c httpd.c

client: client.c
	gcc -W -Wall -lpthread -o client client.c
clean:
	rm fmdb client
