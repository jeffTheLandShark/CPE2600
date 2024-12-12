CFLAGS=-c -g -Wall -Werror
CC=gcc
TARGETS=chat_server chat_client

all: chat_server chat_client

chat_server: 
	$(CC) -o chat_server unix_socket_chat_server.c

chat_client: 
	$(CC) -o chat_client unix_socket_chat_client.c

clean:
	rm -f *.o $(TARGETS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

