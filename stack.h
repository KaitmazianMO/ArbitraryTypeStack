

//{============================================================================
//!  @file
//!
//!  Arbitary type stack instruction.
//!
//!  @note To set the type of the stack use stack_t,
//!        dont forget to undef it before including 
//!        another type stack.
//!
//!  @note To set pointer type of the stack use typedef.
//!
//!  @warning stack_t can be only one word.
//! 
//!  Example of right including two stacks:
//!  @code
//!     #define stack_t double
//!     #include "stack.h"    /* now you can use stack_double type */
//!     #undef stack_t
//!
//!     typedef char * char_ptr
//!     #define stack_t char_ptr
//!     #include "stack.h"    /* now you can use stack_char_ptr type */
//!     #undef stack_t
//!  @endcode
//!
//!
//!  @note To disable all logs use NO_LOG.
//!
//!  Example of right deasabling logging:
//!  @code
//!     #define NO_LOG
//!     #define stack_t double
//!     #include "stack.h"
//!     #undef stack_t
//!  @endcode
//!
//!  @note To set another name of log file use LOG_FILE_NAME.
//!
//!  Example of right setting the log file:
//!  @code
//!     #define LOG_FILE_NAME "new_log_file.txt"
//!     #define stack_t int
//!     #include "stack.h"
//!     #undef stack_t
//!  @endcode
//!
//! @warning All stacks dump in the the same file LOG_FILE_NAME.
//!
//!  @note To disable all verifies use NO_DBG.
//!
//!  @code
//!     #define NO_DBG
//!     #define stack_t char
//!     #include "stack.h"
//!     #undef stack_t
//!  @endcode
//!
//!  @note Protective elements of stack continue to work,
//!        so you can catсh the errors by functions from main.
//!
//}============================================================================


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef LOG_FILE_NAME
    #define LOG_FILE_NAME  "LogStack.txt";    //!<  Name of file for logs.   
#endif

#ifndef ANOTHER_STACK    

    static FILE *LOG_FILE_PTR = NULL;    //!<  Pointer to log file.

    typedef long long canary_t;     
    static const canary_t CHIRP = 0xAEAEAAEAAEAE;    //!<  Right canaries value.   

    #define POISON  0    //!<  Value for unused data spaces.

    int stk_err = 0;    //!<  Number of last stack error, only one for every stack.

#endif

#define cat(struct_, separator, type)  struct_##separator##type   //!< Concatenate all params.
#define declare(struct_, type) cat (struct_, _, type)             //!< Concatenate all params with separator '_'.
#define stack declare (stack, stack_t)                            //!< Dcalration of struct stack.

//!  Struct of stack with previously defined type.
struct stack
    {
    canary_t beginCanary;    //!<  Protected canary, helps to catch random stack changes.

    int stack_hash;          //!<  Stacks hash, helps to cath random stack changes.
    int stack_data_hash;     //!<  Stacks data hash, helps to cath random stacks data changes.

    stack_t *data;           //!<  Pointer to stacks data.
    int      size;           //!<  Current size of stack.
    int      capacity;       //!<  Current capacity of stack.

    canary_t endCanary;      //!<  Protected canary, helps to catch random stack changes.
    };

#ifndef ANOTHER_STACK

//{----------------------------------------------------------------------------
//!  Errors, that can be detected when you working with the stack.
//!  Errors with num from 0 to 47 can happend by stack fucntions
//!  errors and stk_err takes their value.
//!  Other errors  danote some unusual situations, like random stack changes.
//}----------------------------------------------------------------------------

    enum errors
        {
        NULL_STACK_PTR          = 60,
        NULL_STACK_DATA_PTR     = 61,
        CAPACITY_LESS_THAN_SIZE = 62,
        NEGATIVE_CAPACITY       = 63,
        NEGATIVE_SIZE           = 64,

        BEGINS_STACK_CANARY_ERROR = 71,
        ENDS_STACK_CANARY_ERROR   = 72,
        BEGINS_DATA_CANARY_ERROR  = 73,
        ENDS_DATA_CANARY_ERROR    = 74,
        STACK_HASH_ERROR          = 75,
        STACK_DATA_HASH_ERROR     = 76,

        NO_ERROR            = 0,
        REALLOCATION_ERROR  = 41,
        CONSTRUCTING_ERROR  = 42,
        POPPING_EMPTY_STACK = 43,
        PEEKING_EMPTY_STACK = 44,
        WRONG_PUSHUNG_VALUE = 45,
        NEGATIVE_VALUE_SIZE = 46,
        POISON_ERROR        = 47,
        };

