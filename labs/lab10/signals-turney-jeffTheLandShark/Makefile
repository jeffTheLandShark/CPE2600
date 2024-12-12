CFLAGS=-c -g -Wall -Werror
CC=gcc

all: signal_handler signal_alarm signal_segfault signal_sigaction send_signal recv_signal

signal_handler: 
	$(CC) -o signal_handler signal_handler.c

signal_alarm: 
	$(CC) -o signal_alarm signal_alarm.c

signal_segfault:
	$(CC) -o signal_segfault signal_segfault.c

signal_sigaction: 
	$(CC) -o signal_sigaction signal_sigaction.c

send_signal:
	$(CC) -o send_signal send_signal.c

recv_signal:
	$(CC) -o recv_signal recv_signal.c

clean:
	rm -f *.o $(TARGETS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

