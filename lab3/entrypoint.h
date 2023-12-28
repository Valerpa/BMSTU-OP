#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H
#include "context.h"
#include "logic.h"

enum Operations {
    Load_scene,
    Rotate_scene,
    Move_scene,
    Scale_scene,
    Clean_data
};

void do_operation(Operations operation, Context* context);

#endif // ENTRYPOINT_H
