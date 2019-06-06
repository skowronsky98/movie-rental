#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "node_list.h"

/*! brief Struktura wypozyczen*/
struct list_node_rental{
    int id_client; /*!< Pole z id klienta */
    int id_movie; /*!< Pole z id filmu */
    int day; /*!< Pole zawierajace dzien wypozyczenia */
    int month; /*!< Pole zawierajace miesiac wypozyczenia */
    int year; /*!< Pole zawierajace rok wypozyczenia */
    int day_r; /*!< Pole zawierajace dzien oddania */
    int month_r; /*!< Pole zawierajace miesiac oddania */
    int year_r; /*!< Pole zawierajace rok oddania */
    struct list_node_rental *next; /*!< Wskaznik na nastepny element struktury wypozyczen */
};

/*! \brief Funkcja tworzy nowa liste wypozyczen
*         Parametrem jest struktura wypozyczen
*
\return Zwraca wskaznik na pierwszy element listy wypozyczen
*/
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

/*! \brief Funkcja dodaje wypozyczenie na przod listy z wypozyczeniami
*         Parametry to wskaznik na liste z wypozyczeniami oraz nowy wezel wypozyczen
*
\return Zwraca nowy wezel
*/
struct list_node_rental *add_at_front_rental(struct list_node_rental *list_pointer, struct list_node_rental *new_node)
{
    new_node->next = list_pointer;
    return new_node;
}

/*! \brief Funkcja szuka miejsca dla wypozyczenia w liscie wypozyczen
*         Parametry to wskaznik na liste z wypozyczen oraz id klienta
*
\return Po znalezieniu miejsca dla wypozyczenia zwraca wskaznik na poprzedni element listy
*/
struct list_node_rental *find_spot_rental(struct list_node_rental *list_pointer, int id)
{
    struct list_node_rental *previous = NULL;

    while(list_pointer && list_pointer->id_client<id) {
        previous = list_pointer;
        list_pointer = list_pointer->next;
    }
    return previous;
}

/*! \brief Funkcja dodaje element w wyznaczone miejsce
*         Parametrami sa wskazniki na ostatni element listy wypozyczen oraz nowy element listy wypozyczen
*
*/
void add_in_middle_or_at_back_rental(struct list_node_rental *node, struct list_node_rental *new_node)
{
    new_node->next = node->next;
    node->next = new_node;
}

/*! \brief Funkcja dodaje nowe wypozyczenie do listy z wypozyczeniami
*         Parametry to wskaznik na liste oraz struktura wypozyczenia
*
\return Po dodaniu nowego elementu funkcja zwraca wskaznik na liste z wypozyczeniami
*/
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

/*! \brief Funkcja usuwa wypozyczenie z brzegu
*         Parametrem jest wskaznik na liste z wypozyczeniami
*
\return Funkcja usuwa element i zwraca wskaznik na nastepne pole usunietego elementu
*/
struct list_node_rental *delete_at_front_rental(struct list_node_rental *list_pointer)
{
    struct list_node_rental *next = list_pointer->next;
    free(list_pointer);
    return next;
}

