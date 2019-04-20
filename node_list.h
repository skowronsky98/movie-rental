//
// Created by HP on 2019-04-20.
//

#ifndef PPPROJEKT_NODE_LIST_H
#define PPPROJEKT_NODE_LIST_H

struct sll_node;

struct sll_node *create_list(int card, char name[], char surname[], int phone, char mail[]);
struct sll_node *insert_node(struct sll_node *front, int card, char name[], char surname[], int phone, char mail[]);
struct sll_node *delete_node(struct sll_node *front, int card);
void print_list(struct sll_node *front);
void remove_list(struct sll_node **front);



#endif //PPPROJEKT_NODE_LIST_H
