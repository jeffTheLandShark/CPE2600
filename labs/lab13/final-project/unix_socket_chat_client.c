/**********************************************
 *  @file unix_socket_chat_client.c
 *  @brief Chat client using unix sockets based on "unix_socket_read.c"
 *
 *  @author: Leigh Goetsch, Alex Roe-Gulke
 *  @note: gcc -o unix_socket_chat_client unix_socket_chat_client.c
 ***********************************************/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/chatroom"
#define BUFFER_SIZE 150

int client_fd, max_fd;

// Ensures no memory leak when exiting program
void exit_handler() {
  if (client_fd != -1) {
    close(client_fd);
  }
}
// Singal handler so the program exits gracefully
void sigint_handler(int sig) {
  exit_handler();
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  atexit(exit_handler);
  // Register the SIGINT handler
  signal(SIGINT, sigint_handler);
  struct sockaddr_un server_addr;
  fd_set read_fds;
  char buffer[BUFFER_SIZE];
  char username[BUFFER_SIZE];

  // If username was given, apply it
  if (argc == 1) {
    strcpy(username, "Guest");
  } else if (argc == 2) {
    strcpy(username, argv[1]);
  } else {
    printf("Usage: %s [username]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

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

  // Send initial message to the server
  if (write(client_fd, username, strlen(username)) == -1) {
    perror("write error");
    close(client_fd);
    exit(EXIT_FAILURE);
  }

  // Initialize the set of active sockets
  FD_ZERO(&read_fds);
  FD_SET(client_fd, &read_fds);
  FD_SET(STDIN_FILENO, &read_fds);
  max_fd = client_fd;

  //Program loop
  while (1) {
    fd_set temp_fds = read_fds;

    if (select(max_fd + 1, &temp_fds, NULL, NULL, NULL) < 0) {
      perror("select error");
      close(client_fd);
      exit(EXIT_FAILURE);
    }

    // Check for user input
    if (FD_ISSET(STDIN_FILENO, &temp_fds)) {
      fgets(buffer, sizeof(buffer), stdin);
      if (strcmp(buffer, "exit\n") == 0) {
        close(client_fd);
        exit(EXIT_SUCCESS);
      }
      if (write(client_fd, buffer, strlen(buffer)) == -1) {
        perror("write error");
        close(client_fd);
        exit(EXIT_FAILURE);
      }

      
    }

    // Check for messages from the server
    if (FD_ISSET(client_fd, &temp_fds)) {
      int bytes_read = read(client_fd, buffer, sizeof(buffer) - 1);
      if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("%s\n", buffer);
      } else {
        printf("Server disconnected\n");
        close(client_fd);
        exit(EXIT_FAILURE);
      }
    }
  }

  return 0;
}