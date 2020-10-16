#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h> 

#define NO_DBG
#define NO_LOG

#define LOG_FILE_NAME "LogStack.txt"

#define stack_t double
#include "stack.h"
#undef stack_t

#define stack_t int
#include "stack.h"
#undef stack_t

int main()
    {
    stack_double *stk_double = new_stack_double ();

    stack_push (stk_double, 3.14);

    stack_int *stk_int  = new_stack_int(2);

    stack_push (stk_int, -1);

    stack_pop (stk_int);
                        
    stack_pop (stk_double);

    stk_double = dell_stack (stk_double);

    stk_int = dell_stack (stk_int);
    }
