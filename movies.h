//
// Created by exeve on 20.04.2019.
//

#ifndef PPPROJEKT_MOVIES_H
#define PPPROJEKT_MOVIES_H

struct filmy {
    int id_filmu;
    char tytul[27];
    int rok;
    char rezyser[27];
    char gatunek[27];
    int liczba_egzemplarzy;
    int liczba_wypozyczonych;
};

void addMovie(struct filmy *d);
void saveDataFilmy (struct filmy *d,FILE *file);
void readDataFilmy (FILE *file);


#endif //PPPROJEKT_MOVIES_H
