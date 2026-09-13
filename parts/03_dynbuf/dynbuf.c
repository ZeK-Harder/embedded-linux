#include "dynbuf.h"
#include <stdlib.h>
#include <string.h>

void dynbuf_init(struct dynbuf *b){
    b->data = NULL;
    b->len = 0;
    b->cap = 0;
}

int dynbuf_append(struct dynbuf *b, const char *src, size_t n){
    if(b->len + n > b->cap){
        size_t new_cap = b->cap == 0 ? 16 : b->cap * 2;
        while(new_cap < b->len + n){
            new_cap *= 2;
        }
        char *new_data = realloc(b->data, new_cap);
        if(!new_data){
            return 0; // allocation failed
        }
        b->data = new_data;
        b->cap = new_cap;
    }
    memcpy(b->data + b->len, src, n);
    b->len += n;
    return 1;
}

void dynbuf_free(struct dynbuf *b){
    free(b->data);
    b->data = NULL;
    b->len = 0;
    b->cap = 0;
}