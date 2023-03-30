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
#include "item.h"
#include "functions.h"

void playingField(char *filename)
{
    // Variables
    int ch;
    char nomLevel[256];
    // int posY, posX;

    strcpy(nomLevel, filename);
    WINDOW *window, *windowLevel, *windowPlayerInformation, *windowInformations;
    // int door = 01, life=00, bomb = 00, fd_World;
    char level = 01;

    // Initialisation d'ncurses
    setlocale(LC_ALL, "");
    ncurses_init();
    ncurses_init_mouse();
    ncurses_colors();
    palette();

    // Création fenêtre principale
    window = newwin(29, 78, 0, 0);

    // Création fenêtre de jeu
    windowLevel = newwin(22, 62, 0, 0);
    scrollok(windowLevel, TRUE);
    box(windowLevel, 0, 0);
    mvwprintw(windowLevel, 0, 0, "Level");

    // Création fenêtre d'information de jeu
    windowPlayerInformation = newwin(22, 15, 0, 63);
    scrollok(windowPlayerInformation, TRUE);
    box(windowPlayerInformation, 0, 0);
    // mvwprintw(windowPlayerInformation, 0, 0, "Information");

    // Création fenêtre de message d'information
    windowInformations = newwin(5, 77, 23, 0);
    scrollok(windowInformations, TRUE);
    box(windowInformations, 0, 0);
    mvwprintw(windowInformations, 0, 0, "Informations");

    init_Level(windowLevel, windowInformations);

    init_PlayInformations(windowPlayerInformation, level);

    wrefresh(window);
    wrefresh(windowLevel);
    wrefresh(windowPlayerInformation);
    wrefresh(windowInformations);

    wattron(windowInformations, COLOR_PAIR(2));
    mvwprintw(windowInformations, 1, 1, "Press 'ESQ' to quit ...");
    wrefresh(windowInformations);

    // Cherche le start
    for (int i = 2; i < 60; i++)
    {
        for (int j = 2; j < 20; j++)
        {
            // if (mvwinch(windowLevel, j, i) ==)
        }
    }

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
            break;
        }
    }

    // Supprimer fenêtres
    delwin(window);
    delwin(windowLevel);
    delwin(windowPlayerInformation);
    delwin(windowInformations);

    // Stop ncurses
    ncurses_stop();
}