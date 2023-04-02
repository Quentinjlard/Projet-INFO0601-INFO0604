/**
 * @file playingField.c
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2023-02-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>

#include "playingField.h"

#include "functions.h"

// Variables globales
pthread_mutex_t mutex_affichage;
level_t niveau, buff;
robot_t robots[10];
probe_t probes[10];
WINDOW *windowLevel, *windowDEBUG, *windowInformations;

void initialiser_mutex()
{
    int i, j;

    pthread_mutex_init(&mutex_affichage, NULL);

    for (i = 1; i < nbCols; i++)
    { /* Initialisation des cases de la simulation */
        for (j = 1; j < nblignes; j++)
        {
            pthread_mutex_init(&buff.mutex[i * nblignes + j], NULL);
        }
    }
}

void *routine_robot(void *arg)
{
    int *donnees;
    donnees = (int *)arg;
    int direction, pos, numero;
    pos = donnees[0];
    numero = donnees[1];
    robots[numero].actif = 1;
    while (1)
    {

        sleep(1);
        robots[numero].pos = pos;
        if (detectBombe(niveau, pos) == 1)
        {
            mvwprintw(windowInformations, 2, 1, "Robot touche                  ");
            robots[numero].actif = 0;
            sleep(5);
            robots[numero].actif = 1;
        }
        while (pthread_mutex_trylock(&mutex_affichage) != 0)
        {
            usleep(50000);
        }
        direction = rand() % 2;
        switch (direction)
        {
        // gauche
        case 0:
            if (niveau.cells[pos + 1 - nblignes * 2] == 'B' || niveau.cells[pos + 1 - nblignes * 2] == '#' || niveau.cells[pos + 2 - nblignes * 2] == 'B' || niveau.cells[pos + 2 - nblignes * 2] == '#' || niveau.cells[pos + 3 - nblignes * 2] == 'B' || niveau.cells[pos + 3 - nblignes * 2] == '#')
                break;
            if (niveau.cells[pos + 4 - nblignes * 2] == ' ' || niveau.cells[pos + 3 - nblignes * 2] == ACS_RTEE)
                break;
            pos = pos - nblignes;
            moveRobot(&niveau, buff, pos, 1);
            afficherDEBUG(niveau, windowDEBUG);
            level_display(windowLevel, niveau);
            wrefresh(windowLevel);
            break;

        // Droite
        case 1:
            if (niveau.cells[pos + 1 + nblignes * 2] == 'B' || niveau.cells[pos + 1 + nblignes * 2] == '#' || niveau.cells[pos + 2 + nblignes * 2] == 'B' || niveau.cells[pos + 2 + nblignes * 2] == '#' || niveau.cells[pos + 3 + nblignes * 2] == 'B' || niveau.cells[pos + 3 + nblignes * 2] == '#')
                break;
            if (niveau.cells[pos + 4 + nblignes * 2] == ' ' || niveau.cells[pos + 3 + nblignes * 2] == ACS_LTEE)
                break;
            pos = pos + nblignes;
            moveRobot(&niveau, buff, pos, 2);
            afficherDEBUG(niveau, windowDEBUG);
            level_display(windowLevel, niveau);
            wrefresh(windowLevel);
            break;
        }
        pthread_mutex_unlock(&mutex_affichage);
    }
}

void *routine_probe(void *arg)
{
    int *donnees;
    donnees = (int *)arg;
    int direction, pos, numero;
    pos = donnees[0];
    numero = donnees[1];
    probes[numero].actif = 1;
    while (1)
    {

        sleep(1);
        probes[numero].pos = pos;
        if (detectBombe(niveau, pos) == 1)
        {
            mvwprintw(windowInformations, 2, 1, "Sonde touchee                  ");
            probes[numero].actif = 0;
            sleep(5);
            probes[numero].actif = 1;
        }
        while (pthread_mutex_trylock(&mutex_affichage) != 0)
        {
            usleep(50000);
        }
        direction = rand() % 4;
        switch (direction)
        {
            // Gauche
        case 0:
            if (niveau.cells[pos + 1 - nblignes * 2] == 'B' || niveau.cells[pos + 1 - nblignes * 2] == '#' || niveau.cells[pos + 2 - nblignes * 2] == 'B' || niveau.cells[pos + 2 - nblignes * 2] == '#' || niveau.cells[pos + 3 - nblignes * 2] == 'B' || niveau.cells[pos + 3 - nblignes * 2] == '#')
                break;
            pos = pos - nblignes;
            moveProbe(&niveau, buff, pos, 1);
            afficherDEBUG(niveau, windowDEBUG);
            level_display(windowLevel, niveau);
            wrefresh(windowLevel);
            break;

            // Droite
        case 1:
            if (niveau.cells[pos + 1 + nblignes * 2] == 'B' || niveau.cells[pos + 1 + nblignes * 2] == '#' || niveau.cells[pos + 2 + nblignes * 2] == 'B' || niveau.cells[pos + 2 + nblignes * 2] == '#' || niveau.cells[pos + 3 + nblignes * 2] == 'B' || niveau.cells[pos + 3 + nblignes * 2] == '#')
                break;
            pos = pos + nblignes;
            moveProbe(&niveau, buff, pos, 2);
            afficherDEBUG(niveau, windowDEBUG);
            level_display(windowLevel, niveau);
            wrefresh(windowLevel);
            break;

            // Haut
        case 2:
            if (niveau.cells[pos - 1] == 'B')
                break;
            pos = pos - 3;
            moveProbe(&niveau, buff, pos, 3);
            afficherDEBUG(niveau, windowDEBUG);
            level_display(windowLevel, niveau);
            wrefresh(windowLevel);
            break;

            // Bas
        case 3:
            if (niveau.cells[pos + 3] == 'B')
                break;
            pos = pos - 3;
            moveProbe(&niveau, buff, pos, 4);
            afficherDEBUG(niveau, windowDEBUG);
            level_display(windowLevel, niveau);
            wrefresh(windowLevel);
            break;
        }
        pthread_mutex_unlock(&mutex_affichage);
    }
}

