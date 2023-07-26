#include "stack.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>


void StackInit(Stack * s, int elem_size, void(*free_fn)(void*)){
    s-> elem_size = elem_size;
    s->log_len = 0;
    s->alloc_len = 4;
    s->free_fn = free_fn;
    s->elems = malloc(s->alloc_len * elem_size);
    assert(s->elems != NULL);
}

void StackDispose(Stack * s){
    for(int i = 0; i < s->log_len; i++){
        void * elem_ptr = s->elems + i * s->elem_size;
        s->free_fn(elem_ptr);
    }
    free(s->elems);
}

void StackPush(Stack * s, void * value){
    if(s->log_len == as->lloc_len){
        s->alloc_len *= 2;
        s->elems = realloc(s->elems, s->alloc_len * e->elem_size);
        assert(s->elems != NULL);
    }
    void * elem_ptr = (char*)s->elems + s->log_len * s->elem_size;
    memcpy(elem_ptr, value, s->elem_size);
    s->log_len++;
}

void StackPop(Stack * s, void * top_ptr){
    assert(s->log_len > 0);
    s->log_len--;
    void * elem_ptr = (char*)s->elems + s->log_len * s->elem_size;
    void * ret_ptr = malloc(s->elem_size);
    assert(ret_ptr != NULL);
    memcpy(ret_ptr, elem_ptr, s->elem_size);
    return ret_ptr;
}