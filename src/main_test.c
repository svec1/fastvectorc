#include <stdio.h>
#include <stdlib.h>
#include "allocate_list_f.h"

int main(){

    list *l = malloc(sizeof(list));
    l->data_byte_size = sizeof(int);
    l->data_alloc.allocate_data = malloc(l->data_byte_size*MAX_SIZE_NODE_DATA);
    l->data_alloc.data_size = 0;
    int a = 12;
    allocate_data_list(l, &a, sizeof(int));
    void* a_ptr = extract_data_elem(l, 0);
    printf("Int a: %i", *((int*)a_ptr));
    return 0;
}