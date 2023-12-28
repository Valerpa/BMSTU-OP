#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#define NUMBER_SIZE 14

enum Operators {
    Not_chosen,
    Plus,
    Minus,
    Mult,
    Div
};

struct App_context {
    char digits[NUMBER_SIZE];
    double sum_in_memory = 0;
    double first_operand;
    double second_operand;
    Operators operators;
    int clicked_operator;
};

#endif // APPCONTEXT_H
