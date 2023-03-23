#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

// Structure pour la table d'adresses
typedef struct
{
    off_t adresses[N]; // Tableau des adresses
    int size[N];       // Taille de la table
} tableAdresse;

tableAdresse *creer_table();

void supprimer_table(tableAdresse *);

void lire_table(FILE *, tableAdresse *);

void ecrire_table(FILE *, tableAdresse *);

void afficher_table(tableAdresse *);

void ajouter_entree(tableAdresse *, off_t, size_t);

void supprimer_entree(tableAdresse *, off_t);
