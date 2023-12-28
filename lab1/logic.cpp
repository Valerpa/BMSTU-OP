#include "logic.h"

void input_number(App_context* context, char* new_value)
{
    if (context->digits[0] == '0' && context->digits[1] == '\0')
    {
        context->digits[0] = *new_value;
        return;
    }
    if (strlen(context->digits) == NUMBER_SIZE - 1)
    {
        return;
    }
    context->digits[strlen(context->digits) + 1] = '\0';
    context->digits[strlen(context->digits)] = *new_value;
}

void separate(App_context* context)
{
    if (strlen(context->digits) == NUMBER_SIZE - 1)
        return;

    if (strstr(context->digits, ".") == NULL)
        strncat(context->digits, ".", 1);
}

void clear_line(App_context* context)
{
    context->digits[0] = '0';
    context->digits[1] = '\0';
}

void delete_last_digit(App_context* context)
{
    if (strlen(context->digits) == 1)
        clear_line(context);
    else
        context->digits[strlen(context->digits) - 1] = '\0';
}

void do_equality(App_context* context)
{
    context->second_operand = atof(context->digits);
    switch(context->clicked_operator)
    {
    case Plus:
        context->first_operand += context->second_operand;
        break;
    case Minus:
        context->first_operand -= context->second_operand;
        break;
    case Mult:
        context->first_operand *= context->second_operand;
        break;
    case Div:
        if (context->second_operand != 0)
        {
            context->first_operand /= context->second_operand;
        }
        else
        {
            context->first_operand = DEFAULT_VALUE;
        }
        break;
    default:
        context->first_operand = context->second_operand;
    }
    snprintf(context->digits, NUMBER_SIZE, "%.*g", NUMBER_SIZE, context->first_operand);
    context->first_operand = DEFAULT_VALUE;
    context->clicked_operator = Not_chosen;
}

void plus(App_context* context)
{
    if (context->clicked_operator != Not_chosen)
        do_equality(context);
    context->clicked_operator = Plus;
    context->first_operand = atof(context->digits);
    context->second_operand = DEFAULT_VALUE;
    clear_line(context);
}

void substract(App_context* context)
{
    if (context->clicked_operator != Not_chosen)
        do_equality(context);
    context->clicked_operator = Minus;
    context->first_operand = atof(context->digits);
    context->second_operand = DEFAULT_VALUE;
    clear_line(context);
}

void multiply(App_context* context)
{
    if (context->clicked_operator != Not_chosen)
        do_equality(context);
    context->clicked_operator = Mult;
    context->first_operand = atof(context->digits);
    context->second_operand = DEFAULT_VALUE;
    clear_line(context);
}

void divide(App_context* context)
{
    if (context->clicked_operator != Not_chosen)
        do_equality(context);
    context->clicked_operator = Div;
    context->first_operand = atof(context->digits);
    context->second_operand = DEFAULT_VALUE;
    clear_line(context);
}

void change_sign(App_context* context)
{
    int len = (int)strlen(context->digits);

    if (strcmp(context->digits, "0") == 0 || (context->digits[0] == '0' && context->digits[1] == '.' && context->digits[2] == '\0'))
        return;

    if (context->digits[0] == '-')
    {
        for(int i = 0; i < len - 1; i++)
        {
            context->digits[i] = context->digits[i + 1];
        }
        context->digits[len - 1] = '\0';
    }
    else
    {
        if(len == NUMBER_SIZE - 1)
            return;

        for(int i = len; i >= 0; i--)
        {
            context->digits[i + 1] = context->digits[i];
        }
        context->digits[0] = '-';
    }   
}

void divide_1_by_x(App_context* context)
{
    if (strcmp(context->digits, "0") != 0)
    {
        double num = atof(context->digits);
        snprintf(context->digits, NUMBER_SIZE, "%.*g", NUMBER_SIZE, (1 / num));
    }

}

void calculate_root(App_context* context)
{
    double num = atof(context->digits); //char* -> вещ. число, если строка из букв, вернёт 0
    if (num > 0)
        snprintf(context->digits, NUMBER_SIZE, "%.*g", NUMBER_SIZE, sqrt(num));
}

void calculate_sin(App_context* context)
{
    double num = atof(context->digits);
    snprintf(context->digits, NUMBER_SIZE, "%.*g", NUMBER_SIZE, sin(num));
}

void calculate_cos(App_context* context)
{
    double num = atof(context->digits);
    snprintf(context->digits, NUMBER_SIZE, "%.*g", NUMBER_SIZE, cos(num));
}

void calculate_tan(App_context* context)
{
    double num = atof(context->digits);
    snprintf(context->digits, NUMBER_SIZE, "%.*g", NUMBER_SIZE, tan(num));
}

void calculate_cot(App_context* context)
{
    double num = atof(context->digits);
    double tg = tan(num);
    if (tg != 0)
        snprintf(context->digits, NUMBER_SIZE, "%.*g", NUMBER_SIZE, 1 / tg);
}

void do_m_plus(App_context* context)
{
    context->sum_in_memory += atof(context->digits);
}

void do_m_minus(App_context* context)
{
    context->sum_in_memory -= atof(context->digits);
}

void do_mr(App_context* context)
{
    snprintf(context->digits, NUMBER_SIZE, "%.*g", NUMBER_SIZE, context->sum_in_memory);
}

void do_mc(App_context* context)
{
    context->sum_in_memory = DEFAULT_VALUE;
}

void clear(App_context* context)
{
    context->first_operand = DEFAULT_VALUE;
    context->second_operand = DEFAULT_VALUE;
    context->clicked_operator = Not_chosen;
    clear_line(context);
}
