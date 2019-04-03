/*
 * This file is explicit from other auto_ptr files because error.h
 * needs function _free_ptrs to free the auto_ptrs before exit the program.
 *
 * Note: The way of implementing auto_ptr doesn't include how to destroy them
 * when they are permanently useless, which means that those pointers only grows
 * without being destroyed at right time. This could cause very big problem
 * when the program getting big. There should be an improvement on this issue.
 */

#ifndef AUTO_PTR_DEFS_H
#define AUTO_PTR_DEFS_H

#include <malloc.h>
#include <stdio.h>

#ifndef PTR_LIST_MAXSIZE
  // This limits the maximum number of auto_ptrs
  #define PTR_LIST_MAXSIZE 65536
#endif
#define PTR_SIZE (sizeof (void*))
#define AUTO_PTR_SIZE (sizeof (auto_ptr))

// Things with prefix "__" should never be used outside this file.
// Things with prefix "_" should only be used by the main module.

typedef struct auto_ptr {
  void* ptr;
  struct auto_ptr* next;
  struct auto_ptr* prev;
} auto_ptr;

void _free_ptrs();

#endif
