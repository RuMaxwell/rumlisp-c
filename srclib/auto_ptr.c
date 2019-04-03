#include "auto_ptr.h"

extern auto_ptr* __ptr_list;
extern size_t __ptr_count;

auto_ptr* __new_auto_ptr() {
  auto_ptr* p = (auto_ptr*)malloc(AUTO_PTR_SIZE);
  p->ptr = NULL;
  p->next = NULL;
  p->prev = NULL;
}

// A null ptr list contains a head and a tail node
void __init_ptr_list() {
  __ptr_list = __new_auto_ptr();
  __ptr_list->next = __new_auto_ptr();
  __ptr_list->next->prev = __ptr_list;
}

void* new_ptr(size_t size) {
  error_test(__ptr_count >= PTR_LIST_MAXSIZE ? 0 : 1, "error: exceeding maximum auto pointer list size");

  if (!__ptr_list) {
    __init_ptr_list();
  }

  auto_ptr* head = __ptr_list;
  auto_ptr* next = __ptr_list->next;
  auto_ptr* p = __new_auto_ptr();
  p->ptr = calloc(1, size);
  head->next = p;
  next->prev = p;
  p->next = next;
  p->prev = head;

  __ptr_count++;

  return p->ptr;
}

void require_delete(void* ptr) {
  auto_ptr* p = __ptr_list->next;
  for (; p->next != NULL; p = p->next) {
    if (p->ptr == ptr) {
      free(ptr);
      p->ptr = NULL;
      p->prev->next = p->next;
      p->next->prev = p->prev;
      free(p);
      return;
    }
  }
  error_test(0, "error: requiring to delete a pointer that is not in auto pointer list");
}
