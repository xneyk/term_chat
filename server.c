#include "server.h"

#define BUFFER_SIZE 1024
#define MAX_PENDING_CONNECTIONS 1

void run_server(int port) {
   int socket_fd = init_server_socket(port);
   printf("[INFO] socket succefully created:) listening on port %d\n", port);

   int client_fd = accept_client(socket_fd);

   handle_client(client_fd);

   close(client_fd);
   close(socket_fd);
   exit(EXIT_SUCCESS);
};

int init_server_socket(int port) {
   // Defines a socket with IPv4 communication and TCP protocol.
   int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
   // Handle creation error.
   if (socket_fd <= 0) {
      perror("[ERROR] socket creation failed");
      exit(EXIT_FAILURE);
   }

   // Define socket address & config
   struct sockaddr_in socket_address;
   socket_address.sin_family = AF_INET; // Tell the address is IPv4
   socket_address.sin_addr.s_addr = INADDR_ANY; // Tell to listen all the interfaces
   socket_address.sin_port = htons(port); // Parse the port to the expected format.

   // Bind socket
   if (bind(socket_fd, (struct sockaddr*)&socket_address, sizeof(socket_address)) < 0) {
      perror("[ERROR] socket binding failed");
      exit(EXIT_FAILURE);
   }

   // Listen socket (Tell OS this socket will accept connections)
   if (listen(socket_fd, MAX_PENDING_CONNECTIONS) < 0) { // maximum 5 pending connections before refusing the next one.
      perror("[ERROR] socket listen failed");
      close(socket_fd); // close socket file descriptor
      exit(EXIT_FAILURE);
   }

   return socket_fd;
}

int accept_client(int socket_fd) {
   struct sockaddr_in client_address;
   socklen_t client_addr_lenght = sizeof(client_address);
   // Wait for a connection for accepting it.
   int client_fd = accept(socket_fd, (struct sockaddr*)&client_address, &client_addr_lenght);

   if (client_fd < 0) {
      perror("[ERROR] socket accept failed");
      close(socket_fd); // close socket file descriptor
      exit(EXIT_FAILURE);
   }

   return client_fd;
}

void handle_client(int client_fd) {
   char *buffer = malloc(BUFFER_SIZE); // reserve communication buffer on dynamic memory
   fd_set readfds; // set of filedescriptors that need to be watched to read.
   int max_fd;
   while (1) {
      memset(buffer, 0, BUFFER_SIZE);
      FD_ZERO(&readfds);
      FD_SET(STDIN_FILENO, &readfds); // add STDIN
      FD_SET(client_fd, &readfds); // add socket's fd

      max_fd = (client_fd > STDIN_FILENO ? client_fd : STDIN_FILENO) + 1; // choose the max value and add 1.

      // Wait for any channel to have activity
      if (select(max_fd, &readfds, NULL, NULL, NULL) < 0) {
         perror("[ERROR] failure while select(...) syscall");
         exit(EXIT_FAILURE);
      }

      int bytes_read;
      // got a message from the client
      if (FD_ISSET(client_fd, &readfds)) {
         bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
         if (bytes_read <= 0) {
            printf("[INFO] client disconnected\n");
            break; // exit while loop;
         }
         buffer[bytes_read] = '\0'; // add string end to the message
         printf("[-->]: %s\n", buffer); // show recieved message to server user.
      }

      // got a message to send (stdin ready)
      if (FD_ISSET(STDIN_FILENO, &readfds)) {
         bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
         if (bytes_read > 0) {
            buffer[bytes_read - 1] = '\0'; // replace '\n' --> '\0' for null-terminated-str
            send(client_fd, buffer, strlen(buffer), 0); // send data to client.
         }
      }

   }
   free(buffer);  // free communication buffer
}