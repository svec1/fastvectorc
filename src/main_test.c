#include <stdio.h>
#include <stdlib.h>
#include "allocate_list_f.h"

int main(){

    list *l = malloc(sizeof(list));
    l->node = NULL;
    l->data_struct_byte_size = sizeof(size_t);
    for(size_t i = 0; i < 99; ++i){
        add_element_to_list(&l, &i, sizeof(size_t));
    }
    del_index_element_to_list(&l, 97);
    del_index_element_to_list(&l, 94);

    size_t data = 993;
    append_element_to_list(&l, &data, sizeof(size_t), 23);
    append_element_to_list(&l, &data, sizeof(size_t), 25);
    
    //del_last_element_to_list(&l);
    void* a_ptr = get_element(&l, 27);
    printf("Int a: %i\n", *((size_t*)a_ptr));
    return 0;
}