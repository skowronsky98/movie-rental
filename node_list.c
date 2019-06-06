//
// Created by HP on 2019-04-20.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "node_list.h"

/*! brief Struktura klientow*/
struct list_node {
    int numer_karty; /*!< Pole z numerem karty */
    char imie[27]; /*!< Pole zawierajaca imie*/
    char nazwisko[27]; /*!< Pole zawierajace nazwisko */
    int numer_telefonu; /*!< Pole z nr tekefonu */
    char email[50]; /*!< Pole zawierajace email */
    struct list_node *next; /*!< Wskaznik na nastepny element struktury klienci */
};

/*! \brief Funkcja tworzy nowa liste kleintow
*         Parametrem jest struktura klientow
*
\return Zwraca wskaznik na pierwszy element listy klientow
*/
struct list_node *create_list(struct klienci client)
{
    struct list_node *first = (struct list_node *)malloc(sizeof(struct list_node));

    if(first) {
        first->numer_karty = 1;
        strcpy(first->imie,client.imie);
        strcpy(first->nazwisko,client.nazwisko);
        first->numer_telefonu = client.numer_telefonu;
        strcpy(first->email,client.email);
        first->next = NULL;
    }
    return first;
}

/*! \brief Funkcja sprawdza ostatni index numeru karty
*         Parametrem jest lista klientow
*
\return Zwraca numer ostatniego indeksu
*/
int last_index(struct list_node *list_pointer)
{
    int index = 0;
    while (list_pointer)
    {
        index = list_pointer->numer_karty;
        list_pointer = list_pointer->next;
    }

    return index;
}

/*! \brief Funkcja szuka ostatnie miejsce w liscie klientow
*         Parametrem jest wskaznik na liste z klientami
*
\return Po znalezieniu miejsca dla filmu zwraca wskaznik na ostatni element
*/
struct list_node *find_last_spot(struct list_node *list_pointer)
{
    while(list_pointer->next) {
        list_pointer = list_pointer->next;
    }
    return list_pointer;
}

/*! \brief Funkcja dodaje nowy film do listy z klientami
*         Parametry to wskaznik na liste oraz struktura klienci
*
\return Po dodaniu nowego elementu funkcja zwraca wskaznik na liste z klientami
*/
struct list_node *add_node(struct list_node *list_pointer, struct klienci client)
{
    struct list_node *new_node = (struct list_node *) malloc(sizeof(struct list_node));

    if(list_pointer && new_node) {
        struct list_node *previous = find_last_spot(list_pointer);

        new_node->numer_karty = previous->numer_karty+1;
        strcpy(new_node->imie,client.imie);
        strcpy(new_node->nazwisko,client.nazwisko);
        new_node->numer_telefonu = client.numer_telefonu;
        strcpy(new_node->email,client.email);

        previous->next = new_node;
        new_node->next = NULL;

    }

    return list_pointer;
}

/*! \brief Funkcja usuwa klienta z brzegu
*         Parametrem jest wskaznik na liste z klientami
*
\return Funkcja usuwa element i zwraca wskaznik na nastepne pole usunietego elementu
*/
struct list_node *delete_at_front(struct list_node *list_pointer)
{
    struct list_node *next = list_pointer->next;
    free(list_pointer);
    return next;
}

/*! \brief Funkcja szuka elementu przed wskazanym
*         Parametry to wskaznik na liste z klientami oraz numer karty
*
\return Zwraca wskaznik na poprzedni element
*/
struct list_node *find_previous_node (struct list_node *list_pointer, int card)
{
    struct list_node *previous = NULL;
    while(list_pointer && list_pointer->numer_karty!=card) {
        previous=list_pointer;
        list_pointer=list_pointer->next;
    }
    return previous;
}

/*! \brief Funkcja usuwajaca element ze srodka lub znajdujacy sie na koncu
*         Parametrem jest wskaznik na element do usuniecia
*
*\n Funkcja przeszukuje liste a nastepnie wskazany usuwa element
*/
void delete_middle_or_last_node(struct list_node *previous)
{
    struct list_node *node = previous->next;
    if(node) {
        previous->next = node->next;
        free(node);
    }
}

/*! \brief Funkcja szuka i usuwa wskazany element
*         Parametry to wskaznik na liste klientow oraz wybrany numer karty
*
\return Po usunieciu elementu zwraca wskaznik na liste klientow
*/
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

