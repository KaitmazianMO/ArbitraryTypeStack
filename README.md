# ArbitraryTypeStack
  
¨/\_/\ ♥
>^,^<
¨¨/ \
’¨(__)__
  
  ## How to use it

  ### Set type of stack first!

   To set the type of stack write this line:

   #define stack_t **type**
    
   Example of setting int type:
   
   ```#define stack_t int```
   
   **Warning:** for stack_t you can use only standart types with no spaces notation!

  ### Iclude the library after you set the type of stack

   To include the library you sould use this strange command:

   ```#include "stack.h"```
   
   Now you have 2 lines:
   ```
      #define stack_t int
      #include "stack.h"
   ```
      
   That means you can use new type: **stack_int**
   
  ### Using stack
  
   After you include the library right you can declare varriable. So do it:
   
   ```stack_int stk = {};```
   
   To start work with stack by stack functuons construct your stack **stk** by function stack_ctor with start capcity **capacity** (for example capcity is 14):
   
   ```stack_ctor (&stack_with_type_int, 14)```
   
   **Now you can use stack function!**
   
   Examples of stack functions: 
   
   stack_dtor      (stack_ptr       ) - *Delletes all spaces and the data of the stack.* **NEVER FORGET TO DISTRUCT THE STACK**
   
   stack_push      (stack_ptr, value) - *Add an item to the top of the stack.*
   
   stack_peek      (stack_ptr       ) - *Returns value of the top element of the stack.*
   
   stack_pop       (stack_ptr       ) - *Returns value of the top element of the stack and deletes it.*
   
   stack_free_data ( stack_ptr      ) - *Clears the data of stack.*
   
   stack_size      (stack_ptr       ) - *Returnes current size of the stack.*
   
   stack_capacity  (stack_ptr       ) - *Returnes current capacity of the stack.*
   
   stack_resize    (stack_ptr, 
                    new_size, 
                    value_size      ) - *I should modificate this strange function....*

   
    
