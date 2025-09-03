#include "client.h"

#define BUFFER_SIZE 1024

typedef struct {
   int socket_fd;
} SocketReadingThreadArgs;

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
   pthread_t tid; // stores the thread id
   SocketReadingThreadArgs args; // A struct is used to follow a safety pattern.
   args.socket_fd = socket_fd;

   // create a thread dedicated to read socket and print the recived messages
   pthread_create(&tid, NULL, read_socket, &args);
   pthread_detach(tid); // tell SO to free it's resources on dying. (We don't need to collect any data).

   char *buffer = malloc(BUFFER_SIZE);
   int bytes_read = 0;
   while((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE))) {
      buffer[bytes_read - 1] = '\0'; // replace '\n' --> '\0' for null-terminated-str
      if (send(socket_fd, buffer, bytes_read, 0) < 0) {
         printf("[INFO] server disconnected\n");
         // Here we can check errno to know if it disconnected abruptly or not.
         break;
      }
   }
   free(buffer);
}

void *read_socket(void *arg) {
   SocketReadingThreadArgs *thread_args = (SocketReadingThreadArgs *)arg; // convert to the correct type
   int socket_fd = thread_args->socket_fd;

   char *buffer = malloc(BUFFER_SIZE);
   int bytes_read = 0;
   while((bytes_read = read(socket_fd, buffer, BUFFER_SIZE - 1))) {
      if (bytes_read <= 0) {
         printf("[INFO]: server disconnected\n");
         break;
      }

      buffer[bytes_read] = '\0'; // add string terminator.
      printf("[-->]: %s\n", buffer); // Show recieved message to client user.
   }
   free(buffer);

   return (void *)NULL;
}