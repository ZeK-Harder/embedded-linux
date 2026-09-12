#include "list.h"
int main(){
    struct node *head=NULL;
    append_to_tail(&head, 1);
    append_to_tail(&head, 2);
    append_to_tail(&head, 3);
    print_list(head);
    delete_node(&head, 2);
    printf("删除2后:\n");
    print_list(head);
    delete_node(&head, 1);
    printf("删除1后:\n");
    print_list(head);
    delete_node(&head, 99);
    printf("删除99后:\n");
    print_list(head);
    delete_node(&head, 3);
    printf("删除3后:\n");
    print_list(head);
    list_free(head);
    return 0;
}