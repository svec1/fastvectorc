#include "allocate_list_f.h"

#include <stdlib.h>
#include <assert.h>

void byte_data_copy(void** dest, void* src, size_t dest_size_byte, size_t src_size_byte, size_t offset_byte){
    assert(dest_size_byte-offset_byte>src_size_byte);
    for(size_t i = 0, j = offset_byte; i < src_size_byte; ++i, ++j){
        ((unsigned char*)*dest)[j] = ((unsigned char*)src)[i];
    }
}
void* get_data(void* src, size_t dest_size_byte, size_t data_byte_size, size_t offset_byte){
    assert(dest_size_byte-offset_byte>data_byte_size);
    void* data = malloc(data_byte_size);
    for(size_t i = offset_byte, b = 0; i < offset_byte+data_byte_size; ++i, ++b){
        ((unsigned char*)data)[b] = ((unsigned char*)src)[i];
    }
    return data;
}

void allocate_data_list(root* list_r, void* data_src, size_t data_src_byte_size){
    assert(data_src_byte_size==list_r->data_byte_size);
    if(list_r->data_alloc.data_size<MAX_SIZE_NODE_DATA){
        byte_data_copy(&list_r->data_alloc.allocate_data, 
                       data_src, MAX_SIZE_NODE_DATA*list_r->data_byte_size,
                       list_r->data_byte_size, list_r->data_alloc.data_size*list_r->data_byte_size);
        ++list_r->data_alloc.data_size;
    }
    else if(list_r->data_alloc.data_size==MAX_SIZE_NODE_DATA){
        node* curr_node = list_r->node;
        while(curr_node){
            if(curr_node->data_alloc.data_size<MAX_SIZE_NODE_DATA){
                byte_data_copy(&curr_node->data_alloc.allocate_data, 
                               data_src, MAX_SIZE_NODE_DATA*list_r->data_byte_size,
                               list_r->data_byte_size, curr_node->data_alloc.data_size*list_r->data_byte_size);
                ++list_r->data_alloc.data_size;
                break;
            }
            else
                curr_node = curr_node->next_node;
        }
        if(!curr_node){
            curr_node = malloc(sizeof(node));
            curr_node->data_alloc.allocate_data = malloc(list_r->data_byte_size*MAX_SIZE_NODE_DATA);
            ++curr_node->data_alloc.data_size;
            byte_data_copy(&curr_node->data_alloc.allocate_data, 
                           data_src, MAX_SIZE_NODE_DATA*list_r->data_byte_size,
                           list_r->data_byte_size, curr_node->data_alloc.data_size*list_r->data_byte_size);
        }
    }
    else if(list_r->data_alloc.data_size>=MAX_SIZE_NODE_DATA){
        printf("The number of elements must not exceed the specified maximum value");
        exit(1);
    }
}
void* extract_data_elem(root* list_r, size_t index){
    if(list_r->data_alloc.data_size<MAX_SIZE_NODE_DATA){
        assert(list_r->data_alloc.data_size>=index);
        return get_data(list_r->data_alloc.allocate_data, list_r->data_byte_size*MAX_SIZE_NODE_DATA, list_r->data_byte_size, index*list_r->data_byte_size);
    }
    else if(list_r->data_alloc.data_size==MAX_SIZE_NODE_DATA){
        node* curr_node = list_r->node;
        while(curr_node){
            if(curr_node->data_alloc.data_size<MAX_SIZE_NODE_DATA){
                assert(list_r->data_alloc.data_size>=index);
                return get_data(list_r->data_alloc.allocate_data, list_r->data_byte_size*MAX_SIZE_NODE_DATA, list_r->data_byte_size, index*list_r->data_byte_size);
            }
            else
                curr_node = curr_node->next_node;
        }
        if(!curr_node){
            printf("element not found");
            exit(1);
        }
    }
}