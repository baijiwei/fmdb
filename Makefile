all: fmdb client

SOURCE_FILE = server.cpp httpd.cpp buffer.h buffer.cpp fmdb.h fmdb.cpp

fmdb: server.cpp httpd.cpp
	rm -f fmdb
	g++ -W -Wall -lpthread -o fmdb $(SOURCE_FILE)

client: client.cpp
	rm -f client
	g++ -W -Wall -lpthread -o client client.cpp
clean:
	rm fmdb client
