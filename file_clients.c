//
// Created by HP on 2019-04-20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node_list.h"

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
    if(*list == NULL)
        *list = create_list(d);
    else
        *list = add_node(*list,d);

    if(fwrite != 0)
        printf("contents to file written successfully !\n");
    else
        printf("error writing file !\n");

    // close file
    fclose (file);
}

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



void overwriteKlienci(FILE *file, struct list_node **list_pointer){

    int status = remove("klienci.dat");
    file = fopen("klienci.dat","a+");

    if (file == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }

    add_list_to_file(file,*list_pointer);

    if(fwrite != 0)
        printf("contents to file overwritten successfully !\n");
    else
        printf("error overwriting file !\n");

    // close file
    fclose (file);
}

void deleteKlienci(FILE *file,struct list_node **list){

    int id_num=0;
    printf("\nPodaj numer karty klienta do usuniecia: ");
    scanf("%d",&id_num);
    *list = delete_node(*list,id_num);
    overwriteKlienci(file,list);
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
        if(*list == NULL)
            *list = create_list(k);
        else
            *list = add_node(*list,k);
    }
    // close file
    fclose (file);

    // *list = add_node(*list,m);

}



