#include "auto_ptr.h"

#include <stdio.h>

int* sub_array(int* arr, int start, int end) {
  if (start >= end) {
    return NULL;
  }

  int* res = (int*)new_ptr((end - start) * sizeof (int));

  for (int i = start; i < end; i++) {
    res[i - start] = arr[i];
  }

  return res;
}

int product(int* arr, int start, int end) {
  int res = 1;
  for (int i = start; i < end; i++) {
    res *= arr[i];
  }
  return res;
}

int muladd(int* arr, int len, int split_index) {
  int* arr1 = sub_array(arr, 0, split_index);
  int* arr2 = sub_array(arr, split_index, len);
  int res = product(arr1, 0, split_index) + product(arr2, 0, len - split_index);
  require_delete(arr1);
  require_delete(arr2);
  return res;
}

int main() {
  int* arr = (int*)new_ptr(10 * sizeof (int));

  for (int i = 0; i < 10; i++) {
    arr[i] = i + 1;
  }

  int p = 0;
  for (int i = 0; i < 1024; i++) {
    p = muladd(arr, 10, 4);
  }
  printf("%d\n", p);

  _free_ptrs();
  return 0;
}