void *routine_trap(void *arg)
{
    int *p = (int *)&arg;
    int pos = *p;
    while (1)
    {
        pthread_mutex_lock(&mutex_affichage);
        buff.cells[pos] = ' ';
        buff.colors[pos] = 1;
        pthread_mutex_unlock(&mutex_affichage);
        sleep(4);
        pthread_mutex_lock(&mutex_affichage);
        buff.cells[pos] = '#';
        buff.colors[pos] = 9;
        pthread_mutex_unlock(&mutex_affichage);
        sleep(4);
    }
}

int searchStart(level_t niveau)
{
    int position = -1;

    for (int i = 2; i < 60; i++)
    {
        for (int j = 2; j < 20; j++)
        {
            if (niveau.cells[i * nblignes + j] == 'S')
            {
                position = i * nblignes + j;
                return position;
            }
        }
    }
    return position;
}

// int searchTrap(level_t niveau)
// {
//     int position = -1;

//     for (int i = 2; i < 60; i++)
//     {
//         for (int j = 2; j < 20; j++)
//         {
//             if (niveau.cells[i * nblignes + j] == '#')
//             {
//                 position = i * nblignes + j;
//                 return position;
//             }
//         }
//     }
//     return position;
// }

int searchRobot(level_t niveau, int posROld)
{
    int position = -1;

    for (int i = 1; i < 60; i++)
    {
        for (int j = 1; j < 20; j++)
        {
            if (niveau.cells[i * nblignes + j] == ACS_ULCORNER && niveau.cells[i * nblignes + j + nblignes] == ACS_BTEE && niveau.cells[i * nblignes + j + nblignes * 2] == ACS_URCORNER && (i * nblignes + j) != posROld)
            {
                position = i * nblignes + j;
                return position;
            }
        }
    }
    return position;
}

int searchProbe(level_t niveau, int posROld)
{
    int position = -1;

    for (int i = 1; i < 60; i++)
    {
        for (int j = 1; j < 20; j++)
        {
            if (niveau.cells[i * nblignes + j] == ACS_LTEE && niveau.colors[i * nblignes + j] == 8 && niveau.cells[i * nblignes + j + nblignes] == ACS_HLINE && niveau.cells[i * nblignes + j + nblignes * 2] == ACS_RTEE && (i * nblignes + j) != posROld)
            {
                position = i * nblignes + j;
                return position;
            }
        }
    }
    return position;
}

int searchDoorPair(level_t niveau, int num, int posD)
{
    int position = -1;
    for (int i = 2; i < 60; i++)
    {
        for (int j = 2; j < 20; j++)
        {
            if (niveau.cells[i * nblignes + j] == num && (i * nblignes + j) != posD)
            {
                position = i * nblignes + j;
                return position;
            }
        }
    }
    return position;
}

int detectLadder(level_t niveau, int pos)
{
    if (niveau.cells[pos - nblignes] == ACS_LTEE || niveau.cells[pos] == ACS_HLINE)
    {
        return 1;
    }
    if (niveau.cells[pos + 1 - nblignes] == ACS_LTEE || niveau.cells[pos + 1] == ACS_HLINE)
    {
        return 1;
    }
    if (niveau.cells[pos + 2 - nblignes] == ACS_LTEE || niveau.cells[pos + 2] == ACS_HLINE)
    {
        return 1;
    }
    return 0;
}

int detectGround(level_t niveau, int pos)
{
    int objet = -1;
    switch (niveau.cells[pos + 3])
    {
    case 'V':
        objet = 1;
        break;
    case 'o':
        objet = 2;
        break;
    }

    return objet;
}

int detectKey(level_t niveau, int pos)
{
    if (niveau.cells[pos + 2 + nblignes] == 'K')
        return 1;
    return 0;
}

int detectBombe(level_t niveau, int pos)
{
    if (buff.cells[pos + 3 + nblignes] == 'o' || buff.cells[pos + 3 + nblignes * 2] == 'o' || buff.cells[pos + 3 + nblignes * 3] == 'o' || buff.cells[pos + 3 + nblignes * 4] == 'o' || buff.cells[pos + 3 + nblignes * 5] == 'o' || buff.cells[pos + 3 + nblignes * 6] == 'o' || buff.cells[pos + 3 - nblignes] == 'o' || buff.cells[pos + 3 - nblignes * 2] == 'o' || buff.cells[pos + 3 - nblignes * 3] == 'o' || buff.cells[pos + 3 - nblignes * 4] == 'o' || buff.cells[pos + 3 - nblignes * 5] == 'o' || buff.cells[pos + 3 - nblignes * 6] == 'o')
        return 1;
    if (buff.cells[pos + 1] == 'o' || buff.cells[pos + 2] == 'o' || buff.cells[pos + 3] == 'o' || buff.cells[pos + 4] == 'o' || buff.cells[pos + 5] == 'o' || buff.cells[pos + 6] == 'o')
        return 1;
    return 0;
}

int detectDoor(level_t niveau, int pos)
{
    if (niveau.cells[pos + nblignes] == '1' || niveau.cells[pos + nblignes] == '2' || niveau.cells[pos + nblignes] == '3' || niveau.cells[pos + nblignes] == '4' || niveau.cells[pos + nblignes] == '5')
        return 1;
    return 0;
}

int detectExit(level_t niveau, int pos)
{
    if (niveau.cells[pos + 2 + nblignes] == 'E')
        return 1;
    return 0;
}

