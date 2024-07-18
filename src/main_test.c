#include <stdio.h>
#include <stdlib.h>
#include "allocate_list_f.h"

int main(){

    list *l = malloc(sizeof(list));
    l->data_byte_size = sizeof(size_t);
    l->data_alloc.allocate_data = malloc(l->data_byte_size*MAX_SIZE_NODE_DATA);
    l->data_alloc.data_size = 0;
    l->node = NULL;
    for(size_t i = 0; i < 100; ++i){
        allocate_data_list(l, &i, sizeof(size_t));
    }
    void* a_ptr = extract_data_elem(l, 12);
    printf("Int a: %i", *((int*)a_ptr));
    return 0;
}