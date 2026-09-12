#pragma once
#include <stdio.h>
#include <stdlib.h>

struct node{
    int id;
    struct node *next;
};

void print_list(struct node *head);
struct node *find_by_id(struct node *head, int id);
void append_to_tail(struct node **head, int id);
void list_free(struct node *head);
int delete_node(struct node **head, int id);