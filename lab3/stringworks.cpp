#include "stringworks.h"

char** str_split(char* arr, size_t* column, const char sep) {
    char** result = NULL;
    size_t num_of_colms = 0;
    char* tmp = arr;
    while (*tmp) {
        if (*tmp == sep) {
            num_of_colms++;
        }
        tmp++;
    }
    num_of_colms++;
    *column = num_of_colms;
    result = (char**)malloc(num_of_colms * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }
    size_t index = 0;
    char* token = arr;
    for (char* end = (char*)strchr(token, sep); end; token = end + 1, end = (char*)strchr(token, sep), index++) {
        result[index] = (char*)malloc(end - token + 1);
        if (result[index] == NULL) {
            clean_2d_array_of_char(result, index);
            result = NULL;
            break;
        }
        else {
            snprintf(result[index], end - token + 1, "%s", token);
        }
    }
    if (result == NULL) {
        return NULL;
    }
    result[index++] = strdup(token);
    return result;
}

char*** fill_data(char** raw_data, size_t lines, size_t* columns) {
    char ***data = (char***)malloc(lines * sizeof(char**));
    if (data == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < lines; i++) {
        data[i] = str_split(raw_data[i], columns, ',');
        if (data[i] == NULL) {
            clean_3d_array(data, i, lines);
            data = NULL;
            break;
        }

    }
    return data;
}
