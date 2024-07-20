#ifndef LIST__H
#define LIST__H

#include "../src/interaction_list_f.h"

typedef struct data_element
{
    void* allocate_data;
    size_t data_struct_byte_size;
} data_element;


list* create_list(size_t data_struct_byte_size);
void delete_list(list** root_l);

void push(list** root_l, data_element data);
void append(list** root_l, data_element data, size_t index);

data_element pop(list** root_l);
data_element erase(list** root_l, size_t index);

data_element get_element(list** root_l, size_t index);
data_element get_element_last(list** root_l);

#endif