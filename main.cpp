#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define stack_t        double
#define LOG_FILE_NAME  "stack_log.txt"
#include "stack.h"

int main() {
    stack_double stk = {};
    stack_ctor (&stk, 10);

    for (int i = 0; i < 10; ++i) {
        stack_push (&stk, 3.14 + (double)i/100);
    }

    stack_dtor (&stk);
    fclose (LOG_FILE_PTR);
}
