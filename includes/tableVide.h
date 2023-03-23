
#ifndef __TableVide_H__
#define __TableVide_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20

typedef struct TableVide_struct
{
    off_t debut[N];
    int taille[N];
} TableVide_s;

/**
 * @brief
 *
 * @return TableVide_s*
 */
TableVide_s *creation_table_vide();

/**
 * @brief
 *
 * @param table
 * @param debut
 * @param taille
 * @param index
 */
void ajout_table_vide(TableVide_s *table, off_t debut, off_t taille, int index);

/**
 * @brief
 *
 * @param table
 * @param index
 */
void supprimer_table_vide(TableVide_s *table, int index);

/**
 * @brief
 *
 * @param table
 * @param index
 * @return off_t
 */
off_t lire_table_vide(TableVide_s *table, int index);

/**
 * @brief
 *
 * @param table
 */
void affichage_table_vide(TableVide_s *table);

#endif