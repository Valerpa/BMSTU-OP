#ifndef STRINGWORKS_H
#define STRINGWORKS_H

#include <string.h>
#include <stdlib.h>
#include "appcontext.h"
#include "error_methods.h"

Dem_unit parse_line(char *line);
Table* parse_headers(Table *table, FILE *fp, int max_len);

#endif // STRINGWORKS_H
