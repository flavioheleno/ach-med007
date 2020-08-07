#include "stack.h"

int stackIsEmpty(stack *s) {
  return (s == NULL);
}

void stackCreate(stack **s) {
  (*s) = NULL;
}

void stackDestroy(stack **s) {
  stack *p;
  p = (*s);
  while (p) {
    (*s) = (*(*s)).next;
    free(p);
    p = (*s);
  }
}

void stackPush(stack **s, uint16_t data) {
  stack *p;
  p = (stack *)malloc(sizeof(stack));
  (*p).data = data;
  (*p).next = (*s);
  (*s) = p;
}

void stackDrop(stack **s) {
  stack *p;
  if (!stackIsEmpty((*s))) {
    p = (*s);
    (*s) = (*(*s)).next;
    free(p);
  }
}

uint16_t stackTop(stack *s) {
  if (!stackIsEmpty(s)) {
    return (*s).data;
  }

  return 0;
}

uint16_t stackPop(stack **s) {
  uint16_t v;
  if (!stackIsEmpty((*s))) {
    v = stackTop((*s));
    stackDrop(s);

    return v;
  }

  return 0;
}

int stackLen(stack *s) {
  int i = 0;
  stack *p;
  p = s;
  while (p) {
    i++;
    p = (*p).next;
  }

  return i;
}
