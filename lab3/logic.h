#ifndef LOGIC_H
#define LOGIC_H
#include "context.h"
#include "errorfuncs.h"
#include "filefuncs.h"
#include "stringworks.h"
#include "math.h"
#include "memory.h"

#define MATRIX_SIZE 4

void load_data(Context* context);
void rotate(Context* context);
void scale(Context* context);
void move(Context* context);
float get_min_z(Context* context);
float get_max_z(Context* context);
bool is_correct(char*** data, Context* context);
void rotate_x(Context* context);
void rotate_y(Context* context);
void rotate_z(Context* context);
void normalize(Context* context);
float** make_matrix_of_float(char*** data, Context* context);
void multiply_vector_matrix(Context* context, float matrix[][MATRIX_SIZE]);
void clean(Context* context);

#endif // LOGIC_H
