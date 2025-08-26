#include "common.h"

void log_msg(enum log_t type, char *msg) {
   if (type == ERROR_LOG) {
      char buff[256];
      sprintf(buff, "[ERROR] %s", msg);
      perror(buff);
   } else if (type == INFO_LOG) {
      char buff[256];
      sprintf(buff, "[INFO] %s", msg);
   }
}