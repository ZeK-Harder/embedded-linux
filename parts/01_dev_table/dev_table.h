#pragma once
#define DEV_COUNT 3
struct GatewayDevice {
    int id;
    char name[32];
    int type;
    int online;
    int report_value;
};

void print_device(const struct GatewayDevice *dev);
struct GatewayDevice *find_device(struct GatewayDevice *devs, int count, int id);
void set_device_offline(struct GatewayDevice *dev);