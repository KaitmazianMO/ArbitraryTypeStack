# ArbitraryTypeStack
  
```
▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
▐▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▌
▐▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▌
▐▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▌
▐▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░▓▓░░░░▓▓▓▓▓▓▓▓▓▌
▐▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░░▓▓▓▓▓▓▓▓▌
▐▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░░▓▓▓▓▓▓▓▓▌
▐▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░░░░░░▓░░░░▓▓▓▌
▐▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░░█▄░░░░▄█░░░░░░░░▓▓▌
▐▓▓▓▓▓▓▓▓▓▓░░░░▓▓▓▓▓▓▓░░░████████░░░░▄▄░░▓▓▌
▐░░░░▓▓▓▓▓▓░░░░▓▓▓▓▓▓▓░░░███▀██▀█░░▄███░░▓▓▌
▐░░░░▓▓▓▓▓▓░░░░▓▓▓▓▓▓▓░░░▐████▀██▄███▀░░░▓▓▌
▐░░░░░▓▓▓░░░░░░▓▓▓░░░▓░░░░▀████████▀░░▄▄░░░▌
▐░░░░░▓▓▓░░░░░░░░░░░░░░░░▄███████▀░░▄███░░░▌
▐░░░░░▓▓▓░░░░░░░░░░░░░░░▄█████████▄███▀░░░░▌
▐░░░░░░░░░░░░░░░░░░░░▄██████████████▀░░░░░░▌
▐░░░░░░░░░░░░░░░░░░▄██████████████▀░░░░░░░░▌
▐░░░░░░░░░░░░░░░░░▐████████████▀░░░░░░░░░░░▌
▐░░░░░░░░░░░░░░░░░█████████████░░░░░░░░░░░░▌
▐░░░░░░░░░░░░░░░░█████████████▌░░░░░░░░░░░░▌
▐░░░░░░░░░░░░░░░██████████████░░░░░░░░░░░░░▌
▐░██▄░░░░░░░▄▄██████████████▀░░░░░░░░░░░░░░▌
▐░▀███▄░░▄███████████████▀▀░░░░░░░░░░░░░░░░▌
▐░░░▀▀█████▀▀░░▒▀███▌███▄░░░░░░░░░░░░░░░░░░▌
▐░░░░░░░░░░░░░░░░░▀██▌████░░░░░░░░░░░░░░░░░▌
▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

```

  ## How to use it


  ### Set type of stack first!

   To set the type of stack you sould use this strange command:

   *#define stack_t **type***
    
   Example of setting int type:
   
   ```#define stack_t int```
   
   **Warning:** for stack_t you can use only standart types with no spaces notation!
   To use types with sapses declaraion use *typedef*.

  ### Iclude the library after you set the type of stack

   To include the library you sould use this command:

   ```#include "stack.h"```
   
   Now you have 2 lines:
   ```
      #define stack_t int
      #include "stack.h"
   ```
      
   That means you can use new type: **stack_int**
   In the same time you can use more tham only one type stack, but you cant change the log file and log will not work whith structs.
   
  ### Using stack
  
   After you include the library right you can declare varriable with type *stack_**type***. So do it:
   
   ```stack_int stk = {};```
   
   To start work with stack by stack functuons construct your stack *stk* by function *stack_ctor* with start capcity *capacity* (for example capcity is 14):
   
   ```stack_ctor (&stk, 14);```
   
   **Now you can use stack functions!**
   
   Examples of stack functions: 
   
   ```stack_dtor    (stack_ptr)``` - Distrcuts the stack.
   
   ```stack_ctor    (stack_ptr, capacity)``` - Constructs the stack.     
   
   ```stack_push    (stack_ptr, value)``` - Adds an item to the top of the stack.
   
   ```stack_peek    (stack_ptr)``` - Returns value of the top element of the stack.
   
   ```stack_pop       (stack_ptr)``` - Returns value of the top element of the stack and deletes it.
   
   ```stack_free_data (stack_ptr)``` - Clears the data of stack.
   
   ```stack_size      (stack_ptr)``` - Returnes current size of the stack.
   
   ```stack_capacity  (stack_ptr)``` - Returnes current capacity of the stack.
                    
  ## How to use protection and logs      
  All stacks including with protect and logs, you can turn off it if you dont need it. Use 
  
  ```#define NO_LOG```        - to disable logs;
  
  ```#deifne NO_PROTECTION``` - to disable protection (check at the beginning of each function that the stack is correct, for example size <= capacity or hash does not change since the last function call);
  
  Also you can set log file name, use
  
   ```#deifne LOG_FILE_NAME file_name``` - sets log file name as file_name;
   
   **LOG_FILE_NAME sets on first including of stack and cang ce changed**
  
   
    
