#ifndef CONTEXT_H
#define CONTEXT_H
#include "stdlib.h"
#define MAX_LEN 50

enum Rotation_axis {
    X,
    Y,
    Z,
    NONE
};

typedef struct Error {
    char err_info[MAX_LEN] = "\0";
    bool check = true;
}Error;

typedef struct Point_3d {
    float x;
    float y;
    float z;
}Point_3d;

typedef struct Normalization_parameters {
    float min;
    float max;
    float step;
}Normalization_parameters;

typedef struct Scale_params {
    float x_scale;
    float y_scale;
    float z_scale;
}Scale_params;

typedef struct Move_params {
    float x_move;
    float y_move;
    float z_move;
}Move_params;

typedef struct Context {
    float rotation;
    char* file_name = NULL;
    size_t lines = 0;
    size_t columns = 0;
    Point_3d* figure = NULL;
    size_t number_of_points;
    float** matrix = NULL;
    Normalization_parameters params;
    Scale_params scale;
    Move_params move;
    Rotation_axis axis = NONE;
    Error error;
}Context;

#endif // CONTEXT_H
