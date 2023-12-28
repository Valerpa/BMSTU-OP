#include "applogic.h"
void get_data_from_table(Table* table, List *list) {
    FILE *fp = fopen(table->filename, "r");
    if (!fp) {
        initialize_error(table, 3, "File was not opened");
        return;
    }

    table->fields = count_fields_in_file(fp);
    rewind(fp);

    int max_len_str = calculate_max_line_len_in_file(fp);
    rewind(fp);

    table->lines = count_lines_in_file(fp);
    rewind(fp);

    if ((table = parse_headers(table, fp, max_len_str)) == NULL) {
        initialize_error(table, 18, "Can't read headers");
        fclose(fp);
        return;
    }
    int deleted_lines = 0;
    list->head = NULL;
    list->head = read_and_delete_data_from_file(fp, list, &deleted_lines, max_len_str);
    table->lines -= deleted_lines;
    table->invalid_lines = deleted_lines;
    fclose(fp);

}
void load_data_by_region(Table *table, List *list, const char *chosen_region, int min_year, int max_year) {
    delete_node(table, list, chosen_region, min_year, max_year);
}

void calculate_metrics(Table *table, List *list, Metrics *metrics, const int column_num) {
    Node* node = list->head;
    if (node == NULL) {
        initialize_error(table, 35, "Memory for list was not allocated");
        metrics->max_value = 0;
        metrics->min_value = 0;
        metrics->median = 0;
        return;
    }
    if (column_num < 3 || column_num > 7) {
        initialize_error(table, 35, "Invalid number of column");
        return;
    }
    double *stats = (double*)malloc((table->lines - 1) * sizeof(double));
    if (stats == NULL) {
        initialize_error(table, 48, "Memory for array of stats was not allocated");
        return;
    }
    write_stats_from_list(stats, node, column_num);
    double maxim = calculate_max(stats, table->lines - 1);
    double minim = calculate_min(stats, table->lines - 1);
    sort_stats_array(stats, table->lines - 1);
    double median = calculate_median(stats, table->lines - 1);
    metrics->max_value = maxim;
    metrics->min_value = minim;
    free(stats);
    metrics->median = median;
}

void clean_data(List* list) {
    free_list(list);
}
