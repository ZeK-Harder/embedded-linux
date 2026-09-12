#include <stdio.h>
#include <stdlib.h>

struct node{
    int id;
    struct node *next;
};

void print_list(struct node *head){
    struct node *ptr=head;
    while(ptr!=NULL){
        printf("%d\n",ptr->id); 
        ptr=ptr->next;
    }
}

void find_by_id(struct node *head, int id){
    struct node *ptr=head;
    while(ptr!=NULL){
        if(ptr->id==id){
            printf("Found: %d\n",ptr->id);
            return;
        }
        ptr=ptr->next;
    }
    printf("Not found: %d\n",id);
}

void append_to_tail(struct node **head, int id){
    struct node *new_node=malloc(sizeof(struct node));
    new_node->id=id;
    new_node->next=NULL;
    if(*head==NULL){
        *head=new_node;
        return;
    }
    struct node *ptr=*head;
    while(ptr->next!=NULL){
        ptr=ptr->next;
    }
    ptr->next=new_node;
}

int main(){
    struct node *head=NULL;
    append_to_tail(&head, 1);
    append_to_tail(&head, 2);
    append_to_tail(&head, 3);
    print_list(head);
    find_by_id(head, 2);
    find_by_id(head, 4);
    return 0;
}