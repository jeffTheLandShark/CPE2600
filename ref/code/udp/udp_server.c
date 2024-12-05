
/**********************************************
 *  Filename: UDP Server.c
 *  Description: Basic UDP comms
 *  Author: Bob Turney
 *  Date: 3/7/2024
 *  Note: gcc -o Server Server.c
 *        ./Client
 *        ./Server
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
#define BUFLEN 256
#define PORT 1234

char line[BUFLEN];
struct sockaddr_in me, client;
int sock, rlen, clen = sizeof(client);

int main(void) {
  printf("1. create a UDP socket\n");
  sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

  printf("2. fill me with server address and port number\n");
  memset((char *)&me, 0, sizeof(me));
  me.sin_family = AF_INET;
  me.sin_port = htons(PORT);
  me.sin_addr.s_addr = htonl(INADDR_ANY); // use localhost

  printf("3. bind socket to server IP and port\n");
  bind(sock, (struct sockaddr *)&me, sizeof(me));

  printf("4. wait for data");

  while (1) {
    memset(line, 0, BUFLEN);
    printf("UDP server: waiting for data \n");
    // recvfrom() gets client IP, port in sockaddr_in client
    rlen = recvfrom(sock, line, BUFLEN, 0, (struct sockaddr *)&client, &clen);
    printf("received data from [host:port] = [%s:%d]\n",
           inet_ntoa(client.sin_addr), ntohs(client.sin_port));
    printf("rlen = %d: line = %s\n", rlen, line);
    printf("send reply\n");
    sendto(sock, line, rlen, 0, (struct sockaddr *)&client, clen);
    printf("%s\n", line);
    if (!strcmp(line, "quit"))
      return 0;
  }
}
