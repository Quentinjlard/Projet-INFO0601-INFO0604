/**
 * @file tableAdressage.c
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2023-02-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "tableAdressage.h"

#define N 20

// Création table d'adressage
void creation_table(tableAdressage_t *table)
{
    table = (tableAdressage_t *)malloc(sizeof(tableAdressage_t));
    memset(table->adresse, 0, sizeof(table->adresse));
}

// Supprimer table d'adressage
void supprimer_table_adressage(tableAdressage_t *table, int index)
{
    table->adresse[index] = 0;
}

// Lecture table d'adressage'
off_t lire_table_adressage(tableAdressage_t *table, int index)
{
    return table->adresse[index];
}

// Affichage table d'adressage
void affichage_table_adressage(tableAdressage_t *table)
{
    for (int i = 0; i < N; i++)
    {
        printf("Adresse %d: %ld\n", i, table->adresse[i]);
    }
}
