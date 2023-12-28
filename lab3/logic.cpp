#include "logic.h"

void load_data(Context* context) {
    FILE* fp = fopen(context->file_name, "r");
    if (!fp) {
        open_file_error(context);
        return;
    }
    char** arr = read_from_file(fp, context);
    fclose(fp);
    if (arr == NULL) {
        memory_error(context);
        return;
    }
    char*** data = fill_data(arr, context->lines, &context->columns);
    if (data == NULL) {
        memory_error(context);
        clean_2d_array_of_char(arr, context->lines);
        return;
    }
    if (is_correct(data, context) == false) {
        empty_elem_error(context);
        clean_3d_array(data, context->lines, context->columns);
        clean_2d_array_of_char(arr, context->lines);
        return;
    }
    float** matrix = make_matrix_of_float(data, context);
    if (matrix == NULL) {
        memory_error(context);
        clean_3d_array(data, context->lines, context->columns);
        clean_2d_array_of_char(arr, context->lines);
        return;
    }
    context->matrix = matrix;
    clean_3d_array(data, context->lines, context->columns);
    clean_2d_array_of_char(arr, context->lines);
    Point_3d* figure = (Point_3d*)malloc(context->lines * context->columns * sizeof(Point_3d));
    if (figure == NULL) {
        memory_error(context);
        return;
    }
    int index = 0;
    for (size_t i = 0; i < context->lines; i++) {
        for (size_t j = 0; j < context->columns; j++) {
            figure[index].x = i;
            figure[index].y = j;
            figure[index].z = context->matrix[i][j];
            index++;
        }
    }
    context->number_of_points = index;
    context->figure = figure;
    normalize(context);
}

void rotate(Context* context) {
    switch(context->axis) {
    case X:
        rotate_x(context);
        break;
    case Y:
        rotate_y(context);
        break;
    case Z:
        rotate_z(context);
        break;
    default:
       break;
    }
}

void scale(Context* context) {
    if (context->scale.x_scale <= 0 || context->scale.y_scale <= 0 || context->scale.z_scale <= 0) {
        scale_params_error(context);
        return;
    }
    float x = context->scale.x_scale;
    float y = context->scale.y_scale;
    float z = context->scale.z_scale;
    float matrix[MATRIX_SIZE][MATRIX_SIZE] = {{x, 0, 0, 0},
                                              {0, y, 0, 0},
                                              {0, 0, z, 0},
                                              {0, 0, 0, 1}};
    multiply_vector_matrix(context, matrix);
}

void move(Context* context) {
    float x = context->move.x_move;
    float y = context->move.y_move;
    float z = context->move.z_move;
    float matrix[MATRIX_SIZE][MATRIX_SIZE] = {{1, 0, 0, x},
                                              {0, 1, 0, y},
                                              {0, 0, 1, z},
                                              {0, 0, 0, 1}};
    multiply_vector_matrix(context, matrix);
}

float get_min_z(Context* context) {
    float minim = context->figure[0].z;
    for (size_t i = 1; i < context->number_of_points; i++) {
        if (context->figure[i].z < minim) {
            minim = context->figure[i].z;
        }
    }
    return minim;
}

float get_max_z(Context* context) {
    float maxim = context->figure[0].z;
    for (size_t i = 1; i < context->number_of_points; i++) {
        if (context->figure[i].z > maxim) {
            maxim = context->figure[i].z;
        }
    }
    return maxim;
}

bool is_correct(char*** data, Context* context) {
    bool flag = true;
    for (size_t i = 0; i < context->lines; i++) {
        for (size_t j = 0; j < context->columns; j++) {
            if (strcmp(data[i][j], "") == 0) {
                flag = false;
            }
        }
    }
    return flag;
}

void rotate_x(Context* context) {
    float rad_x = (M_PI / 180) * context->rotation;
    float matrix[MATRIX_SIZE][MATRIX_SIZE] = {{1,     0,           0,      0},
                                              {0, cos(rad_x), -sin(rad_x), 0},
                                              {0, sin(rad_x),  cos(rad_x), 0},
                                              {0,     0,           0,      1}};
    multiply_vector_matrix(context, matrix);
}
void rotate_y(Context* context) {
    float rad_y = (M_PI / 180) * context->rotation;
    float matrix[MATRIX_SIZE][MATRIX_SIZE] = {{cos(rad_y), 0, sin(rad_y), 0},
                                              {    0,      1,     0,      0},
                                              {-sin(rad_y),0, cos(rad_y), 0},
                                              {    0,      0,     0,      1}};
    multiply_vector_matrix(context, matrix);
}

void rotate_z(Context* context) {
    float rad_z = (M_PI / 180) * context->rotation;
    float matrix[MATRIX_SIZE][MATRIX_SIZE] = {{cos(rad_z), -sin(rad_z), 0, 0},
                                              {sin(rad_z),  cos(rad_z), 0, 0},
                                              {0,                0,     1, 0},
                                              {0,                0,     0, 1}};
    multiply_vector_matrix(context, matrix);
}

void normalize(Context* context) {
    if (context->params.max == 0 && context->params.min == 0 && context->params.step == 0) {
        norm_params_error(context);
        return;
    }
    for (size_t i = 0; i < context->number_of_points; i++) {
        context->figure[i].x = context->figure[i].x * context->params.step;
        context->figure[i].y = context->figure[i].y * context->params.step;
    }
    float min_z = get_min_z(context);
    float max_z = get_max_z(context);
    for (size_t i = 0; i < context->number_of_points; i++) {
       context->figure[i].z = context->params.min + ((context->figure[i].z - min_z) / (max_z - min_z)) * (context->params.max - context->params.min);
    }
}

float** make_matrix_of_float(char*** data, Context* context) {
    float** matrix = (float**)malloc(context->lines * sizeof(float*));
    if (matrix == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < context->lines; i++) {
        matrix[i] = (float*)malloc(context->columns * sizeof(float));
        if (matrix[i] == NULL) {
            clean_2d_array_of_float(matrix, i);
            matrix = NULL;
            break;
        }
        for (size_t j = 0; j < context->columns; j++) {
            matrix[i][j] = atof(data[i][j]);
        }
    }
    return matrix;
}

void multiply_vector_matrix(Context* context, float matrix[][MATRIX_SIZE]) {
    for (size_t i = 0; i < context->number_of_points; i++) {
        Point_3d tmp_point = context->figure[i];
        context->figure[i].x = matrix[0][0] * tmp_point.x + matrix[0][1] * tmp_point.y + matrix[0][2] * tmp_point.z + matrix[0][3];
        context->figure[i].y = matrix[1][0] * tmp_point.x + matrix[1][1] * tmp_point.y + matrix[1][2] * tmp_point.z + matrix[1][3];
        context->figure[i].z = matrix[2][0] * tmp_point.x + matrix[2][1] * tmp_point.y + matrix[2][2] * tmp_point.z + matrix[2][3];
    }
}

void clean(Context* context) {
    if (context->file_name) {
        free(context->file_name);
    }
    if (context->figure) {
        free(context->figure);
    }
    if (context->matrix) {
        clean_2d_array_of_float(context->matrix, context->lines);
    }
    context->error.check = true;
}
