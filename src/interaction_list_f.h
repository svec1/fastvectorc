#ifndef INTERACTION_LIST__H
#define INTERACTION_LIST__H

//#include "allocate_node_mem_f.h"
#include "interaction_data_f.h"

typedef struct root{
    size_t data_struct_byte_size;

    node* node;
} root;

typedef root list;

void allocate_mem_fdata(list** root_l);

void add_element_to_list(list** root_l, void* data, size_t data_struct_byte_size);
void append_element_to_list(list** root_l, void* data, size_t data_struct_byte_size, size_t after_index);
void del_last_element_to_list(list** root_l);
void del_index_element_to_list(list** root_l, size_t index);

void* get_element_list(list** root_l, size_t index);
void* get_last_element_list(list** root_l);

#endif