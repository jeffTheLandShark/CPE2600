CFLAGS=-c -g -Wall -Werror
CC=gcc

all: signal_handler signal_alarm signal_segfault

signal_handler: signal_handler.o
	$(CC) -o signal_handler signal_handler.o

signal_alarm: signal_alarm.o
	$(CC) -o signal_alarm signal_alarm.o

signal_segfault:
	$(CC) -o signal_segfault signal_segfault.c

clean:
	rm -f *.o signal_handler signal_alarm signal_segfault

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

