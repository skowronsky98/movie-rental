//
// Created by HP on 2019-04-20.
//

#ifndef PPPROJEKT_NODE_LIST_H
#define PPPROJEKT_NODE_LIST_H

struct klienci {
    int numer_karty;
    char imie[27];
    char nazwisko[27];
    int numer_telefonu;
    char email[50];
};

void addClient(struct klienci *d);
void saveDataKlienci(struct klienci *d,FILE *file);

extern struct list_node;

extern struct list_node *create_list(struct klienci);
extern struct list_node *add_node(struct list_node*,struct klienci);
extern struct list_node *delete_node(struct list_node*, char);
extern void print_list(struct list_node*);
extern void remove_list(struct list_node**);


void readDataKlienci(FILE *file, struct list_node**);


#endif //PPPROJEKT_NODE_LIST_H
