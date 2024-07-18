#ifndef _ALLOCATE_LIST_F__H
#define _ALLOCATE_LIST_F__H

#include <stdio.h>

#define MAX_SIZE_NODE_DATA 5

typedef struct data{
    void* allocate_data;
    size_t data_size;
} data;
typedef struct node{
    data data_alloc;
    struct node* next_node;
} node;
typedef struct root{
    data data_alloc;
    size_t data_byte_size;

    node* node;
} root;

typedef root list;

void byte_data_copy(void** dest, void* src, size_t dest_size_byte, size_t src_size_byte, size_t offset_byte);
void* get_data(void* src, size_t dest_size_byte, size_t data_byte_size, size_t offset_byte);

void allocate_data_list(root* list_r, void* data_src, size_t data_src_byte_size);
void* extract_data_elem(root* list_r, size_t index);

#endif