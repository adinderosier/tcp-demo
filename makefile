CC = gcc

default: all

all: servermake clientmake

servermake:
	$(CC) -o server_net.out ./net/server_net.c

clientmake:
	$(CC) -o client_net.out ./net/client_net.c
