#ifndef LIST_METHODS_H
#define LIST_METHODS_H
#include "appcontext.h"
#include "stdlib.h"
#include "stdio.h"
#include "error_methods.h"

typedef struct Node {
    Dem_unit data;
    Node *next;
}Node;

typedef struct List {
    Node *head;
}List;

void free_list(List *list);
void add_node(List *list, Dem_unit data);
void delete_node(Table *table, List *list, const char *chosen_region, int min_year, int max_year);
double get_field_value(Node *list, int column_num);

#endif // LIST_METHODS_H
