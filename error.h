#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void warning_msg(const char* fmt, ...);
void error_msg(const char* fmt, ...);

#endif
