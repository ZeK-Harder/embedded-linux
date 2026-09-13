#pragma once
#include <stddef.h>
struct dynbuf {
    char *data;
    size_t len;
    size_t cap;
};

void dynbuf_init(struct dynbuf *b);
int dynbuf_append(struct dynbuf *b, const char *src, size_t n);
void dynbuf_free(struct dynbuf *b);