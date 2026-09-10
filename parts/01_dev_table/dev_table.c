#include "dev_table.h"
#include <stdio.h>
void print_device(const struct GatewayDevice *dev) {
    printf("设备ID: %d\n", dev->id);
    printf("设备名称: %s\n", dev->name);
    printf("设备类型: %d (0=传感器 1=开关 2=执行器)\n", dev->type);
    printf("在线状态: %d (0=离线 1=在线)\n", dev->online);
    printf("本轮上报值: %d\n", dev->report_value);
}

struct GatewayDevice *find_device(struct GatewayDevice *devs, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (devs[i].id == id) {
            return &devs[i];
        }
    }
    return NULL;
}

void set_device_offline(struct GatewayDevice *dev) {
    dev->online = 0;
}