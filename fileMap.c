/**
 * @file fileMap.c
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @brief 
 * @version 0.1
 * @date 2023-02-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "fileMap.h"

fileMap_t *create_fileMap()
{
    fileMap_t *fileMap = (fileMap_t *)malloc(sizeof(fileMap_t));
    memset(fileMap->map, 0, sizeof(fileMap->map));    
    return  fileMap;
}

void add_item_fileMap(fileMap_t *map ,int posX,int posY,int item)
{
    map->map[posX][posY] = item;
}

void remove_item_fileMap(fileMap_t *map,int posX,int posY)
{
    map->map[posX][posY] = 0;
}

off_t read_fileMap(fileMap_t *map, int posX, int posY)
{
    return map->map[posX][posY];
}


void display_fileMap(fileMap_t *map)
{
    for (int i = 0; i < HEIGHT; i++) 
        for (int j = 0; j < WIDTH; j++) 
            printf("Item %d %d: %ld\n", i, j, map->map[i][j]);
}