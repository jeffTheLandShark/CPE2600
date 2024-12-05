
/**********************************************
 *  Filename: Client.c
 *  Description: Basic UDP comms
 *  Author: Bob Turney
 *  Date: 3/7/2024
 *  Note: gcc -o Client Client.c
 *        ./Client
 *        ./Server
 *
 ***********************************************/
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// define some constants
#define SERVER_HOST "172.28.103.78" // $ hostname -I
#define BUFLEN 256
#define SERVER_PORT 1234

char line[BUFLEN];
struct sockaddr_in server;
int sock, rlen, slen = sizeof(server);

int main(void) {
  printf("1. create a UDP socket\n");
  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  printf("2. fill me with server address and port number\n");
  memset((char *)&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(SERVER_PORT);
  inet_aton(SERVER_HOST, &server.sin_addr);

  while (strcmp(line, "quit")) {
    printf("Enter a line (type quit to end): ");
    fgets(line, BUFLEN, stdin);
    line[strlen(line) - 1] = 0;
    printf("send line to server\n");
    sendto(sock, line, strlen(line), 0, (struct sockaddr *)&server, slen);
    printf("try to receive a line from server\n");
    rlen = recvfrom(sock, line, BUFLEN, 0, (struct sockaddr *)&server, &slen);
    printf("rlen = %d: line = %s\n", rlen, line);
  }
}
