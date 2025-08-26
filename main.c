#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void usage() {
   printf("usage:\n");
   printf("term_chat create <port> for creating the room\n");
   printf("term_chat connect <ip> <port>\n");
   exit(1);
}

int main(int argc, char **argv) {
   if (argc < 3 || argc > 4) usage();
   
   if (strcmp(argv[1], "create") == 0) { // SERVER SIDE ==> fork to server.c
      printf("SERVER SIDE\n");
      int port_number = atoi(argv[2]);
      run_server(port_number);
   }
   else if (strcmp(argv[1], "connect") == 0) { // CLIENT SIDE ==> fork to client.c
      printf("CLIENT SIDE\n");
   }
}