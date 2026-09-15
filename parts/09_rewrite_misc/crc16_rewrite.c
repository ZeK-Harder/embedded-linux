#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

uint16_t crc16_modbus(const uint8_t *data, size_t len){
    uint16_t crc = 0xFFFF;
    for(size_t i = 0 ; i < len ; i ++){
        crc ^= data[i];
        for(uint8_t j = 0 ; j < 8 ; j ++){
            if(crc & 0x0001){
                crc >>= 1;
                crc ^= 0xA001;
            }
            else{
                crc >>= 1;
            }
        }
    }
    return crc;
}

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