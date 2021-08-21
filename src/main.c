#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "test.h"

#include <stdio.h>

//user defined names must be case insensitive
//NT enums have the same prefix
//double exclam in a row?

void parse_test()
{
    Computation *cmp;
    String *string;

    // string = string_new("3!^2+1");
    string = string_new("i");

    cmp = parse(string);

    print_computation(cmp);

    string_delete(&string);
    computation_delete(&cmp);
}

int main()
{
    // parse_test();
    test_syntax(valid_strings);

    return 0;
}