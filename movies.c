//
// Created by exeve on 20.04.2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movies.h"

void addMovie(struct filmy *d){
    printf("Podaj id filmu: ");
    scanf("%d",&d->id_filmu);
    printf("Podaj tytul: ");
    scanf("%s",d->tytul);
    printf("Podaj rok produkcji: ");
    scanf("%d",&d->rok);
    printf("Podaj rezysera: ");
    scanf("%s",d->rezyser);
    printf("Podaj gatunek: ");
    scanf("%s",d->gatunek);
    printf("Podaj ilosc egzemplarzy: ");
    scanf("%d",&d->liczba_egzemplarzy);
    printf("Podaj ilosc wypozyczonych: ");
    scanf("%d",&d->liczba_wypozyczonych);

}

void saveDataFilmy(struct filmy *d,FILE *file){
    fprintf(file,"%d|",d->id_filmu);
    fprintf(file,"%s|",d->tytul);
    fprintf(file,"%d|",d->rok);
    fprintf(file,"%s|",d->rezyser);
    fprintf(file,"%s|",d->gatunek);
    fprintf(file,"%d|",d->liczba_egzemplarzy);
    fprintf(file,"%d\n",d->liczba_wypozyczonych);
}

void readDataFilmy(FILE *file){
    char tab[100];
    printf("Odczyt danych:\n");
    int i=1;
    while(!feof(file))
    {
        fgets(tab,100,file);
        i++;
        printf("%s\n",tab);
        memset(tab,0,100);
    }
}