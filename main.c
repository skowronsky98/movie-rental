#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node_list.h"

int main()
{
    struct klienci k;
    k.numer_karty = 0;
    strcpy( k.imie, "imie" );
    strcpy( k.nazwisko, "nazwisko" );
    k.numer_telefonu = 0;
    strcpy( k.email, "@" );

    struct filmy f;
    f.id_filmu = 0;
    strcpy( f.tytul, "tytul" );
    f.rok = 0;
    strcpy( f.rezyser, "rez" );
    strcpy( f.gatunek, "gat" );
    f.liczba_egzemplarzy= 0;
    f.liczba_wypozyczonych= 0;

    FILE *file_klienci;
    struct list_node *list = create_list(k);
    readDataKlienci(file_klienci,&list);

    FILE *file_filmy;
    struct list_node_movie *list_movie = create_list_movie(f);
    readDataFilmy(file_filmy,&list_movie);


    int operacja;

    while(operacja != 0) {
        printf("Spis tresci:\n");
        printf("1. Dodaj Klienta\n");
        printf("2. Usun Klienta\n");
        printf("3. Edytuj Klienta\n");
        printf("4. Wypisz liste klientow\n\n");
        printf("5. Dodaj film\n");
        printf("6. Usun film\n");
        printf("7. Edytuj film\n");
        printf("8. Wypisz liste filmow\n");
        printf("0 - Koniec programu\n\n");
        printf("Wybor: ");
        scanf("%d", &operacja);

        switch (operacja) {

            case 1:
                addClient(file_klienci, &list);
                break;
            case 2:
                // cos
                break;
            case 3:
                //cos
                break;
            case 4:
                print_list(list);
                break;
            case 5:
                addMovie(file_filmy,&list_movie);
                break;
            case 6:
                //cos
            case 7:
                //cos
            case 8:
                print_list_movie(list_movie);
                break;

        }

    }
    remove_list(&list);
    remove_list_movie(&list_movie);

    return 0;
}

