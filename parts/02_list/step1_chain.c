#include <stdio.h>
struct node{
    int id;
    struct node *next;
};
int main(void){
    struct node n1={1,NULL};
    struct node n2={2,NULL};
    struct node n3={3,NULL};
    n1.next=&n2;
    n2.next=&n3;
    struct node *ptr=&n1;
    while(ptr!=NULL){
        printf("%d\n",ptr->id); 
        ptr=ptr->next;
    }
    return 0;
}