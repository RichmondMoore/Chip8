#ifndef STACK.H
#define STACK.H

typedef struct {
    int capacity;
    int sp;
    int *data;
} Stack;

/* FUNCTIONS */

void create_stack(int size);
void push(int val);
int pop();
int peek();
int is_empty();

#endif
