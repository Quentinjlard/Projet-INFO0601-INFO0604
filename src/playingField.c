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
    for (posX = 5; posX > 0; posX--)
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
    for (posX = 5; posX > 0; posX--)
    {
        wattron(windowPlayerInformation, COLOR_PAIR(1));
        if (mvwinch(windowPlayerInformation, 12, posX) == 'o')
        {
            mvwprintw(windowPlayerInformation, 12, posX, " ");
            wrefresh(windowPlayerInformation);
            return;
        }
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

void playingField(char *filename)
{
    // Variables
    WINDOW *windowLevel, *windowPlayerInformation, *windowInformations, *windowDEBUG;
    int ch, pos, gagne, fd_World, err, directionTete = 1, life = 3, bombe = 3, level = 0, key[4];
    char nameWorld[256];
    level_t niveau, buff;
    tableAdressage_t *table;

    table = (tableAdressage_t *)malloc(sizeof(tableAdressage_t));
    memset(table->adresse, 0, sizeof(table->adresse));
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

    for (int k = 0; k < 20; k++)
    {
        gagne = 0;
        memset(key, 0, 4 * sizeof(int));
        // Initialisation du niveau (level_t)
        init_Level(windowLevel, windowInformations);
        init_matLevel(&niveau);
        niveau = loadLevel(level, table, nameWorld);
        buff = loadLevel(level, table, nameWorld);
        level_display(windowLevel, niveau);
        wrefresh(windowLevel);

        pos = searchStart(niveau) - level;
        spawnPlayer(&niveau, pos, directionTete);
        afficherDEBUG(niveau, windowDEBUG);
        level_display(windowLevel, niveau);
        wrefresh(windowLevel);
        while (gagne == 0)
        {
            switch (ch = getch())
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
            case 27:
                return;
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
                break;
            }
            // On marche sur une clé ?
            if (detectKey(buff, pos) == 1)
            {
                mvwprintw(windowInformations, 2, 1, "Cle trouve                      ");
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

            // On est sur une sortie ?
            if (detectExit(buff, pos) == 1)
            {
                gagne = 1;
                level++;
            }
            wrefresh(windowInformations);
        }
    }

    // Supprimer fenêtres
    delwin(windowLevel);
    delwin(windowPlayerInformation);
    delwin(windowInformations);

    // Stop ncurses
    ncurses_stop();
}