#endif

//-----------------------------------------------------------------------------

    
//{----------------------------------------------------------------------------
//!  Constructor for stack with type stack_t.
//!
//!  @param [in] new_capacity - capacity of the created stack
//!                             default value is 0;
//!  
//!  @note In case of an error, replaces stk_err with the error number.
//!
//!  @return Pointer to new stack of NULL in error case.
//}----------------------------------------------------------------------------
stack   *declare (new_stack, stack_t)
                             (int new_capasity = 0);

//{----------------------------------------------------------------------------
//!  Add an item to the top of the stack.
//!
//!  @param [in] stack_ptr - a pointer to the stack;
//!  @param [in] value     - pushing value;
//!
//!  @note In case of an error, replaces stk_err with the error number.
//!
//!  @return In case of an error - number of error, otherwise NO_ERROR.
//}----------------------------------------------------------------------------
int      stack_push          (stack *stack_ptr, stack_t value);

//{----------------------------------------------------------------------------
//!  Returns value of the top element of the stack.
//!
//!  @param [in] stack_ptr - a pointer to the stack; 
//!
//!  @note In case of an error, replaces stk_err with the error number.
//!
//!  @return Value of the top element of the stack or POISON in case of an error.
//}----------------------------------------------------------------------------
stack_t  stack_peek          (stack *stack_ptr);
                                                                                  
//{----------------------------------------------------------------------------
//!  Returns value of the top element of the stack and deletes it.
//!
//!  @param [in] stack_ptr - a pointer to the stack; 
//!
//!  @note In case of an error, replaces stk_err with the error number.
//!
//!  @return Value of the top element of the stack or POISON in case of an error.
//}----------------------------------------------------------------------------
stack_t  stack_pop           (stack *stack_ptr);

//{----------------------------------------------------------------------------
//!  Clears the data of stack.
//!
//!  @param [in] stack_ptr - a pointer to the stack; 
//}----------------------------------------------------------------------------
int      stack_clear         (stack *stack_ptr);

//{----------------------------------------------------------------------------
//!  Returnes current size of the stack.
//!                                               
//!  @param [in] stack_ptr - a pointer to the stack;
//}----------------------------------------------------------------------------
size_t   stack_size          (stack *stack_ptr);
                                                                                    
//{----------------------------------------------------------------------------
//!  Returnes current size of the stack.
//!                                               
//!  @param [in] stack_ptr - a pointer to the stack;
//}----------------------------------------------------------------------------
size_t   stack_capacity      (stack *stack_ptr);

//{----------------------------------------------------------------------------
//!  Delletes all spaces and the data of the stack. 
//!                                               
//!  @param [in] stack_ptr - a pointer to the stack;
//!
//!  @return NULL.
//}----------------------------------------------------------------------------
stack   *dell_stack          (stack *stack_ptr);
                                                                                  
//{----------------------------------------------------------------------------
//!  Frees the data of the stack. 
//!                                               
//!  @param [in] stack_ptr - a pointer to the stack;
//!
//!  @return NULL.
//}----------------------------------------------------------------------------
stack_t *stack_free_data     (stack *stack_ptr);

//{----------------------------------------------------------------------------
//}----------------------------------------------------------------------------
int      stack_resize        (stack *stack_ptr, int new_capacity, int size_value);

//{----------------------------------------------------------------------------
//}----------------------------------------------------------------------------
void     add_poison          (stack *stack_ptr);

//{----------------------------------------------------------------------------
//}----------------------------------------------------------------------------
int      stack_construct     (stack *stack_ptr, int new_capacity);


//{----------------------------------------------------------------------------
//}----------------------------------------------------------------------------
int      get_stack_hash      (stack *stack_ptr);

//{----------------------------------------------------------------------------
//}----------------------------------------------------------------------------
int      get_stack_data_hash (stack *stack_ptr);

//{----------------------------------------------------------------------------
//}----------------------------------------------------------------------------
int      poison_error        (stack *stack_ptr);

//{----------------------------------------------------------------------------
//}----------------------------------------------------------------------------
int      stack_error         (stack *stack_ptr);

//{----------------------------------------------------------------------------
//}----------------------------------------------------------------------------
int      canary_error        (stack *stack_ptr);

//{----------------------------------------------------------------------------
//}----------------------------------------------------------------------------
int      hash_error          (stack *stack_ptr);

