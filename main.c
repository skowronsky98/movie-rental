#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node_list.h"
#include "movies.h"

int main()
{
    struct klienci k;
    k.numer_karty = 0;
    strcpy( k.imie, "imie" );
    strcpy( k.nazwisko, "nazwisko" );
    k.numer_telefonu = 0;
    strcpy( k.email, "@" );

    FILE *file_klienci;
    struct list_node *list = create_list(k);
    readDataKlienci(file_klienci,&list);

    FILE *plik2;
    plik2 = fopen("filmy.txt","a+");
    struct filmy f[10];


    int operacja;

    char exit;
    do {
        printf("Spis tresci:\n");
        printf("1. Dodaj Klienta\n");
        printf("2. Usun Klienta\n");
        printf("3. Edytuj Klienta\n");
        printf("4. Wypisz liste klientow\n\n");
        printf("5. Dodaj film\n");
        printf("6. Usun film\n");
        printf("7. Edytuj film\n");
        printf("8. Wypisz liste filmow\n");
        printf("q - Koniec programu\n\n");
        printf("Wybor: ");
        scanf("%d", &operacja);

        exit = getchar();
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
                addMovie(&f[0]);
                saveDataFilmy(&f, plik2);
                break;
            case 6:
                //cos
            case 7:
                //cos
            case 8:
                fseek(plik2, 0, SEEK_SET);
                readDataFilmy(plik2);
                break;

        }

    } while(exit != 'q');

    remove_list(&list);
    fclose(plik2);

    return 0;
}

