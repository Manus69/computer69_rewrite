#include "variable.h"
#include "frontend_declarations.h"
#include "why_definitions.h"
#include "variable.h"

VariableTable *v_table_new(const Variable *variable)
{
    return tree_new(variable, variable_compare);
}

void v_table_delete(VariableTable **v_table)
{
    return tree_delete(v_table, variable_delete);
}

int_signed match_variable(const Variable *variable, const String *name)
{
    return string_compare_length(variable->name, name, 0);
}

Variable *v_table_search(const VariableTable *v_table, const String *name)
{
    return tree_search_function(v_table, name, match_variable);
}

VariableTable *v_table_insert(VariableTable *v_table, const Variable *variable)
{
    if (!v_table)
        return v_table_new(variable);
    
    tree_insert(v_table, variable);
    
    return v_table;
}

boolean v_table_insert_report(VariableTable *v_table, const Variable *variable)
{
    return tree_insert(v_table, variable);
}