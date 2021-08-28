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

const char *valid_sequence_basic[] = {"A = [[1]]", "B = 2*A", 0};

const char *valid_sequence[] = {"f(x) = sin(x)", "f(x) = f(x)", 0};

const char *valid_sequences[][SEQUENCE_LENGTH] = {{"x = 1", "y = x + x", 0},
{"var = pi", "var2 = var*var + 1", 0},
{"f(x) = x", "y = f(1)", 0},
{"ass(cock) = cock + cock", "y = ass(ass(1))", 0},
{"f(x) = x + x + x", "g(x) = x^2", "y = f(g(1))", "z = g(f(1))", 0},
{"f(x) = sin(x)", "ass2(x) = -f(x)", "var = ass2(pi/2)", 0},
{"x1 = -pi/e", "x2 = x1^2 - 1", 0},
{"x = 0", "x = x + 1", 0},
{"ass1 = pi", "ass1 = ass1 + 1", 0},
{"ass10 = pi/2", "f(x) = sin(x) + ass10", "ass1 = f(ass10)", 0},
{"x = pi*e", "x = x^2", "x = x*3!", "f(w) = w + w", "z = f(1)", 0},
{"x = pi/4", "f(y) = sin(y)^(3!) - e", "w = f(x)", 0},
{"x = -sin(2*cos(0))/sin(pi/2)", "y(k) = x^k", "w = y(2)", 0},
{"thisIsaVariable = -1-1-1", "f(vvv) = vvv^3!", "w = f(thisIsaVariable)", 0},
{"1-(1+(2*3-1))+1", "sin(pi/2)", 0},
{"p(x) = pi + x + x^2", "p(1)", 0},
{"cos(2*pi*sin(-pi+2*pi))*cos(pi)^2+sin(pi)^2-sin(-pi/2)", 0},
{"f(x) = x + x", "g(x) = 2*x", "w(x) = f(x) + g(x)", "k = w(1)", 0},
{"f(x) = 2!*sin(x^2)^2", 0},
{"ffff(x) = x^2 + sin(x)*cos(x)", 0},
{"f(x) = 2!*sin(x^2)^2", "g(x) = x^2 + sin(x)*cos(x)", 0},
{"f(x) = 2!*sin(x^2)^2", "g(x) = x^2 + sin(x)*cos(x)", "w(x) = f(g(x))", "w(1)", 0},
{"f(x) = x^2", "g(x) = x + 1", "h(x) = f(g(x))", "h(x) = g(f(x))", 0},
{"f(x) = x^2", "g(x) = sin(f(x))", 0},
{"f(x) = x^2", "g(x) = f(sin(x))", 0},
{"f(a) = a + a", "g(x) = f(sin(x))", "g(pi/2)", 0},
{"f = pi", "f = i", 0},
{"f(x) = x", "g(x) = x * x", "f(x) = g(x)", 0},
{"f(x) = sin(x)", "f(x) = f(x)", 0},
{"f(x) = x^2", "g(x) = sin(x)", "f(x) = g(x)", "g(x) = f(x)", 0},
{"f(x) = x^2", "g(x) = sin(x)", "f(x) = g(x)", "g(x) = g(x) + f(x)", 0},
{0}};

const char *valid_matrix_strings[] = {"[[0]]", "[[0,1]]", "[[-1,10]]",
"[[99];[-99]]", "[[-1,-2];[-9.1,-1.99]]", "[[pi]]", "[[-pi];[-i];[0.0]]",
"[[cos(pi/2),-sin(pi/2)]]", 0};

const char *valid_matrix_sequences[][SEQUENCE_LENGTH] = {{"[[0]]", 0},
{"[[1,0];[0,1]]", 0},
{"x = [[0]]", 0},
{"a = 1", "[[a]]", 0},
{"a(x) = [[x]]", 0},
{"a(x) = [[sin(x)]]", 0},
{"A(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]", "A(pi/2)", 0},
{"A(x) = [[cos(x)]]", 0},
{"A(x) = [[cos(x), sin(x)]]", 0},
{"A(x) = [[cos(x)];[sin(x)]]", 0},
{"f(y) = y + 1", "g(w) = w^2", "A(x) = [[g(f(x))]]", 0},
{"[[1]] + [[1]]", 0},
{"[[1,0]] + [[0,1]]", 0},
{"[[1,0];[0,1]] + [[-1,0];[0,-1]]", 0},
{"A = [[0,0]]", 0},
{"A = [[1,0];[0,1]]", "B = A + [[1,0];[0,1]]", 0},
{"A = [[1,0];[0,1]]", "B = 2*A", 0},
{"A = [[pi, -i];[i, -pi]]", "B = [[1, 0];[0, 1]]", "A * B", 0},
{"a(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]", "a(pi/2)", "a(pi/4 + pi/4)", 0},
{"a(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]", "b(x) = a", "b(pi/2)", 0},
{"a(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]", "b(x) = a(x)", "c(x) = a(x) * b(x)", "c(pi)", 0},
{"A(x) = [[x^2 + sin(x)*cos(x), 2!*sin(x^2)^2]]", 0},
{"A = [[1];[1]]", "B = [[pi, pi]]", "B * A", 0},
{"A = [[1,0];[0,1]]", "b = [[1];[1]]", "A * b", 0},
{"A = [[1,0];[0,1]]", "B = [[pi,pi];[pi,pi]]", "A*B", 0},
{"A = [[1,1];[1,0]]", "A^20", 0}, //22nd fib number
{"A = [[1,1];[1,0]]", "A^20*[[1];[0]]", 0},
{"A = [[1]]", "f(x) = x + x", "f(A)", 0},
{"A(x) = [[sin(x)]]", "B(x) = A(x) + A(x)", "B(pi/2)", 0},
{"A(x) = [[cos(x), -sin(x)];[sin(x), cos(x)]]", "B(x) = x^2", "A(pi/2)", "B(A(pi/2))", 0},
{"[[0,-1];[1,0]]^2", 0},
{"[[5,2,6,1];[0,6,2,0];[3,8,1,4];[1,8,5,6]]*[[7,5,8,0];[1,8,2,6];[9,4,3,8];[5,3,7,9]]", 0},
//[[96,68,69,69];[24,56,18,52];[58,95,71,92];[90,107,81,142]]
{0}};

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
        computation = parse(string, NULL);

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
        computation = _parse(string, NULL);
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
    Variable *v;
    VariableTable *v_table;
    int_signed n;

    n = 0;
    v_table = NULL;
    while (strings[n])
    {
        string = string_new_no_space(strings[n]);
        print_string_n(string);

        variable = variable_create_from_string(string, v_table);

        print_variable(variable);
        printf("\n");
        string_delete(&string);

        if (variable_get_name(variable) == NULL)
        {
            variable_delete(&variable);
            n ++;

            continue ;
        }

        if (!v_table)
            v_table = v_table_new(variable);
        else if ((v = v_table_search(v_table, variable_get_name(variable))))
        {
            v = variable_assign(v, variable_get_value(variable), TRUE);
            variable_delete(&variable);
        }
        else if (!v_table_insert_report(v_table, variable))
            variable_delete(&variable);
        
        // printf("TABLE:\n");
        // print_v_table(v_table);
        // printf("\n");

        n ++;
    }

    v_table_delete(&v_table);
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