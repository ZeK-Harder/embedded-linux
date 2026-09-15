#pragma once
#include <stdint.h>
#include <stddef.h>

struct ringbuf {
    uint8_t *data;
    size_t cap;
    size_t read;   /* 读位置 */
    size_t write;   /* 写位置 */
    size_t count;    /* 当前缓冲区中数据的字节数 */
};

int    ringbuf_init(struct ringbuf *rb, size_t cap);      /* 成功1，失败0 */
void   ringbuf_free(struct ringbuf *rb);
size_t ringbuf_write(struct ringbuf *rb, const uint8_t *src, size_t n);  /* 返回实际写入数 */
size_t ringbuf_read(struct ringbuf *rb, uint8_t *dst, size_t n);         /* 返回实际读出数 */
size_t ringbuf_avail(const struct ringbuf *rb);           /* 可读字节数 */
size_t ringbuf_space(const struct ringbuf *rb);           /* 可写空间 */