void movePlayer(level_t *niveau, level_t buff, int pos, int direction, int directionTete)
{
    switch (direction)
    {
    // UP
    case 1:
        spawnPlayer(niveau, pos, directionTete);
        // Gauche
        niveau->cells[pos + 4 - nblignes] = buff.cells[pos + 4 - nblignes];
        niveau->colors[pos + 4 - nblignes] = buff.colors[pos + 4 - nblignes];

        // Milieu
        niveau->cells[pos + 4] = buff.cells[pos + 4];
        niveau->colors[pos + 4] = buff.colors[pos + 4];

        // Droite
        niveau->cells[pos + 4 + nblignes] = buff.cells[pos + 4 + nblignes];
        niveau->colors[pos + 4 + nblignes] = buff.colors[pos + 4 + nblignes];
        break;
    // DOWN
    case 2:
        spawnPlayer(niveau, pos, directionTete);
        // Gauche
        niveau->cells[pos - nblignes] = buff.cells[pos - nblignes];
        niveau->colors[pos - nblignes] = buff.colors[pos - nblignes];

        // Milieu
        niveau->cells[pos] = buff.cells[pos];
        niveau->colors[pos] = buff.colors[pos];

        // Droite
        niveau->cells[pos + nblignes] = buff.cells[pos + nblignes];
        niveau->colors[pos + nblignes] = buff.colors[pos + nblignes];
        break;
    // LEFT
    case 3:
        spawnPlayer(niveau, pos, directionTete);
        // Haut
        niveau->cells[pos + 1 + nblignes * 2] = buff.cells[pos + 1 + nblignes * 2];
        niveau->colors[pos + 1 + nblignes * 2] = buff.colors[pos + 1 + nblignes * 2];

        // Milieu
        niveau->cells[pos + 2 + nblignes * 2] = buff.cells[pos + 2 + nblignes * 2];
        niveau->colors[pos + 2 + nblignes * 2] = buff.colors[pos + 2 + nblignes * 2];

        // Bas
        niveau->cells[pos + 3 + nblignes * 2] = buff.cells[pos + 3 + nblignes * 2];
        niveau->colors[pos + 3 + nblignes * 2] = buff.colors[pos + 3 + nblignes * 2];
        break;
    // RIGHT
    case 4:
        spawnPlayer(niveau, pos, directionTete);
        // Haut
        niveau->cells[pos + 1 - nblignes * 2] = buff.cells[pos + 1 - nblignes * 2];
        niveau->colors[pos + 1 - nblignes * 2] = buff.colors[pos + 1 - nblignes * 2];

        // Milieu
        niveau->cells[pos + 2 - nblignes * 2] = buff.cells[pos + 2 - nblignes * 2];
        niveau->colors[pos + 2 - nblignes * 2] = buff.colors[pos + 2 - nblignes * 2];

        // Bas
        niveau->cells[pos + 3 - nblignes * 2] = buff.cells[pos + 3 - nblignes * 2];
        niveau->colors[pos + 3 - nblignes * 2] = buff.colors[pos + 3 - nblignes * 2];

        break;
    }
}

void moveRobot(level_t *niveau, level_t buff, int pos, int direction)
{
    switch (direction)
    {
    // Gauche
    case 1:
        spawnRobot(niveau, pos);
        // Tete
        niveau->cells[pos + nblignes * 2] = buff.cells[pos + nblignes * 2];
        niveau->colors[pos + nblignes * 2] = buff.colors[pos + nblignes * 2];

        // Haut
        niveau->cells[pos + 1 + nblignes * 2] = buff.cells[pos + 1 + nblignes * 2];
        niveau->colors[pos + 1 + nblignes * 2] = buff.colors[pos + 1 + nblignes * 2];

        // Milieu
        niveau->cells[pos + 2 + nblignes * 2] = buff.cells[pos + 2 + nblignes * 2];
        niveau->colors[pos + 2 + nblignes * 2] = buff.colors[pos + 2 + nblignes * 2];

        // Bas
        niveau->cells[pos + 3 + nblignes * 2] = buff.cells[pos + 3 + nblignes * 2];
        niveau->colors[pos + 3 + nblignes * 2] = buff.colors[pos + 3 + nblignes * 2];

        break;
    // Droite
    case 2:
        spawnRobot(niveau, pos);
        // Tete
        niveau->cells[pos - nblignes * 2] = buff.cells[pos - nblignes * 2];
        niveau->colors[pos - nblignes * 2] = buff.colors[pos - nblignes * 2];

        // Haut
        niveau->cells[pos + 1 - nblignes * 2] = buff.cells[pos + 1 - nblignes * 2];
        niveau->colors[pos + 1 - nblignes * 2] = buff.colors[pos + 1 - nblignes * 2];

        // Milieu
        niveau->cells[pos + 2 - nblignes * 2] = buff.cells[pos + 2 - nblignes * 2];
        niveau->colors[pos + 2 - nblignes * 2] = buff.colors[pos + 2 - nblignes * 2];

        // Bas
        niveau->cells[pos + 3 - nblignes * 2] = buff.cells[pos + 3 - nblignes * 2];
        niveau->colors[pos + 3 - nblignes * 2] = buff.colors[pos + 3 - nblignes * 2];
        break;
    }
}

