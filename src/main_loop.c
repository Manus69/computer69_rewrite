#include "frontend_declarations.h"
#include "print.h"

#include <unistd.h>

void main_loop()
{
    VariableTable *v_table;
    String *line;

    v_table = NULL;
    while (TRUE)
    {
        line = get_line(STDIN_FILENO);
        line = string_trim(line);
        if (string_is_identical_to(line, "q"))
        {
            string_delete(&line);
            break ;
        }
        
        v_table = process_input_line(line, v_table);
        string_delete(&line);
    }
    get_line(-1);
}