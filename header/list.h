#ifndef _RLISP_LIST_H_
#define _RLISP_LIST_H_

#include "../srclib/auto_ptr.h"
#include <memory.h>
#include <stdio.h>
#include <string.h>

#define _Const_CAST (void*)

enum BasicType {
  TList,
  TInt,
  TInteger,
  TFloat,
  TString,
  TBindName,
  TFunction
};

// Consider hiding structs later.

typedef struct {
  const enum BasicType type;
  int value;
} IntType;

typedef struct {
  const enum BasicType type;
  size_t digitCount;
  char* value;
} IntegerType;

typedef struct {
  const enum BasicType type;
  double value;
} FloatType;

typedef struct {
  const enum BasicType type;
  size_t length;
  char* value;
} StringType;

typedef struct {
  const enum BasicType type;
  char value;
} BooleanType;

typedef struct {
  const enum BasicType type;
  char* name;
  void* value;
} BindNameType;

typedef struct {
  const enum BasicType type;
  const char* parameter;
  const char* expression;
} FunctionType;

typedef struct ListPrototype {
  const enum BasicType type;
  void* car;
  struct ListPrototype* cdr;
} ListPrototype;
typedef ListPrototype list;

void* newInt(int value);
void* newInteger(size_t bigvlen, int* bigvalue);
void* newFloat(double value);
void* newString(const char* value);
void* newBindName(const char* name, const void* value);
void* newFunction(const char* parameter, const char* expression);

const list* nil();
const list* T();
const list* cons(const void* car, const list* cdr);
const void* car(const list* xs);
const list* cdr(const list* xs);

const list* cat(const list* xs, const list* ys);

// Returns the first element passed to `f` yielding `true`.
const void* find(int (*f)(const void*), const list* xs);
// Returns the index of the first element passed to `f` yielding `true`.
// const void* findIndex(int (*f)(void*), const list* xs);

#endif
