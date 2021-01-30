#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define stack_t int
#define LOG_FILE_NAME "stack_log.txt"
#include "stack.h"


typedef long long ll;
#define stack_t ll
#define LOG_FILE_NAME "stack_log.txt"
#include "stack.h"

int main() {

    stack_int stk1 = {};
    stack_ctor(&stk1, 2);

    stack_ll stk2 = {};
    stack_ctor(&stk2, 2);
    
    for (int i = 0; i < 10; ++i) {
        stack_push(&stk2, 3.14 + (double)i / 100);
    }                  
    
    stk2.backCanary = 1;  // Error simulation

    stack_dtor(&stk1);
    stack_dtor(&stk2);
    close_log_file();
    return 0;
}