/*! \brief Funkcja szuka elementu przed wskazanym
*         Parametry to wskaznik na liste z wypozyczeniami oraz id klienta
*
\return Zwraca wskaznik na poprzedni element
*/
struct list_node_rental *find_previous_node_rental (struct list_node_rental *list_pointer, int id)
{
    struct list_node_rental *previous = NULL;
    while(list_pointer && list_pointer->id_client!=id) {
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
void delete_middle_or_last_node_rental(struct list_node_rental *previous)
{
    struct list_node_rental *node = previous->next;
    if(node) {
        previous->next = node->next;
        free(node);
    }
}

/*! \brief Funkcja szuka i usuwa wskazany element
*         Parametry to wskaznik na liste wypozyczen oraz wybrane id klienta
*
\return Po usunieciu elementu zwraca wskaznik na liste wypozyczen
*/
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

/*! \brief Funkcja wypisuje zawartosc listy wypozyczen
*         Parametrem jest wskaznik na liste z wypozyczeniami
*
*/
void print_list_rental(struct list_node_rental *list_pointer)
{
    puts("");
    while(list_pointer) {
        printf("id klienta: %d\t| id filmu: %d\t| data wypozyczenia: %d.%d.%d\t| data oddania: %d.%d.%d\n",
                list_pointer->id_client, list_pointer->id_movie, list_pointer->day,
                list_pointer->month, list_pointer->year,list_pointer->day_r,
               list_pointer->month_r, list_pointer->year_r);

        list_pointer = list_pointer->next;
    }
    puts("");
}

/*! \brief Funkcja dodaje liste wypozyczen do pliku
*         Parametry to sciezka do pliku oraz wskaznik na liste z wypozyczeniami
*
*/
void add_list_rental_to_file(FILE *file, struct list_node_rental *list_pointer)
{
    struct rental r;
    while(list_pointer) {
        r.id_client = list_pointer->id_client;
        r.id_movie = list_pointer->id_movie;
        r.day = list_pointer->day;
        r.month = list_pointer->month;
        r.year = list_pointer->year;

        r.day_r = list_pointer->day_r;
        r.month_r = list_pointer->month_r;
        r.year_r = list_pointer->year_r;

        fwrite (&r, sizeof(struct rental), 1, file);

        if(fwrite == 0)
            printf("Tarapaty");

        list_pointer = list_pointer->next;

       // fclose (file);

    }


}

/*! \brief Funkcja szuka i wypisuje wskazany element wypozyczen
*         Parametrami sa wskaznik na liste z wypozyczeniami oraz wybrany numer id klienta
*
\return Jesli wybrany element znajduje sie w liscie zwraca 1, w przeciwnym razie -1
*/
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

/*! brief Struktura Daty*/
struct Date
{
    int d, m, y;
};

/*! brief Tablica z dniami danego miesiaca*/
const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};

/*! \brief Funkcja sprawdza czy aktualny rok jest przestepny
*         Parametrem jest struktura Daty
*
\return Zwraca czy wprowadzony rok jest przestepny.
*/
int countLeapYears(struct Date d)
{
    int years = d.y;

    if (d.m <= 2)
        years--;

    return years / 4 - years / 100 + years / 400;
}

/*! \brief Funkcja sprawdza roznice pomiedzy datami wypozyczen
*         Parametrami sa dwie daty, wypozyczenia i oddania lub biezca jesli film nie zostal oddany
*
\return Zwraca roznice w dniach pomiedzy datami
*/
int getDifference(struct Date dt1, struct Date dt2)
{
    long int n1 = dt1.y*365 + dt1.d;

    for (int i=0; i<dt1.m - 1; i++)
        n1 += monthDays[i];


    n1 += countLeapYears(dt1);

    long int n2 = dt2.y*365 + dt2.d;
    for (int i=0; i<dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);
    return (n2 - n1);
}

/*! \brief Funkcja obliczajaca ile wynosi kara za dane wypozyczenie
*         Parametrem jest lista wypozyczen
*
*\n Jesli film nie zostal oddany to funkcja oblicza kare dla aktualnej daty
*\n Jesli film zostal oddany ale wypozyczenie trwalo dluzej niz 30 dni rowniez wylicza kare dla wypozyczenia
*\n W przypadku wypozyczenia ktore trwalo krocej niz 30 dni nie zostaje naliczana zadna kara
*/
void calculate_fee(struct list_node_rental *rental){

    while (rental)
    {

        if(rental->day_r == 0) {

            int a_day, a_month, a_year;
            time_t now;
            time(&now);

            struct tm *local = localtime(&now);

            a_day = local->tm_mday;
            a_month = local->tm_mon + 1;
            a_year = local->tm_year + 1900;

            struct Date dt1 = {rental->day, rental->month, rental->year};
            struct Date dt2 = {a_day, a_month, a_year};

            int fee = getDifference(dt1, dt2);


                printf("\nid klienta: %d\t| id filmu: %d\t| data wypozyczenia: %d.%d.%d\t| data oddania: %d.%d.%d"
                       ,
                       rental->id_client, rental->id_movie, rental->day,
                       rental->month, rental->year,rental->day_r,
                       rental->month_r, rental->year_r);
                if (fee > 30) printf("| Kara %dzl",fee-30);
                else printf("| Kara 0zl");
        }
        else {
            struct Date dt3 = {rental->day, rental->month, rental->year};
            struct Date dt4 = {rental->day_r, rental->month_r, rental->year_r};

            int fee = getDifference(dt3, dt4);

            printf("\nid klienta: %d\t| id filmu: %d\t| data wypozyczenia: %d.%d.%d\t| data oddania: %d.%d.%d"
                    ,
                   rental->id_client, rental->id_movie, rental->day,
                   rental->month, rental->year,rental->day_r,
                   rental->month_r, rental->year_r);
            if (fee > 30) printf("| Kara %dzl",fee-30);
            else printf("| Kara 0zl");
        }
        rental = rental->next;
    }

    puts("\n");

}

/*! \brief Funkcja usuwa liste z wypozyczeniami
*         Parametrem jest wskaznik na wskaznik z liste wypozyczen
*
*/
void remove_list_rental(struct list_node_rental **list_pointer)
{
    while(*list_pointer) {
        struct list_node_rental *next = (*list_pointer)->next;
        free(*list_pointer);
        *list_pointer = next;
    }
}


/*! \brief Funkcja edytujaca wskazane wypozyczenie
*         Parametry to: sciezka do pliku, wskaznik na liste z wypozyczeniami, id klienta oraz tymczasowy wskaznik na liste z wypozyczeniami
*
*\n Funkcja szuka czy element istnieje jesli tak to edytuje pole z oddaniem filmu.
*/
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

        printf("Podaj dzien oddania: ");
        scanf("%d",&k.day_r);

        printf("Podaj miesiac oddania: ");
        scanf("%d",&k.month_r);

        printf("Podaj rok oddania: ");
        scanf("%d",&k.year_r);

        *list_pointer = delete_node_rental(*list_pointer,id);

        *list_pointer = add_node_rental(*list_pointer,k);

        overwriteRental(file,list_pointer);
    }

}