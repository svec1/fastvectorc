/* Copyright (c) 2024 svec */

#include "../include/list.h"

#include <stdlib.h>

list* create_list(size_t data_struct_byte_size){
    list* _list = malloc(sizeof(list));
    _list->data_struct_byte_size = data_struct_byte_size;
    allocate_mem_fdata_node(&_list->node, data_struct_byte_size);
    return _list;
}
void delete_list(list** root_l){
    free_node(&(*root_l)->node);
    free(*root_l);
}

void push(list** root_l, data_element data){
    add_element_to_list(root_l, data.allocate_data, data.data_struct_byte_size);
}
void append(list** root_l, data_element data, size_t index){
    append_element_to_list(root_l, data.allocate_data, data.data_struct_byte_size, index-1);
}

data_element pop(list** root_l){
    del_last_element_to_list(root_l);
}
data_element erase(list** root_l, size_t index){
    del_index_element_to_list(root_l, index);
}

data_element get_element(list** root_l, size_t index){
    data_element data;
    data.allocate_data = get_element_list(root_l, index);
    data.data_struct_byte_size = (*root_l)->data_struct_byte_size;
    return data;
}
data_element get_element_last(list** root_l){
    data_element data;
    data.allocate_data = get_last_element_list(root_l);
    data.data_struct_byte_size = (*root_l)->data_struct_byte_size;
    return data;
}