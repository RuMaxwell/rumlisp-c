/*
 * A simple implementation of auto-allocated-and-deleted pointers.
 * Every pointer needing heap allocation should use the functions in this file.
 * User should always include this file instead of auto_ptr_basic.h for use of auto_ptr.
 */

#ifndef AUTO_PTR_H
#define AUTO_PTR_H

#include "auto_ptr_defs.h"
#include "error.h"

// Do not use this in user programs
void __proceed_index();

// Only use this in main module
void _initialize_ptr_list();

// Always use this function to get the pointer
void* new_ptr(size_t size);

// For user to manually delete a pointer
void require_delete(void* ptr);

#endif
