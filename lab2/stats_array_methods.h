#ifndef STATS_ARRAY_METHODS_H
#define STATS_ARRAY_METHODS_H

#include "list_methods.h"

void write_stats_from_list(double *stats, Node* list, const int column_num);
void sort_stats_array(double *stats, size_t lines);
void swap(double *pa, double *pb);
double calculate_max(double *stats, size_t lines);
double calculate_min(double *stats, size_t lines);
double calculate_median(double *stats, size_t lines);

#endif // STATS_ARRAY_METHODS_H
