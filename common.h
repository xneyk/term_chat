#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#ifndef COMMON_H
#define COMMON_H

enum log_t {
   ERROR_LOG,
   INFO_LOG
};

void log_msg(enum log_t type, char *msg);

#endif