/*! \brief Funkcja wypisuje zawartosc listy klientow
*         Parametrem jest wskaznik na liste z klientami
*
*/
void print_list(struct list_node *list_pointer)
{
    puts("");
    while(list_pointer) {
        printf("nr. karty: %d \t| imie: %s \t| nazwisko: %s \t| nr. tel: %d \t| email: %s\n",list_pointer->numer_karty,list_pointer->imie,list_pointer->nazwisko,list_pointer->numer_telefonu,list_pointer->email);
        list_pointer=list_pointer->next;
    }
    puts("");
}

/*! \brief Funkcja tworzy liste z pliku
*         Parametrem jest struktura klientow
*
*/
struct list_node *create_list_from_file(struct klienci client)
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

/*! \brief Funkcja zapisuje liste do pliku
*         Parametry to sciezka do pliku oraz wskaznik na liste z klientami
*
*/
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

/*! \brief Funkcja dodaje element z brzegu
*         Parametry to wskazniki na liste z klientami oraz nowy element
*
\return Funkcja zwraca wskaznik na nowy element
*/
struct list_node *add_at_front(struct list_node *list_pointer, struct list_node *new_node)
{
    new_node->next = list_pointer;
    return new_node;
}

/*! \brief Funkcja szuka miejsca dla elementu
*         Parametry to wskaznik na liste z klientami oraz numer karty
*
\return Funkcja zwraca wskaznik na odpowiednie miejsce
*/
struct list_node *find_spot(struct list_node *list_pointer, char card)
{
    struct list_node *previous = NULL;

    while(list_pointer && list_pointer->numer_karty<card) {
        previous = list_pointer;
        list_pointer = list_pointer->next;
    }
    return previous;
}

/*! \brief Funkcja dodaje element w srodku lub na koncu
*         Parametry to wskaznik sprawdzany element oraz nowy element
*
*/
void add_in_middle_or_at_back(struct list_node *node, struct list_node *new_node)
{
    new_node->next = node->next;
    node->next = new_node;
}

/*! \brief Funkcja wczytuje elementy i zapisuje do listy
*         Parametry to wskaznik na lizte z klientami oraz struktura klienci
*
\return Zwraca wskaznik na liste
*/
struct list_node *read_node_from_file(struct list_node *list_pointer, struct klienci client)
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

/*! \brief Funkcja sprawdzajaca czy istnieje dany klient
*         Parametrami sa wskaznik na liste klientow oraz wybrany numer karty
*
\return Zwraca 1 jesli klient z podanym numerem istnieje, w przeciwnym wypadku -1
*/
int check_id(struct list_node *list_pointer, int id)
{
    while (list_pointer)
    {
        if(list_pointer->numer_karty == id)
            return 1;

        list_pointer = list_pointer->next;
    }
    return -1;
}
/*! \brief Funkcja edytuje liste z klientami
*         Parametry to sciezka do pliku, wskaznik na liste z klientami, pole ktore chcemy edytowac oraz tymczasowy wskaznik na liste
*
*\n Funkcja szuka czy element istnieje jesli tak to edytuje wskazane pole.
*/
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

                while (check_id(*list_pointer,tmp_int) == 1)
                {
                    printf("\nNumer karty juz istnieje podaj nowy nr karty: ");
                    scanf("%d",&tmp_int);
                }
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

        *list_pointer = read_node_from_file(*list_pointer,k);

        overwriteKlienci(file,list_pointer);
    }

}

/*! \brief Funkcja wypisuje wskazane pole
*         Parametry to wskaznik na liste z klientami oraz numer karty
*
\return Zwraca 1 jesli klient o podanym numerze istnieje, w przecywinym wypadku -1
*/
int print_node(struct list_node *list_pointer, int id)
{
    puts("");
    while(list_pointer && list_pointer->numer_karty != id) {
        list_pointer=list_pointer->next;
    }

    if(list_pointer){
        printf("nr. karty: %d \t| imie: %s \t| nazwisko: %s \t| nr. tel: %d \t| email: %s\n",list_pointer->numer_karty,list_pointer->imie,list_pointer->nazwisko,list_pointer->numer_telefonu,list_pointer->email);
        return 1;
    }

    return -1;
}



/*! \brief Funkcja usuwa liste z klientami
*         Parametrem jest wskaznik na wskaznik z lista klientow
*
*/
void remove_list(struct list_node **list_pointer)
{
    while(*list_pointer) {
        struct list_node *next = (*list_pointer)->next;
        free(*list_pointer);
        *list_pointer = next;
    }
}




