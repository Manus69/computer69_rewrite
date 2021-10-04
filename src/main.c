#include "why_lib.h"
#include "print.h"
#include "frontend_definitions.h"
#include "frontend_declarations.h"
#include "data_interface.h"
#include "why_error.h"

void test_all_statements(const char** strings)
{
    int_signed      n;
    String*         string;
    VariableTable*  v_table;

    n = 0;
    v_table = NULL;
    while (strings[n])
    {
        string = string_new_trimmed(strings[n]);
        print_string_n(string);

        v_table = process_input_line(string, v_table);
        string_delete(&string);

        n ++;
    }
}

static void _at_exit()
{
    get_line(-1);
    data_delete(&data);
}

int main()
{
    atexit(_at_exit);
    data = data_init();

    main_loop();

    return EXIT_SUCCESS;
}
