#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

#include "server.h"
#include "client.h"

void usage() {
   printf("usage:\n");
   printf("term_chat create <port> for creating the room\n");
   printf("term_chat connect <ip> <port>\n");
   exit(1);
}

int main(int argc, char **argv) {
   if (argc < 3 || argc > 4) usage();
   
   signal(SIGPIPE, SIG_IGN); // avoid send(...) to generate a SIGPIPE ==> is better to treat it.
   
   int port_number;
   
   if (strcmp(argv[1], "create") == 0) { // SERVER SIDE ==> fork to server.c
      printf("SERVER SIDE\n");
      port_number = atoi(argv[2]);
      run_server(port_number);
   }
   else if (strcmp(argv[1], "connect") == 0) { // CLIENT SIDE ==> fork to client.c
      printf("CLIENT SIDE\n");
      port_number = atoi(argv[3]);
      run_client(argv[2], port_number);
   }
}