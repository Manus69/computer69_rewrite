#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"

#include <stdio.h>

int main()
{
    Number *number;

    number = number_new_complex(complex(-1, -1));
    print_number(number);
    
    return 0;
}