#include "allocate_node_mem_f.h"

#include <string.h>
#include <stdlib.h>

void debug_output_allocate_mem_char(node** nod, size_t data_struct_byte_size){
    if(!(*nod) || !(*nod)->data_alloc){
        printf("It's not possible to read data to unallocated memory\n");
        exit(1);
    }
    for(size_t i = 0; i < MAX_SIZE_NODE_DATA*data_struct_byte_size; ++i){
        if(i%data_struct_byte_size==0 && i != 0)
            printf(" %zu BYTE\n", data_struct_byte_size);
        if(((unsigned char*)(*nod)->data_alloc->allocate_data)[i] == NULL)
            printf("NL ");
        else if(is_digit_uchar(((unsigned char*)(*nod)->data_alloc->allocate_data)[i]) || is_alpha_hex_uchar(((unsigned char*)(*nod)->data_alloc->allocate_data)[i]))
            printf("0%X ", ((unsigned char*)(*nod)->data_alloc->allocate_data)[i]);
        else
            printf("%X ", ((unsigned char*)(*nod)->data_alloc->allocate_data)[i]);
    }
    if((*nod)->data_alloc->ros*data_struct_byte_size%data_struct_byte_size==0 && (*nod)->data_alloc->ros*data_struct_byte_size != 0)
        printf(" %zu BYTE\n", data_struct_byte_size);
    printf("\n");
}

data** allocate_mem_fdata_node(node** nod, size_t data_struct_byte_size){
    (*nod) = malloc(sizeof(node));
    (*nod)->data_alloc = malloc(sizeof(data));
    (*nod)->data_alloc->allocate_data = malloc(data_struct_byte_size*MAX_SIZE_NODE_DATA);
    memset((*nod)->data_alloc->allocate_data, NULL, data_struct_byte_size*MAX_SIZE_NODE_DATA);
    (*nod)->data_alloc->count_elem = 0;
    (*nod)->data_alloc->ros = 0;
    (*nod)->next_node = NULL;
    return &(*nod)->data_alloc;
}
data** try_allocate_mem_fdata_node(node** nod, size_t data_struct_byte_size){
    if(!(*nod)) return allocate_mem_fdata_node(nod, data_struct_byte_size);
    else if((*nod)->data_alloc->count_elem < MAX_SIZE_NODE_DATA) return &(*nod)->data_alloc;
    return try_allocate_mem_fdata_node(&(*nod)->next_node, data_struct_byte_size);
}
void try_free_mem_fdata_node(node** nod){
    if(!(*nod)) return;
    else if((*nod)->data_alloc->count_elem) try_free_mem_fdata_node(&(*nod)->next_node);
    else {
        free((*nod)->data_alloc->allocate_data);
        free((*nod)->data_alloc);
        if ((*nod)->next_node)
            *nod = (*nod)->next_node;
        else
            free(*nod);
    }
}
void free_node(node** nod){
    if((*nod)->next_node) free_node(&(*nod)->next_node);
    free((*nod)->data_alloc->allocate_data);
    free((*nod)->data_alloc);
    free((*nod));
}

node** find_node_wfree_allocate_mem(node** nod_last, node** nod){
    if(!(*nod)) return nod_last;
    else if((*nod)->data_alloc->count_elem < MAX_SIZE_NODE_DATA && !(*nod)->next_node) return nod;
    return find_node_wfree_allocate_mem(nod, &(*nod)->next_node);
}

node** find_node_index_allocate_mem(node** nod, size_t *index){
    if(!(*nod)) return NULL;
    else if(*index<(*nod)->data_alloc->ros){
        return nod;
    }
    else if (index > (*nod)->data_alloc->ros && (*nod)->next_node)
        *index -= (*nod)->data_alloc->ros;
    else
        *index-=MAX_SIZE_NODE_DATA;
    return find_node_index_allocate_mem(&(*nod)->next_node, index);
}