#include <stdio.h>

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

int main(void) {
    struct GatewayDevice devs[3] = {
        {1, "温度传感器", 0, 1, 25},
        {2, "灯光开关", 1, 1, 1},
        {3, "窗帘执行器", 2, 0, 50}
    };

    for (int i = 0; i < 3; i++) {
        printf("=== 设备%d ===\n", i + 1);
        print_device(&devs[i]);
        if (i < 2) {
            printf("\n");
        }
    }

    return 0;
}
