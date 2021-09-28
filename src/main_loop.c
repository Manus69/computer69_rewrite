#include "frontend_declarations.h"
#include "print.h"
#include "main_loop_commands.h"

#include <unistd.h>

void main_loop()
{
    VariableTable*  v_table;
    String*         line;

    v_table = NULL;
    while (TRUE)
    {
        line = get_line(STDIN_FILENO);
        if (!(line = string_trim(line)))
            break ;

        if (string_is_identical_to(line, CMD_QUIT))
            break ;
        else if (string_is_identical_to(line, CMD_LIST))
            print_v_table(v_table);
        else if (string_is_identical_to(line, CMD_PURGE))
            v_table = NULL;
        else if (string_starts_with(line, CMD_COMMENT))
        {
            _string_shift(line, cstr_length(CMD_COMMENT));
            print_string_n(line);
        }
        else
        {
            line = string_to_lower(line);
            v_table = process_input_line(line, v_table);
        }
        string_delete(&line);
    }
    string_delete(&line);
}