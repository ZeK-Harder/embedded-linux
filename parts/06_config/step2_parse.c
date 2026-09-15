#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *fp = fopen("config_test.conf", "r");
    if (fp == NULL) {
        printf("failed to open config_test.conf\n");
        return 1;
    }

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        char *newline = strchr(line, '\n');
        if (newline != NULL) {
            *newline = '\0';
        }

        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }

        char *eq = strchr(line, '=');
        if (eq == NULL) {
            printf("非法行: %s\n", line);
            continue;
        }

        *eq = '\0';
        printf("key=[%s] value=[%s]\n", line, eq + 1);
        count++;
    }

    printf("有效键值对: %d\n", count);
    fclose(fp);
    return 0;
}