/**
 * @file fichier_map.h
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
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
#define WIDTH  62

#define NEAN    0
#define BLOCK   1
#define TRAP    2
#define LIFE    3
#define BOMBER  4
#define LADDER  5
#define START   6
#define EXIT    7
#define GATEP   8
#define GATEG   9
#define GATEY   10
#define GATEB   11
#define KEYP    12
#define KEYG    13
#define KEYY    14
#define KEYB    15
#define DOOR    16
#define PROBE   17
#define ROBOT   18

typedef struct fileMap_type
{
    off_t map[HEIGHT][WIDTH];
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
 * @param posX
 * @param posY
 * @param item
 * 
 * @return fileMap_t 
 */
void add_item_fileMap(fileMap_t*,int,int,int);

/**
 * @brief remove an item from the fileMap
 * 
 * @param fileMap
 * @param posX
 * @param posY
 * 
 * @return fileMap_t 
 */
void remove_item_fileMap(fileMap_t*,int,int);
/**
 * @brief remove all items from the fileMap
 * 
 * @param fileMap
 * @param posX
 * @param posY
 * 
 * @return off_t 
 */
off_t read_fileMap(fileMap_t*, int, int);

/**
 * @brief 
 * 
 * @param fileMap
 */
void display_fileMap(fileMap_t*);

#endif
