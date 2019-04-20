//
// Created by HP on 2019-04-20.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node_list.h"

struct sll_node
{
    int numer_karty;
    char imie[27];
    char nazwisko[27];
    int numer_telefonu;
    char email[50];
    struct sll_node *next;
};

struct sll_node *create_list(int card, char name[], char surname[], int phone, char mail[])
{
    struct sll_node *front = (struct sll_node *)
            malloc(sizeof(struct sll_node));
    if (NULL != front)
    {
        front->numer_karty = card;
        strcpy(front->imie,name);
        strcpy(front->nazwisko,surname);
        front->numer_telefonu = phone;
        strcpy(front->email,mail);
        front->next = NULL;
    }
    return front;
}

struct sll_node *insert_front(struct sll_node *front, struct sll_node *new_node)
{
    new_node->next = front;
    return new_node;
}

struct sll_node *find_spot(struct sll_node *front, int card)
{
    struct sll_node *prev = NULL;
    while ((NULL != front) && (front->numer_karty > card))
    {
        prev = front;
        front = front->next;
    }
    return prev;
}

void insert_after(struct sll_node *node, struct sll_node *new_node)
{
    new_node->next = node->next;
    node->next = new_node;
}

void insert_back(struct sll_node *back, struct sll_node *new_node)
{
    back->next = new_node;
}

struct sll_node *insert_node(struct sll_node *front, int card, char name[], char surname[], int phone, char mail[])
{
    if (NULL == front)
        return NULL;

    struct sll_node *new_node = (struct sll_node *) malloc(sizeof(struct sll_node));
    if (NULL != new_node)
    {
        front->numer_karty = card;
        strcpy(front->imie,name);
        strcpy(front->nazwisko,surname);
        front->numer_telefonu = phone;
        strcpy(front->email,mail);
        new_node->next = NULL;
        if (front->numer_karty <= card)
            return insert_front(front, new_node);
        else
        {
            struct sll_node *node = find_spot(front, card);
            if (NULL != node->next)
                insert_after(node, new_node);
            else
                insert_back(node, new_node);
        }
    }
    return front;
}

struct sll_node *delete_front(struct sll_node *front)
{
    struct sll_node *next = front->next;
    free(front);
    return next;
}

struct sll_node *find_prev_node(struct sll_node *front, int card)
{
    struct sll_node *prev = NULL;
    while ((NULL != front) && (front->numer_karty != card))
    {
        prev = front;
        front = front->next;
    }
    return prev;
}

void delete_after(struct sll_node *node)
{
    struct sll_node *next = node->next;
    if (NULL != next)
    {
        node->next = next->next;
        free(next);
    }
}

struct sll_node *delete_node(struct sll_node *front, int card)
{
    if (NULL == front)
        return NULL;

    if (front->numer_karty == card)
        return delete_front(front);

    struct sll_node *prev = find_prev_node(front, card);
    delete_after(prev);
    return front;
}

void print_list(struct sll_node *front)
{
    for (; NULL != front; front = front->next)
        printf("nr. karty: %d | imie: %s | nazwisko: %s | nr. tel: %d | email: %s",front->numer_karty,front->imie,front->nazwisko,front->numer_telefonu,front->email);
    printf("\n");
}

void remove_list(struct sll_node **front)
{
    while (NULL != *front)
    {
        struct sll_node *next = (*front)->next;
        free(*front);
        *front = next;
    }
}