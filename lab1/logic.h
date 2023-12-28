#ifndef LOGIC_H
#define LOGIC_H
#include "appcontext.h"
#include "cmath"
#include "string"

#define DEFAULT_VALUE 0


void input_number(App_context* context, char* new_value);
void separate(App_context* context);
void clear(App_context* context);
void delete_last_digit(App_context* context);
void do_equality(App_context* context);
void change_sign(App_context* context);
void plus(App_context* context);
void substract(App_context* context);
void multiply(App_context* context);
void divide(App_context* context);
void divide_1_by_x(App_context* context);
void calculate_root(App_context* context);
void calculate_sin(App_context* context);
void calculate_cos(App_context* context);
void calculate_tan(App_context* context);
void calculate_cot(App_context* context);
void do_m_plus(App_context* context);
void do_m_minus(App_context* context);
void do_mr(App_context* context);
void do_mc(App_context* context);


#endif // LOGIC_H
