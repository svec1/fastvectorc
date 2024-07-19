#include "allocate_list_f.h"

#include <string.h>
#include <stdlib.h>

void debug_output_allocate_mem_char(node** nod, size_t data_struct_byte_size){
    if(!(*nod) || !(*nod)->data_alloc){
        printf("It's not possible to read data to unallocated memory\n");
        exit(1);
    }
    for(size_t i = 0; i < MAX_SIZE_NODE_DATA*data_struct_byte_size; ++i){
        if(i%8==0 && i != 0)
            printf(" 8 BYTE\n");
        
        if(((unsigned char*)(*nod)->data_alloc->allocate_data)[i] == NULL)
            printf("NL ");
        else
            printf("%X ", ((unsigned char*)(*nod)->data_alloc->allocate_data)[i]);
    }
    if((*nod)->data_alloc->ros*data_struct_byte_size%8==0 && (*nod)->data_alloc->ros*data_struct_byte_size != 0)
        printf(" 8 BYTE\n");
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
void allocate_mem_fdata(list** root_l){
    allocate_mem_fdata_node(&(*root_l)->node, (*root_l)->data_struct_byte_size);
}

node** find_node_wfree_allocate_mem(node** nod_last, node** nod){
    if(!(*nod)) return nod_last;
    else if((*nod)->data_alloc->count_elem < MAX_SIZE_NODE_DATA && !(*nod)->next_node) return nod;
    return find_node_wfree_allocate_mem(nod, &(*nod)->next_node);
}

node** find_node_index_allocate_mem(node** nod, size_t index, size_t* curr_index){
    if(!(*nod)) return NULL;
    else if(index<(*curr_index)+MAX_SIZE_NODE_DATA && index >=(*curr_index) && index-(*curr_index)<=(*nod)->data_alloc->ros){
        return nod;
    }
    (*curr_index)+=5;
    return find_node_index_allocate_mem(&(*nod)->next_node, index, curr_index);
}

unsigned char index_element_is_null(data* data_alloc, size_t data_struct_byte_size, size_t offset){
    if(!data_alloc){
        printf("It's not possible to check data to unallocated memory\n");
        exit(1);
    }
    unsigned char is_null = 0;
    for(size_t i = offset*data_struct_byte_size; i < offset*data_struct_byte_size+data_struct_byte_size; ++i){
        if(((unsigned char*)data_alloc->allocate_data)[i] == NULL && !is_null) is_null = 1;
        else if(((unsigned char*)data_alloc->allocate_data)[i] != NULL){
            is_null = 0;
            break;
        }
    }
    return is_null;
}

size_t get_offset_last_element_allocate_mem(data* data_alloc, size_t data_struct_byte_size){
    if(!data_alloc){
        printf("It's not possible to check data to unallocated memory\n");
        exit(1);
    }
    for(size_t i = MAX_SIZE_NODE_DATA-1; i >= 0; --i){
        if(index_element_is_null(data_alloc, data_struct_byte_size, i)) continue;
        else return i;
    }
    return NULL;
}

void copy_data_byte_to_data_alloc_allocate_mem(data** data_alloc, void* data, size_t data_struct_byte_size){
    if(!(*data_alloc) || !(*data_alloc)->allocate_data){
        printf("It's not possible to copy data to unallocated memory\n");
        exit(1);
    }
    for(size_t i = (*data_alloc)->count_elem*data_struct_byte_size, j = 0; i < (*data_alloc)->count_elem*data_struct_byte_size+data_struct_byte_size; ++i, ++j){
        ((unsigned char*)(*data_alloc)->allocate_data)[i] = ((unsigned char*)data)[j];
    }
    ++(*data_alloc)->count_elem;
    ++(*data_alloc)->ros;
}
void erase_data_byte_last_in_allocate_mem(data** data_alloc, size_t data_struct_byte_size){
    if(!(*data_alloc) || !(*data_alloc)->allocate_data){
        printf("It's not possible to copy data to unallocated memory\n");
        exit(1);
    }
    for(size_t i = (*data_alloc)->count_elem*data_struct_byte_size; i < (*data_alloc)->count_elem*data_struct_byte_size+data_struct_byte_size; ++i){
        ((unsigned char*)(*data_alloc)->allocate_data)[i] = NULL;
    }
    --(*data_alloc)->count_elem;
    --(*data_alloc)->ros;
}
void erase_data_byte_in_allocate_mem(data** data_alloc, size_t data_struct_byte_size, size_t offset){
    if(!(*data_alloc) || !(*data_alloc)->allocate_data){
        printf("It's not possible to copy data to unallocated memory\n");
        exit(1);
    }
    for(size_t i = offset*data_struct_byte_size; i < offset*data_struct_byte_size+data_struct_byte_size; ++i){
        ((unsigned char*)(*data_alloc)->allocate_data)[i] = NULL;
    }
    --(*data_alloc)->count_elem;
}
void* copy_data_byte_from_allocate_mem(data** data_alloc, size_t data_struct_byte_size, size_t offset){
    if(!(*data_alloc) || !(*data_alloc)->allocate_data){
        printf("It's not possible to copy data to unallocated memory\n");
        exit(1);
    }
    void* data_copy = malloc(data_struct_byte_size);
    for(size_t i = offset*data_struct_byte_size, j = 0; i < offset*data_struct_byte_size+data_struct_byte_size; ++i, ++j){
        ((unsigned char*)data_copy)[j] = ((unsigned char*)(*data_alloc)->allocate_data)[i];
    }
    return data_copy;
}

void add_element_to_list(list** root_l, void* data, size_t data_struct_byte_size){
    if(!(*root_l)){
        printf("Passed to function - copy_el_data_to_allocate_mem_fdata(), the list does not exist\n");
        exit(1);
    }
    else if(data_struct_byte_size!=(*root_l)->data_struct_byte_size){
        printf("The size of the list item structure is not equal to the size passed to the function: add_element_to_list()\n");
        exit(1);
    }
    
    copy_data_byte_to_data_alloc_allocate_mem(
        try_allocate_mem_fdata_node(
            &(*root_l)->node,
            data_struct_byte_size),
        data,
        data_struct_byte_size);
}
void del_last_element_to_list(list** root_l){
    if(!(*root_l)){
        printf("Passed to function - copy_el_data_to_allocate_mem_fdata(), the list does not exist\n");
        exit(1);
    }
    /*
    DEBUG_TRACKING_ALLOC_MEM_BEFORE(
        "LIST AT DELETE OF LAST ELEMENT",
        find_node_wfree_allocate_mem(
            NULL,
            &(*root_l)->node),
        (*root_l)->data_struct_byte_size);
    */
    erase_data_byte_last_in_allocate_mem(
        &(*find_node_wfree_allocate_mem(
            NULL,
            &(*root_l)->node))->data_alloc,
        (*root_l)->data_struct_byte_size);
    /*
    DEBUG_TRACKING_ALLOC_MEM_AFTER(
        "LIST AT DELETE OF LAST ELEMENT",
        find_node_wfree_allocate_mem(
            NULL,
            &(*root_l)->node),
        (*root_l)->data_struct_byte_size);
    */
    try_free_mem_fdata_node(&(*root_l)->node);
}
void del_index_element_to_list(list** root_l, size_t index){
    if(!(*root_l)){
        printf("Passed to function - copy_el_data_to_allocate_mem_fdata(), the list does not exist\n");
        exit(1);
    }
    size_t index_count_el_nodes = 0;
    node** nod = find_node_index_allocate_mem(&(*root_l)->node, index, &index_count_el_nodes);
    if((nod == NULL)){
        printf("Element with index not found - %d\n", index);
        exit(1);
    }
    // DEBUG_TRACKING_ALLOC_MEM_BEFORE("LIST AT DELETE OF INDEX ELEMENT", nod , (*root_l)->data_struct_byte_size);
    erase_data_byte_in_allocate_mem(&(*nod)->data_alloc, (*root_l)->data_struct_byte_size, (index >= index_count_el_nodes) ? index - index_count_el_nodes : index);
    // DEBUG_TRACKING_ALLOC_MEM_AFTER("LIST AT DELETE OF INDEX ELEMENT", nod , (*root_l)->data_struct_byte_size);
    try_free_mem_fdata_node(&(*root_l)->node);
}
void* get_element(list** root_l, size_t index){
    if (!(*root_l)) {
        printf("Passed to function - copy_el_data_to_allocate_mem_fdata(), the list does not exist\n");
        exit(1);
    }
    size_t index_count_el_nodes = 0;
    node** nod = find_node_index_allocate_mem(&(*root_l)->node, index, &index_count_el_nodes);
    if(nod == NULL){
        not_exist_el:
        printf("Element with index not found - %d\n", index);
        exit(1);
    }
    if(index_element_is_null((*nod)->data_alloc, (*root_l)->data_struct_byte_size, (index>= index_count_el_nodes) ? index-index_count_el_nodes : index) == 1)
        goto not_exist_el;
    return copy_data_byte_from_allocate_mem(&(*nod)->data_alloc, (*root_l)->data_struct_byte_size, (index>= index_count_el_nodes) ? index-index_count_el_nodes : index);
}
void* get_last_element(list** root_l){
    if (!(*root_l)) {
        printf("Passed to function - copy_el_data_to_allocate_mem_fdata(), the list does not exist\n");
        exit(1);
    }
    node** nod = find_node_wfree_allocate_mem(NULL, &(*root_l)->node);
    //debug_output_allocate_mem_char(nod, (*root_l)->data_struct_byte_size);
    return copy_data_byte_from_allocate_mem(&(*nod)->data_alloc,(*root_l)->data_struct_byte_size, get_offset_last_element_allocate_mem(&(*nod)->data_alloc, (*root_l)->data_struct_byte_size));
}