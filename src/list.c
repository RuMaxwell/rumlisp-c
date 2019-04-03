#include "../header/list.h"

void* newInt(int value) {
  IntType* p = new_ptr(sizeof (IntType));
  *(enum BasicType*)p = TInt;

  p->value = value;
  return p;
}

void* newInteger(size_t bigvlen, int* bigvalue) {
  IntegerType* p = new_ptr(sizeof (IntegerType));
  *(enum BasicType*)p = TInteger;

  p->digitCount = bigvlen;
  memcpy(p->value, bigvalue, bigvlen * (sizeof (char)));
  return p;
}

void* newFloat(double value) {
  FloatType* p = new_ptr(sizeof (FloatType));
  *(enum BasicType*)p = TFloat;

  p->value = value;
  return p;
}

void* newString(const char* value) {
  StringType* p = new_ptr(sizeof (StringType));
  *(enum BasicType*)p = TString;

  size_t length = strlen(value);
  p->length = length;
  p->value = new_ptr(length);
  strcpy(p->value, value);
  return p;
}

void* newBindName(const char* name, const void* value) {
  BindNameType* p = new_ptr(sizeof (BindNameType));
  *(enum BasicType*)p = TBindName;

  size_t nameLength = strlen(name);
  p->name = new_ptr(nameLength);
  strcpy((char*)p->name, name);

  p->value = _Const_CAST value;
  return p;
}

void* newFunction(const char* parameter, const char* expression) {
  FunctionType* p = new_ptr(sizeof (FunctionType));
  *(enum BasicType*)p = TFunction;

  size_t length;
  length = strlen(parameter);
  p->parameter = new_ptr(length);
  strcpy((char*)p->parameter, parameter);

  length = strlen(expression);
  p->expression = new_ptr(length);
  strcpy((char*)p->expression, expression);

  return p;
}

inline const list* nil() {
  return NULL;
}

static const ListPrototype _T = { 1, NULL, NULL };
inline const list* T() {
  return &_T;
}

const list* cons(const void* car, const list* cdr) {
  ListPrototype* p = new_ptr(sizeof (ListPrototype)); // Invisibly set `*(enum BasicType*)p = TList`
  p->car = _Const_CAST car;
  p->cdr = _Const_CAST cdr;
  return p;
}

const void* car(const list* xs) {
  return xs->car;
}

const list* cdr(const list* xs) {
  return xs->cdr;
}

const list* cat(const list* xs, const list* ys) {
  if (!xs) return ys;
  if (!ys) return xs;

  const void* x = car(xs);
  const list* xss = cdr(xs);

  return cons(x, cat(xss, ys));
}

const void* find(int (*f)(const void*), const list* xs) {
  if (!xs) return NULL;

  const void* x = car(xs);
  const list* xss = cdr(xs);

  return f(x) ? x : find(f, xss);
}
// const void* findIndex(int (*f)(void*)) {
// }
