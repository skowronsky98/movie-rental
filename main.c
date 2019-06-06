#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "node_list.h"

int main()
{
    FILE *file_klienci;
    struct list_node *list = NULL;
    readDataKlienci(file_klienci,&list);

    FILE *file_filmy;
    struct list_node_movie *list_movie = NULL;
    readDataFilmy(file_filmy,&list_movie);

    FILE *file_rental;
    struct list_node_rental *list_rental = NULL;
    readDataRental(file_rental,&list_rental);

    int operacja,editklient,editmovie,editrental,fieldklient,fieldmovie;
    int menu;
    while (menu != 0 ){
        printf("Spis tresci:\n");
        printf("1. Klienci\n");
        printf("2. Filmy\n");
        printf("3. Wypozyczenia\n");
        printf("0. Wyjscie\n");
        printf("Twoj wybor: ");
        scanf("%d",&menu);

        switch (menu) {
            case 1:
                printf("\n1. Dodaj Klienta\n");
                printf("2. Usun Klienta\n");
                printf("3. Edytuj Klienta\n");
                printf("4. Wypisz liste klientow\n\n");
                printf("Twoj wybor: ");
                scanf("%d",&operacja);

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
                                printf("0: Cofnij\n");
                                printf("Wybor: ");

                                scanf("%d",&fieldklient);

                                //zakres
                                if(fieldklient > 0 && fieldklient < 6)
                                    edit_list(file_klienci,&list,editklient,fieldklient,list);

                            }
                            break;
                        case 4:
                            print_list(list);
                            break;
                        default:printf("Wybrano inna opcje\n");
                    }

            break;



            case 2:
                printf("\n1. Dodaj film\n");
                printf("2. Usun film\n");
                printf("3. Edytuj film\n");
                printf("4. Wypisz liste filmow\n");
                printf("5. Sortuj filmy\n");
                printf("6. Szukaj filmu\n\n");
                printf("Twoj wybor:");
                scanf("%d",&operacja);

                    switch (operacja) {
                        case 1:
                            addMovie(file_filmy, &list_movie);
                            break;
                        case 2:
                            deleteFilmy(file_filmy, &list_movie);
                            break;
                        case 3:
                            printf("Podaj id filmu ktory chcesz edytowac: ");
                            scanf("%d", &editmovie);

                            if (print_node_movie(list_movie, editmovie) == 1) {
                                printf("\nPodaj numer pola ktore chcesz edytowac:\n");
                                printf("1: Id Filmu\n");
                                printf("2: Tytul\n");
                                printf("3: Rok\n");
                                printf("4: Rezyser\n");
                                printf("5: Gatunek\n");
                                printf("6: Liczba egzemplarzy\n");
                                printf("7: Liczba wypozyczonych\n");
                                printf("0: Cofnij\n");
                                printf("Wybor: ");
                                scanf("%d", &fieldmovie);

                                if (fieldmovie > 0 && fieldmovie < 8)
                                    edit_list_movie(file_filmy, &list_movie, editmovie, fieldmovie, list_movie);
                            }

                            break;
                        case 4:
                            print_list_movie(list_movie);
                            break;
                        case 5:
                            sort_by_name(list_movie);
                            break;
                        case 6:
                            printf("Podaj tyttul filmu: ");
                            char pattern[] = {0};
                            scanf(" %[^\n]s", pattern);
                            search_movie(pattern, list_movie);
                            break;
                        default:
                            printf("Wybrano inna opcje\n\n");
                    }
            break;

            case 3:
                printf("\n1. Dodaj wypozyczenie\n");
                printf("2. Usun z listy wypo\n");
                printf("3. Oddaj film\n");
                printf("4. Wyswietl liste kar\n");
                printf("5. Wyswietl wypozyczenia\n\n");
                printf("Twoj wybor: ");
                scanf("%d",&operacja);

                    switch (operacja){
                        case 1:
                            addRental(file_rental, &list_rental,list,list_movie);
                            break;
                        case 2:
                            deleteRental(file_rental,&list_rental);
                            break;
                        case 3:
                            printf("Podaj id clienta ktory oddal film: ");
                            scanf("%d",&editrental);
                            edit_list_rental(file_rental,&list_rental,editrental,list_rental);
                            break;
                        case 4:
                            calculate_fee(list_rental);
                            break;
                        case 5:
                            print_list_rental(list_rental);
                            break;
                    }
            break;
            case 0: printf("\nKoniec programu\n\n");
            break;
            default: printf("\nWybrano inna opcje\n\n");
        }


    }

        /* while(operacja != 0) {
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
        printf("10. Szukaj filmu\n\n");
        printf("11. Dodaj wypozyczenie\n");
        printf("12. Usun z listy wypo\n");
        printf("13. Oddal film\n");
        printf("14. Wyswietl liste kar\n");
        printf("15. Wyswietl liste wypo\n");
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
                    printf("0: Cofnij\n");
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
                    printf("0: Cofnij\n");
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
                char pattern[] = {0};
                scanf(" %[^\n]s",pattern);

                search_movie(pattern, list_movie);

                break;

            case 11:
                addRental(file_rental, &list_rental,list,list_movie);

                break;

            case 12:
                deleteRental(file_rental,&list_rental);
                break;

            case 13:
                printf("Podaj id clienta ktory oddal film: ");
                scanf("%d",&editrental);
                edit_list_rental(file_rental,&list_rental,editrental,list_rental);
                break;

            case 14:
                calculate_fee(list_rental);
                break;

            case 15:
                print_list_rental(list_rental);
                break;

            case 0:
                printf("\nKoniec programu");
                break;
            default:
                printf("\nNiepoprawny wybor\n");

        }
    }
*/
    remove_list(&list);
    remove_list_movie(&list_movie);
    remove_list_rental(&list_rental);

    return 0;
}

