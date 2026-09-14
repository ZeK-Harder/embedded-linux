#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include "ringbuf.h"

int main(void)
{
    struct ringbuf rb;
    uint8_t buf[32];  // 临时缓存，存放读出的数据
    size_t ret;       // 通用返回值变量

    // ========== 第1步：初始化测试 ==========
    printf("=== 1. 初始化测试 ===\n");
    int init_ok = ringbuf_init(&rb, 8);
    if (init_ok == 1) {
        printf("初始化成功，缓冲区容量 cap = 8\n");
    } else {
        printf("初始化失败！\n");
        return 1;
    }
    printf("\n");

    // ========== 第2步：写入"ABC"测试 ==========
    printf("=== 2. 写入\"ABC\"测试 ===\n");
    ret = ringbuf_write(&rb, (const uint8_t *)"ABC", 3);
    printf("write 返回值: %zu\n", ret);
    printf("avail 可读字节: %zu\n", ringbuf_avail(&rb));
    printf("space 剩余空间: %zu\n", ringbuf_space(&rb));
    printf("\n");

    // ========== 第3步：读取3字节测试 ==========
    printf("=== 3. 读取3字节测试 ===\n");
    ret = ringbuf_read(&rb, buf, 3);
    printf("读出内容: ");
    fwrite(buf, 1, ret, stdout);  // 按字节打印内容，比%s更安全通用
    printf("\n");
    printf("read 返回值: %zu\n", ret);
    printf("读取后 avail: %zu\n", ringbuf_avail(&rb));
    printf("\n");

    // ========== 第4步：回绕核心测试 ==========
    printf("=== 4. 回绕核心测试 ===\n");
    // 当前状态：read=3, write=3, count=0（读写指针都在索引3的位置）

    // 写入6字节，让 write 指针从3走到1，跨过数组末尾（索引7），完成回绕
    ret = ringbuf_write(&rb, (const uint8_t *)"abcdef", 6);
    printf("写入6字节(abcdef)，返回: %zu,当前avail: %zu\n", ret, ringbuf_avail(&rb));

    // 读取5字节，让 read 指针从3走到0，跨过数组末尾，完成回绕
    ret = ringbuf_read(&rb, buf, 5);
    printf("读取5字节,内容: ");
    fwrite(buf, 1, ret, stdout);
    printf("，返回: %zu,剩余avail: %zu\n", ret, ringbuf_avail(&rb));

    // 再写入3字节，验证环形连续写入
    ret = ringbuf_write(&rb, (const uint8_t *)"xyz", 3);
    printf("再写入3字节(xyz)，返回: %zu,当前avail: %zu\n", ret, ringbuf_avail(&rb));

    // 整段全部读出，核对数据顺序是否错乱
    ret = ringbuf_read(&rb, buf, ringbuf_avail(&rb));
    printf("整段读出内容: ");
    fwrite(buf, 1, ret, stdout);
    printf("，总长度: %zu\n", ret);
    printf("\n");

    // ========== 第5步：部分写测试 ==========
    printf("=== 5. 部分写测试 ===\n");
    // 此时缓冲区已空，一次性写入10字节（超过容量8）
    ret = ringbuf_write(&rb, (const uint8_t *)"0123456789", 10);
    printf("空表写入10字节,返回: %zu\n", ret);

    // 缓冲区已满，再写1字节应返回0
    ret = ringbuf_write(&rb, (const uint8_t *)"X", 1);
    printf("满后再写1字节,返回: %zu\n", ret);
    printf("\n");

    // ========== 第6步：读空测试 ==========
    printf("=== 6. 读空测试 ===\n");
    // 先把缓冲区数据全部读完清空
    ret = ringbuf_read(&rb, buf, ringbuf_avail(&rb));
    printf("先清空缓冲区，读取长度: %zu\n", ret);

    // 空状态下再读取，验证返回0且程序不崩溃
    ret = ringbuf_read(&rb, buf, 5);
    printf("空表读取5字节,返回: %zu\n", ret);
    printf("\n");

    // 释放内存，收尾
    ringbuf_free(&rb);
    printf("全部测试完成，缓冲区已释放\n");

    return 0;
}