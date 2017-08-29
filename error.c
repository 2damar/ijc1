#include "error.h"

void warning_msg(const char* fmt, ...) {
   fprintf(stderr, "WARNING: ");
   va_list ap;
   va_start(ap, fmt);

   vfprintf(stderr, fmt, ap);
   va_end(ap);
   exit(1);
}

void error_msg(const char* fmt, ...) {
   fprintf(stderr, "ERROR: ");
   va_list ap;
   va_start(ap, fmt);
  
   vfprintf(stderr, fmt, ap);
   va_end(ap);
   exit(1);
}
