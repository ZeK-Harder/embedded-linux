#include "ringbuf.h"
#include <stdlib.h>

int    ringbuf_init(struct ringbuf *rb, size_t cap){
    rb->data = NULL;
    rb->cap = cap;
    rb->read = 0;
    rb->write = 0;
    rb->count = 0;
    rb->data=(uint8_t *)malloc(cap);
    if(!rb->data){
        return 0;
    }
    return 1;
}

void   ringbuf_free(struct ringbuf *rb){
    free (rb->data);
    rb->data = NULL;
    rb->cap = 0;
    rb->read = 0;
    rb->write = 0;
    rb->count = 0;
}

size_t ringbuf_write(struct ringbuf *rb, const uint8_t *src, size_t n){
    size_t space = ringbuf_space(rb);
    if(n > space){
        n = space; //限制写入字节数
    }
    for(size_t i=0;i < n ;i++){
        rb->data [rb->write] = src[i];
        rb->write = (rb->write+1) % rb->cap;
    }
    rb->count += n;
    return n;
}

size_t ringbuf_read(struct ringbuf *rb, uint8_t *dst, size_t n){
    size_t avail = ringbuf_avail(rb);
    if (n > avail) {
        n = avail;  /* 限制读取字节数 */
    }
    for(size_t i =0;i < n;i++){
    dst[i] = rb->data[rb->read];
    rb->read = (rb->read+1) % rb->cap;
    }
    rb->count -= n;
    return n;
}    

size_t ringbuf_avail(const struct ringbuf *rb){
    return rb->count;
}

size_t ringbuf_space(const struct ringbuf *rb){
    return rb->cap - rb->count;
}