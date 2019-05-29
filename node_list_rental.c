#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "node_list.h"

struct list_node_rental{
    int id_client;
    int id_movie;
    int day;
    int month;
    int year;
    int day_r;
    int month_r;
    int year_r;
    struct list_node_rental *next;
};

struct list_node_rental *create_list_rental(struct rental rental)
{
    struct list_node_rental *first = (struct list_node_rental *) malloc(sizeof(struct list_node_rental));

    if(first) {
        first->id_client = rental.id_client;
        first->id_movie = rental.id_movie;

        first->day = rental.day;
        first->month = rental.month;
        first->year = rental.year;
        first->day_r = rental.day_r;
        first->month_r = rental.month_r;
        first->year_r = rental.year_r;

        first->next = NULL;
    }
    return first;
}

struct list_node_rental *add_at_front_rental(struct list_node_rental *list_pointer, struct list_node_rental *new_node)
{
    new_node->next = list_pointer;
    return new_node;
}

struct list_node_rental *find_spot_rental(struct list_node_rental *list_pointer, int id)
{
    struct list_node_rental *previous = NULL;

    while(list_pointer && list_pointer->id_client<id) {
        previous = list_pointer;
        list_pointer = list_pointer->next;
    }
    return previous;
}

void add_in_middle_or_at_back_rental(struct list_node_rental *node, struct list_node_rental *new_node)
{
    new_node->next = node->next;
    node->next = new_node;
}

struct list_node_rental *add_node_rental(struct list_node_rental *list_pointer, struct rental rental)
{
    struct list_node_rental *new_node = (struct list_node_rental *) malloc(sizeof(struct list_node_rental));

    if(list_pointer && new_node) {
        new_node->id_client = rental.id_client;
        new_node->id_movie = rental.id_movie;
        new_node->day = rental.day;
        new_node->month = rental.month;
        new_node->year = rental.year;
        new_node->day_r = rental.day_r;
        new_node->month_r = rental.month_r;
        new_node->year_r = rental.year_r;

        if(list_pointer->id_client>=rental.id_client) {
            return add_at_front_rental(list_pointer, new_node);
        }
        else {
            struct list_node_rental *node= find_spot_rental(list_pointer,rental.id_client);
            add_in_middle_or_at_back_rental(node,new_node);
        }
    }

    return list_pointer;
}

struct list_node_rental *delete_at_front_rental(struct list_node_rental *list_pointer)
{
    struct list_node_rental *next = list_pointer->next;
    free(list_pointer);
    return next;
}

struct list_node_rental *find_previous_node_rental (struct list_node_rental *list_pointer, int id)
{
    struct list_node_rental *previous = NULL;
    while(list_pointer && list_pointer->id_client!=id) {
        previous=list_pointer;
        list_pointer=list_pointer->next;
    }
    return previous;
}

void delete_middle_or_last_node_rental(struct list_node_rental *previous)
{
    struct list_node_rental *node = previous->next;
    if(node) {
        previous->next = node->next;
        free(node);
    }
}

struct list_node_rental *delete_node_rental(struct list_node_rental *list_pointer, int id)
{
    if(list_pointer) {
        if(list_pointer->id_client==id)
            return delete_at_front_rental(list_pointer);
        else {
            struct list_node_rental *previous = find_previous_node_rental(list_pointer,id);
            delete_middle_or_last_node_rental(previous);
        }
    }
    return list_pointer;
}

void print_list_rental(struct list_node_rental *list_pointer)
{
    while(list_pointer) {
        printf("\nid klienta: %d\t| id filmu: %d\t| data wypozyczenia: %d.%d.%d\t| data oddania: %d.%d.%d\n",
                list_pointer->id_client, list_pointer->id_movie, list_pointer->day,
                list_pointer->month, list_pointer->year,list_pointer->day_r,
               list_pointer->month_r, list_pointer->year_r );
        list_pointer=list_pointer->next;
    }
    puts("");
}

void add_list_rental_to_file(FILE *file, struct list_node_rental *list_pointer)
{
    struct rental rental;

    while(list_pointer) {
        rental.id_client = list_pointer->id_client;
        rental.id_movie = list_pointer->id_movie;
        rental.day = list_pointer->day;
        rental.month = list_pointer->month;
        rental.year = list_pointer->year;

        fwrite (&rental, sizeof(struct rental), 1, file);

        list_pointer=list_pointer->next;

        fclose (file);

    }
}

int print_node_rental(struct list_node_rental *list_pointer, int id)
{
    while(list_pointer && list_pointer->id_client!=id) {
        list_pointer=list_pointer->next;
    }

    if(list_pointer)
    {
        printf("\nid klienta: %d\t| id filmu: %d\t| data wypozyczenia: %d.%d.%d\t| data oddania: %d.%d.%d\n",
               list_pointer->id_client, list_pointer->id_movie, list_pointer->day,
               list_pointer->month, list_pointer->year,list_pointer->day_r,
               list_pointer->month_r, list_pointer->year_r );

        return 1;
    }

    return -1;
}

void remove_list_rental(struct list_node_rental **list_pointer)
{
    while(*list_pointer) {
        struct list_node_rental *next = (*list_pointer)->next;
        free(*list_pointer);
        *list_pointer = next;
    }
}

void edit_list_rental(FILE *file, struct list_node_rental **list_pointer, int id, struct list_node_rental *list_pointer_temp)
{

    while(list_pointer_temp && list_pointer_temp->id_client != id) {
        list_pointer_temp=list_pointer_temp->next;
    }

    if(list_pointer_temp){
        struct rental k;
        k.id_client = list_pointer_temp->id_client;
        k.id_movie = list_pointer_temp->id_movie;
        k.day = list_pointer_temp->day;
        k.month = list_pointer_temp->month;
        k.year = list_pointer_temp->year;

        k.day_r = 1;
        k.month_r = 1;
        k.year_r = 1;

        *list_pointer = delete_node_rental(*list_pointer,id);

        *list_pointer = add_node_rental(*list_pointer,k);

        overwriteRental(file,list_pointer);
    }

}