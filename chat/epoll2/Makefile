all : server client
server : server.cpp
	g++ -std=c++11 server.cpp -o server
client : client.cpp
	g++ -std=c++11 client.cpp -o client -lpthread
clean :
	rm -rf server client *.o
