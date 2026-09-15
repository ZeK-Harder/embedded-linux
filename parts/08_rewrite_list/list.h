#pragma once
#include <stdio.h>
#include <stdlib.h>

struct node {
    int id;
    struct node *next;
};

void append_to_tail (struct node **head,int id);
void print_list (struct node *head);
int delete_node (struct node **head,int id);
void free_all (struct node *head);