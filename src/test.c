#include "frontend_declarations.h"
#include "print.h"

#include <stdio.h>

const char *valid_strings[] = {"1", "-1", "0", "0+0", "0-1",
"1+1", "-1-1", "1-1", "-1-1-1", "-1-1+1", "1-1-1+1",
"5*5", "1-(2*2)", "1+(2*2)",
"1+1*2", "1+2^2", "1-2*2", "1-(2*2)",
"(1-1)^2", "(1+1)*2", "(1+1)^2", "1-(1-(1))", "(1-1)^(1-1)",
"(1+1)^(1*2-1)", "-1*2-1*2-1*2-1*2-1*2",
"(1+1)!", "1+2*3^2!", "3!+(2+2)", "1+(1+1)^2", "(1+1)^(1+1)", 
"3!^2+1*(1+1)", "1-(1+1)", "1-(1-(1+1*(2)))", "1-(1+2*3^(1+1))", 
"1-(1+(2*3-1))+1", "2-2*2-2^3+1", "3!-1", "1-3!", "(3-1)!-1", "2!!!",
"(3!)!", "sin(0)", "sin(pi)", "cos(2*pi-pi)", "cos(pi)^2+sin(pi)^2",
"cos(2*pi*sin(-pi+2*pi))", "-pi", "-pi*sin(pi/2)", "pi*i", "i*pi", 
"-i*pi", "-pi*i", "-sin(pi/2)", "sin(-pi/2)", 0};

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