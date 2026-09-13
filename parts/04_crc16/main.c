#include<stdio.h>
#include<stdint.h>
#include "crc16.h"

int main() {
    uint16_t r1 = crc16_modbus((const uint8_t *)"123456789", 9);
    printf("用例1 \"123456789\": 0x%04X\n", r1);
    const uint8_t frame[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x0A};
    uint16_t r2 = crc16_modbus(frame, sizeof(frame));
    printf("用例2 \"Frame\": 0x%04X\n", r2);
    uint16_t r3 = crc16_modbus(NULL, 0);
    printf("用例3 空数据: 0x%04X\n", r3);
    return 0;
}