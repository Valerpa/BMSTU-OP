#include "stringworks.h"
#include <cstdlib>

Dem_unit parse_line(char *line) {
    Dem_unit unit;
    char *token = strtok(line, ",");
    unit.year = atoi(token);

    token = strtok(NULL, ",");
    unit.region = (char*)malloc(strlen(token) + 1);
    strncpy(unit.region, token, strlen(token) + 1);

    token = strtok(NULL, ",");
    unit.npg = atof(token);

    token = strtok(NULL, ",");
    unit.birth_rate = atof(token);

    token = strtok(NULL, ",");
    unit.death_rate = atof(token);

    token = strtok(NULL, ",");
    unit.gdw = atof(token);

    token = strtok(NULL, "\n");
    unit.urban = atof(token);

    return unit;
}

Table* parse_headers(Table *table, FILE *fp, int max_len) {
    char headers_line[max_len];
    fgets(headers_line, max_len + 1, fp);
    char *token = strtok(headers_line, ",");

    table->headers.year_header = (char*)malloc(strlen(token) + 1);
    if (table->headers.year_header == NULL) {
        initialize_error(table, 35, "Memory for year header was not allocated");
        return NULL;
    }
    strncpy(table->headers.year_header, token, strlen(token) + 1);

    token = strtok(NULL, ",");
    table->headers.region_header = (char*)malloc(strlen(token) + 1);
    if (table->headers.region_header == NULL) {
        initialize_error(table, 43, "Memory for region headers was not allocated");
        return NULL;
    }
    strncpy(table->headers.region_header, token, strlen(token) + 1);

    token = strtok(NULL, ",");
    table->headers.npg_header = (char*)malloc(strlen(token) + 1);
    if (table->headers.npg_header == NULL) {
        initialize_error(table, 50, "Memory for npg header was not allocated");
        return NULL;
    }
    strncpy(table->headers.npg_header, token, strlen(token) + 1);

    token = strtok(NULL, ",");
    table->headers.birth_rate_header = (char*)malloc(strlen(token) + 1);
    if (table->headers.birth_rate_header == NULL) {
        initialize_error(table, 58, "Memory for birth_rate header was not allocated");
        return NULL;
    }
    strncpy(table->headers.birth_rate_header, token, strlen(token) + 1);

    token = strtok(NULL, ",");
    table->headers.death_rate_header = (char*)malloc(strlen(token) + 1);
    if (table->headers.death_rate_header == NULL) {
        initialize_error(table, 67, "Memory for death_rate header was not allocated");
        return NULL;
    }
    strncpy(table->headers.death_rate_header, token, strlen(token) + 1);

    token = strtok(NULL, ",");
    table->headers.gdw_header = (char*)malloc(strlen(token) + 1);
    if (table->headers.gdw_header == NULL) {
        initialize_error(table, 75, "Memory for gdw header was not allocated");
        return NULL;
    }
    strncpy(table->headers.gdw_header, token, strlen(token) + 1);

    token = strtok(NULL, "\n");
    table->headers.urban_header = (char*)malloc(strlen(token) + 1);
    if (table->headers.urban_header == NULL) {
        initialize_error(table, 83, "Memory for urbanization header was not allocated");
        return NULL;
    }
    strncpy(table->headers.urban_header, token, strlen(token) + 1);
    return table;
}
