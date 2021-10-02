#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "data_interface.h"
#include "why_error.h"

void test_all_statements(const char** strings)
{
    int_signed  n;
    String*     string;

    n = 0;
    while (strings[n])
    {
        string = string_new_trimmed(strings[n]);
        print_string_n(string);

        process_input_line(string, NULL);
        string_delete(&string);

        n ++;
    }
}

static void _at_exit()
{
    get_line(-1);
    data_delete(&data);
}

//dont forget the author file
//be careful around things of the form f(x) = ... ; g(x) = f with no arg; this must be checked
// f(x) = ? should be equivalent to "f" ?
//test functions with veird values: log(-1), etc

int main()
{
    atexit(_at_exit);
    data = data_init();

    main_loop();

    return 0;
}