//{----------------------------------------------------------------------------
//}----------------------------------------------------------------------------
int      stack_verify        (stack *stack_ptr);


//{----------------------------------------------------------------------------
//!  Returns a string with the input number of the error.
//!
//!  @param [in] error - number of error;
//!
//!  @return A pointer to a string wiht number of the error.
//}----------------------------------------------------------------------------
const char *str_error            (int error);


//{----------------------------------------------------------------------------
//!  Prints a line in the file.
//!
//!  @param [in] file - a pointer to a file to print;
//}----------------------------------------------------------------------------
static inline void print_line    (FILE * file);

//{----------------------------------------------------------------------------
//!  Verifies input canary.
//!
//!  @param [in] canary - a canary for verifying;
//!
//!  @return true if canary is OK, otherwise false.
//}----------------------------------------------------------------------------
static bool        is_dead       (canary_t canary);

//-----------------------------------------------------------------------------

#ifndef NO_DBG

//{----------------------------------------------------------------------------
//!  Handles errors not in NO_DBG mode.
//!
//!  @param [in] error - returned value from function,
//!                      that checks stack errors;
//!
//!  In case of non-zero error, aborts the program
//!  and dumps some info about error at log file (LOG_FILE_NAME). 
//}----------------------------------------------------------------------------

    #define Verify(error)                                                                   \
        if ((error))                                                                        \
            {                                                                               \
            if (LOG_FILE_PTR == NULL)                                                       \
                LOG_FILE_PTR = fopen (LOG_FILE_NAME, "w+");                                 \
            const char *str_err = str_error (error);                                        \
            print_line (LOG_FILE_PTR);                                                      \
            fprintf (LOG_FILE_PTR, "Stack (ERROR %d: %s) [%p] \n\n"                         \
                              "Function: %s\n\n", error, str_err,                           \
                                                  stack_ptr, __func__);                     \
                                                                                            \
            printf ("\n\n>>>FATAL ERROR!"                                                   \
                    "\n\n>>>You can find log information in file: %s\n\n", LOG_FILE_NAME);  \
                                                                                            \
            fflush    (LOG_FILE_PTR);                                                       \
            print_line (LOG_FILE_PTR);                                                      \
                                                                                            \
            abort ();                                                                       \
            }

#else
    #define Verify(error)  ;

#endif


//-----------------------------------------------------------------------------

//!  Sets stack hashes. 
#define SetHashes(stack_ptr)  stack_ptr->stack_hash      = get_stack_hash      (stack_ptr);   \
                              stack_ptr->stack_data_hash = get_stack_data_hash (stack_ptr);   

//!  Verifies stack at start. 
#define StartVerify  Verify (stack_error  (stack_ptr))\
                     Verify (canary_error (stack_ptr))\
                     Verify (hash_error   (stack_ptr))

//!  Verifies stack at end and sets new hashes.
#define EndVerify    Verify (stack_error  (stack_ptr))\
                     Verify (canary_error (stack_ptr))\
                     SetHashes            (stack_ptr)
   
//-----------------------------------------------------------------------------

