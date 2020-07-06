#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "node_list.h"

/*! \brief Funkcja zapisujaca dane wypozyczen do pliku
*         Parametry to struktura wypozyczen, sciezka do pliku oraz wskaznik na liste z wypozyczeniami
*
*/
void saveDataRental(struct rental d, FILE *file, struct list_node_rental **list){

    file = fopen("rental.dat","a+");

    if (file == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }
    // write struct to file
    fwrite (&d, sizeof(struct rental), 1, file);
    // add element to list
    if(*list == NULL)
        *list = create_list_rental(d);
    else
        *list = add_node_rental(*list,d);

    if(fwrite != 0)
        printf("contents to file written successfully !\n");
    else
        printf("error writing file !\n");

    // close file
    fclose (file);
}

/*! \brief Funkcja dodajace wypozyczenie
*         Parametry to sciezka do pliku, wskaznik na liste z wypozyczeniami, wskaznik na liste z klientami oraz wskaznik na liste z filmami
*
*/
void addRental(FILE *file, struct list_node_rental **list, struct list_node *list_client, struct list_node_movie *list_movie){

    struct rental d;
    printf("Podaj numer karty klienta: ");
    scanf("%d",&d.id_client);
    while (check_id(list_client,d.id_client) == -1)
    {
        printf("Klient nie istnieje podaj id klienta: ");
        scanf("%d",&d.id_client);
    }


    printf("Podaj id filmu: ");
    scanf("%d",&d.id_movie);
    while (check_id_movie(list_movie,d.id_movie) == -1)
    {
        printf("Film nie istnieje podaj id filmu: ");
        scanf("%d",&d.id_movie);
    }

    printf("Podaj dzien wypozyczenia: ");
    scanf("%d",&d.day);

    printf("Podaj miesiac wypozyczenia: ");
    scanf("%d",&d.month);

    printf("Podaj rok wypozyczenia: ");
    scanf("%d",&d.year);

    d.day_r = 0;
    d.month_r = 0;
    d.year_r = 0;

    saveDataRental(d,file,list);
}

/*! \brief Funkcja nadpisujaca zawartosc pliku z wypozyczeniami
*         Parametry to sciezka do pliku oraz wskaznik na liste z wypozyczeniami
*
*/
void overwriteRental(FILE *file, struct list_node_rental **list){

    int status = remove("rental.dat");
    file = fopen("rental.dat","a+");


    if (file == NULL)
    {
        fprintf(stderr, "\nBlad podczas otwierania pliku\n");
        exit (1);
    }

    add_list_rental_to_file(file,*list);

    if(fwrite != 0)
        printf("Zapisano poprawnie do pliku!\n");
    else
        printf("Blad podczas zapisywania do pliku!\n");

    // close file
    fclose (file);
}

/*! \brief Funkcja usuwajaca wskazane wypozyczenie
*         Parametry to sciezka do pliku oraz wskaznik na liste z wypozyczeniami
*
*\n Funkcja pyta o numer klienta do usuniecia a nastepnie nadpisuje zawartosc pliku po usunieciu
*/
void deleteRental(FILE *file,struct list_node_rental **list){

    int id_num=0;
    printf("\nPodaj numer klienta do usuniecia: ");
    scanf("%d",&id_num);
    *list = delete_node_rental(*list,id_num);
    overwriteRental(file,list);
}

/*! \brief Funkcja odczytujaca dane z wypozyczeniami
*         Parametry funkcji to sciezka do pliku oraz wskaznik na liste z wypozyczeniami
*
*/
void readDataRental(FILE *file,struct list_node_rental **list){

    struct rental f;
    file = fopen("rental.dat","r");

    if (file == NULL){
        //create file
        file = fopen ("rental.dat", "w");


        if (file == NULL){
            fprintf(stderr, "\nBlad podczas otwierania pliku\n");
            exit (1);
        }

        fclose (file);

        file = fopen ("rental.dat", "r");

        if (file == NULL){
            fprintf(stderr, "\nBlad podczas otwierania pliku\n");
            exit (1);
        }

    }

    // read file contents till end of file
    while(fread(&f, sizeof(struct rental), 1, file))
    {
        if(*list == NULL)
            *list = create_list_rental(f);
        else
            *list = add_node_rental(*list,f);
    }
    // close file
    fclose (file);


}
