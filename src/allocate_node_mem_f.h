#ifndef _ALLOCATE_NODE_MEM_F__H
#define _ALLOCATE_NODE_MEM_F__H

#include <stdio.h>


#define MAX_SIZE_NODE_DATA 5

#define BYTE_RESERV_COMPOSE 0xFF

#define is_digit_uchar(ch) (ch >= 0 && ch <= 9)
#define is_alpha_hex_uchar(ch) (ch >= 10 && ch <= 15)

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
void free_node(node** nod);


node** find_node_wfree_allocate_mem(node** nod_last, node** nod);

node** find_node_index_allocate_mem(node** nod, size_t* index);

#endif