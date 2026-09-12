#include "list.h"
int main(){
    struct node *head=NULL;
    append_to_tail(&head, 1);
    append_to_tail(&head, 2);
    append_to_tail(&head, 3);
    print_list(head);
    struct node *p = find_by_id(head, 2);
    if(p!=NULL){
        printf("Found: %d\n",p->id);
    }else{
        printf("Not found: %d\n",2);
    }
    struct node *q = find_by_id(head, 99);
    if(q!=NULL){
        printf("Found: %d\n",q->id);
    }else{      
        printf("Not found: %d\n",99);
    }   
    return 0;
}