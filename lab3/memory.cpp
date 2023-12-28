#include "memory.h"

void clean_2d_array_of_char(char** str_arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        free(str_arr[i]);
    }
    free(str_arr);
}

void clean_2d_array_of_float(float** arr, size_t size) {
    for (size_t i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}

void clean_3d_array(char*** str_arr, size_t size_x, size_t size_y) {
    for (size_t i = 0; i < size_x; i++) {
        clean_2d_array_of_char(str_arr[i], size_y);
    }
    free(str_arr);
}
