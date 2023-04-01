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

#include "playingField.h"

#include "functions.h"

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

void movePlayer(level_t *niveau, level_t buff, int pos, int direction)
{
    switch (direction)
    {
    // UP
    case 1:
        break;
    // DOWN
    case 2:
        break;
    // LEFT
    case 3:
        break;
    // RIGHT
    case 4:
        spawnPlayer(niveau, pos);
        // Haut
        niveau->cells[pos + 1 - nblignes * 2] = buff.cells[pos - nblignes * 2];
        niveau->colors[pos + 1 - nblignes * 2] = buff.colors[pos - nblignes * 2];

        // Milieu
        niveau->cells[pos + 2 - nblignes * 2] = buff.cells[pos + 1 - nblignes * 2];
        niveau->colors[pos + 2 - nblignes * 2] = buff.colors[pos + 1 - nblignes * 2];

        // Bas
        niveau->cells[pos + 3 - nblignes * 2] = buff.cells[pos + 2 - nblignes * 2];
        niveau->colors[pos + 3 - nblignes * 2] = buff.colors[pos + 2 - nblignes * 2];

        break;
    }
}

void spawnPlayer(level_t *niveau, int pos)
{
    // Tete
    niveau->cells[pos + 1 - nblignes] = '-';
    niveau->colors[pos + 1 - nblignes] = 14;
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

void playingField(char *filename)
{
    // Variables
    int ch, fd_World, err; // life = 3;
    char nameWorld[256];
    tableAdressage_t *table;
    table = (tableAdressage_t *)malloc(sizeof(tableAdressage_t));
    memset(table->adresse, 0, sizeof(table->adresse));
    level_t niveau, buff;
    int pos;
    // int posY, posX;
    WINDOW *windowLevel, *windowPlayerInformation, *windowInformations, *windowDEBUG;
    // int door = 01, life=00, bomb = 00, fd_World;
    char level = 00;

    strcpy(nameWorld, filename);

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
    init_PlayInformations(windowPlayerInformation, level);
    wrefresh(windowPlayerInformation);

    // Création fenêtre de message d'information
    windowInformations = newwin(5, 77, 23, 0);
    scrollok(windowInformations, TRUE);
    box(windowInformations, 0, 0);
    mvwprintw(windowInformations, 0, 0, "Informations");
    wattron(windowInformations, COLOR_PAIR(2));
    mvwprintw(windowInformations, 1, 1, "Press 'ESQ' to quit ...");
    wrefresh(windowInformations);

    // Initialisation du niveau (level_t)
    init_Level(windowLevel, windowInformations);
    init_matLevel(&niveau);
    niveau = loadLevel(level, table, nameWorld);
    buff = loadLevel(level, table, nameWorld);
    level_display(windowLevel, niveau);
    wrefresh(windowLevel);

    pos = searchStart(niveau);
    spawnPlayer(&niveau, pos);
    afficherDEBUG(niveau, windowDEBUG);
    level_display(windowLevel, niveau);
    wrefresh(windowLevel);

    while ((ch = getch()) != 27)
    {
        switch (ch)
        {
        case KEY_UP:
            // Traitement de la touche "flèche haut"
            break;
        case KEY_DOWN:
            // Traitement de la touche "flèche bas"
            break;
        case KEY_LEFT:
            // Traitement de la touche "flèche gauche"
            break;
        case KEY_RIGHT:
            // Traitement de la touche "flèche droite"
            if (niveau.cells[pos + nblignes * 2] == 'B' || niveau.cells[pos + nblignes * 2] == '#')
                break;
            pos = pos + nblignes;
            movePlayer(&niveau, buff, pos, 4);
            afficherDEBUG(niveau, windowDEBUG);
            level_display(windowLevel, niveau);
            wrefresh(windowLevel);

            break;
        }
    }

    // Supprimer fenêtres
    delwin(windowLevel);
    delwin(windowPlayerInformation);
    delwin(windowInformations);

    // Stop ncurses
    ncurses_stop();
}