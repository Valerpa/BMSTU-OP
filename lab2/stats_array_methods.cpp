#include "stats_array_methods.h"

void write_stats_from_list(double *stats, Node* list, const int column_num) {
    int k = 0;
    while (list != NULL) {
        stats[k] = get_field_value(list, column_num);
        k++;
        list = list->next;
    }
}

void sort_stats_array(double *stats, size_t lines) {
    for (int i = 0; i < (int)(lines); i++) {
        for (int j = 0; j < (int)(lines) - 1; j++) {
            if (stats[j] > stats[j + 1]) {
                swap(stats + j, stats + j + 1);
            }
        }
    }
}


void swap(double *pa, double *pb) {
    double tmp = *pa;
    *pa = *pb;
    *pb = tmp;
}

double calculate_max(double *stats, size_t lines) {
    double maxim = stats[0];
    for (int i = 0; i < (int)lines; i++) {
        if (stats[i] > maxim) {
            maxim = stats[i];
        }
    }
    return maxim;
}

double calculate_min(double *stats, size_t lines) {
    double minim = stats[0];
    for (int i = 0; i < (int)lines; i++) {
        if (stats[i] < minim) {
            minim = stats[i];
        }
    }
    return minim;
}

double calculate_median(double *stats, size_t lines) {
    double med;
    int median_index = (int)(lines) / 2;
    if (median_index == 0) {
        med = stats[median_index];
    }
    else if (median_index % 2 == 0) {
        med = (stats[median_index] + stats[median_index - 1]) / 2.0;
    }
    else {
        med = stats[median_index];
    }
    return med;
}
