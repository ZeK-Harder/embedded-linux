#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("config_test.conf", "r");
    if (fp == NULL) {
        printf("failed to open config_test.conf\n");
        return 1;
    }

    char line[256];
    int line_num = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        line_num++;
        printf("%d: [%s]\n", line_num, line);
    }

    fclose(fp);
    return 0;
}