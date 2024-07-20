#include "interaction_data_f.h"

#include <stdlib.h>

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