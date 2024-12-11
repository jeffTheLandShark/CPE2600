/**********************************************
 *  Filename: unix_socket_write2.c
 *  Description: using unix sockets
 *  Author: Bob Turney
 *  Date: 3/4/2020
 *  Note: gcc -o unix_socket_write unix_socket_write.c
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
  int server_fd, client_fd;
  struct sockaddr_un server_addr;
  char buffer[BUFFER_SIZE];

  // Create socket
  if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
    perror("socket error");
    exit(EXIT_FAILURE);
  }

  // Bind socket to a file
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sun_family = AF_UNIX;
  strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

  unlink(SOCKET_PATH); // Remove any existing file
  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      -1) {
    perror("bind error");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_fd, 5) == -1) {
    perror("listen error");
    close(server_fd);
    exit(EXIT_FAILURE);
  }

  printf("Server is listening on %s\n", SOCKET_PATH);

  // Accept a connection
  if ((client_fd = accept(server_fd, NULL, NULL)) == -1) {
    perror("accept error");
    close(server_fd);
    exit(EXIT_FAILURE);
  } else {
    printf("connection accepted\n");
    sleep(3);
  }

  // Read data from the client and send a new message back
  for (int i = 0; i < 3; i++) {
    int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
      buffer[bytes_read] = '\0';
      printf("Received from the client: %s\n", buffer);
      printf("\nEnter message: ");
      // scanf("%s", buffer);
      fgets(buffer, 99, stdin);
      write(client_fd, buffer,
            strlen(buffer)); // Send new message back to client
    } else {
      break;
    }
  }

  // Clean up
  close(client_fd);
  close(server_fd);
  unlink(SOCKET_PATH);

  return 0;
}
