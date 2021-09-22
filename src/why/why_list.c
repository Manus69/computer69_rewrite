#include "why_list_interface.h"
#include "why_list.h"
#include "why_memory.h"

//not tested

List* list_new(void* (*copy)(), void (*delete)())
{
    List* list;

    list = allocate(sizeof(List));
    list->copy = copy;
    list->_delete = delete;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

void sequence_delete(Sequence** sequence, void (*_delete)())
{
    Sequence* next;

    if (!sequence || !*sequence)
        return ;
    
    while (*sequence)
    {
        next = (*sequence)->next;
        _delete(&(*sequence)->data);
        free(*sequence);
        *sequence = next;
    }
}

static void _list_delete_empty(List** list)
{
    free(*list);
    *list = NULL;
}

void list_delete(List** list)
{
    if (!list || !*list)
        return ;
    
    if (!(*list)->size)
        return _list_delete_empty(list);

    sequence_delete(&(*list)->head, (*list)->_delete);
    _list_delete_empty(list);
}

Sequence* sequence_new(const void* data, void* (*copy)())
{
    Sequence* sequence;

    sequence = allocate(sizeof(Sequence));
    sequence->data = copy ? copy(data) : (void* )data;
    sequence->next = NULL;

    return sequence;
}

static List* _list_init(List* list, const void* data)
{
    Sequence* item;

    item = sequence_new(data, list->copy);
    list->head = item;
    list->tail = item;
    list->size = 1;

    return list;
}

List* _list_new_init(void* (*copy)(), void (*delete)(), const void* data)
{
    List* list;

    list = list_new(copy, delete);
    
    return _list_init(list, data);
}

List* list_push_back(List* list, const void* data)
{
    Sequence* item;

    if (!list)
        return NULL;
    
    if (list->head == NULL)
        return _list_init(list, data);

    item = sequence_new(data, list->copy);
    
    list->tail->next = item;
    list->tail = item;
    list->size ++;

    return list;
}

static void* _list_pop_last(List* list)
{
    void* item;

    item = list->head;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return item;
}

static Sequence* _get_parent(List* list, Sequence* _sequence)
{
    Sequence* current;

    current = list->head;
    while (current->next != _sequence)
        current = current->next;
    
    return current;
}

void* list_pop_back(List* list)
{
    void*       item;
    Sequence*   new_tail;

    if (!list)
        return NULL;
    
    if (list->size == 0)
        return NULL;
    
    if (list->size == 1)
        return _list_pop_last(list);

    item = list->tail->data;
    new_tail = _get_parent(list, list->tail);
    new_tail->next = NULL;
    free(list->tail);
    list->size --;

    return item;
}

List* list_push_front(List* list, const void* data)
{
    Sequence* new_head;

    if (!list)
        return NULL;
    
    if (list->size == 0)
        return _list_init(list, data);

    new_head = sequence_new(data, list->copy);
    new_head->next = list->head;
    list->head = new_head;
    list->size ++;

    return list;    
}

void* list_pop_front(List* list)
{
    void*       item;
    Sequence*   new_head;

    if (!list)
        return NULL;
    
    if (list->size == 0)
        return list;
    
    if (list->size == 1)
        return _list_pop_last(list);
    
    item = list->head->data;
    new_head = list->head->next;
    free(list->head);
    list->head = new_head;
    list->size --;

    return item;
}

static Sequence* _reverse_sequence(Sequence* _sequence)
{
    Sequence* next;
    Sequence* previous;

    previous = NULL;
    next = _sequence->next;
    while (next)
    {
        _sequence->next = previous;
        previous = _sequence;
        _sequence = next;
        next = next->next;
    }

    _sequence->next = previous;
    
    return _sequence;
}

List* list_reverse(List* list)
{
    if (!list)
        return NULL;
    
    if (list->size == 0)
        return list;
    
    if (list->size == 1)
        return list;
    
    list->tail = list->head;
    list->head = _reverse_sequence(list->head);
    list->tail->next = NULL;

    return list;
}

void list_map(List* list, void (*function)())
{
    Sequence* current;

    if (!list || !function)
        return ;
    
    current = list->head;
    while (current)
    {
        function(current->data);
        current = current->next;
    }
}