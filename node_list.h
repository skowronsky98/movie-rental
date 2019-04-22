//
// Created by HP on 2019-04-20.
//

#ifndef PPPROJEKT_NODE_LIST_H
#define PPPROJEKT_NODE_LIST_H

#include "file_clients.h"

extern struct list_node;

extern struct list_node *create_list(struct klienci);
extern struct list_node *add_node(struct list_node*,struct klienci);
extern struct list_node *delete_node(struct list_node*, char);
extern void print_list(struct list_node*);
extern void remove_list(struct list_node**);

//char card, char name[], char surname[], char phone, char mail[]

#endif //PPPROJEKT_NODE_LIST_H
