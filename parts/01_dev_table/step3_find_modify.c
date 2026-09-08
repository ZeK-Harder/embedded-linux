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

void set_offline_by_value(struct GatewayDevice dev) {
    dev.online = 0;
    (void)dev;
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

int main(void) {
    struct GatewayDevice devs[DEV_COUNT] = {
        {1, "温度传感器", 0, 1, 25},
        {2, "灯光开关", 1, 1, 1},
        {3, "窗帘执行器", 2, 0, 50}
    };

    printf("===== 1. 传值方式修改（错误演示）=====\n");
    printf("修改前的灯光开关：\n");
    print_device(&devs[1]);

    set_offline_by_value(devs[1]);
    printf("调用传值函数后：\n");
    print_device(&devs[1]);
    printf("结论：传值改的是副本，原数组数据完全没变化\n\n");

    printf("===== 2. 指针方式修改（正确演示）=====\n");
    struct GatewayDevice *dev_ptr = find_device(devs, DEV_COUNT, 2);
    if (dev_ptr != NULL) {
        printf("找到设备，修改前：\n");
        print_device(dev_ptr);

        set_device_offline(dev_ptr);
        printf("置离线后：\n");
        print_device(dev_ptr);
        printf("结论：传指针改的是原数组元素，数据真的变了\n\n");
    }

    printf("===== 3. 查找不存在的设备 =====\n");
    dev_ptr = find_device(devs, DEV_COUNT, 99);
    if (dev_ptr == NULL) {
        printf("设备不存在\n");
    }

    return 0;
}
