#include "dynbuf.h"
#include <stdio.h>

int main() {
    struct dynbuf buf;
    dynbuf_init(&buf);

    dynbuf_append(&buf, "Hello", 5);
    printf("len: %zu\n", (size_t)buf.len);
    dynbuf_append(&buf, " World", 6);

    printf("Result: %.*s\n", (int)buf.len, buf.data);
    
    for(int i = 0; i < 100; i++){
        dynbuf_append(&buf, "A", 1);
    }
    printf("len: %zu\n", (size_t)buf.len);
    printf("Result: %.*s\n", (int)buf.len, buf.data);

    dynbuf_free(&buf);
    return 0;
}