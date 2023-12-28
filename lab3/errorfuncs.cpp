#include "errorfuncs.h"

void open_file_error(Context* context) {
    context->error.check = false;
    strncpy(context->error.err_info, OPEN_FILE_ERROR, MAX_LEN + 1);
}

void memory_error(Context* context) {
    context->error.check = false;
    strncpy(context->error.err_info, MEMORY_ALLOCATION_ERROR, MAX_LEN + 1);
}

void type_error(Context* context) {
    context->error.check = false;
    strncpy(context->error.err_info, TYPE_ERROR, MAX_LEN + 1);
}

void empty_elem_error(Context* context) {
    context->error.check = false;
    strncpy(context->error.err_info, EMPTY_ELEMENTS_ERROR, MAX_LEN + 1);
}

void scale_params_error(Context* context) {
    context->error.check = false;
    strncpy(context->error.err_info, SCALE_PARAMS_ERROR, MAX_LEN + 1);
}

void norm_params_error(Context* context) {
    context->error.check = false;
    strncpy(context->error.err_info, NORMALIZATION_PARAMS_ERROR, MAX_LEN + 1);
}
