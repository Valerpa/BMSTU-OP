#include "entrypoint.h"

void do_operation(Operations operations, Context* context) {
    switch (operations) {
        case Load_scene:
            load_data(context);
            break;
        case Rotate_scene:
            rotate(context);
            break;
        case Move_scene:
            move(context);
            break;
        case Scale_scene:
            scale(context);
            break;
        case Clean_data:
            clean(context);
            break;
    }


    //char *(*a)(int, double (int)) = NULL;
}
