#ifndef _ENV_H_
#define _ENV_H_

#include "list.h"

typedef list Environment;

// Get an empty environment.
const Environment* initialEnvironment();
// Extend an environment by a name-value pair.
const Environment* extendEnvironment(const BindNameType* nv, const Environment* env);
// Lookup the inner-most name-value pair in an environment.
const BindNameType* lookupEnvironment(const char* name, const Environment* env);

typedef struct {
  FunctionType* f;
  Environment* env;
} Closure;

const Closure* enclosure(const FunctionType* f, const Environment* env);

#endif
