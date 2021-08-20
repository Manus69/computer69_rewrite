#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"

#include <stdio.h>

//user defined names must be case insensitive
//NT enums have the same prefix

void parse_test()
{
    Computation *cmp;
    String *string;

    string = string_new("0+1*2^2");
    cmp = parse(string);

    print_computation(cmp);

    string_delete(&string);
    computation_delete(&cmp);
}

int main()
{
    parse_test();

    return 0;
}