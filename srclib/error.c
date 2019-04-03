#include "debug.h"
#include "error.h"

#ifdef NOERROR

  void error_test(int expr, const char* msg) {
  }

#else

  #include <stdio.h>
  #include <stdlib.h>

  extern void _free_ptrs();

  void error_test(int expr, const char* msg) {
    if (!expr) {
      fprintf(stderr, "%s\n", msg);

      // Free the pointers in auto pointer list
      _free_ptrs();

      exit(1);
    }
  }

#endif
