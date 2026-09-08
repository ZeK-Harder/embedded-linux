#include <stdio.h>

#define DEV_COUNT 3

struct GatewayDevice {
    int id;
    char name[32];
    int type;
    int online;
    int report_value;
};

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

void set_report_value(struct GatewayDevice *dev, int value) {
    dev->report_value = value;
}

int main(void) {
    struct GatewayDevice devs[DEV_COUNT] = {
        {1, "温度传感器", 0, 1, 25},
        {2, "灯光开关", 1, 1, 1},
        {3, "窗帘执行器", 2, 0, 50}
    };

    printf("===== 查找ID=2的设备（修改前）=====\n");
    struct GatewayDevice *dev_ptr = find_device(devs, DEV_COUNT, 2);
    if (dev_ptr != NULL) {
        print_device(dev_ptr);
    }

    printf("\n===== 修改上报值为0后 =====\n");
    set_report_value(dev_ptr, 0);
    if (dev_ptr != NULL) {
        print_device(dev_ptr);
    }

    printf("\n===== 查找ID=99的设备 =====\n");
    dev_ptr = find_device(devs, DEV_COUNT, 99);
    if (dev_ptr == NULL) {
        printf("设备不存在\n");
    }

    return 0;
}
