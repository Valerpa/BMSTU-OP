#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "appcontext.h"
#include "stringworks.h"
#include "list_methods.h"
#include "error_methods.h"

int calculate_max_line_len_in_file(FILE *fp);
size_t count_lines_in_file(FILE *fp);
size_t count_fields_in_file(FILE *fp);
bool read_headers(Table *table, FILE *fp, Headers *headers);
Node* read_and_delete_data_from_file(FILE *fp, List *list, int *deleted_lines, int max_len);

#endif // FILEMANAGER_H
