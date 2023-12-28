#include "error_methods.h"

void initialize_error(Table* table, const int line, const char* error_info) {
    table->errors.error_check = 1;
    table->errors.err_line = line;
    strncpy(table->errors.err_info, error_info, SIZE + 1);
}
