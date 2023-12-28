#ifndef APPLOGIC_H
#define APPLOGIC_H

#include "appcontext.h"
#include "stdio.h"
#include "filemanager.h"
#include "list_methods.h"
#include "stats_array_methods.h"
#include "stringworks.h"

void get_data_from_table(Table* table, List *list);
bool parse_data(FILE *fp, Dem_unit *dem_unit, Node* head, Node *current);
void load_data_by_region(Table *table, List *list, const char *chosen_region, int min_year, int max_year);
void calculate_metrics(Table *table, List *list, Metrics *metrics, const int column_num);
void clean_data(List* list);

#endif // APPLOGIC_H
