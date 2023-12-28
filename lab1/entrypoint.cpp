#include "entrypoint.h"

void do_operation(Operation operation, App_context* context, void* params)
{
    switch(operation)
    {
    case Add_Digit:
      input_number(context, (char*)params);
      break;
    case Separator:
        separate(context);
        break;
    case Clear_all:
        clear(context);
        break;
    case Del_last_digit:
        delete_last_digit(context);
        break;
    case Equality:
        do_equality(context);
        break;
    case Sign:
        change_sign(context);
        break;
    case Summ:
        plus(context);
        break;
    case Substraction:
        substract(context);
        break;
    case Multiplication:
        multiply(context);
        break;
    case Division:
        divide(context);
        break;
    case Root:
        calculate_root(context);
        break;
    case One_division:
        divide_1_by_x(context);
        break;
    case Sin:
        calculate_sin(context);
        break;
    case Cos:
        calculate_cos(context);
        break;
    case Tan:
        calculate_tan(context);
        break;
    case Cot:
        calculate_cot(context);
        break;
    case M_plus:
        do_m_plus(context);
        break;
    case M_minus:
        do_m_minus(context);
        break;
    case M_R:
        do_mr(context);
        break;
    case M_C:
        do_mc(context);
        break;
    }
}
