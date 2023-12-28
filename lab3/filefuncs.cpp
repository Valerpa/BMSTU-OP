#include "filefuncs.h"

size_t calculate_number_of_lines(FILE* fp) {
    size_t count = 0;
    int c;
    do {
        c = fgetc(fp);
        if (c == '\n') {
            count++;
        }
    } while(c != EOF);

    return count + 1;
}

size_t calculate_max_len_str(FILE *fp) {
    int curr_len = 0;
    int max_len = 0;
    int c;
    while ((c = fgetc(fp)) != EOF) {
        curr_len++;
        if (c == '\n') {
            if (curr_len > max_len) {
                max_len = curr_len;
            }
            curr_len = 0;
        }
    }
    if (curr_len > max_len) {
        max_len = curr_len;
    }
    return max_len;
}

char** read_from_file(FILE* fp, Context* context) {
    int max_len = calculate_max_len_str(fp);
    rewind(fp);

    context->lines = calculate_number_of_lines(fp);
    rewind(fp);

    char line[max_len + 1];
    char** arr = (char**)malloc(context->lines * sizeof(char*));
    if (arr == NULL) {
        return NULL;
    }

    int i = 0;
    while (fgets(line, max_len + 1, fp)) {
        size_t a = strlen(line);
        size_t b;
        if (i == (int)context->lines - 1) {
            b = 1;
        }
        else {
            b = 0;
        }
        arr[i] = (char*)malloc(a + b);
        if (arr[i] == NULL) {
            clean_2d_array_of_char(arr, i);
            break;
        }
        snprintf(arr[i], a + b, "%s", line);
        i++;
    }
    context->lines = i;
    return arr;
}
