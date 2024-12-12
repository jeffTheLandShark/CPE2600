
/**********************************************
 *  @file unix_socket_chat_server.c
 *  @brief Chat server using unix sockets based on "unix_socket_read.c"
 *
 *  @author Leigh Goetsch, Alex Roe-Gulke
 *  @note gcc -o unix_socket_chat_server unix_socket_chat_server.c
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

int server_fd, client_fd, max_fd;
char *usernames[FD_SETSIZE] = {NULL};

void exit_handler() {
  close(server_fd);
  unlink(SOCKET_PATH);
  for (int i = 0; i <= max_fd; i++) {
    if (usernames[i] != NULL) {
      free(usernames[i]);
    }
  }
}

void sigint_handler(int sig) {
  exit_handler();
  exit(EXIT_SUCCESS);
}

int main() {
  atexit(exit_handler);
  // Register the SIGINT handler
  signal(SIGINT, sigint_handler);

  struct sockaddr_un server_addr;
  fd_set read_fds;
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

  // Initialize the set of active sockets
  FD_ZERO(&read_fds);
  FD_SET(server_fd, &read_fds);
  max_fd = server_fd;

  while (1) {
    fd_set temp_fds = read_fds;

    if (select(max_fd + 1, &temp_fds, NULL, NULL, NULL) < 0) {
      perror("select error");
      close(server_fd);
      exit(EXIT_FAILURE);
    }

    // Check for new connections
    if (FD_ISSET(server_fd, &temp_fds)) {
      if ((client_fd = accept(server_fd, NULL, NULL)) == -1) {
        perror("accept error");
        continue;
      }
      printf("New connection accepted\n");
      FD_SET(client_fd, &read_fds);
      if (client_fd > max_fd) {
        max_fd = client_fd;
      }

      // Store the username
      char username[BUFFER_SIZE];
      int bytes_read = read(client_fd, username, sizeof(username) - 1);
      if (bytes_read > 0) {
        username[bytes_read] = '\0';
        printf("Username received: %s\n", username);
      } else {
        free(usernames[client_fd]);
        usernames[client_fd] = NULL;
        close(client_fd);
        FD_CLR(client_fd, &read_fds);
      }
      usernames[client_fd] = strdup(username);

      // Notify others that this user has joined
      char join_message[BUFFER_SIZE + 50];
      snprintf(join_message, sizeof(join_message), "%s has joined the chat.\n",
               username);
      for (int j = 0; j <= max_fd; j++) {
        if (FD_ISSET(j, &read_fds) && j != server_fd && j != client_fd) {
          write(j, join_message, strlen(join_message));
        }
      }
    }

    // Check for data from clients
    for (int i = 0; i <= max_fd; i++) {
      if (FD_ISSET(i, &temp_fds) && i != server_fd) {
        int bytes_read = read(i, buffer, sizeof(buffer) - 1);
        if (bytes_read > 0) {
          buffer[bytes_read] = '\0';
          printf("Received from %s: %s\n", usernames[i], buffer);

          // Prepare the message with the sender's identifier
          char message[BUFFER_SIZE + 50];
          snprintf(message, sizeof(message), "%s: %s", usernames[i], buffer);

          // Echo the message back to all clients
          for (int j = 0; j <= max_fd; j++) {
            if (FD_ISSET(j, &read_fds) && j != server_fd && j != i) {
              write(j, message, strlen(message) - 1);
            }
          }
        } else {

          // Notify others that this user has left
          char leave_message[BUFFER_SIZE + 50];
          snprintf(leave_message, sizeof(leave_message),
                   "%s has left the chat.\n", usernames[i]);
          for (int j = 0; j <= max_fd; j++) {
            if (FD_ISSET(j, &read_fds) && j != server_fd && j != i) {
              write(j, leave_message, strlen(leave_message));
            }
          }
          printf("User left: %s\n", usernames[i]);
          close(i);
          FD_CLR(i, &read_fds);
        }
      }
    }
  }

  return 0;
}