void moveProbe(level_t *niveau, level_t buff, int pos, int direction)
{
    switch (direction)
    {
    // Gauche
    case 1:
        spawnProbe(niveau, pos);
        // Haut
        niveau->cells[pos + nblignes * 2] = buff.cells[pos + nblignes * 2];
        niveau->colors[pos + nblignes * 2] = buff.colors[pos + nblignes * 2];

        // Bas
        niveau->cells[pos + 1 + nblignes * 2] = buff.cells[pos + 1 + nblignes * 2];
        niveau->colors[pos + 1 + nblignes * 2] = buff.colors[pos + 1 + nblignes * 2];

        break;
    // Droite
    case 2:
        spawnProbe(niveau, pos);
        // Haut
        niveau->cells[pos - nblignes * 2] = buff.cells[pos - nblignes * 2];
        niveau->colors[pos - nblignes * 2] = buff.colors[pos - nblignes * 2];

        // Bas
        niveau->cells[pos + 1 - nblignes * 2] = buff.cells[pos + 1 - nblignes * 2];
        niveau->colors[pos + 1 - nblignes * 2] = buff.colors[pos + 1 - nblignes * 2];

        break;
    // Haut
    case 3:
        spawnProbe(niveau, pos);
        // Gauche
        niveau->cells[pos + 2 - nblignes] = buff.cells[pos + 2 - nblignes];
        niveau->colors[pos + 2 - nblignes] = buff.colors[pos + 2 - nblignes];

        // Milieu
        niveau->cells[pos + 2] = buff.cells[pos + 2];
        niveau->colors[pos + 2] = buff.colors[pos + 2];

        // Droite
        niveau->cells[pos + 2 + nblignes] = buff.cells[pos + 2 + nblignes];
        niveau->colors[pos + 2 + nblignes] = buff.colors[pos + 2 + nblignes];

        break;
    // Bas
    case 4:
        spawnProbe(niveau, pos);
        // Gauche
        niveau->cells[pos - nblignes] = buff.cells[pos - nblignes];
        niveau->colors[pos - nblignes] = buff.colors[pos - nblignes];

        // Milieu
        niveau->cells[pos] = buff.cells[pos];
        niveau->colors[pos] = buff.colors[pos];

        // Droite
        niveau->cells[pos + nblignes] = buff.cells[pos + nblignes];
        niveau->colors[pos + nblignes] = buff.colors[pos + nblignes];

        break;
    }
}

void spawnPlayer(level_t *niveau, int pos, int d)
{
    // Tete
    // orientation
    switch (d)
    {
        // gauche
    case 1:
        niveau->cells[pos + 1 - nblignes] = '-';
        niveau->colors[pos + 1 - nblignes] = 14;
        niveau->cells[pos + 1 + nblignes] = ' ';
        niveau->colors[pos + 1 + nblignes] = 1;
        break;

        // droite
    case 2:
        niveau->cells[pos + 1 + nblignes] = '-';
        niveau->colors[pos + 1 + nblignes] = 14;
        niveau->cells[pos + 1 - nblignes] = ' ';
        niveau->colors[pos + 1 - nblignes] = 1;
        break;
    }
    niveau->cells[pos + 1] = 'T';
    niveau->colors[pos + 1] = 14;

    // Haut du corps
    niveau->cells[pos + 2 - nblignes] = ACS_HLINE;
    niveau->colors[pos + 2 - nblignes] = 5;
    niveau->cells[pos + 2] = ACS_PLUS;
    niveau->colors[pos + 2] = 5;
    niveau->cells[pos + 2 + nblignes] = ACS_HLINE;
    niveau->colors[pos + 2 + nblignes] = 5;

    // Bas du corps
    niveau->cells[pos + 3 - nblignes] = ACS_ULCORNER;
    niveau->colors[pos + 3 - nblignes] = 5;
    niveau->cells[pos + 3] = ACS_BTEE;
    niveau->colors[pos + 3] = 5;
    niveau->cells[pos + 3 + nblignes] = ACS_URCORNER;
    niveau->colors[pos + 3 + nblignes] = 5;
}

void spawnRobot(level_t *niveau, int pos)
{
    // Tête
    niveau->cells[pos - nblignes] = ACS_ULCORNER;
    niveau->colors[pos - nblignes] = 8;
    niveau->cells[pos] = ACS_BTEE;
    niveau->colors[pos] = 8;
    niveau->cells[pos + nblignes] = ACS_URCORNER;
    niveau->colors[pos + nblignes] = 8;

    // Haut du corps
    niveau->cells[pos + 1 - nblignes] = ACS_LLCORNER;
    niveau->colors[pos + 1 - nblignes] = 8;
    niveau->cells[pos + 1] = ACS_TTEE;
    niveau->colors[pos + 1] = 8;
    niveau->cells[pos + 1 + nblignes] = ACS_LRCORNER;
    niveau->colors[pos + 1 + nblignes] = 8;

    // Milieu du corps
    niveau->cells[pos + 2 - nblignes] = ACS_HLINE;
    niveau->colors[pos + 2 - nblignes] = 8;
    niveau->cells[pos + 2] = ACS_PLUS;
    niveau->colors[pos + 2] = 8;
    niveau->cells[pos + 2 + nblignes] = ACS_HLINE;
    niveau->colors[pos + 2 + nblignes] = 8;

    // Bas du corps
    niveau->cells[pos + 3 - nblignes] = ACS_ULCORNER;
    niveau->colors[pos + 3 - nblignes] = 8;
    niveau->cells[pos + 3] = ACS_BTEE;
    niveau->colors[pos + 3] = 8;
    niveau->cells[pos + 3 + nblignes] = ACS_URCORNER;
    niveau->colors[pos + 3 + nblignes] = 8;
}

void spawnProbe(level_t *niveau, int pos)
{
    // Haut
    niveau->cells[pos - nblignes] = ACS_LTEE;
    niveau->colors[pos - nblignes] = 8;
    niveau->cells[pos] = ACS_HLINE;
    niveau->colors[pos] = 8;
    niveau->cells[pos + nblignes] = ACS_RTEE;
    niveau->colors[pos + nblignes] = 8;

    // Bas
    niveau->cells[pos + 1 - nblignes] = ACS_LLCORNER;
    niveau->colors[pos + 1 - nblignes] = 8;
    niveau->cells[pos + 1] = ACS_HLINE;
    niveau->colors[pos + 1] = 8;
    niveau->cells[pos + 1 + nblignes] = ACS_LRCORNER;
    niveau->colors[pos + 1 + nblignes] = 8;
}

