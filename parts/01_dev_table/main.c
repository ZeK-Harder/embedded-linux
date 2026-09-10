#include "dev_table.h"
#include <stdio.h>
int main(void) {
    struct GatewayDevice devs[DEV_COUNT] = {
        {1, "温度传感器", 0, 1, 25},
        {2, "灯光开关", 1, 1, 1},
        {3, "窗帘执行器", 2, 0, 50}
    };

    struct GatewayDevice *dev_ptr = find_device(devs, DEV_COUNT, 2);
    if (dev_ptr != NULL) {
        printf("找到设备，修改前：\n");
        print_device(dev_ptr);

        set_device_offline(dev_ptr);
        printf("置离线后：\n");
        print_device(dev_ptr);
        printf("结论：传指针改的是原数组元素，数据真的变了\n\n");
    }

    dev_ptr = find_device(devs, DEV_COUNT, 99);
    if (dev_ptr == NULL) {
        printf("设备不存在\n");
    }

    return 0;
}
