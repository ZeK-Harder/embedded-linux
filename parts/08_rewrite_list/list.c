#include "list.h"
#include <stdio.h>
#include <stdlib.h>

int append_to_tail (struct node **head,int id){
    struct node *new_node = malloc(sizeof(struct node));
    if(new_node == NULL){
        return 0;
    }
    new_node->id = id;
    new_node->next = NULL;
    if(*head == NULL){
        *head = new_node;
        return 1;
    }
    struct node *ptr = *head;
    while(ptr->next != NULL){
        ptr = ptr->next;
    }
    ptr->next = new_node;
    return 1;
}

void print_list (struct node *head){
    struct node *ptr = head;
    while(ptr != NULL){
        printf("%d\n",ptr->id);
        ptr = ptr->next;
    }
}

int delete_node (struct node **head,int id){
    struct node *cur = *head;
    struct node *prev = NULL;
    while(cur != NULL){
        if(cur->id == id){
            if(prev == NULL){
                *head = cur->next;
            }
            else{
                prev->next = cur->next;
            }
            free(cur);
            return 1; // success
        }
        prev = cur;
        cur = cur->next;
    }
    return 0; //not found
}

void free_all (struct node *head){
    struct node *ptr = head;
    while(ptr != NULL){
        struct node *temp = ptr;
        ptr = ptr->next;
        free(temp);
    }
}