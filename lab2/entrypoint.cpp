#include "entrypoint.h"

void entry_point(Operations operations, Table* table, List *lst, Metrics *metrics, Params *params) {
    switch (operations) {
        case Open_file:
            get_data_from_table(table, lst);
            break;
        case Load_data:
            load_data_by_region(table, lst, params->chosen_region, params->min_year, params->max_year);
            break;
        case Calculate_metrics:
            calculate_metrics(table, lst, metrics, params->column_num);
            break;
        case Clean_data:
            clean_data(lst);
            break;
    }
}
