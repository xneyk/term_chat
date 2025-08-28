#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h> // for treating IPs and PORT conversions

#ifndef SERVER_H
#define SERVER_H

/**
 * @brief Main function of server side
 */
void run_server(int port);

/**
 * @brief handle socket creation: socket(), bind() and listen()
 * @return socket file descriptor.
 */
int init_server_socket(int port);

/**
 * @brief wait for client connections and accept it
 * @return the client file descriptor where server and client can talk each other
 */
int accept_client(int socket_fd);

/**
 * @brief handle client connection ==> control I/O with it.
 */
void handle_client(int client_fd);

#endif