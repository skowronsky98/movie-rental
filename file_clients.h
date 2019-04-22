//
// Created by HP on 2019-04-20.
//

#ifndef PPPROJEKT_FILE_CLIENTS_H
#define PPPROJEKT_FILE_CLIENTS_H

#include "node_list.h"

struct klienci {
    int numer_karty;
    char imie[27];
    char nazwisko[27];
    int numer_telefonu;
    char email[50];
};

void addClient(struct klienci *d);
void saveDataKlienci(struct klienci *d,FILE *file);
void readDataKlienci(FILE *file, struct list_node**);


#endif //PPPROJEKT_FILE_CLIENTS_H
