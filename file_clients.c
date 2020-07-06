//
// Created by HP on 2019-04-20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "node_list.h"

/*! \brief Funkcja zapisuje dane Klientow
*         Parametrami funkcji jest struktura klientow, sciezka do pliku oraz wskaznik na liste klientow
*
*/
void saveDataKlienci(struct klienci d,FILE *file, struct list_node **list){

    // add element to list
    if(*list == NULL)
        *list = create_list(d);
    else
        *list = add_node(*list,d);

    d.numer_karty = last_index(*list);

    file = fopen("klienci.dat","a+");

    if (file == NULL)
    {
        fprintf(stderr, "\nBlad podczas otwierania pliku\n");
        exit (1);
    }
    // write struct to file
    fwrite (&d, sizeof(struct klienci), 1, file);


    if(fwrite != 0)
        printf("Poprawnie zapisano dane!\n\n");
    else
        printf("Blad podczas zapisywania danych!\n");

    // close file
    fclose (file);
}

/*! \brief Funkcja dodaje nowego klienta
*         Parametrami funkcji jest sciezka do pliku oraz wskaznik na liste klientow
*
*\n Funkcja po podaniu danych klienta korzysta z funkcji zapisujacej dane klienta do pliku.
*/
void addClient(FILE *file, struct list_node **list){

    struct klienci d;
   /* printf("Podaj numer karty: ");
    scanf("%d",&d.numer_karty);*/
    printf("Podaj imie: ");
    scanf(" %[^\n]s",d.imie);
    printf("Podaj nazwisko: ");
    scanf(" %[^\n]s",d.nazwisko);
    printf("Podaj numer telefonu: ");
    scanf("%d",&d.numer_telefonu);
    printf("Podaj email: ");
    scanf(" %[^\n]s",d.email);


    saveDataKlienci(d,file,list);
}


/*! \brief Funkcja nadpisuje plik z klientami
*         Parametrami funkcji jest sciezka do pliku klientow oraz wskaznik na liste z klientami
*
*\n Funkcja wykorzystywana jest podczas usuwania klientow.
*/
void overwriteKlienci(FILE *file, struct list_node **list_pointer){

    int status = remove("klienci.dat");
    file = fopen("klienci.dat","a+");

    if (file == NULL)
    {
        fprintf(stderr, "\nBlad podczas otwierania pliku\n");
        exit (1);
    }

    add_list_to_file(file,*list_pointer);

    if(fwrite != 0)
        printf("Zapisano poprawnie do pliku!\n");
    else
        printf("Blad podczas zapisywania do pliku!\n");

    // close file
    fclose (file);
}

/*! \brief Funkcja usuwa klienta
*         Parametrami funkcji jest sciezka do pliku klientow oraz wskaznik na liste z klientami
*
*\n Funkcja po usunieciu klienta wykorzystuje funkcje nadpisujaca plik z danymi klientow
*/
void deleteKlienci(FILE *file,struct list_node **list){

    int id_num=0;
    printf("\nPodaj numer karty klienta do usuniecia: ");
    scanf("%d",&id_num);
    *list = delete_node(*list,id_num);
    overwriteKlienci(file,list);
}

/*! \brief Funkcja odczytuje dane klientow z pliku
*         Parametry funkcji to sciezka do pliku klientow oraz wskaznik na liste z klientami
*
*\n Funkcja sprawdza czy plik zostal poprawnie otwarty, jesli nie wyswietla jednoznaczny komunikat
*/
void readDataKlienci(FILE *file, struct list_node **list){

    struct klienci k;
    file = fopen ("klienci.dat", "r");

    if (file == NULL){
        //create file
        file = fopen ("klienci.dat", "w");


        if (file == NULL){
            fprintf(stderr, "\nBlad podczas otwierania pliku\n");
            exit (1);
        }

        fclose (file);

        file = fopen ("klienci.dat", "r");

        if (file == NULL){
            fprintf(stderr, "\nBlad podczas otwierania pliku\n");
            exit (1);
        }

    }

    // read file contents till end of file
    while(fread(&k, sizeof(struct klienci), 1, file))
    {
        if(*list == NULL)
            *list = create_list_from_file(k);
        else
            *list = read_node_from_file(*list,k);
    }
    // close file
    fclose (file);

    // *list = add_node(*list,m);

}



