#include "frontend_declarations.h"
#include "print.h"
#include "main_loop_commands.h"

#include <unistd.h>

#define DBG 0

void main_loop()
{
    VariableTable   *v_table;
    String          *line;

    v_table = NULL;
    while (TRUE)
    {
        line = get_line(STDIN_FILENO);
        if (!(line = string_trim(line)))
            break ;

        if (string_is_identical_to(line, CMD_QUIT))
        {
            string_delete(&line);
            break ;
        }
        else if (string_is_identical_to(line, CMD_LIST))
        {
            print_v_table(v_table);
            string_delete(&line);
        }
        else if (string_is_identical_to(line, CMD_PURGE))
        {
            v_table = NULL;
            string_delete(&line);
        }
        else if (string_starts_with(line, CMD_COMMENT))
        {
            _string_shift(line, 2);
            print_string_n(line);
            string_delete(&line);
        }
        else
        {
            v_table = process_input_line(line, v_table);
            string_delete(&line);
        }
    }
    get_line(-1);
}