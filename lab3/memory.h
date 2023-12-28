#ifndef MEMORY_H
#define MEMORY_H
#include "stdlib.h"

void clean_2d_array_of_char(char** str_arr, size_t size);
void clean_2d_array_of_float(float** arr, size_t size);
void clean_3d_array(char*** str_arr, size_t size_x, size_t size_y);

#endif // MEMORY_H
