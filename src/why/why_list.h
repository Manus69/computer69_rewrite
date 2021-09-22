#ifndef WHY_LIST_H
#define WHY_LIST_H

#include "why_list_interface.h"

struct List
{
    void*       (*copy)();
    void        (*_delete)();

    Sequence*   head;
    Sequence*   tail;
    int_signed  size;
};

struct Sequence
{
    void*       data;
    Sequence*   next;
};

#endif