#ifndef STRINGWORKS_H
#define STRINGWORKS_H
#include "string.h"
#include "stdlib.h"
#include "memory.h"
#include "stdio.h"

char** str_split(char* arr, size_t* column, const char sep);
char*** fill_data(char** raw_data, size_t lines, size_t* columns);

#endif // STRINGWORKS_H
