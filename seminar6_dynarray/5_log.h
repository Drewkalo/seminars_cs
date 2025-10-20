#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#ifdef DEBUG
#define LOG(message) fprintf(stderr, "[DEBUG] %s: %d: %s\n", __FILE__, __LINE__, message)
#else
#define LOG(message)

#endif