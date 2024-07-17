#ifndef _ALLOCATE_LIST_F__H
#define _ALLOCATE_LIST_F__H

#include <stdio.h>

typedef struct node{
    void* allocate_data;
    size_t data_size;

    node* next_node;
} node;
typedef struct root{
    void* allocate_data;

    size_t data_size;
    size_t data_byte_size;
    size_t max_data_size;

    node* node;
} root;

typedef root list;

#endif