#include <stdio.h>
#include <string.h>

int main(void)
{
    char line[128];

    while (1) {
        printf("> ");
        if(fgets(line, sizeof(line), stdin) == NULL){
            printf("EOF\n");
            break;
        }
        char *newline_pos = strchr(line, '\n');
        if (newline_pos != NULL) {
            *newline_pos = '\0';
        }
        if(strcmp(line,"quit") == 0){
            printf("bye\n");
            break;
        }
        printf("收到：[%s]\n",line);
    }
    return 0;
}