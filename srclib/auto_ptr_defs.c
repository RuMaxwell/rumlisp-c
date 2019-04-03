#include "auto_ptr_defs.h"

auto_ptr* __ptr_list = NULL;
size_t __ptr_count = 0;

void _free_ptrs() {
  #ifndef NODEBUG
    printf("Trying to free auto pointer list...\n");
  #endif

  if (__ptr_list) {
    auto_ptr* p = __ptr_list;
    auto_ptr* q = NULL;
    for (; p->next != NULL; p = q) {
      q = p->next;
      if (__ptr_list->ptr) {
        free(p->ptr);
      }
      free(p);
      p = NULL;
    }
    __ptr_list = NULL;
    __ptr_count = 0;
  }
}
