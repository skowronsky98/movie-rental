#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "node_list.h"

void saveDataRental(struct rental d, FILE *file, struct list_node_rental **list){

    file = fopen("rental.dat","a+");

    if (file == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }
    // write struct to file
    fwrite (&d, sizeof(struct rental), 1, file);
    // add element to list
    if(*list == NULL)
        *list = create_list_rental(d);
    else
        *list = add_node_rental(*list,d);

    if(fwrite != 0)
        printf("contents to file written successfully !\n");
    else
        printf("error writing file !\n");

    // close file
    fclose (file);
}

void addRental(FILE *file, struct list_node_rental **list, struct list_node *list_client, struct list_node_movie *list_movie){

    struct rental d;
    printf("Podaj numer karty klienta: ");
    scanf("%d",&d.id_client);
    while (check_id(list_client,d.id_client) == -1)
    {
        printf("Klient nie istnieje podaj id klienta: ");
        scanf("%d",&d.id_client);
    }


    printf("Podaj id filmu: ");
    scanf("%d",&d.id_movie);
    while (check_id_movie(list_movie,d.id_movie) == -1)
    {
        printf("Film nie istnieje podaj id filmu: ");
        scanf("%d",&d.id_movie);
    }

    d.day = 0;
    d.month = 0;
    d.year = 0;

    d.day_r = 0;
    d.month_r = 0;
    d.year_r = 0;

    saveDataRental(d,file,list);
}

void overwriteRental(FILE *file, struct list_node_rental **list){

    int status = remove("rental.dat");
    file = fopen("rental.dat","a+");


    if (file == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }

    add_list_rental_to_file(file,*list);

    if(fwrite != 0)
        printf("contents to file overwritten successfully !\n");
    else
        printf("error overwriting file !\n");

    // close file
    fclose (file);
}

void deleteRental(FILE *file,struct list_node_rental **list){

    int id_num=0;
    printf("\nPodaj numer klienta do usuniecia: ");
    scanf("%d",&id_num);
    *list = delete_node_rental(*list,id_num);
    overwriteRental(file,list);
}

void readDataRental(FILE *file,struct list_node_rental **list){

    struct rental f;
    file = fopen("rental.dat","r");

    if (file == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
        exit (1);
    }

    // read file contents till end of file
    while(fread(&f, sizeof(struct rental), 1, file))
    {
        if(*list == NULL)
            *list = create_list_rental(f);
        else
            *list = add_node_rental(*list,f);
    }
    // close file
    fclose (file);


}
