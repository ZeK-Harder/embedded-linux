#include "list.h"
int main(){
    struct node *head=NULL;
    append_to_tail(&head, 1);
    append_to_tail(&head, 2);
    append_to_tail(&head, 3);
    print_list(head);
    find_by_id(head, 2);
    find_by_id(head, 99);
    return 0;
}