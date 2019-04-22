#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node_list.h"
#include "file_clients.h"
#include "movies.h"




int main()
{
    struct klienci k,m;
    k.numer_karty = 3;
    strcpy( k.imie, "Sara" );
    strcpy( k.nazwisko, "Sara" );
    k.numer_telefonu = 1234;
    strcpy( k.email, "Sara@" );




    struct list_node *list = create_list(k);


    struct klienci d[10];
    struct filmy f[10];
    int operacja;

    FILE *plik1;
    plik1 = fopen("klienci.txt","a+");
    FILE *plik2;
    plik2 = fopen("filmy.txt","a+");

    printf("Spis tresci:\n");
    printf("1. Dodaj Klienta\n");
    printf("2. Usun Klienta\n");
    printf("3. Edytuj Klienta\n");
    printf("4. Wypisz liste klientow\n\n");
    printf("5. Dodaj film\n");
    printf("6. Usun film\n");
    printf("7. Edytuj film\n");
    printf("8. Wypisz liste filmow\n\n");
    printf("Wybor: ");
    scanf("%d",&operacja);

    switch (operacja){

        case 1:
            addClient(&d[0]);
            saveDataKlienci(&d,plik1);
            break;
        case 2:
            // cos
            break;
        case 3:
            //cos
            break;
        case 4:
            fseek(plik1,0,SEEK_SET);
            readDataKlienci(plik1,&list);
            print_list(list);
            break;
        case 5:
            addMovie(&f[0]);
            saveDataFilmy(&f,plik2);
            break;
        case 6:
            //cos
        case 7:
            //cos
        case 8:
            fseek(plik2,0,SEEK_SET);
            readDataFilmy(plik2);
            break;
    }

    remove_list(&list);
    fclose(plik1);
    fclose(plik2);

    return 0;
}

