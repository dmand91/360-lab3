server:server.c
	g++ -o server server.c -pthread
all: client server download
client: client.c
	gcc -o client client.c
clean: 
	rm client server

