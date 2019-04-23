//
// Created by HP on 2019-04-20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node_list.h"

void addClient(FILE *file, struct list_node **list){

    struct klienci d;
    printf("Podaj numer karty: ");
    scanf("%d",&d.numer_karty);
    printf("Podaj imie: ");
    scanf("%s",d.imie);
    printf("Podaj nazwisko: ");
    scanf("%s",d.nazwisko);
    printf("Podaj numer telefonu: ");
    scanf("%d",&d.numer_telefonu);
    printf("Podaj email: ");
    scanf("%s",d.email);

    saveDataKlienci(d,file,list);
}

void saveDataKlienci(struct klienci d,FILE *file, struct list_node **list){

    file = fopen("klienci.dat","a+");

    if (file == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }
    // write struct to file
    fwrite (&d, sizeof(struct klienci), 1, file);
    // add element to list
    *list = add_node(*list,d);

    if(fwrite != 0)
        printf("contents to file written successfully !\n");
    else
        printf("error writing file !\n");

    // close file
    fclose (file);
}

void deleteKlienci(struct klienci d,FILE *file,struct list_node **list){

    int id_num=0;
    printf("\nPodaj numer karty klienta do usuniecia: ");
    scanf("%d",&id_num);
    delete_node(*list,id_num);
    overwriteKlienci(d,file,list);
}
void overwriteKlienci(struct klienci d,FILE *file, struct list_node **list){

    file = fopen("klienci.dat","w");

    if (file == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }
    // overwrite struct to file
    fwrite (&d, sizeof(struct klienci), 1, file);

    if(fwrite != 0)
        printf("contents to file overwritten successfully !\n");
    else
        printf("error overwriting file !\n");

    // close file
    fclose (file);
}

void readDataKlienci(FILE *file, struct list_node **list){

    struct klienci k;
    file = fopen ("klienci.dat", "r");

    if (file == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // read file contents till end of file
    while(fread(&k, sizeof(struct klienci), 1, file))
    {
        *list = add_node(*list,k);
    }
    // close file
    fclose (file);

    // *list = add_node(*list,m);

}



