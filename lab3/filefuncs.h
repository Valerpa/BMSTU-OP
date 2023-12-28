#ifndef FILEFUNCS_H
#define FILEFUNCS_H
#include "context.h"
#include "errorfuncs.h"
#include "memory.h"
#include "stdio.h"

size_t calculate_number_of_lines(FILE* fp);
size_t calculate_max_len_str(FILE* fp);
char** read_from_file(FILE* fp, Context* context);

#endif // FILEFUNCS_H
