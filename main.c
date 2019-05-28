#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node_list.h"

int main()
{
    FILE *file_klienci;
    struct list_node *list = NULL;
    readDataKlienci(file_klienci,&list);

    FILE *file_filmy;
    struct list_node_movie *list_movie = NULL;
    readDataFilmy(file_filmy,&list_movie);

    int operacja,editklient,editmovie,fieldklient,fieldmovie;

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
        printf("9. Sortuj filmy\n");
        printf("10. Szukaj filmu\n");
        printf("0 - Koniec programu\n\n");
        printf("Wybor: ");
        scanf("%d", &operacja);

        switch (operacja) {

            case 1:
                addClient(file_klienci, &list);
                break;
            case 2:
                deleteKlienci(file_klienci,&list);
                break;
            case 3:
                printf("Podaj numer karty klienta ktorego chcesz edytowac: ");
                scanf("%d",&editklient);

                if(print_node(list,editklient) == 1)
                {
                    printf("\nPodaj numer pola ktore chcesz edytowac:\n");
                    printf("1: Numer karty\n");
                    printf("2: Imie\n");
                    printf("3: Nazwisko\n");
                    printf("4: Numer Telefonu\n");
                    printf("5: Email\n");
                    printf("Wybor: ");

                    scanf("%d",&fieldklient);

                    //zakres
                    if(fieldklient > 0 && fieldklient < 6)
                        edit_list(file_klienci,&list,editklient,fieldklient,list);

                }


                //      TUTAJ FUNKCJA EDYTUJACA
                break;
            case 4:
                print_list(list);
                break;
            case 5:
                addMovie(file_filmy,&list_movie);
                break;
            case 6:
                deleteFilmy(file_filmy,&list_movie);
                break;
            case 7:
                printf("Podaj id filmu ktory chcesz edytowac: ");
                scanf("%d",&editmovie);

                if(print_node_movie(list_movie,editmovie) == 1)
                {
                    printf("\nPodaj numer pola ktore chcesz edytowac:\n");
                    printf("1: Id Filmu\n");
                    printf("2: Tytul\n");
                    printf("3: Rok\n");
                    printf("4: Rezyser\n");
                    printf("5: Gatunek\n");
                    printf("6: Liczba egzemplarzy\n");
                    printf("7: Liczba wypozyczonych\n");
                    printf("Wybor: ");
                    scanf("%d",&fieldmovie);

                    if(fieldmovie> 0 && fieldmovie < 8)
                        edit_list_movie(file_filmy,&list_movie,editmovie,fieldmovie,list_movie);
                }

                //      TUTAJ FUNKCJA EDYTUJACA
                break;
            case 8:
                print_list_movie(list_movie);
                break;
            case 9:
                sort_by_name(list_movie);
                //sort_by_phone_number(list);
                break;
            case 10:
                printf("Podaj tyttul filmu: ");
                char pattern[] = {NULL};
                scanf(" %[^\n]s",pattern);

                search_movie(pattern, list_movie);

                break;
            case 0:
                printf("\nKoniec programu");
                break;
            default:
                printf("\nNiepoprawny wybor\n");

        }
    }
    remove_list(&list);
    remove_list_movie(&list_movie);

    return 0;
}

