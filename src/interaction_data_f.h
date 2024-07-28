/* Copyright (c) 2024 svec */

#ifndef INTERACTION_DATA_F__H
#define INTERACTION_DATA_F__H

#include "allocate_node_mem_f.h"

unsigned char index_element_is(data* data_alloc, size_t data_struct_byte_size, size_t offset, unsigned char is_ch);

#define index_element_is_null(data_alloc, data_struct_byte_size, offset) index_element_is(data_alloc, data_struct_byte_size, offset, NULL)
#define index_element_is_reserv(data_alloc, data_struct_byte_size, offset) index_element_is(data_alloc, data_struct_byte_size, offset, BYTE_RESERV_COMPOSE)

size_t get_offset_last_element_allocate_mem(data* data_alloc, size_t data_struct_byte_size);

void copy_data_byte_to_data_alloc_allocate_mem(data** data_alloc, void* data, size_t data_struct_byte_size);
void erase_data_byte_last_in_allocate_mem(data** data_alloc, size_t data_struct_byte_size);
void erase_data_byte_in_allocate_mem(data** data_alloc, size_t data_struct_byte_size, size_t offset);

void* copy_data_byte_from_allocate_mem(data** data_alloc, size_t data_struct_byte_size, size_t offset);

#endif