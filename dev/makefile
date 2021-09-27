CC = gcc

default: all

all: servermake clientmake shipmake boardmake devmake

servermake:
	$(CC) -o server_net.out -g ../net/server_net.c

clientmake:
	$(CC) -o client_net.out -g ../net/client_net.c

shipmake:
	$(CC) -o ship.out -g ../game/ship.c

devmake:
	$(CC) -o build.out -g  ../game/ship.c ../game/board.c ../game/game_logic.c