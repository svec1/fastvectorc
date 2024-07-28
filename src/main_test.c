
#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

int main(){

    list *l = create_list(sizeof(size_t));
    for(size_t i = 0; i < 99; ++i){
        data_element data;
        data.allocate_data = &i;
        data.data_struct_byte_size = sizeof(size_t);
        push(&l, data);
    }
    erase(&l, 97);
    erase(&l, 94);

    size_t tmp = 993;
    data_element data;
    data.allocate_data = &tmp;
    data.data_struct_byte_size = sizeof(size_t);
    append(&l, data, 23);
    tmp = 994;
    append(&l, data, 25);
    append(&l, data, 25);
    erase(&l, 25);
    /*
    */
   debug_output_list_chain_u64t(l);
    
    
    //del_last_element_to_list(&l);
    void* a_ptr = get_element_list(&l,24);
    printf("Int a: %i\n", *((size_t*)a_ptr));
    return 0;
}