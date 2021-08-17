#include "why_buffer_interface.h"
#include "why_string_interface.h"
#include "why_memory.h"

#define READ_SIZE (1 << 11)
#define NUMBER_OF_DESCRIPTORS (1 << 10)

static Buffer *_get_buffer(int_signed index)
{
    static Buffer *buffers[NUMBER_OF_DESCRIPTORS];

    if (index >= NUMBER_OF_DESCRIPTORS)
        return NULL;

    if (buffers[index] == NULL)
    {
        buffers[index] = buffer_new();
    }

    return buffers[index];
}

String *get_line(int file_descriptor)
{
    String *line;
    int status;
    Buffer *buffer;
    
    buffer =  _get_buffer(file_descriptor);
    if (!buffer)
        return NULL;
    
    while (TRUE)
    {
        line = buffer_flush_sequence(buffer, '\n', TRUE);
        if (line)
            return line;
        
        status = buffer_write_into(buffer, READ_SIZE, file_descriptor);
        if (status <= 0)
            return buffer_flush_all(buffer, TRUE);
    }
}

String *get_all_lines(int file_descriptor)
{
    Buffer *buffer;
    String *string;

    buffer = buffer_new();

    buffer_write_all_bytes_into(buffer, file_descriptor);
    string = buffer_read_from(buffer, buffer_count_unread_bytes(buffer), TRUE);
    buffer_delete(&buffer);

    return string;
}