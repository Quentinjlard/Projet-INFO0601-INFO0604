/**
 * @file fichier_map.h
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2023-01-31
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __FILE_MAP_H__
#define __FILE_MAP_H__

#include "includeAll.h"

#define HEIGHT 22
#define WIDTH 62

typedef struct fileMap_type
{
    off_t map[HEIGHT][WIDTH];
    off_t debut;
} fileMap_t;

/**
 * @brief Create a fileMap object
 *
 * @return fileMap_t
 */
fileMap_t *create_fileMap();

/**
 * @brief Add a intem on the fileMap
 *
 * @param fileMap
 * @param fileName
 * @param posX
 * @param posY
 * @param item
 *
 */
void add_item_fileMap(int, int, int, int);

/**
 * @brief remove an item from the fileMap
 *
 * @param fileMap
 * @param posX
 * @param posY
 *
 * @return fileMap_t
 */
void remove_item_fileMap(fileMap_t *, int, int);
/**
 * @brief remove all items from the fileMap
 *
 * @param fileMap
 * @param posX
 * @param posY
 *
 * @return off_t
 */
off_t read_fileMap(fileMap_t *, int, int);

/**
 * @brief
 *
 * @param fileMap
 */
void display_fileMap(fileMap_t *);

void init_fileMap(int);

void add_lseek(int, char);

void remove_lseek(int);

#endif
