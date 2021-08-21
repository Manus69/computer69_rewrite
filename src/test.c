#include "frontend_declarations.h"
#include "print.h"

#include <stdio.h>

const char *valid_basic_strings[] = {"1", "-1", "0", "0+0", "0-1",
"1+1", "-1-1", "1-1", "-1-1-1", "-1-1+1", "1-1-1+1",
"5*5", "1-(2*2)", "1+(2*2)",
"1+1*2", "1+2^2", "1-2*2", "1-(2*2)",
"(1-1)^2", "(1+1)*2", "(1+1)^2", "1-(1-(1))", "(1-1)^(1-1)",
"(1+1)^(1*2-1)", "-1*2-1*2-1*2-1*2-1*2",
"(1+1)!", "1+2*3^2!", "3!+(2+2)", "1+(1+1)^2", "(1+1)^(1+1)", 
"3!^2+1*(1+1)", "1-(1+1)", "1-(1-(1+1*(2)))", "1-(1+2*3^(1+1))", 
"1-(1+(2*3-1))+1", "2-2*2-2^3+1", "3!-1", "1-3!", "(3-1)!-1", "2!!!",
"(3!)!", 0};

const char *valid_id_strings[] = {"sin(0)", "sin(pi)",
"cos(2*pi-pi)", "cos(pi)^2+sin(pi)^2",
"cos(2*pi*sin(-pi+2*pi))", "-pi", "-pi*sin(pi/2)", "pi*i", "i*pi", 
"-i*pi", "-pi*i", "-sin(pi/2)", "sin(-pi/2)", 0};

const char *valid_assignments[] = {"a(y) = 43*y/(4%2*y)", 0};

const char *valid_matrix_strings[] = {"[[0]]", "[[0,1]]", "[[-1,10]]",
"[[99];[-99]]", "[[-1,-2];[-9.1,-1.99]]", "[[pi]]", "[[-pi];[-i];[0.0]]",
"[[cos(pi/2),-sin(pi/2)]]", 0};

void test_syntax(const char **strings)
{
    Computation *computation;
    String *string;
    int_signed n;

    n = 0;
    while (strings[n])
    {
        string = string_new(strings[n]);
        print_string(string);
        fflush(NULL);
        computation = parse(string);

        printf(" => ");
        print_computation(computation);
        printf("\n");

        computation_delete(&computation);
        string_delete(&string);

        n ++;
    }
}

void computation_test_basic(const char **strings)
{
    String *string;
    int_signed n;
    Computation *computation;
    Number *result;

    n = 0;
    while (strings[n])
    {
        string = string_new_no_space(strings[n]);
        computation = _parse(string);
        computation = computation_resolve(computation, NULL, NULL);
        result = computation_eval(computation);

        printf("%s => ", strings[n]);
        print_computation(computation);
        printf(" => ");
        print_number(result);
        printf("\n");

        string_delete(&string);
        computation_delete(&computation);
        number_delete(&result);

        n ++;
    }
}