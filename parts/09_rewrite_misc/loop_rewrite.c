#include <stdio.h>
#include <string.h>

int main(){

    char line[128];

    while(1){
        printf("> ");
        if(fgets(line , sizeof (line) , stdin) == NULL){
            printf("EOF，退出\n");
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
        if(strlen(line) == 0){
            printf("收到: [空]\n");
            continue;
        }
        printf("收到：[%s]\n",line);
    }
    return 0;
}