void dispawnPlayer(level_t *niveau, level_t buff, int pos, int d)
{
    // Tete
    // orientation
    switch (d)
    {
        // gauche
    case 1:
        niveau->cells[pos + 1 - nblignes] = buff.cells[pos + 1 - nblignes];
        niveau->colors[pos + 1 - nblignes] = buff.colors[pos + 1 - nblignes];
        niveau->cells[pos + 1 + nblignes] = buff.cells[pos + 1 + nblignes];
        niveau->colors[pos + 1 + nblignes] = buff.colors[pos + 1 + nblignes];
        break;

        // droite
    case 2:
        niveau->cells[pos + 1 + nblignes] = buff.cells[pos + 1 + nblignes];
        niveau->colors[pos + 1 + nblignes] = buff.colors[pos + 1 + nblignes];
        niveau->cells[pos + 1 - nblignes] = buff.cells[pos + 1 - nblignes];
        niveau->colors[pos + 1 - nblignes] = buff.colors[pos + 1 - nblignes];
        break;
    }
    niveau->cells[pos + 1] = buff.cells[pos + 1];
    niveau->colors[pos + 1] = buff.colors[pos + 1];

    // Haut du corps
    niveau->cells[pos + 2 - nblignes] = buff.cells[pos + 2 - nblignes];
    niveau->colors[pos + 2 - nblignes] = buff.colors[pos + 2 - nblignes];
    niveau->cells[pos + 2] = buff.cells[pos + 2];
    niveau->colors[pos + 2] = buff.colors[pos + 2];
    niveau->cells[pos + 2 + nblignes] = buff.cells[pos + 2 + nblignes];
    niveau->colors[pos + 2 + nblignes] = buff.colors[pos + 2 + nblignes];

    // Bas du corps
    niveau->cells[pos + 3 - nblignes] = buff.cells[pos + 3 - nblignes];
    niveau->colors[pos + 3 - nblignes] = buff.colors[pos + 3 - nblignes];
    niveau->cells[pos + 3] = buff.cells[pos + 3];
    niveau->colors[pos + 3] = buff.colors[pos + 3];
    niveau->cells[pos + 3 + nblignes] = buff.cells[pos + 3 + nblignes];
    niveau->colors[pos + 3 + nblignes] = buff.colors[pos + 3 + nblignes];
}

void dispawnRobot(level_t *buff, int pos)
{
    // Tête
    buff->cells[pos - nblignes] = ' ';
    buff->colors[pos - nblignes] = 1;
    buff->cells[pos] = ' ';
    buff->colors[pos] = 1;
    buff->cells[pos + nblignes] = ' ';
    buff->colors[pos + nblignes] = 1;

    // Haut du corps
    buff->cells[pos + 1 - nblignes] = ' ';
    buff->colors[pos + 1 - nblignes] = 1;
    buff->cells[pos + 1] = ' ';
    buff->colors[pos + 1] = 1;
    buff->cells[pos + 1 + nblignes] = ' ';
    buff->colors[pos + 1 + nblignes] = 1;

    // Milieu du corps
    buff->cells[pos + 2 - nblignes] = ' ';
    buff->colors[pos + 2 - nblignes] = 1;
    buff->cells[pos + 2] = ' ';
    buff->colors[pos + 2] = 1;
    buff->cells[pos + 2 + nblignes] = ' ';
    buff->colors[pos + 2 + nblignes] = 1;

    // Bas du corps
    buff->cells[pos + 3 - nblignes] = ' ';
    buff->colors[pos + 3 - nblignes] = 1;
    buff->cells[pos + 3] = ' ';
    buff->colors[pos + 3] = 1;
    buff->cells[pos + 3 + nblignes] = ' ';
    buff->colors[pos + 3 + nblignes] = 1;
}

void dispawnProbe(level_t *buff, int pos)
{
    // Haut
    buff->cells[pos - nblignes] = ' ';
    buff->colors[pos - nblignes] = 1;
    buff->cells[pos] = ' ';
    buff->colors[pos] = 1;
    buff->cells[pos + nblignes] = ' ';
    buff->colors[pos + nblignes] = 1;

    // Bas
    buff->cells[pos + 1 - nblignes] = ' ';
    buff->colors[pos + 1 - nblignes] = 1;
    buff->cells[pos + 1] = ' ';
    buff->colors[pos + 1] = 1;
    buff->cells[pos + 1 + nblignes] = ' ';
    buff->colors[pos + 1 + nblignes] = 1;
}

void addLife(WINDOW *windowPlayerInformation)
{

    int posX;
    for (posX = 2; posX < 7; posX++)
    {
        wattron(windowPlayerInformation, COLOR_PAIR(2));
        if (mvwinch(windowPlayerInformation, 8, posX) == ' ')
        {
            mvwprintw(windowPlayerInformation, 8, posX, "V");
            wrefresh(windowPlayerInformation);
            return;
        }
    }
}

void subLife(WINDOW *windowPlayerInformation)
{

    int posX;
    for (posX = 7; posX > 2; posX--)
    {
        wattron(windowPlayerInformation, COLOR_PAIR(1));
        if (mvwinch(windowPlayerInformation, 8, posX) == 'V')
        {
            mvwprintw(windowPlayerInformation, 8, posX, " ");
            wrefresh(windowPlayerInformation);
            return;
        }
    }
}

void addBomb(WINDOW *windowPlayerInformation)
{

    int posX;
    for (posX = 2; posX < 7; posX++)
    {
        wattron(windowPlayerInformation, COLOR_PAIR(8));
        if (mvwinch(windowPlayerInformation, 12, posX) == ' ')
        {
            mvwprintw(windowPlayerInformation, 12, posX, "o");
            wrefresh(windowPlayerInformation);
            return;
        }
    }
}

void subBomb(WINDOW *windowPlayerInformation)
{

    int posX;
    for (posX = 7; posX > 2; posX--)
    {
        wattron(windowPlayerInformation, COLOR_PAIR(1));
        if (mvwinch(windowPlayerInformation, 12, posX) == 'o')
        {
            mvwprintw(windowPlayerInformation, 12, posX, " ");
            wrefresh(windowPlayerInformation);
            return;
        }
        wrefresh(windowInformations);
    }
}

