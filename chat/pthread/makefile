all: client server
server : server.c
	gcc -std=c99 server.c -o server -lpthread

client : client.c
	gcc -std=c99 client.c -o client -lpthread
