/**
 * @file publisher.c
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2022-12-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <locale.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#include "publisher.h"

void publisher(char *nameWorld)
{
    // Variables
    WINDOW *window, *windowLevel, *windowTools, *windowInformations, *windowDEBUG;
    int door = 01, ch, posX, err, posY, life = 00, bomb = 0, fd_World, level = 0;
    tableAdressage_t *table;
    table = (tableAdressage_t *)malloc(sizeof(tableAdressage_t));
    memset(table->adresse, 0, sizeof(table->adresse));
    level_t niveau;

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

    // Fermeture fichier
    if (close(fd_World) == -1)
    {
        perror("Erreur fermeture descripteur fichier (publisher).");
        exit(EXIT_FAILURE);
    }

    // Initialisation ncurses
    setlocale(LC_ALL, "");
    ncurses_init();
    ncurses_init_mouse();
    ncurses_colors();
    palette();

    // Crée la fenêtre principale
    window = newwin(29, 78, 0, 0);

    // Crée la fenêtre du niveau
    windowLevel = newwin(22, 62, 0, 0);
    scrollok(windowLevel, TRUE);
    box(windowLevel, 0, 0);
    mvwprintw(windowLevel, 0, 0, "Level");
    init_Level(windowLevel, windowInformations);

    // Crée la fenêtre des outils
    windowTools = newwin(22, 15, 0, 63);
    scrollok(windowTools, TRUE);
    box(windowTools, 0, 0);
    mvwprintw(windowTools, 0, 0, "Tools");
    init_Tools(windowTools, level, door);
    wrefresh(windowTools);

    // Crée la fenêtre des messages d'informations
    windowInformations = newwin(5, 77, 23, 0);
    scrollok(windowInformations, TRUE);
    box(windowInformations, 0, 0);
    mvwprintw(windowInformations, 0, 0, "Informations");
    wattron(windowInformations, COLOR_PAIR(2));
    mvwprintw(windowInformations, 1, 1, "Press 'ESQ' to quit ...");
    wrefresh(windowInformations);

    // Création fenêtre de debugage
    windowDEBUG = newwin(25, 70, 0, 80);
    scrollok(windowDEBUG, TRUE);
    box(windowDEBUG, 0, 0);
    mvwprintw(windowDEBUG, 0, 0, "DEBUG");
    wrefresh(windowDEBUG);

    // Initialisation du niveau (level_t)
    init_matLevel(&niveau);
    niveau = loadLevel(level, table, nameWorld);
    level_display(windowLevel, niveau);
    wrefresh(windowLevel);

    wrefresh(window);

    // Stop 'ESP'
    while ((ch = getch()) != 27)
    {
        mvwprintw(windowInformations, 2, 1, "                                       ");
        wrefresh(windowInformations);
        init_Tools(windowTools, level, door);
        wrefresh(windowTools);
        afficherDEBUG(niveau, windowDEBUG);
        switch (ch)
        {
        case KEY_MOUSE:
            if (mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
            }
            wattron(windowTools, COLOR_PAIR(8));
            if (posY == 1 && 66 <= posX && posX <= 71)
                mvwprintw(windowTools, posY, 1, "> Delete");

            if (posY == 2 && 66 <= posX && posX <= 70)
                mvwprintw(windowTools, posY, 1, "> Block"), wrefresh(windowTools), place_block(windowLevel, windowInformations, &niveau);

            if (posY == 3 && 66 <= posX && posX <= 71)
                mvwprintw(windowTools, posY, 1, "> Ladder"), wrefresh(windowTools), place_ladder(windowLevel, windowInformations, &niveau);

            if (posY == 4 && 66 <= posX && posX <= 69)
                mvwprintw(windowTools, posY, 1, "> Trap"), wrefresh(windowTools), place_Trap(windowLevel, windowInformations, &niveau);

            if (posY == 5 && 66 <= posX && posX <= 69)
                mvwprintw(windowTools, posY, 1, "> Gate"), wrefresh(windowTools), place_Gate(windowLevel, windowInformations, windowTools, &niveau);

            if (posY == 6 && 66 <= posX && posX <= 68)
                mvwprintw(windowTools, posY, 1, "> Key"), wrefresh(windowTools), place_Key(windowLevel, windowInformations, windowTools, &niveau);

            if (posY == 7 && posX == 72)
            {
                if (door == 1)
                    door = 5, mvwprintw(windowTools, 7, 10, "%.2d", door);
                else
                    door--, mvwprintw(windowTools, 7, 10, "%.2d", door);
            }

            if (posY == 7 && posX == 75)
            {
                if (door == 5)
                    door = 1, mvwprintw(windowTools, 7, 10, "%.2d", door);
                else
                    door++, mvwprintw(windowTools, 7, 10, "%.2d", door);
            }

            if (posY == 7 && 66 <= posX && posX <= 69)
                mvwprintw(windowTools, posY, 1, "> Door"), wrefresh(windowTools), place_Door(windowLevel, windowInformations, door, &niveau);

            if (posY == 8 && 66 <= posX && posX <= 68)
                mvwprintw(windowTools, posY, 1, "> Exit"), wrefresh(windowTools), place_Exit(windowLevel, windowInformations, &niveau);

            if (posY == 9 && 66 <= posX && posX <= 69)
                mvwprintw(windowTools, posY, 1, "> Start"), wrefresh(windowTools), place_Start(windowLevel, windowInformations, &niveau);

            if (posY == 10 && 66 <= posX && posX <= 69)
                mvwprintw(windowTools, posY, 1, "> Robot"), wrefresh(windowTools), place_Robot(windowLevel, windowInformations, &niveau);

            if (posY == 11 && 66 <= posX && posX <= 69)
                mvwprintw(windowTools, posY, 1, "> Probe"), wrefresh(windowTools), place_Probe(windowLevel, windowInformations, &niveau);

            if (posY == 12 && 66 <= posX && posX <= 68)
                mvwprintw(windowTools, posY, 1, "> Life"), wrefresh(windowTools), place_Life(windowLevel, windowInformations, &niveau), life++;

            if (posY == 13 && 66 <= posX && posX <= 68)
                mvwprintw(windowTools, posY, 1, "> Bomb"), wrefresh(windowTools), place_bomb(windowLevel, windowInformations, &niveau), bomb++;

            if (posY == 17 && posX == 67) // Diminuer
            {
                if (level == 1)
                    level = 25, mvwprintw(windowTools, 17, 6, "%.3d", level);
                else
                    level--, mvwprintw(windowTools, 17, 6, "%.3d", level);
            }

            if (posY == 17 && posX == 73) // Augmenter
            {
                if (level == 25)
                    level = 1, mvwprintw(windowTools, 17, 6, "%.3d", level);
                else
                    level++, mvwprintw(windowTools, 17, 6, "%.3d", level);
            }

            if (posY == 19 && 67 <= posX && posX <= 72)
            {
                init_Level(windowLevel, windowInformations);
                supprimerLevel(table, level, nameWorld);
                clear_windowLevel(windowLevel);
                afficherDEBUG(niveau, windowDEBUG);
                mvwprintw(windowInformations, 3, 1, "Niveau supprimé                ");
                wrefresh(windowInformations);
                wrefresh(windowLevel);
            }

            wattron(windowInformations, COLOR_PAIR(8));

            wrefresh(windowTools);
            wrefresh(windowInformations);
            wrefresh(windowLevel);
            break;

        // Sauvegarde
        case 's':
            supprimerLevel(table, level, nameWorld);
            ajouterLevel(&niveau, table, nameWorld);
            mvwprintw(windowInformations, 3, 1, "Level sauvegardé                 ");
            wrefresh(windowInformations);
            break;
        }
    }

    // Supprimer fenêtres
    delwin(window);
    delwin(windowLevel);
    delwin(windowTools);
    delwin(windowInformations);
    delwin(windowDEBUG);

    // Stop ncurses
    ncurses_stop();
}