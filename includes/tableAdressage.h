/**
 * @file tableAdressage.h
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2023-02-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __TableAdressage_H__
#define __TableAdressage_H__

#include "includeAll.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define N 20

// Structure d'une table d'adressage
typedef struct
{
    off_t adresse[N];
} tableAdressage_t;

void creation_table(tableAdressage_t *);

void supprimer_table_adressage(tableAdressage_t *table, int index);

off_t lire_table_adressage(tableAdressage_t *table, int index);

void affichage_table_adressage(tableAdressage_t *table);

#endif
