#include "header/list.h"

void print(const void* x);
void printInt(const IntType* x) {
  printf("%d", x->value);
}
void printInteger(const IntegerType* x) {
  size_t i;
  for (i = 0; i < x->digitCount; i++) {
    printf("%c", x->value[i]);
  }
}
void printFloat(const FloatType* x) {
  printf("%f", x->value);
}
void printString(const StringType* x) {
  printf("\"%s\"", x->value);
}
void printBindName(const BindNameType* x) {
  printf("<%s . ", x->name);
  print(x->value);
  putchar('>');
}
void printFunction(const FunctionType* x) {
  printf("<\\ (");
  int i;
  printf("%s", x->parameter);
  printf(") %s \\>", x->expression);
}
void printListHelper(const list* xs) {
  if (!xs) return;
  else if (xs == T()) printf("T");
  else if (!cdr(xs)) print(car(xs));
  else {
    print(car(xs));
    putchar(' ');
    printListHelper(cdr(xs));
  }
}
void printList(const list* xs) {
  putchar('(');
  printListHelper(xs);
  putchar(')');
}
void print(const void* x) {
  if (!x) { printf("NIL"); return; }
  switch (*(const enum BasicType*)x) {
    case TList    : printList((list*)x); break;
    case TInt     : printInt((IntType*)x); break;
    case TInteger : printInteger((IntegerType*)x); break;
    case TFloat   : printFloat((FloatType*)x); break;
    case TString  : printString((StringType*)x); break;
    case TBindName: printBindName((BindNameType*)x); break;
    case TFunction: printFunction((FunctionType*)x); break;
    default: break;
  }
}
void println(const void* x) {
  print(x);
  putchar('\n');
}

int main(int argc, char* argv[]) {
  void* vs[5];
  size_t i;
  for (i = 0; i < 5; i++)
    vs[i] = newInt(i + 1);

  void* xs = _Const_CAST nil();
  println(xs);
  for (i = 0; i < 5; i++)
    xs = _Const_CAST cons(vs[i], xs);

  const void* f;
  println(f = newFunction("x", "(+ x 1)"));
  println(newBindName("f", f));
  println(xs);

  return 0;
}
