#include "client.h"

#define BUFFER_SIZE 1024

void run_client(char *server_IP, int port) {
   // Create the socket.
   int socket_fd = init_client_socket();
   // Estabilsh connection with the server.
   connect_socket(socket_fd, server_IP, port);

   // Connection established ==> Handle connection
   handle_connection(socket_fd);
   // Close client's socket file descriptor
   close(socket_fd);
   exit(EXIT_SUCCESS);
}

int init_client_socket() {
   // Defines a socket with IPv4 communication and TCP protocol.
   int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
   // Handle creation error.
   if (socket_fd <= 0) {
      perror("[ERROR] socket creation failed");
      exit(EXIT_FAILURE);
   }
   
   return socket_fd;
}

void connect_socket(int socket_fd, char *server_IP, int port) {
   struct sockaddr_in server_addr;
   server_addr.sin_family = AF_INET; // Tell the address is IPv4.
   server_addr.sin_port = htons(port); // Parse the port to the expected format.
   if (inet_pton(AF_INET, server_IP, &server_addr.sin_addr) < 0) { // Tell the address of the server.
      // Handle conversion errors
      perror("[ERROR] Invalid or non supported address");
      exit(EXIT_FAILURE);
   }

   // Connect the socket to server.
   if (connect(socket_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
      perror("[ERROR] Failed to connect with the server");
      exit(EXIT_FAILURE);
   }
}

void handle_connection(int socket_fd) {
   char *buffer = malloc(BUFFER_SIZE);
   int bytes_readed = 0;
   while((bytes_readed = read(STDIN_FILENO, buffer, BUFFER_SIZE))) {
      if (send(socket_fd, buffer, bytes_readed, 0) < 0) {
         printf("[INFO] server disconnected\n");
         // Here we can check errno to know if it disconnected abruptly or not.
      }
   }
   free(buffer);
}