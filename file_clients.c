//
// Created by HP on 2019-04-20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node_list.h"


/*struct klienci {
    int numer_karty;
    char imie[27];
    char nazwisko[27];
    int numer_telefonu;
    char email[50];
};*/

void addClient(struct klienci *d){
    printf("Podaj numer karty: ");
    scanf("%d",&d->numer_karty);
    printf("Podaj imie: ");
    scanf("%s",d->imie);
    printf("Podaj nazwisko: ");
    scanf("%s",d->nazwisko);
    printf("Podaj numer telefonu: ");
    scanf("%d",&d->numer_telefonu);
    printf("Podaj email: ");
    scanf("%s",d->email);

}

void saveDataKlienci(struct klienci *d,FILE *file){
    fprintf(file,"%d|",d->numer_karty);
    fprintf(file,"%s|",d->imie);
    fprintf(file,"%s|",d->nazwisko);
    fprintf(file,"%d|",d->numer_telefonu);
    fprintf(file,"%s\n",d->email);
}

void readDataKlienci(FILE *file, struct list_node **list){
    char tab[100];
    printf("Odczyt danych:\n");
    while(!feof(file))
    {
        fgets(tab,100,file);
        printf("%s\n",tab);
        memset(tab,0,100);
    }

    struct klienci m;
    m.numer_karty = 1;
    strcpy( m.imie, "Sara" );
    strcpy( m.nazwisko, "Sara" );
    m.numer_telefonu = 1234;
    strcpy( m.email, "Sara@" );

    *list = add_node(*list,m);

}



