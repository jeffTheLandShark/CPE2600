
/**********************************************
 *  Filename: unix_socket_read2.c
 *  Description: using unix sockets
 *  Author: Bob Turney
 *  Date: 3/4/2020
 *  Note: gcc -o unix_socket_write unix_socket_read.c
 *  bi directional communications
 ***********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/my_socket"
#define BUFFER_SIZE 100

int main() {
  int client_fd;
  struct sockaddr_un server_addr;
  char buffer[BUFFER_SIZE] = "Hello message from client!";

  // Create socket
  if ((client_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    perror("socket error");
    exit(EXIT_FAILURE);
  }

  // Set server address
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

  // Connect to the server
  if (connect(client_fd, (struct sockaddr *)&server_addr,
              sizeof(server_addr)) == -1) {
    perror("connect error");
    close(client_fd);
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < 3; i++) {
    printf("\nEnter message: ");
    // scanf("%s", buffer);
    fgets(buffer, 99, stdin);
    // Send message to the server
    if (write(client_fd, buffer, strlen(buffer)) == -1) {
      perror("write error");
      close(client_fd);
      exit(EXIT_FAILURE);
    }

    // Read echo from the server
    int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
      buffer[bytes_read] = '\0';
      printf("Message from the server: %s\n", buffer);
    }
  }
  // Clean up
  close(client_fd);

  return 0;
}
