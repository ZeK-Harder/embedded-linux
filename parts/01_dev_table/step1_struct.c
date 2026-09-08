#include <stdio.h>

struct GatewayDevice {
    int id;
    char name[32];
    int type;
    int online;
    int report_value;
};

int main() {
    struct GatewayDevice dev1 = {1, "温度传感器", 0, 1, 25};
    struct GatewayDevice dev2 = {2, "灯光开关", 1, 1, 1};
    struct GatewayDevice dev3 = {3, "窗帘执行器", 2, 0, 50};

    printf("=== 设备1 ===\n");
    printf("设备ID: %d\n", dev1.id);
    printf("设备名称: %s\n", dev1.name);
    printf("设备类型: %d (0=传感器 1=开关 2=执行器)\n", dev1.type);
    printf("在线状态: %d (0=离线 1=在线)\n", dev1.online);
    printf("本轮上报值: %d\n\n", dev1.report_value);

    printf("=== 设备2 ===\n");
    printf("设备ID: %d\n", dev2.id);
    printf("设备名称: %s\n", dev2.name);
    printf("设备类型: %d (0=传感器 1=开关 2=执行器)\n", dev2.type);
    printf("在线状态: %d (0=离线 1=在线)\n", dev2.online);
    printf("本轮上报值: %d\n\n", dev2.report_value);

    printf("=== 设备3 ===\n");
    printf("设备ID: %d\n", dev3.id);
    printf("设备名称: %s\n", dev3.name);
    printf("设备类型: %d (0=传感器 1=开关 2=执行器)\n", dev3.type);
    printf("在线状态: %d (0=离线 1=在线)\n", dev3.online);
    printf("本轮上报值: %d\n", dev3.report_value);

    return 0;
}