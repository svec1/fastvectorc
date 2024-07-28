#include "interaction_list_f.h"

#include <stdlib.h>

void debug_output_list_chain_u64t(list* root_l){
    node* curr_nod = root_l->node;
    while(curr_nod){
        debug_output_allocate_mem_char(curr_nod, root_l->data_struct_byte_size);
        curr_nod = curr_nod->next_node;
    }
}

void allocate_mem_fdata(list** root_l){
    allocate_mem_fdata_node(&(*root_l)->node, (*root_l)->data_struct_byte_size);
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
    else if(data_struct_byte_size==8 && *(size_t*)data == ULLONG_MAX){
        printf("ULLONG_MAX is a value to indicate a backup item in the current list\n");
        exit(1);
    }
    
    copy_data_byte_to_data_alloc_allocate_mem(
        try_allocate_mem_fdata_node(
            &(*root_l)->node,
            data_struct_byte_size),
        data,
        data_struct_byte_size);
}
void append_element_to_list(list** root_l, void* data, size_t data_struct_byte_size, size_t index){
    if(!(*root_l)){
        printf("Passed to function - copy_el_data_to_allocate_mem_fdata(), the list does not exist\n");
        exit(1);
    }
    else if(data_struct_byte_size!=(*root_l)->data_struct_byte_size){
        printf("The size of the list item structure is not equal to the size passed to the function: add_element_to_list()\n");
        exit(1);
    }
    else if(data_struct_byte_size==8 && *(size_t*)data == ULLONG_MAX){
        printf("ULLONG_MAX is a value to indicate a backup item in the current list\n");
        exit(1);
    }
    node** nod = find_node_index_allocate_mem(&(*root_l)->node, &index);
    //debug_output_allocate_mem_char(*nod, (*root_l)->data_struct_byte_size);
    if((*nod)->data_alloc->count_elem==MAX_SIZE_NODE_DATA){
        node* new_nod;
        node* tmp_nod;
        allocate_mem_fdata_node(&new_nod, (*root_l)->data_struct_byte_size);
        if((*nod)->next_node) {
            tmp_nod = (*nod)->next_node;
            (*nod)->next_node = new_nod;
            (*nod)->next_node->next_node = tmp_nod;
        }
        else (*nod)->next_node = new_nod;
        copy_data_byte_to_data_alloc_allocate_mem(&(*nod)->next_node->data_alloc, data, (*root_l)->data_struct_byte_size);
    }
    else
        copy_data_byte_to_data_alloc_allocate_mem(&(*nod)->data_alloc, data, (*root_l)->data_struct_byte_size);
}
void del_last_element_to_list(list** root_l){
    if(!(*root_l)){
        printf("Passed to function - copy_el_data_to_allocate_mem_fdata(), the list does not exist\n");
        exit(1);
    }
    /*
    DEBUG_TRACKING_ALLOC_MEM_BEFORE(
        "LIST AT DELETE OF LAST ELEMENT",
        *find_node_wfree_allocate_mem(
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
        *find_node_wfree_allocate_mem(
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
    node** nod = find_node_index_allocate_mem(&(*root_l)->node, &index);
    if((nod == NULL)){
        printf("Element with index not found - %d\n", index);
        exit(1);
    }
    // DEBUG_TRACKING_ALLOC_MEM_BEFORE("LIST AT DELETE OF INDEX ELEMENT", *nod , (*root_l)->data_struct_byte_size);
    erase_data_byte_in_allocate_mem(&(*nod)->data_alloc, (*root_l)->data_struct_byte_size, index);
    // DEBUG_TRACKING_ALLOC_MEM_AFTER("LIST AT DELETE OF INDEX ELEMENT", *nod , (*root_l)->data_struct_byte_size);
    try_free_mem_fdata_node(&(*root_l)->node);
}
void* get_element_list(list** root_l, size_t index){
    if (!(*root_l)) {
        printf("Passed to function - copy_el_data_to_allocate_mem_fdata(), the list does not exist\n");
        exit(1);
    }
    size_t tmp_index = index;
    node** nod = find_node_index_allocate_mem(&(*root_l)->node, &index);
    if(nod == NULL){
        not_exist_el:
        printf("Element with index not found - %d\n", tmp_index);
        exit(1);
    }
    if(index_element_is_reserv((*nod)->data_alloc, (*root_l)->data_struct_byte_size, index)){
        index = --tmp_index;
        while((nod = find_node_index_allocate_mem(&(*root_l)->node, &index)) != NULL && index_element_is_reserv((*nod)->data_alloc, (*root_l)->data_struct_byte_size, index)){
            if(!index)
                index = --tmp_index;
         }
    }
    debug_output_allocate_mem_char(*nod, (*root_l)->data_struct_byte_size);
    if(index_element_is_null((*nod)->data_alloc, (*root_l)->data_struct_byte_size, index) == 1)
        goto not_exist_el;
    return copy_data_byte_from_allocate_mem(&(*nod)->data_alloc, (*root_l)->data_struct_byte_size, index);
}
void* get_last_element_list(list** root_l){
    if (!(*root_l)) {
        printf("Passed to function - copy_el_data_to_allocate_mem_fdata(), the list does not exist\n");
        exit(1);
    }
    node** nod = find_node_wfree_allocate_mem(NULL, &(*root_l)->node);
    //debug_output_allocate_mem_char(*nod, (*root_l)->data_struct_byte_size);
    return copy_data_byte_from_allocate_mem(&(*nod)->data_alloc,(*root_l)->data_struct_byte_size, get_offset_last_element_allocate_mem(&(*nod)->data_alloc, (*root_l)->data_struct_byte_size));
}