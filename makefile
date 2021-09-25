CC = gcc

default: all

all: servermake clientmake

servermake:
	$(CC) -o server_net.out server_net.c

clientmake:
	$(CC) -o client_net.out client_net.c
