//
// Created by HP on 2019-04-20.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "node_list.h"

struct list_node {
    int numer_karty;
    char imie[27];
    char nazwisko[27];
    int numer_telefonu;
    char email[50];
    struct list_node *next;
};

struct list_node *create_list(struct klienci client)
{
    struct list_node *first = (struct list_node *)malloc(sizeof(struct list_node));

    if(first) {
        first->numer_karty = client.numer_karty;
        strcpy(first->imie,client.imie);
        strcpy(first->nazwisko,client.nazwisko);
        first->numer_telefonu = client.numer_telefonu;
        strcpy(first->email,client.email);
        first->next = NULL;
    }
    return first;
}

struct list_node *add_at_front(struct list_node *list_pointer, struct list_node *new_node)
{
    new_node->next = list_pointer;
    return new_node;
}

struct list_node *find_spot(struct list_node *list_pointer, char card)
{
    struct list_node *previous = NULL;

    while(list_pointer && list_pointer->numer_karty<card) {
        previous = list_pointer;
        list_pointer = list_pointer->next;
    }
    return previous;
}

void add_in_middle_or_at_back(struct list_node *node, struct list_node *new_node)
{
    new_node->next = node->next;
    node->next = new_node;
}

struct list_node *add_node(struct list_node *list_pointer, struct klienci client)
{
    struct list_node *new_node = (struct list_node *) malloc(sizeof(struct list_node));

    if(list_pointer && new_node) {
        new_node->numer_karty = client.numer_karty;
        strcpy(new_node->imie,client.imie);
        strcpy(new_node->nazwisko,client.nazwisko);
        new_node->numer_telefonu = client.numer_telefonu;
        strcpy(new_node->email,client.email);

        if(list_pointer->numer_karty>=client.numer_karty) {
            return add_at_front(list_pointer, new_node);
        }
        else {
            struct list_node *node= find_spot(list_pointer,client.numer_karty);
            add_in_middle_or_at_back(node,new_node);
        }
    }

    return list_pointer;
}

struct list_node *delete_at_front(struct list_node *list_pointer)
{
    struct list_node *next = list_pointer->next;
    free(list_pointer);
    return next;
}

struct list_node *find_previous_node (struct list_node *list_pointer, int card)
{
    struct list_node *previous = NULL;
    while(list_pointer && list_pointer->numer_karty!=card) {
        previous=list_pointer;
        list_pointer=list_pointer->next;
    }
    return previous;
}

void delete_middle_or_last_node(struct list_node *previous)
{
    struct list_node *node = previous->next;
    if(node) {
        previous->next = node->next;
        free(node);
    }
}

struct list_node *delete_node(struct list_node *list_pointer, int card)
{
    if(list_pointer) {
        if(list_pointer->numer_karty==card)
            return delete_at_front(list_pointer);
        else {
            struct list_node *previous = find_previous_node(list_pointer,card);
            delete_middle_or_last_node(previous);
        }
    }
    return list_pointer;
}

void print_list(struct list_node *list_pointer)
{
    while(list_pointer) {
        printf("nr. karty: %d | imie: %s | nazwisko: %s | nr. tel: %d | email: %s\n",list_pointer->numer_karty,list_pointer->imie,list_pointer->nazwisko,list_pointer->numer_telefonu,list_pointer->email);
        list_pointer=list_pointer->next;
    }
    puts("");
}

void add_list_to_file(FILE *file, struct list_node *list_pointer)
{
    struct klienci k;

    while(list_pointer) {
        k.numer_karty = list_pointer->numer_karty;
        strcpy(k.imie,list_pointer->imie);
        strcpy(k.nazwisko,list_pointer->nazwisko);
        k.numer_telefonu= list_pointer->numer_telefonu;
        strcpy(k.email,list_pointer->email);

        fwrite (&k, sizeof(struct klienci), 1, file);

        list_pointer=list_pointer->next;
    }
}


void edit_list(FILE *file, struct list_node **list_pointer, int id, int field, struct list_node *list_pointer_temp)
{

    while(list_pointer_temp && list_pointer_temp->numer_karty != id) {
        list_pointer_temp=list_pointer_temp->next;
    }

    if(list_pointer_temp){
        struct klienci k;
        k.numer_karty = list_pointer_temp->numer_karty;
        strcpy(k.imie,list_pointer_temp->imie);
        strcpy(k.nazwisko,list_pointer_temp->nazwisko);
        k.numer_telefonu= list_pointer_temp->numer_telefonu;
        strcpy(k.email,list_pointer_temp->email);

        int tmp_int = 0;
        char tmp_char[27] = {0};

        switch(field){
            case 1:
                printf("Podaj nowy nr karty: ");
                scanf("%d",&tmp_int);
                k.numer_karty = tmp_int;
                break;
            case 2:
                printf("Podaj nowe imie: ");
                scanf(" %[^\n]s",tmp_char);
                strcpy(k.imie,tmp_char);
                break;
            case 3:
                printf("Podaj nowe nazwisko: ");
                scanf(" %[^\n]s",tmp_char);
                strcpy(k.nazwisko,tmp_char);
                break;
            case 4:
                printf("Podaj nowy nr telefonu: ");
                scanf("%d",&tmp_int);
                k.numer_telefonu = tmp_int;
                break;
            case 5:
                printf("Podaj nowy email: ");
                scanf(" %[^\n]s",tmp_char);
                strcpy(k.email,tmp_char);
                break;

        }

        *list_pointer = delete_node(*list_pointer,id);

        *list_pointer = add_node(*list_pointer,k);

        overwriteKlienci(file,list_pointer);
    }

}

int print_node(struct list_node *list_pointer, int id)
{
    while(list_pointer && list_pointer->numer_karty != id) {
        list_pointer=list_pointer->next;
    }

    if(list_pointer){
        printf("nr. karty: %d | imie: %s | nazwisko: %s | nr. tel: %d | email: %s\n",list_pointer->numer_karty,list_pointer->imie,list_pointer->nazwisko,list_pointer->numer_telefonu,list_pointer->email);
        return 1;
    }

    return -1;
}



void remove_list(struct list_node **list_pointer)
{
    while(*list_pointer) {
        struct list_node *next = (*list_pointer)->next;
        free(*list_pointer);
        *list_pointer = next;
    }
}




