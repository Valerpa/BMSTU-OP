#include "list_methods.h"

void free_list(List *list) {
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void add_node(List *list, Dem_unit data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if(new_node == NULL) {
        return;
    }
    new_node->data = data;
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
        return;
    }

    Node *current_node = list->head;
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }

    current_node->next = new_node;
}

void delete_node(Table *table, List *list, const char *chosen_region, int min_year, int max_year) {
    Node* curr = list->head;
    Node* prev = NULL;
    while (curr != NULL) {
        if ((strcmp(curr->data.region, chosen_region) != 0) || (curr->data.year < min_year) || (curr->data.year > max_year)) {
            if (prev == NULL) {
                list->head = curr->next;
            }
            else {
                prev->next = curr->next;
            }
            Node* temp = curr;
            curr = curr->next;
            free(temp);
            table->lines--;
        }
        else {
            prev = curr;
            curr = curr->next;
        }
    }
}

double get_field_value(Node *list, const int column_num) {
    double field;
    switch (column_num) {
        case 3:
            field = list->data.npg;
            break;
        case 4:
            field = list->data.birth_rate;
            break;
        case 5:
            field = list->data.death_rate;
            break;
        case 6:
            field = list->data.gdw;
            break;
        case 7:
            field = list->data.urban;
            break;
    }
    return field;
}

