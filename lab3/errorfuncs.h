#ifndef ERRORFUNCS_H
#define ERRORFUNCS_H
#include "context.h"
#include "string.h"

#define OPEN_FILE_ERROR "File was not opened!"
#define MEMORY_ALLOCATION_ERROR "Memory was not allocated!"
#define TYPE_ERROR "Expected numbers in file!"
#define EMPTY_ELEMENTS_ERROR "Number in matrix was not found!"
#define SCALE_PARAMS_ERROR "All scale parameters must be positive"
#define NORMALIZATION_PARAMS_ERROR "Incorrect normalization parameters"

void open_file_error(Context* context);
void memory_error(Context* context);
void type_error(Context* context);
void empty_elem_error(Context* context);
void scale_params_error(Context* context);
void norm_params_error(Context* context);

#endif // ERRORFUNCS_H