#ifndef NO_LOG

    #define IS_FLOAT_TYPE(type) (((type)(1 + 0.1)) ==  1.1)
    #define CANARY(i)  *(canary_t *)((char *)stack_ptr->data + i*sizeof (stack_t) - ((i == 0) ? sizeof(canary_t) : sizeof (stack_t))) //i am so sorry...

    //!  Prints arbitrary type element.
    void PrintElem (FILE *file, stack *stack_ptr, int i)
        {
        if (IS_FLOAT_TYPE(stack_t))
            if (i == 0 || i == stack_ptr->capacity + 1)                                          
                fprintf (LOG_FILE_PTR, "%lld (CANARY)\n", CANARY (i)); 
            else if (i > stack_ptr->size)                                                        
                fprintf (LOG_FILE_PTR, "%lg  (POISON)\n", (double)*(stack_ptr->data + i - 1));  
            else                                                                                 
                fprintf (LOG_FILE_PTR, "%lg\n",           (double)*(stack_ptr->data + i - 1));

        else
            if (i == 0 || i == stack_ptr->capacity + 1)                                          
                fprintf (LOG_FILE_PTR, "%lld (CANARY)\n", CANARY (i)); 
            else if (i > stack_ptr->size)                                                        
                fprintf (LOG_FILE_PTR, "%lld (POISON)\n", (long long)*(stack_ptr->data + i - 1));  
            else                                                                                 
                fprintf (LOG_FILE_PTR, "%lld\n",          (long long)*(stack_ptr->data + i - 1));

        }
    #undef CANARY
    #undef IS_FLOAT_TYPE

    //! Dumps stack info not in NO_LOG mode.
    #define StackDump                                                                                \
        {                                                                                            \
        if (LOG_FILE_PTR == NULL)                                                                    \
                LOG_FILE_PTR = fopen (LOG_FILE_NAME, "w+");                                          \
        print_line (LOG_FILE_PTR);                                                                   \
                                                                                                     \
        fprintf (LOG_FILE_PTR, "Stack (OK) [%p] \n\n"                                                \
                          "Function: %s\n\n" , stack_ptr, __FUNCSIG__) ;                             \
                                                                                                     \
        fprintf (LOG_FILE_PTR,                                                                       \
                          "{\n"                                                                      \
                          "\tsize     = %d\n"                                                        \
                          "\tcapasity = %d\n"                                                        \
                          "\tdata[%p]\n\t{\n",                                                       \
                           stack_ptr->size,                                                          \
                           stack_ptr->capacity,                                                      \
                           stack_ptr->data);                                                         \
                                                                                                     \
        for (int i = 0; i <= stack_ptr->capacity + 1; ++i)                                           \
            {                                                                                        \
            if (i <= stack_ptr->size && i != 0) fprintf (LOG_FILE_PTR, "\t   *");                    \
            else                                fprintf (LOG_FILE_PTR, "\t\t");                      \
                                                                                                     \
            fprintf (LOG_FILE_PTR, "[%d] = ", i - 1);                                                \
                                                                                                     \
            PrintElem (LOG_FILE_PTR, stack_ptr, i);                                                  \
            }                                                                                        \
        fprintf (LOG_FILE_PTR, "\t}\n}\n");                                                          \
                                                                                                     \
        print_line (LOG_FILE_PTR);                                                                   \
        fflush    (LOG_FILE_PTR);                                                                    \
        }

#else
    #define StackDump  ;

#endif

//-----------------------------------------------------------------------------

stack *declare(new_stack, stack_t) (int capasity)
    {
    stack *stack_ptr = (stack *)calloc (1, sizeof (*stack_ptr)); 

    stk_err = stack_construct (stack_ptr, capasity);
    
    if (stk_err != 0) return NULL;
                                   
    EndVerify
    StackDump

    return stack_ptr;
    }

//-----------------------------------------------------------------------------

int stack_construct (stack *stack_ptr, int capacity)
    {
    if (capacity < 0) return stk_err = NEGATIVE_CAPACITY;

    char *new_stack_ptr_data  = (char *)calloc (capacity * sizeof (*stack_ptr->data) + 
                                                       2 * sizeof (stack_ptr->beginCanary), sizeof (char));

    if (new_stack_ptr_data == NULL)
        return stk_err = CONSTRUCTING_ERROR;
    else
        stack_ptr->data = (stack_t *)(new_stack_ptr_data + sizeof (stack_ptr->beginCanary));

    stack_ptr->beginCanary                      = CHIRP;
    *((canary_t *)stack_ptr->data - 1)          = CHIRP; 
    *((canary_t *)(stack_ptr->data + capacity)) = CHIRP; 
    stack_ptr->endCanary                        = CHIRP;

    stack_ptr->capacity = capacity;
    stack_ptr->size     = 0;

    add_poison (stack_ptr);
    SetHashes (stack_ptr)

    return NO_ERROR;
    }

//-----------------------------------------------------------------------------

int stack_push (stack *stack_ptr, stack_t value)
    {
    StartVerify
    StackDump

    if (value != value) return stk_err = WRONG_PUSHUNG_VALUE;

    if (stack_ptr->size == stack_ptr->capacity)
        stk_err = stack_resize (stack_ptr, stack_ptr->capacity * 2 + 1,
                                           sizeof (*stack_ptr->data));
    if ( !stk_err )
        *(stack_ptr->data + stack_ptr->size++) = value;
                                  
    EndVerify
    StackDump

    return NO_ERROR;
    }

//-----------------------------------------------------------------------------

stack_t stack_pop (stack *stack_ptr)
    {
    StartVerify
    StackDump

    if (stack_ptr->size == 0) { stk_err = POPPING_EMPTY_STACK; return POISON; }

    if (stack_ptr->capacity > 4 * stack_ptr->size)
        stk_err = stack_resize (stack_ptr, stack_ptr->size * 2 + 1, sizeof(stack_t));

    if (stk_err) return POISON;

    stack_t value = *(stack_ptr->data + --stack_ptr->size);

    *(stack_ptr->data + stack_ptr->size) = POISON;
                                  
    EndVerify
    StackDump

    return value;
    }

