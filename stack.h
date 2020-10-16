#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#ifndef ANOTHER_STACK

static FILE *LOG_FILE_PTR = NULL;

#ifndef LOG_FILE_NAME
#define LOG_FILE_NAME "LogStack.txt"
#endif

typedef long long canary_t;
static const canary_t CHIRP = 0xAEAEAAEAAEAE;

#define POISON  0

#endif

#define cat(stack, separator, type)  stack##separator##type
#define declare(stack_, type) cat (stack_, _, type)
#define stack declare (stack, stack_t)

struct stack
    {
    canary_t beginCanary;

    int stack_hash;
    int stack_data_hash;

    stack_t *data;
    int     size;
    int     capacity;

    canary_t endCanary;
    };

#ifndef ANOTHER_STACK

enum errors
    {
    NULL_STACK_PTR          = 60,
    NULL_STACK_DATA_PTR     = 61,
    CAPACITY_LESS_THAN_SIZE = 62,
    NEGATIVE_CAPACITY       = 63,
    NEGATIVE_SIZE           = 64,

    BEGINS_STACK_CANARY_IS_DEAD = 71,
    ENDS_STACK_CANARY_IS_DEAD   = 72,
    BEGINS_DATA_CANARY_IS_DEAD  = 73,
    ENDS_DATA_CANARY_IS_DEAD    = 74,
    STACK_HASH_ERROR            = 75,
    STACK_DATA_HASH_ERROR       = 76,

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

stack   *declare(new_stack, stack_t)
                             (int new_capasity = 0);
int      stack_push          (stack *stack_ptr, stack_t value);
stack_t  stack_peek          (stack *stack_ptr);
stack_t  stack_pop           (stack *stack_ptr);
int      stack_clear         (stack *stack_ptr);
size_t   stack_size          (stack *stack_ptr);
size_t   stack_capacity      (stack *stack_ptr);
stack   *dell_stack          (stack *stack_ptr);

stack_t *stack_free_data     (stack *stack_ptr);
int      stack_resize        (stack *stack_ptr, int new_capacity, int size_value);
void     add_poison          (stack *stack_ptr);
int      stack_construct     (stack *stack_ptr, int new_capacity);

int      get_stack_hash      (stack *stack_ptr);
int      get_stack_data_hash (stack *stack_ptr);
int      poison_error        (stack *stack_ptr);
int      stack_error         (stack *stack_ptr);
int      canary_error        (stack *stack_ptr);
int      hash_error          (stack *stack_ptr);
int      stack_verify        (stack *stack_ptr);

const char *str_error     (int error);

inline void print_line    (FILE * file);
bool        is_dead       (canary_t canary);


//-----------------------------------------------------------------------------


#ifndef NO_DBG
#define Verify(error)                                                                   \
    if ((error))                                                                        \
        {                                                                               \
        if (LOG_FILE_PTR == NULL)                                                       \
            LOG_FILE_PTR = fopen (LOG_FILE_NAME, "w+");                                 \
        const char *str_err = str_error (error);                                         \
        print_line (LOG_FILE_PTR);                                                       \
        fprintf (LOG_FILE_PTR, "Stack (ERROR %d: %s) [%p] \n\n"                         \
                          "Function: %s\n\n", error, str_err,                           \
                                              stack_ptr, __func__);                     \
                                                                                        \
        printf ("\n\n>>>FATAL ERROR!"                                                   \
                "\n\n>>>You can find log information in file: %s\n\n", LOG_FILE_NAME);  \
                                                                                        \
        fflush    (LOG_FILE_PTR);                                                       \
        print_line (LOG_FILE_PTR);                                                       \
                                                                                        \
        abort ();                                                                       \
        }
#else
#define Verify(error)  ;
#endif


//-----------------------------------------------------------------------------

#define SetHashes(stack_ptr)  stack_ptr->stack_hash      = get_stack_hash     (stack_ptr);   \
                              stack_ptr->stack_data_hash = get_stack_data_hash (stack_ptr);   

#define StartVerify  Verify (stack_error  (stack_ptr))\
                     Verify (canary_error (stack_ptr))\
                     Verify (hash_error   (stack_ptr))

#define EndVerify    Verify (stack_error  (stack_ptr))\
                     Verify (canary_error (stack_ptr))\
                     SetHashes           (stack_ptr)
   
//-----------------------------------------------------------------------------
#ifndef NO_LOG

#define IS_FLOAT_TYPE(type) (((type)(1 + 0.1)) ==  1.1)
#define CANARY(i)  *(canary_t *)((char *)stack_ptr->data + i*sizeof (stack_t) - ((i == 0) ? sizeof(canary_t) : sizeof (stack_t))) //i am so sorry...

void PrintElem (FILE *file, stack *stack_ptr, int i)
    {
    if (IS_FLOAT_TYPE(stack_t))
        if (i == 0 || i == stack_ptr->capacity + 1)                                          
            fprintf (LOG_FILE_PTR, "%lld (CANARY)\n", CANARY (i)); 
        else if (i > stack_ptr->size)                                                        
            fprintf (LOG_FILE_PTR, "%lg (POISON)\n",  (double)*(stack_ptr->data + i - 1));  
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

#define StackDump                                                                                \
    {                                                                                            \
    if (LOG_FILE_PTR == NULL)                                                                    \
            LOG_FILE_PTR = fopen (LOG_FILE_NAME, "w+");                                          \
    print_line (LOG_FILE_PTR);                                                                    \
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
    print_line (LOG_FILE_PTR);                                                                    \
    fflush    (LOG_FILE_PTR);                                                                    \
    }
#else
#define StackDump  ;
#endif


//-----------------------------------------------------------------------------


stack *declare(new_stack, stack_t) (int capasity)
    {
    stack *stack_ptr = (stack *)calloc (1, sizeof (*stack_ptr)); 

    int err_num = stack_construct (stack_ptr, capasity);
    
    if (err_num != 0) return NULL;
                                   
    EndVerify
    StackDump

    return stack_ptr;
    }

//-----------------------------------------------------------------------------

int stack_construct (stack *stack_ptr, int capacity)
    {
    if (capacity < 0) return NEGATIVE_CAPACITY;

    char *new_stack_ptr_data  = (char *)calloc (capacity * sizeof (*stack_ptr->data) + 
                                                       2 * sizeof (stack_ptr->beginCanary), sizeof (char));

    if (new_stack_ptr_data == NULL)
        return CONSTRUCTING_ERROR;
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

    return 0;
    }

//-----------------------------------------------------------------------------

int stack_push (stack *stack_ptr, stack_t value)
    {
    StartVerify
    StackDump

    if (value != value) return WRONG_PUSHUNG_VALUE;

    int error = 0;

    if (stack_ptr->size == stack_ptr->capacity)
        error = stack_resize (stack_ptr, stack_ptr->capacity * 2 + 1,
                                        sizeof (*stack_ptr->data));
    if ( !error )
        *(stack_ptr->data + stack_ptr->size++) = value;
                                  
    EndVerify
    StackDump

    return error;
    }

//-----------------------------------------------------------------------------

stack_t stack_pop (stack *stack_ptr)
    {
    StartVerify
    StackDump

    if (stack_ptr->size == 0)
        return 0;

    if (stack_ptr->capacity > 4 * stack_ptr->size)
        stack_resize (stack_ptr, stack_ptr->size * 2 + 1, sizeof(stack_t));

    int value = *(stack_ptr->data + --stack_ptr->size);

    *(stack_ptr->data + stack_ptr->size) = 0;
                                  
    EndVerify
    StackDump

    return value;
    }

//-----------------------------------------------------------------------------

stack_t stack_peek (stack *stack_ptr)
    {
    StartVerify
    StackDump

    if (stack_ptr->size == 0)
       return POISON;


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
        return REALLOCATION_ERROR;

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

    return 0;
    }

//-----------------------------------------------------------------------------

int stack_clear (stack *stack_ptr)
    {
    StartVerify
    StackDump

    for (int i = 0; i < stack_ptr->size; ++i)
        *(stack_ptr->data + i) = 0;

    stack_ptr->size = 0;
    stack_resize (stack_ptr, 0, sizeof (stack_t));

    EndVerify
    StackDump

    return 0;
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
    free (stack_ptr->data - 1);
    stack_ptr->data = NULL;

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

int Stackhash_error (stack *stack_ptr)
    {
    if (stack_ptr->stack_hash != get_stack_hash (stack_ptr))
        return STACK_HASH_ERROR;

    return 0;
    }

int StackDatahash_error (stack *stack_ptr)
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

    return 0;
    }

int stack_error (stack *stack_ptr)
    {
    catch (stack_ptr           == NULL, NULL_STACK_PTR         ); 
    catch (stack_ptr->data     == NULL, NULL_STACK_DATA_PTR    ); 
    catch (stack_ptr->capacity <  0,    NEGATIVE_CAPACITY      ); 
    catch (stack_ptr->size     <  0,    NEGATIVE_SIZE          ); 
    catch (stack_ptr->capacity <                                               
           stack_ptr->size,             CAPACITY_LESS_THAN_SIZE);
    catch (poison_error (stack_ptr)    , POISON_ERROR           );
    return 0;
    }

int canary_error (stack *stack_ptr)
    {
    catch (is_dead   (stack_ptr->beginCanary), BEGINS_STACK_CANARY_IS_DEAD); 
    catch (is_dead   (stack_ptr->endCanary),   ENDS_STACK_CANARY_IS_DEAD  );

    catch (is_dead (*((canary_t *)stack_ptr->data - 1)), BEGINS_DATA_CANARY_IS_DEAD ); 
    catch (is_dead (*(canary_t *)(stack_ptr->data +                                              
                       stack_ptr->capacity)),       BEGINS_DATA_CANARY_IS_DEAD );
    return 0;
    }

int hash_error (stack *stack_ptr)
    {
    catch (Stackhash_error     (stack_ptr), STACK_HASH_ERROR     );
    catch (StackDatahash_error (stack_ptr), STACK_DATA_HASH_ERROR);
    return 0;
    }

int poison_error (stack *stack_ptr)
    {
    for (int i = stack_ptr->size; i < stack_ptr->capacity; ++i)
        if (*(stack_ptr->data + i) != POISON)
            return POISON_ERROR;

    return 0;
    }



#ifndef ANOTHER_STACK

#define Is(err_num)  if (error == err_num) return #err_num;
                                                                   
inline const char *str_error (int error)                              
    {
    Is (NULL_STACK_PTR)
    Is (NULL_STACK_DATA_PTR)
    Is (NEGATIVE_CAPACITY)
    Is (NEGATIVE_SIZE)
    Is (CAPACITY_LESS_THAN_SIZE)
    Is (BEGINS_STACK_CANARY_IS_DEAD)
    Is (ENDS_STACK_CANARY_IS_DEAD)
    Is (BEGINS_DATA_CANARY_IS_DEAD)
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
    return NULL;
    }
#undef Is

bool is_dead (canary_t canary)
    {
    return (canary != CHIRP) ? true : false;
    }

inline void print_line (FILE * file)
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
#undef stack

#define ANOTHER_STACK
