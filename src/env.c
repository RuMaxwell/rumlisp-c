#include "../header/env.h"

const Environment* initialEnvironment() {
  return nil();
}

const Environment* extendEnvironment(const BindNameType* nv, const Environment* env) {
  return cons(nv, env);
}

// Stores current binded name to be looked-up.
static char* lookupName;
static int lookupFunc(const void* nv) {
  const BindNameType* p = nv;
  return !(strcmp(p->name, lookupName));
}

const BindNameType* lookupEnvironment(const char* name, const Environment* env) {
  lookupName = _Const_CAST name;
  const void* res = find(lookupFunc, env);
  lookupName = NULL;
  return res;
}

const Closure* enclosure(const FunctionType* f, const Environment* env) {
  Closure* p = new_ptr(sizeof (Closure));
  p->f = _Const_CAST f;
  p->env = _Const_CAST env;
  return p;
}
