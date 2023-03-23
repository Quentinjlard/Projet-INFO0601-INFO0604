/**
 * @file fileMap.c
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
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
    return fileMap;
}

void add_item_fileMap(int fd_World, int posX, int posY, int item)
{
    int size = 3;
    char buffeurs[size];
    // map->map[posX][posY] = item;
    buffeurs[0] = (char)posX;
    buffeurs[1] = (char)posY;
    buffeurs[2] = (char)item;

    if ((write(fd_World, buffeurs, size * sizeof(char))) == -1)
    {
        printf("Error writing to file: %s\n", strerror(errno));
    }
}

void remove_item_fileMap(fileMap_t *map, int posX, int posY)
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

void init_fileMap(int fd_World)
{
    char *vide = "";
    lseek(fd_World, 0, SEEK_SET);
    for (unsigned char i = 1; i <= 25; i++)
    {
        if (write(fd_World, &i, sizeof(unsigned char)) == -1)
        {
            perror("Error writing integer");
            exit(EXIT_FAILURE);
        }
        if (write(fd_World, &vide, sizeof(unsigned char)) == -1)
        {
            perror("Error writing integer");
            exit(EXIT_FAILURE);
        }
    }

    char pos = 0;
    if ((pos = lseek(fd_World, 0, SEEK_CUR)) == -1)
    {
        perror("lseek");
        close(fd_World);
        exit(EXIT_FAILURE);
    }

    lseek(fd_World, 1, SEEK_SET);
    if (write(fd_World, &pos, sizeof(char)) == -1)
    {
        perror("Error writing integer");
        exit(EXIT_FAILURE);
    }

    lseek(fd_World, pos, SEEK_CUR);
}

void add_lseek(int fd_World, char level)
{
    if (fd_World < 0)
    {
        perror("Error: Invalid file descriptor");
        exit(EXIT_FAILURE);
    }

    off_t pos = 0;
    if ((pos = lseek(fd_World, 0, SEEK_CUR)) == -1)
    {
        perror("lseek 1");
        close(fd_World);
        exit(EXIT_FAILURE);
    }
    if ((pos = lseek(fd_World, pos + 2907, SEEK_CUR)) == -1)
    {
        perror("lseek 2");
        close(fd_World);
        exit(EXIT_FAILURE);
    }

    char vide = '\0'; // DF dans le fichier "BIN"
    if (write(fd_World, &vide, sizeof(char)) == -1)
    {
        perror("Error writing character");
        exit(EXIT_FAILURE);
    }

    int i = -1;
    char c;
    do
    {
        i++;
        lseek(fd_World, i, SEEK_CUR);
        if (read(fd_World, &c, sizeof(char)) == -1)
        {
            perror("Error reading character");
            exit(EXIT_FAILURE);
        }
    } while (c != level);

    lseek(fd_World, i + 1, SEEK_CUR);
    if (write(fd_World, &pos, sizeof(off_t)) == -1)
    {
        perror("Error writing position");
        exit(EXIT_FAILURE);
    }
}