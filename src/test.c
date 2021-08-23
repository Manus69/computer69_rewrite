#include "frontend_declarations.h"
#include "print.h"
#include "test.h"

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
"-i*pi", "-pi*i", "-sin(pi/2)", "sin(-pi/2)", "-sin(2*cos(0))/sin(pi/2)", 0};

const char *valid_ass_strings[] = {"a(y) = 43*y/(4%2*y)", "f(x) = 1", "f(x) = x",
"f(x) = x^x",
"cock(ass) = ass^ass", 0};

const char *valid_sequence_basic[] = {"x = 1", "y = x + x", 0};

const char *valid_sequence[] = {"ass(cock) = cock + cock", "y = ass(ass(1))", 0};

const char *valid_sequences[][SEQUENCE_LENGTH] = {{"x = 1", "y = x + x", 0},
{"var = pi", "var2 = var*var + 1", 0},
{"f(x) = x", "y = f(1)", 0},
{"ass(cock) = cock + cock", "y = ass(ass(1))", 0},
{"f(x) = x + x + x", "g(x) = x^2", "h = f(g(1))", 0},
{0}};

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

void test_computation(const char **strings)
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
        result = computation_eval(computation, NULL, NULL);

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

void test_assignment(const char **strings)
{
    String *string;
    Variable *variable;
    int_signed n;

    n = 0;
    while (strings[n])
    {
        string = string_new_no_space(strings[n]);
        variable = variable_create_from_string(string, NULL);

        print_variable(variable);
        printf("\n");

        variable_delete(&variable);
        string_delete(&string);

        n ++;
    }
}

void test_sequence(const char **strings)
{
    String *string;
    Variable *variable;
    VariableTable *v_table;
    int_signed n;

    if (!*strings)
        return ;

    n = 0;
    v_table = NULL;
    while (strings[n])
    {
        string = string_new_no_space(strings[n]);
        print_string_n(string);

        variable = variable_create_from_string(string, v_table);
        v_table = v_table_insert(v_table, variable);

        print_variable(variable);
        printf("\n");
        // fflush(NULL);
        string_delete(&string);
        // variable_delete(&variable);

        n ++;
    }

    v_table_delete(&v_table);
    // free(variable);
    // variable_delete(&variable);
}

void test_all_sequences(const char *array[][SEQUENCE_LENGTH])
{
    int_signed n;
    const char **sequence;

    n = 0;
    sequence = array[n];
    while (*sequence)
    {
        test_sequence(array[n]);
        printf("\n");
        
        n ++;
        sequence = array[n];
    }
}