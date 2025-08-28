#include "server.h"

#define BUFFER_SIZE 1024

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
   if (listen(socket_fd, 5) < 0) { // maximum 5 pending connections before refusing the next one.
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
   while (1) {
      memset(buffer, 0, BUFFER_SIZE);
      if (read(client_fd, buffer, BUFFER_SIZE) <= 0) {
         printf("[INFO] client disconnected\n");
         break; // exit while loop;
      }
      printf("[INFO] recived %s", buffer);
      // bounce the message.
      if (send(client_fd, buffer, strlen(buffer), 0) < 0) {
         printf("[INFO] client disconnected\n");
         // Here we can check errno to know if it disconnected abruptly or not.
      }
   }
   free(buffer);  // free communication buffer
}