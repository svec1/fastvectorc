#ifndef _ALLOCATE_LIST_F__H
#define _ALLOCATE_LIST_F__H

#include <stdio.h>

#define MAX_SIZE_NODE_DATA 5

typedef struct data{
    void* allocate_data;
    size_t count_elem;
    
    // real occupied size
    size_t ros;
} data;
typedef struct node{
    data* data_alloc;
    struct node* next_node;
} node;
typedef struct root{
    size_t data_struct_byte_size;

    node* node;
} root;

typedef root list;

void debug_output_allocate_mem_char(node** nod, size_t data_struct_byte_size);

#define DEBUG_TRACKING_ALLOC_MEM_BEFORE(what_tracking, node, data_struct_byte_size) \
                                        printf("[%s] MEMORY BEFORE: \n", what_tracking); \
                                        debug_output_allocate_mem_char(node, data_struct_byte_size)

#define DEBUG_TRACKING_ALLOC_MEM_AFTER(what_tracking, node, data_struct_byte_size) \
                                        printf("[%s] MEMORY AFTER: \n", what_tracking); \
                                        debug_output_allocate_mem_char(node, data_struct_byte_size)

data** allocate_mem_fdata_node(node** nod, size_t data_struct_byte_size);
data** try_allocate_mem_fdata_node(node** nod, size_t data_struct_byte_size);
void try_free_mem_fdata_node(node** nod);
void allocate_mem_fdata(list** root_l);

node** find_node_wfree_allocate_mem(node** nod_last, node** nod);

node** find_node_index_allocate_mem(node** nod, size_t* index);

unsigned char index_element_is_null(data* data_alloc, size_t data_struct_byte_size, size_t offset);

size_t get_offset_last_element_allocate_mem(data* data_alloc, size_t data_struct_byte_size);

void copy_data_byte_to_data_alloc_allocate_mem(data** data_alloc, void* data, size_t data_struct_byte_size);
void erase_data_byte_last_in_allocate_mem(data** data_alloc, size_t data_struct_byte_size);
void erase_data_byte_in_allocate_mem(data** data_alloc, size_t data_struct_byte_size, size_t offset);

void* copy_data_byte_from_allocate_mem(data** data_alloc, size_t data_struct_byte_size, size_t offset);

void add_element_to_list(list** root_l, void* data, size_t data_struct_byte_size);
void append_element_to_list(list** root_l, void* data, size_t data_struct_byte_size, size_t after_index);
void del_last_element_to_list(list** root_l);
void del_index_element_to_list(list** root_l, size_t index);

void* get_element(list** root_l, size_t index);
void* get_last_element(list** root_l);

#endif