//-----------------------------------------------------------------------------

stack_t stack_peek (stack *stack_ptr)
    {
    StartVerify
    StackDump

    if (stack_ptr->size == 0) {stk_err = PEEKING_EMPTY_STACK; return POISON; }


    EndVerify
    StackDump

    return *(stack_ptr->data + stack_ptr->size - 1);
    }

//-----------------------------------------------------------------------------

int stack_resize (stack *stack_ptr, int new_capacity, int size_value)
    {
    StartVerify
    StackDump

    if (new_capacity < 0) 
        return NEGATIVE_CAPACITY;

    if (size_value < 0)
        return NEGATIVE_VALUE_SIZE;

    char *new_data = (char *)realloc ((char *)stack_ptr->data -  sizeof (stack_ptr->endCanary),
                                     new_capacity*size_value + 2*sizeof (stack_ptr->endCanary));

    if (new_data == NULL)
        return stk_err = REALLOCATION_ERROR;

    else
        {
        stack_ptr->data     = (stack_t *)(new_data + sizeof (stack_ptr->endCanary));
        stack_ptr->capacity = new_capacity;

        stack_ptr->beginCanary = CHIRP;
        stack_ptr->endCanary   = CHIRP;

        *((canary_t *)stack_ptr->data - 1)              = CHIRP; 
        *((canary_t *)(stack_ptr->data + new_capacity)) = CHIRP;
        add_poison (stack_ptr);
        }

    EndVerify
    StackDump

    return NO_ERROR;
    }

//-----------------------------------------------------------------------------

int stack_clear (stack *stack_ptr)
    {
    StartVerify
    StackDump

    for (int i = 0; i < stack_ptr->size; ++i)
        *(stack_ptr->data + i) = 0;

    stack_ptr->size = 0;

    EndVerify
    StackDump

    return NO_ERROR;
    }

//-----------------------------------------------------------------------------

stack *dell_stack (stack *stack_ptr)
    {
    StartVerify
    
    stack_ptr->data = stack_free_data (stack_ptr);

    free (stack_ptr);

    return NULL;
    }
                      

//-----------------------------------------------------------------------------

stack_t *stack_free_data (stack *stack_ptr)
    {
    free ((canary_t *)stack_ptr->data - 1);

    return NULL;
    }

//-----------------------------------------------------------------------------

void add_poison (stack *stack_ptr)
    {
    for (int i = stack_ptr->size; i < stack_ptr->capacity; ++i)
        *(stack_ptr->data + i) = POISON;
    }

//-----------------------------------------------------------------------------

size_t stack_size (stack *stack_ptr)
    {
    StartVerify

    return stack_ptr->size;
    }

//-----------------------------------------------------------------------------

size_t stack_capacity (stack *stack_ptr)
    {
    StartVerify

    return stack_ptr->capacity;
    }

//-----------------------------------------------------------------------------

int get_stack_hash (stack *stack_ptr)
    {
    int old_stack_hash      = stack_ptr->stack_hash;
    int old_stack_data_hash = stack_ptr->stack_data_hash;

    stack_ptr->stack_hash      = 0;
    stack_ptr->stack_data_hash = 0;
    int *hash_ptr = (int *)stack_ptr;

    int new_stack_hash = 0;
    
    int p = 1, p_pow = 2147483647;
    for (size_t i = 0; i < sizeof (*stack_ptr) / sizeof (int); ++i, p *= p_pow)
        new_stack_hash += *(hash_ptr + i) * p;

    stack_ptr->stack_data_hash = old_stack_data_hash;
    stack_ptr->stack_hash      = old_stack_hash;

    return new_stack_hash + (int)stack_ptr * p;
    }

//-----------------------------------------------------------------------------

int get_stack_data_hash (stack *stack_ptr)
    {
    int new_stack_data_hash = 0;
    stack_t *hash_ptr = stack_ptr->data;

    int p = 1, p_pow = 2147483647;
    for (int i = 0; i < stack_ptr->capacity; ++i, p *= p_pow)
        new_stack_data_hash += (int)*(hash_ptr + i) * p;

    return new_stack_data_hash + (int)stack_ptr * p;
    }

//-----------------------------------------------------------------------------

