#include "variable.h"
#include "frontend_declarations.h"
#include "why_definitions.h"
#include "variable.h"
#include "data_interface.h"

VariableTable* v_table_new(const Variable* variable)
{
    VariableTable* v_table;

    v_table = tree_new(variable, variable_compare);

    data_add_pointer(data, v_table, sizeof(void* ));

    return v_table;
}

void v_table_delete(VariableTable** v_table)
{
    #if NO_DELETE
    return ;
    #endif

    return tree_delete(v_table, variable_delete);
}

int_signed match_variable(const Variable* variable, const char* name)
{
    return cstr_compare(variable->name, name);
}

Variable* v_table_search(const VariableTable* v_table, const char* name)
{
    return tree_search_function(v_table, name, match_variable);
}

VariableTable* v_table_insert(VariableTable* v_table, const Variable* variable)
{
    void* result;

    if (!v_table)
        return v_table_new(variable);
    
    result = tree_insert(v_table, variable);
    
    data_add_pointer(data, result, sizeof(void* ));

    return v_table;
}

Tree* v_table_insert_report(VariableTable* v_table, const Variable* variable)
{
    void* pointer;

    pointer = tree_insert(v_table, variable);

    data_add_pointer(data, pointer, sizeof(void* ));

    return pointer;
}
