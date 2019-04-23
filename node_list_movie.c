//
// Created by HP on 2019-04-22.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "node_list.h"

struct list_node_movie {
    int id_filmu;
    char tytul[27];
    int rok;
    char rezyser[27];
    char gatunek[27];
    int liczba_egzemplarzy;
    int liczba_wypozyczonych;
    struct list_node_movie *next;
};

struct list_node_movie *create_list_movie(struct filmy movie)
{
    struct list_node_movie *first = (struct list_node_movie *) malloc(sizeof(struct list_node_movie));

    if(first) {
        first->id_filmu = movie.id_filmu;
        strcpy(first->tytul,movie.tytul);
        first->rok = movie.rok;
        strcpy(first->rezyser,movie.rezyser);
        strcpy(first->gatunek,movie.gatunek);
        first->liczba_egzemplarzy = movie.liczba_egzemplarzy;
        first->liczba_wypozyczonych = movie.liczba_wypozyczonych;
        first->next = NULL;
    }
    return first;
}

struct list_node_movie *add_at_front_movie(struct list_node_movie *list_pointer, struct list_node_movie *new_node)
{
    new_node->next = list_pointer;
    return new_node;
}

struct list_node_movie *find_spot_movie(struct list_node_movie *list_pointer, int id)
{
    struct list_node_movie *previous = NULL;

    while(list_pointer && list_pointer->id_filmu<id) {
        previous = list_pointer;
        list_pointer = list_pointer->next;
    }
    return previous;
}

void add_in_middle_or_at_back_movie(struct list_node_movie *node, struct list_node_movie *new_node)
{
    new_node->next = node->next;
    node->next = new_node;
}

struct list_node_movie *add_node_movie(struct list_node_movie *list_pointer, struct filmy movie)
{
    struct list_node_movie *new_node = (struct list_node_movie *) malloc(sizeof(struct list_node_movie));

    if(list_pointer && new_node) {
        new_node->id_filmu = movie.id_filmu;
        strcpy(new_node->tytul,movie.tytul);
        new_node->rok = movie.rok;
        strcpy(new_node->rezyser,movie.rezyser);
        strcpy(new_node->gatunek,movie.gatunek);
        new_node->liczba_egzemplarzy = movie.liczba_egzemplarzy;
        new_node->liczba_wypozyczonych = movie.liczba_wypozyczonych;

        if(list_pointer->id_filmu>=movie.id_filmu) {
            return add_at_front_movie(list_pointer, new_node);
        }
        else {
            struct list_node_movie *node= find_spot_movie(list_pointer,movie.id_filmu);
            add_in_middle_or_at_back_movie(node,new_node);
        }
    }

    return list_pointer;
}

struct list_node_movie *delete_at_front_movie(struct list_node_movie *list_pointer)
{
    struct list_node_movie *next = list_pointer->next;
    free(list_pointer);
    return next;
}

struct list_node_movie *find_previous_node_movie (struct list_node_movie *list_pointer, int id)
{
    struct list_node_movie *previous = NULL;
    while(list_pointer && list_pointer->id_filmu!=id) {
        previous=list_pointer;
        list_pointer=list_pointer->next;
    }
    return previous;
}

void delete_middle_or_last_node_movie(struct list_node_movie *previous)
{
    struct list_node_movie *node = previous->next;
    if(node) {
        previous->next = node->next;
        free(node);
    }
}

struct list_node_movie *delete_node_movie(struct list_node_movie *list_pointer, int id)
{
    if(list_pointer) {
        if(list_pointer->id_filmu==id)
            return delete_at_front_movie(list_pointer);
        else {
            struct list_node_movie *previous = find_previous_node_movie(list_pointer,id);
            delete_middle_or_last_node_movie(previous);
        }
    }
    return list_pointer;
}

void print_list_movie(struct list_node_movie *list_pointer)
{
    while(list_pointer) {
        printf("id filmu: %d | tytul: %s | rok: %d | rezyser: %s | gatunek: %s | l.egzemplarzy: %d | l.wypozyczonych: %d \n",
                list_pointer->id_filmu,list_pointer->tytul,list_pointer->rok,list_pointer->rezyser,list_pointer->gatunek,list_pointer->liczba_egzemplarzy,list_pointer->liczba_wypozyczonych);
        list_pointer=list_pointer->next;
    }
    puts("");
}

void add_list_movie_to_file(FILE *file, struct list_node_movie *list_pointer)
{
    struct filmy f;

    while(list_pointer) {
        f.id_filmu= list_pointer->id_filmu;
        strcpy(f.tytul,list_pointer->tytul);
        f.rok= list_pointer->rok;
        strcpy(f.rezyser,list_pointer->rezyser);
        strcpy(f.gatunek,list_pointer->gatunek);
        f.liczba_egzemplarzy= list_pointer->liczba_egzemplarzy;
        f.liczba_wypozyczonych= list_pointer->liczba_wypozyczonych;

        fwrite (&f, sizeof(struct filmy), 1, file);

        list_pointer=list_pointer->next;
    }
}


void remove_list_movie(struct list_node_movie **list_pointer)
{
    while(*list_pointer) {
        struct list_node_movie *next = (*list_pointer)->next;
        free(*list_pointer);
        *list_pointer = next;
    }
}