void addKey(WINDOW *windowPlayerInformation, int couleur)
{

    switch (couleur)
    {
        // Vert
    case 3:
        wattron(windowPlayerInformation, COLOR_PAIR(11));
        mvwprintw(windowPlayerInformation, 3, 2, " ");
        wattron(windowPlayerInformation, COLOR_PAIR(3));
        mvwaddch(windowPlayerInformation, 4, 2, ACS_LLCORNER);
        break;
        // Jaune
    case 4:
        wattron(windowPlayerInformation, COLOR_PAIR(12));
        mvwprintw(windowPlayerInformation, 3, 4, " ");
        wattron(windowPlayerInformation, COLOR_PAIR(4));
        mvwaddch(windowPlayerInformation, 4, 4, ACS_LLCORNER);
        break;
        // Bleu
    case 5:
        wattron(windowPlayerInformation, COLOR_PAIR(13));
        mvwprintw(windowPlayerInformation, 3, 6, " ");
        wattron(windowPlayerInformation, COLOR_PAIR(5));
        mvwaddch(windowPlayerInformation, 4, 6, ACS_LLCORNER);
        break;
        // Magenta
    case 6:
        wattron(windowPlayerInformation, COLOR_PAIR(10));
        mvwprintw(windowPlayerInformation, 3, 8, " ");
        wattron(windowPlayerInformation, COLOR_PAIR(6));
        mvwaddch(windowPlayerInformation, 4, 8, ACS_LLCORNER);
        break;
    }

    wrefresh(windowPlayerInformation);
}

void *placeBombe(void *arg)
{

    int *p = (int *)arg;
    int tmp = 0, tmp2 = 0, tmp3 = 0, pos, avantI;
    char avantC;
    pos = *p;
    pthread_mutex_lock(&buff.mutex[pos]);
    pthread_mutex_lock(&mutex_affichage);
    avantC = buff.cells[pos + 3];
    avantI = buff.colors[pos + 3];
    niveau.cells[pos + 3] = 'o';
    niveau.colors[pos + 3] = 8;
    buff.cells[pos + 3] = 'o';
    buff.colors[pos + 3] = 8;
    pthread_mutex_unlock(&mutex_affichage);
    sleep(1);
    pthread_mutex_lock(&mutex_affichage);
    niveau.cells[pos + 3] = avantC;
    niveau.colors[pos + 3] = avantI;
    buff.cells[pos + 3] = avantC;
    buff.colors[pos + 3] = avantI;
    pthread_mutex_unlock(&mutex_affichage);
    for (int i = 0; i < 3; i++)
    {
        pthread_mutex_lock(&mutex_affichage);
        if (niveau.cells[pos + 3 - (nblignes * i)] == ' ')
        {
            niveau.cells[pos + 3 - (nblignes * i)] = '-';
            niveau.colors[pos + 3 - (nblignes * i)] = 8;
            tmp = 1;
        }
        if (niveau.cells[pos + 3 + (nblignes * i)] == ' ')
        {
            niveau.cells[pos + 3 + (nblignes * i)] = '-';
            niveau.colors[pos + 3 + (nblignes * i)] = 8;
            tmp2 = 1;
        }
        if (niveau.cells[pos + 3 + nblignes - i] == ' ')
        {
            niveau.cells[pos + 3 + nblignes - i] = '|';
            niveau.colors[pos + 3 + nblignes - i] = 8;
            tmp3 = 1;
        }
        pthread_mutex_unlock(&mutex_affichage);
        sleep(1);
        pthread_mutex_lock(&mutex_affichage);
        if (tmp == 1)
        {
            niveau.cells[pos + 3 - (nblignes * i)] = ' ';
            niveau.colors[pos + 3 - (nblignes * i)] = 1;
            tmp = 0;
        }
        if (tmp2 == 1)
        {
            niveau.cells[pos + 3 + (nblignes * i)] = ' ';
            niveau.colors[pos + 3 + (nblignes * i)] = 1;
            tmp2 = 0;
        }
        if (tmp3 == 1)
        {
            niveau.cells[pos + 3 + nblignes - i] = ' ';
            niveau.colors[pos + 3 + nblignes - i] = 1;
            tmp3 = 0;
        }
        pthread_mutex_unlock(&mutex_affichage);
    }
    pthread_mutex_unlock(&buff.mutex[pos]);
    pthread_exit(NULL);
}

