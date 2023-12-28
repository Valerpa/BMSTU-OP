#include "filemanager.h"

int calculate_max_line_len_in_file(FILE *fp) {
    int current_length = 0, max_length = 0;
    int c;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            if (current_length > max_length) {
                max_length = current_length + 1;
            }
            current_length = 0;
        }
        else current_length++;
    }
    if (current_length > max_length) {
        max_length = current_length + 1;
    }
    return max_length;
}

size_t count_lines_in_file(FILE *fp) {
    int c;
    size_t lines = 0;
    do {
        c = fgetc(fp);
        if (c == '\n') {
            lines++;
        }
    } while (c != EOF);

    rewind(fp);
    c = fgetc(fp);

    if (c != EOF && lines == 0) {
        lines++;
    }
    return lines;
}

size_t count_fields_in_file(FILE *fp) {
    int c;
    size_t fields = 0;
    while ((c = fgetc(fp)) != '\n' && c != EOF) {
        if (c == ',') {
            fields++;
        }
    }
    fields++;
    return fields;
}

Node* read_and_delete_data_from_file(FILE *fp, List *list, int *deleted_lines, int max_len) {
    char line[max_len];
    while(fgets(line, max_len + 1, fp)) {
        if(strstr(line, ",,")) {
            (*deleted_lines)++;
            continue;
        }
        Dem_unit dem_unit = parse_line(line);
        add_node(list, dem_unit);
    }
    return list->head;
}
