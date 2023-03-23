

#ifndef __TableAdressage_H__
#define __TableAdressage_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20

typedef struct TableAdressage_struct
{
    off_t adresse[N];
} TableAdressage_s;

/**
 * @brief
 *
 * @return TableAdressage_s*
 */
TableAdressage_s *creation_table();

/**
 * @brief
 *
 * @param table
 * @param addresse
 * @param index
 */
void ajout_table_adressage(TableAdressage_s *table, off_t addresse, int index);

/**
 * @brief
 *
 * @param table
 * @param index
 */
void supprimer_table_adressage(TableAdressage_s *table, int index);

/**
 * @brief
 *
 * @param table
 * @param index
 * @return off_t
 */
off_t lire_table_adressage(TableAdressage_s *table, int index);

/**
 * @brief
 *
 * @param table
 */
void affichage_table_adressage(TableAdressage_s *table);

#endif
