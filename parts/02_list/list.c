#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void print_list(struct node *head){
    struct node *ptr=head;
    while(ptr!=NULL){
        printf("%d\n",ptr->id); 
        ptr=ptr->next;
    }
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

void list_free(struct node *head){
    struct node *ptr=head;
    while(ptr!=NULL){
        struct node *temp=ptr;
        ptr=ptr->next;
        free(temp);
    }
}

struct node *find_by_id(struct node *head, int id){
    struct node *ptr=head;
    while(ptr!=NULL){
        if(ptr->id==id){
            return ptr;
        }
        ptr=ptr->next;
    }
    return NULL;
}