#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "appcontext.h"
#include "applogic.h"

void entry_point(Operations operations, Table* table, List *lst, Metrics *metrics, Params *params);
#endif // ENTRYPOINT_H
