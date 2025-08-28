#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> // for treating IPs and PORT conversions

#ifndef CLIENT_H
#define CLIENT_H

/**
 * @brief main function of the client side
 */
void run_client(char *server_IP, int port);

/**
 * @brief initialize the socket (socket(...))
 * @return socket file descriptor
 */
int init_client_socket();

/**
 * @brief connects with the server and check connection is succefully estabilshed.
 */
void connect_socket(int socket_fd, char *server_IP, int port);

/**
 * @brief handles the connection between the client and the server (controls I/O)
 */
void handle_connection(int socket_fd);

#endif