#ifndef _ALLOCATE_LIST_F__H
#define _ALLOCATE_LIST_F__H

#include <stdio.h>

#define MAX_SIZE_NODE_DATA 5

typedef struct data{
    void* allocate_data;
    size_t data_size_byte;
} data;
typedef struct node{
    data data_alloc;
    struct node* next_node;
} node;
typedef struct root{
    data data_alloc;
    size_t data_struct_byte_size;

    node* node;
} root;

typedef root list;

void allocate_mem_fdata(list* root_l, size_t size);
void copy_el_data_to_allocate_mem_fdata(list* root_l, void* data, size_t data_struct_byte_size);

#endif