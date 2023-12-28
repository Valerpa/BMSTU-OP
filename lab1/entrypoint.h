#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H
#include "appcontext.h"
#include "logic.h"

enum Operation
{
    Add_Digit,
    Separator,
    Clear_all,
    Del_last_digit,
    Equality,
    Sign,
    Summ,
    Substraction,
    Multiplication,
    Division,
    Root,
    One_division,
    M_plus,
    M_minus,
    M_R,
    M_C,
    Sin,
    Cos,
    Tan,
    Cot
};

void do_operation(Operation operation, App_context* context, void* params);

#endif // ENTRYPOINT_H
