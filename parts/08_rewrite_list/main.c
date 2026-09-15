#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    struct node *head = NULL;
    if (append_to_tail(&head, 1) == 0) {
    printf("添加节点失败");
    return 1;
    }
    append_to_tail(&head, 2);
    append_to_tail(&head, 3);
    print_list(head);
    delete_node (&head,2);
    printf("删除2后:\n");
    print_list(head);
    if(!delete_node (&head,4)){
        printf("未找到\n");
    }
    delete_node (&head,1);
    print_list(head);
    delete_node (&head,3);
    delete_node (&head,1);
    free_all (head);
    return 0;
}