int stack_data_error (stack *stack_ptr)
    {
    if (stack_ptr->stack_hash != get_stack_hash (stack_ptr))
        return STACK_HASH_ERROR;

    return 0;
    }

int stack_data_hash_error (stack *stack_ptr)
    {
    if (stack_ptr->stack_data_hash != get_stack_data_hash (stack_ptr))
        return STACK_DATA_HASH_ERROR;

    return 0;
    }

//-----------------------------------------------------------------------------

#define catch(condition, err_num) if (condition) return err_num;


int stack_verify (stack *stack_ptr)
    {  
    int err_num = 0;

    if (err_num = stack_error  (stack_ptr)) return err_num;

    if (err_num = canary_error (stack_ptr)) return err_num;
                                                           
    if (err_num = hash_error   (stack_ptr)) return err_num;

    return NO_ERROR;
    }

int stack_error (stack *stack_ptr)
    {
    catch (stack_ptr           == NULL,  NULL_STACK_PTR         ); 
    catch (stack_ptr->data     == NULL,  NULL_STACK_DATA_PTR    ); 
    catch (stack_ptr->capacity <  0,     NEGATIVE_CAPACITY      ); 
    catch (stack_ptr->size     <  0,     NEGATIVE_SIZE          ); 
    catch (stack_ptr->capacity <                                               
           stack_ptr->size,              CAPACITY_LESS_THAN_SIZE);
    catch (poison_error (stack_ptr)    , POISON_ERROR           );
    return NO_ERROR;
    }

int canary_error (stack *stack_ptr)
    {
    catch (is_dead   (stack_ptr->beginCanary), BEGINS_STACK_CANARY_ERROR);               
    catch (is_dead   (stack_ptr->endCanary),   ENDS_STACK_CANARY_ERROR  );

    catch (is_dead (*((canary_t *)stack_ptr->data - 1)), BEGINS_DATA_CANARY_ERROR); 
    catch (is_dead (*(canary_t *)(stack_ptr->data +                                              
                       stack_ptr->capacity)),            BEGINS_DATA_CANARY_ERROR);
    return NO_ERROR;
    }

int hash_error (stack *stack_ptr)
    {
    catch (stack_data_error      (stack_ptr), STACK_HASH_ERROR     );
    catch (stack_data_hash_error (stack_ptr), STACK_DATA_HASH_ERROR);
    return NO_ERROR;
    }

int poison_error (stack *stack_ptr)
    {
    for (int i = stack_ptr->size; i < stack_ptr->capacity; ++i)
        if (*(stack_ptr->data + i) != POISON)
            return stk_err = POISON_ERROR;

    return NO_ERROR;
    }



#ifndef ANOTHER_STACK
    
    #define Is(err_num)  if(error == err_num) return #err_num;
    #define or(err_num)  return #err_num;
                                                                   
    inline const char *str_error (int error)                              
        {
        Is (NULL_STACK_PTR)
        Is (NULL_STACK_DATA_PTR)
        Is (NEGATIVE_CAPACITY)
        Is (NEGATIVE_SIZE)
        Is (CAPACITY_LESS_THAN_SIZE)
        Is (BEGINS_STACK_CANARY_ERROR)
        Is (ENDS_STACK_CANARY_ERROR)
        Is (BEGINS_DATA_CANARY_ERROR)
        Is (STACK_HASH_ERROR)
        Is (STACK_DATA_HASH_ERROR)
        Is (POISON_ERROR)
        Is (REALLOCATION_ERROR)
        Is (CONSTRUCTING_ERROR)
        Is (POPPING_EMPTY_STACK)
        Is (PEEKING_EMPTY_STACK)
        Is (WRONG_PUSHUNG_VALUE)
        Is (NEGATIVE_VALUE_SIZE)
        Is (POISON_ERROR)       
        Is (NO_ERROR)
        or (UNCNOWN_ERROR)
        }
    #undef or
    #undef Is

    static bool is_dead (canary_t canary)
        {
        return (canary != CHIRP) ? true : false;
        }

    static inline void print_line(FILE * file)
        {
        if (file == NULL) return;
        fputs ("\n", file);

        for (int i = 0; i < 100; ++i)
            fputs ("-", file);

        fputs ("\n", file);
        }

#endif
    
#undef catch
#undef cat
#undef declare
#undef cat
#undef declare
#undef stack
#undef LOG_FILE_NAME

#define ANOTHER_STACK    //!< Used by other stack types to avoid double-inclusion errors.
