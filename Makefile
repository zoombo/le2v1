CC=gcc
CFLAGS=-std=c11 -Wall -O0

all:
	$(CC) $(CFLAGS) -pthread buyer.c loader.c main.c -o less2

clean:
	rm less2
