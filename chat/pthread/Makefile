all: client server
server : server.c
	gcc -g -std=c99 server.c -o output/server -lpthread

client : client.c
	gcc -g -std=c99 client.c -o output/client -lpthread

clean :
	rm -f output/*.o output/client output/server