void playingField(char *filename)
{
    // Variables
    WINDOW *windowPlayerInformation;
    int ch, gagne, fd_World, err, directionTete = 1, life = 3, bombe = 3, level = 0, key[4], donnee[2], donneeP[2];
    int pos, posDoor, posR, posROld = -1, posP, posPOld = -1; // posT = 0;
    char nameWorld[MAX];
    // pthread_t *trap = NULL;
    pthread_t *Rbombe = (pthread_t *)malloc(sizeof(pthread_t));
    tableAdressage_t *table;

    // Initialisations
    table = (tableAdressage_t *)malloc(sizeof(tableAdressage_t));
    memset(table->adresse, 0, sizeof(table->adresse));
    strcpy(nameWorld, filename);
    initialiser_mutex();

    // Ouverture fichier
    if ((fd_World = open(nameWorld, O_RDWR)) == -1)
    {

        perror("Erreur ouverture de fichier (publisher).");
        exit(EXIT_FAILURE);
    }

    // Lecture du fichier
    if ((err = read(fd_World, table, sizeof(tableAdressage_t))) == -1)
    {
        perror("Erreur lecture table adressage (publisher).");
        exit(EXIT_FAILURE);
    }
    lseek(fd_World, sizeof(tableAdressage_t), SEEK_SET);

    // Initialisation d'ncurses
    setlocale(LC_ALL, "");
    ncurses_init();
    ncurses_init_mouse();
    ncurses_colors();
    palette();

    // Création fenêtre de debugage
    windowDEBUG = newwin(22, 62, 0, 80);
    scrollok(windowDEBUG, TRUE);
    box(windowDEBUG, 0, 0);
    mvwprintw(windowDEBUG, 0, 0, "DEBUG");
    afficherDEBUG(niveau, windowDEBUG);

    // Création fenêtre de jeu
    windowLevel = newwin(22, 62, 0, 0);
    scrollok(windowLevel, TRUE);
    box(windowLevel, 0, 0);
    mvwprintw(windowLevel, 0, 0, "Level");

    // Création fenêtre d'information de jeu
    windowPlayerInformation = newwin(22, 15, 0, 63);
    scrollok(windowPlayerInformation, TRUE);
    box(windowPlayerInformation, 0, 0);
    mvwprintw(windowPlayerInformation, 0, 0, "Player Info");

    // Création fenêtre de message d'information
    windowInformations = newwin(5, 77, 23, 0);
    scrollok(windowInformations, TRUE);
    box(windowInformations, 0, 0);
    mvwprintw(windowInformations, 0, 0, "Informations");
    wattron(windowInformations, COLOR_PAIR(2));
    mvwprintw(windowInformations, 1, 1, "Press 'ESQ' to quit ...");
    wrefresh(windowInformations);

    for (int k = 0; k < 20; k++)
    {
        gagne = 0;
        memset(key, 0, 4 * sizeof(int));
        robots[k].thread = NULL;
        probes[k].thread = NULL;

        pthread_mutex_lock(&mutex_affichage);
        // Initialisation du niveau (level_t)
        init_Level(windowLevel, windowInformations);
        init_matLevel(&niveau);
        niveau = loadLevel(level, table, nameWorld);
        buff = loadLevel(level, table, nameWorld);
        level_display(windowLevel, niveau);
        wrefresh(windowLevel);
        init_PlayInformations(windowPlayerInformation, level);
        wrefresh(windowPlayerInformation);

        // Chercher et démarrer thread sonde

        if ((posP = searchProbe(buff, posPOld)) != -1)
        {
            posPOld = posP;
            if (probes[0].thread == NULL)
            {
                donneeP[0] = posP;
                donneeP[1] = 0;
                probes[0].thread = (pthread_t *)malloc(sizeof(pthread_t));
                dispawnProbe(&buff, posP + nblignes);
                pthread_create(probes[0].thread, NULL, routine_probe, (void *)donneeP);
                break;
            }
        }

        // Chercher et démarrer thread trap
        // if ((posT = searchTrap(buff)) != -1)
        // {
        //     if (trap == NULL)
        //     {
        //         trap = (pthread_t *)malloc(sizeof(pthread_t));
        //         pthread_create(trap, NULL, routine_trap, (void *)&pos);
        //     }
        //}

        // Chercher et démarrer thread robot
        for (int i = 0; i < 10; i++)
        {
            if ((posR = searchRobot(buff, posROld)) != -1)
            {
                posROld = posR;
                if (robots[i].thread == NULL)
                {
                    donnee[0] = posR;
                    donnee[1] = i;
                    robots[i].thread = (pthread_t *)malloc(sizeof(pthread_t));
                    dispawnRobot(&buff, posR + nblignes);
                    pthread_create(robots[i].thread, NULL, routine_robot, (void *)donnee);
                    break;
                }
            }
        }
        if (k == 1)
            pos = searchStart(niveau) - level;
        else
            pos = searchStart(niveau);
        spawnPlayer(&niveau, pos, directionTete);
        afficherDEBUG(niveau, windowDEBUG);
        level_display(windowLevel, niveau);
        wrefresh(windowLevel);
        pthread_mutex_unlock(&mutex_affichage);
        while (gagne == 0)
        {
            ch = getch();
            pthread_mutex_lock(&mutex_affichage);
            switch (ch)
            {
            case KEY_UP:
                // Traitement de la touche "flèche haut"
                if (niveau.cells[pos] == 'B' || niveau.cells[pos] == '#' || detectLadder(buff, pos) == 0)
                    break;
                pos = pos - 1;
                movePlayer(&niveau, buff, pos, 1, directionTete);
                afficherDEBUG(niveau, windowDEBUG);
                level_display(windowLevel, niveau);
                wrefresh(windowLevel);

                break;
            case KEY_DOWN:
                // Traitement de la touche "flèche bas"
                if (niveau.cells[pos + 4] == 'B' || niveau.cells[pos + 4] == '#' || detectLadder(buff, pos + 1) == 0)
                    break;
                pos = pos + 1;
                movePlayer(&niveau, buff, pos, 2, directionTete);
                afficherDEBUG(niveau, windowDEBUG);
                level_display(windowLevel, niveau);
                wrefresh(windowLevel);
                break;
            case KEY_LEFT:
                // Traitement de la touche "flèche gauche"
                if (niveau.cells[pos + 1 - nblignes * 2] == 'B' || niveau.cells[pos + 1 - nblignes * 2] == '#' || niveau.cells[pos + 2 - nblignes * 2] == 'B' || niveau.cells[pos + 2 - nblignes * 2] == '#' || niveau.cells[pos + 3 - nblignes * 2] == 'B' || niveau.cells[pos + 3 - nblignes * 2] == '#')
                    break;
                if (niveau.cells[pos + 4 - nblignes * 2] == ' ')
                    break;
                if (buff.cells[pos + 1 - nblignes * 3] == ACS_PLUS)
                {
                    if (buff.colors[pos + 1 - nblignes * 3] != key[0] && buff.colors[pos + 1 - nblignes * 3] != key[1] && buff.colors[pos + 1 - nblignes * 3] != key[2] && buff.colors[pos + 1 - nblignes * 3] != key[3])
                        break;
                }
                pos = pos - nblignes;
                directionTete = 1;
                movePlayer(&niveau, buff, pos, 3, directionTete);
                afficherDEBUG(niveau, windowDEBUG);
                level_display(windowLevel, niveau);
                wrefresh(windowLevel);
                break;
            case KEY_RIGHT:
                // Traitement de la touche "flèche droite"
                if (niveau.cells[pos + 1 + nblignes * 2] == 'B' || niveau.cells[pos + 1 + nblignes * 2] == '#' || niveau.cells[pos + 2 + nblignes * 2] == 'B' || niveau.cells[pos + 2 + nblignes * 2] == '#' || niveau.cells[pos + 3 + nblignes * 2] == 'B' || niveau.cells[pos + 3 + nblignes * 2] == '#')
                    break;
                if (niveau.cells[pos + 4 + nblignes * 2] == ' ')
                    break;
                if (buff.cells[pos + 1 + nblignes * 3] == ACS_PLUS)
                {
                    if (buff.colors[pos + 1 + nblignes * 3] != key[0] && buff.colors[pos + 1 + nblignes * 3] != key[1] && buff.colors[pos + 1 + nblignes * 3] != key[2] && buff.colors[pos + 1 + nblignes * 3] != key[3])
                        break;
                }
                pos = pos + nblignes;
                directionTete = 2;
                movePlayer(&niveau, buff, pos, 4, directionTete);
                afficherDEBUG(niveau, windowDEBUG);
                level_display(windowLevel, niveau);
                wrefresh(windowLevel);
                break;
            case 'o':
            case 'O':
                // Poser une bombe
                if (bombe == 0)
                {
                    mvwprintw(windowInformations, 2, 1, "Vous n'avez plus de bombes          ");
                    break;
                }
                subBomb(windowPlayerInformation);
                bombe--;
                pthread_create(Rbombe, NULL, placeBombe, (void *)&pos);
                break;
            }
            // Objet au sol ?
            switch (detectGround(buff, pos))
            {
                // Une vie
            case 1:
                buff.cells[pos + 3] = ' ';
                buff.colors[pos + 3] = 1;
                addLife(windowPlayerInformation);
                wattron(windowInformations, COLOR_PAIR(8));
                if (life != 5)
                {
                    life++;
                    mvwprintw(windowInformations, 2, 1, " +1 vie recupere  (%d)        ", life);
                }
                else
                {
                    mvwprintw(windowInformations, 2, 1, "Stock de bombe plein (%d)          ", bombe);
                }
                break;
                // Une bombe
            case 2:
                // Bombe posée ?
                if (pthread_mutex_trylock(&buff.mutex[pos + 3]) != 0)
                {
                    break;
                }
                buff.cells[pos + 3] = ' ';
                buff.colors[pos + 3] = 1;
                addBomb(windowPlayerInformation);
                wattron(windowInformations, COLOR_PAIR(8));
                if (bombe != 5)
                {
                    bombe++;
                    mvwprintw(windowInformations, 2, 1, "+1 bombe recupere (%d)        ", bombe);
                }
                else
                {
                    mvwprintw(windowInformations, 2, 1, "Stock de bombe plein (%d)           ", bombe);
                }
                pthread_mutex_unlock(&buff.mutex[pos + 3]);
                break;
            }
            // On marche sur une clé ?
            if (detectKey(buff, pos) == 1)
            {
                mvwprintw(windowInformations, 2, 1, "Cle trouve                            ");
                for (int i = 0; i < 4; i++)
                {
                    if (key[i] == 0)
                    {
                        switch (buff.colors[pos + 2 + nblignes])
                        {
                        case 10:
                            key[i] = 6;
                            addKey(windowPlayerInformation, 6);
                            break;
                        case 11:
                            key[i] = 3;
                            addKey(windowPlayerInformation, 3);
                            break;
                        case 12:
                            key[i] = 4;
                            addKey(windowPlayerInformation, 4);
                            break;
                        case 13:
                            key[i] = 5;
                            addKey(windowPlayerInformation, 5);
                            break;
                        }

                        buff.cells[pos + 2 + nblignes] = ' ';
                        buff.colors[pos + 2 + nblignes] = 1;
                        buff.cells[pos + 3 + nblignes] = ' ';
                        buff.colors[pos + 3 + nblignes] = 1;
                        break;
                    }
                }
            }

            // On est dans une porte ?
            if (detectDoor(buff, pos) == 1)
            {
                posDoor = searchDoorPair(buff, buff.cells[pos + nblignes], pos + nblignes);
                mvwprintw(windowInformations, 2, 1, "Teleporte a la porte : (%c)     ", buff.cells[pos + nblignes]);
                dispawnPlayer(&niveau, buff, pos, directionTete);
                pos = posDoor - nblignes;
                spawnPlayer(&niveau, posDoor, directionTete);
                afficherDEBUG(niveau, windowDEBUG);
                level_display(windowLevel, niveau);
                wrefresh(windowLevel);
            }
            // On est sur une sortie ?
            if (detectExit(buff, pos) == 1)
            {
                gagne = 1;
                level++;
            }

            for (int i = 0; i < 10; i++)
            {
                // Attention aux sondes !
                if (pos == probes[i].pos)
                {
                    if (probes[i].actif == 1)
                    {
                        life--;
                        subLife(windowPlayerInformation);
                        mvwprintw(windowInformations, 2, 1, "Vous avez perdu une vie (%d)          ", life);
                    }
                    // Attention aux robots !
                    if (pos == robots[i].pos)
                    {
                        if (robots[i].actif == 1)
                        {
                            life--;
                            subLife(windowPlayerInformation);
                            mvwprintw(windowInformations, 2, 1, "Vous avez perdu une vie (%d)          ", life);
                        }
                    }
                }
            }

            wrefresh(windowInformations);

            if (ch == 27)
                break;
            pthread_mutex_unlock(&mutex_affichage);
        }
        if (ch == 27)
            break;
    }
    free(Rbombe);
    free(table);
    // Supprimer fenêtres
    delwin(windowLevel);
    delwin(windowPlayerInformation);
    delwin(windowInformations);

    // Stop ncurses
    ncurses_stop();
}