CFLAGS=-c -g -Wall -Werror
CC=gcc

all: signal_handler

signal_handler: signal_handler.o
	$(CC) -o signal_handler signal_handler.o

clean:
	rm -f *.o signal_handler

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

