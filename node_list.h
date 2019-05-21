//
// Created by HP on 2019-04-20.
//

#ifndef PPPROJEKT_NODE_LIST_H
#define PPPROJEKT_NODE_LIST_H

struct klienci {
    int numer_karty;
    char imie[27];
    char nazwisko[27];
    int numer_telefonu;
    char email[50];
};

struct list_node;

extern struct list_node *create_list(struct klienci);
extern struct list_node *add_node(struct list_node*,struct klienci);
extern struct list_node *delete_node(struct list_node*, int);
extern void print_list(struct list_node*);
void add_list_to_file(FILE *, struct list_node *);
extern void remove_list(struct list_node**);
int print_node(struct list_node *, int);

void readDataKlienci(FILE *file, struct list_node**);
void addClient(FILE *,struct list_node **);
void deleteKlienci(FILE *file ,struct list_node**);
void overwriteKlienci(FILE *file, struct list_node **list_pointer);

void edit_list(FILE *file, struct list_node **list_pointer, int id, int field, struct list_node *);
void sort_by_phone_number(struct list_node *);



struct filmy {
    int id_filmu;
    char tytul[27];
    int rok;
    char rezyser[27];
    char gatunek[27];
    int liczba_egzemplarzy;
    int liczba_wypozyczonych;
};


struct list_node_movie;

extern struct list_node_movie *create_list_movie(struct filmy);
extern struct list_node_movie *add_node_movie(struct list_node_movie*,struct filmy);
extern struct list_node_movie *delete_node_movie(struct list_node_movie*, int);
extern void print_list_movie(struct list_node_movie*);
void add_list_movie_to_file(FILE *, struct list_node_movie *);
extern void remove_list_movie(struct list_node_movie**);
int print_node_movie(struct list_node_movie *, int);


void addMovie(FILE *, struct list_node_movie **);
void readDataFilmy (FILE *file,struct list_node_movie**);
void deleteFilmy(FILE *file ,struct list_node_movie**);

void overwriteFilmy(FILE *file, struct list_node_movie **list);
void edit_list_movie(FILE *file, struct list_node_movie **list_pointer, int id, int field, struct list_node_movie *);


#endif //PPPROJEKT_NODE_LIST_H
