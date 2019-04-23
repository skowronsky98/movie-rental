//
// Created by exeve on 20.04.2019.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node_list.h"

void saveDataFilmy(struct filmy d, FILE *file, struct list_node_movie **list){

    file = fopen("filmy.dat","a+");

    if (file == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }
    // write struct to file
    fwrite (&d, sizeof(struct filmy), 1, file);
    // add element to list
    if(*list == NULL)
        *list = create_list_movie(d);
    else
        *list = add_node_movie(*list,d);

    if(fwrite != 0)
        printf("contents to file written successfully !\n");
    else
        printf("error writing file !\n");

    // close file
    fclose (file);
}

void addMovie(FILE *file, struct list_node_movie **list){

    struct filmy d;
    printf("Podaj id filmu: ");
    scanf("%d",&d.id_filmu);
    printf("Podaj tytul: ");
    scanf("%s",d.tytul);
    printf("Podaj rok produkcji: ");
    scanf("%d",&d.rok);
    printf("Podaj rezysera: ");
    scanf("%s",d.rezyser);
    printf("Podaj gatunek: ");
    scanf("%s",d.gatunek);
    printf("Podaj ilosc egzemplarzy: ");
    scanf("%d",&d.liczba_egzemplarzy);
    printf("Podaj ilosc wypozyczonych: ");
    scanf("%d",&d.liczba_wypozyczonych);

    saveDataFilmy(d,file,list);
}

void overwriteFilmy(FILE *file, struct list_node_movie **list){

    int status = remove("filmy.dat");
    file = fopen("filmy.dat","a+");


    if (file == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }

    add_list_movie_to_file(file,*list);

    if(fwrite != 0)
        printf("contents to file overwritten successfully !\n");
    else
        printf("error overwriting file !\n");

    // close file
    fclose (file);
}


void deleteFilmy(FILE *file,struct list_node_movie **list){

    int id_num=0;
    printf("\nPodaj numer filmu do usuniecia: ");
    scanf("%d",&id_num);
    *list = delete_node_movie(*list,id_num);
    overwriteFilmy(file,list);
}


void readDataFilmy(FILE *file,struct list_node_movie **list){

    struct filmy f;
    file = fopen("filmy.dat","r");

    if (file == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // read file contents till end of file
    while(fread(&f, sizeof(struct filmy), 1, file))
    {
        if(*list == NULL)
            *list = create_list_movie(f);
        else
            *list = add_node_movie(*list,f);
    }
    // close file
    fclose (file);


}