#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"

#include <stdio.h>

struct test
{
    union
    {
        int n;
        char *str;
        char *str2;
        String *string;
    };
};

//user defined names must be case insensitive

int main()
{
    struct test *test;

    test = allocate(sizeof(struct test));
    void *p = string_new_allocated("01234", 2);
    test->str = p;
    
    string_delete((String **)&test->str);
    free(test);

    return 0;
}