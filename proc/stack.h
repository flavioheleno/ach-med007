#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>
#include <stdint.h>

typedef struct stk {
  uint16_t data;
  struct stk *next;
} stack;

int stackIsEmpty(stack *s);
void stackCreate(stack **s);
void stackDestroy(stack **s);
void stackPush(stack **s, uint16_t data);
void stackDrop(stack **s);
uint16_t stackTop(stack *s);
uint16_t stackPop(stack **s);
int stackLen(stack *s);

#endif
