#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../include/Stack.h"

Stack stack;

void create_stack(int size) {
    stack.capacity = size;
    stack.data = (int *)malloc(size * sizeof(int));
    stack.sp = -1; // -1 means there is no data
}

void push(int val) {
    if (stack.sp == stack.capacity) {
        printf("ERROR: stack is full!");
        return;
    }
    stack.sp += 1;
    stack.data[stack.sp] = val;
}

int pop() {
    if (stack.sp == -1) {
        printf("ERROR: Stack is empty!\n");
        return INT_MIN;
    }

    int val = stack.data[stack.sp];
    stack.sp =- 1;
    return val;
}

int peek() {
    if (stack.sp == -1) {
        printf("ERROR: Stack is empty!\n");
        return INT_MIN;
    }
    return stack.data[stack.sp];
}

int is_empty() {
    if (stack.sp == -1)
        return 1;
    else
        return 0;
}
