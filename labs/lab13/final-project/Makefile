CFLAGS=-c -g -Wall -Werror
CC=gcc
TARGETS=chat_server chat_client

all: chat_server chat_client

chat_server: unix_socket_chat_server.o
	$(CC) -o chat_server unix_socket_chat_server.o

chat_client: unix_socket_chat_client.o
	$(CC) -o chat_client unix_socket_chat_client.o

clean:
	rm -f *.o $(TARGETS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

