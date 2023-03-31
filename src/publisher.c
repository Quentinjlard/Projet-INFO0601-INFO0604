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
#include <locale.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

#include "publisher.h"
#include "item.h"

void publisher(char *nameWorld)
{
    // Variables
    WINDOW *windowLevel, *windowTools, *windowInformations, *windowDEBUG;
    int door = 01, ch, posX, err, posY, life = 00, bomb = 0, fd_World, level = 0;
    int outil = -1;
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

    // Création fenêtre de debugage
    windowDEBUG = newwin(22, 62, 0, 80);
    scrollok(windowDEBUG, TRUE);
    box(windowDEBUG, 0, 0);
    mvwprintw(windowDEBUG, 0, 0, "DEBUG");

    // Crée la fenêtre du niveau
    windowLevel = newwin(22, 62, 0, 0);
    scrollok(windowLevel, TRUE);
    box(windowLevel, 0, 0);
    mvwprintw(windowLevel, 0, 0, "Level");
    

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
    

    // Initialisation du niveau (level_t)
    init_Level(windowLevel, windowInformations);
    init_matLevel(&niveau);
    niveau = loadLevel(level, table, nameWorld);
    level_display(windowLevel, niveau);


    wrefresh(windowLevel);
    wrefresh(windowTools);
    wrefresh(windowInformations);

    // Stop 'ESP'
    while ((ch = getch()) != 27)
    {
        mvwprintw(windowInformations, 2, 1, "                                       ");
        mvwprintw(windowInformations, 3, 1, "                                       ");
        wrefresh(windowInformations);
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
            
            if (posY == 1 && 66 <= posX && posX <= 71) 
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Delete"), wrefresh(windowTools), outil = DELETE,mvwprintw(windowInformations, 3, 1, "Outil selectionne : DELETE                ");

            if (posY == 2 && 66 <= posX && posX <= 70)
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Block"), wrefresh(windowTools), outil = BLOCK,mvwprintw(windowInformations, 3, 1, "Outil selectionne : BLOCK                "); 

            if (posY == 3 && 66 <= posX && posX <= 71)
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Ladder"), wrefresh(windowTools), outil = LADDER,mvwprintw(windowInformations, 3, 1, "Outil selectionne : LADDER                ");

            if (posY == 4 && 66 <= posX && posX <= 69)
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Trap"), wrefresh(windowTools), outil = TRAP,mvwprintw(windowInformations, 3, 1, "Outil selectionne : TRAP                "); 

            if (posY == 5 && 66 <= posX && posX <= 69)
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Gate"), wrefresh(windowTools), outil = GATE,mvwprintw(windowInformations, 3, 1, "Outil selectionne : GATE                "); 

            if (posY == 6 && 66 <= posX && posX <= 68)
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Key"), wrefresh(windowTools), outil = KEY,mvwprintw(windowInformations, 3, 1, "Outil selectionne : KEY                "); 

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
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Door"), wrefresh(windowTools), outil = DOOR,mvwprintw(windowInformations, 3, 1, "Outil selectionne : DOOR                "); 

            if (posY == 8 && 66 <= posX && posX <= 68)
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Exit"), wrefresh(windowTools), outil = EXIT,mvwprintw(windowInformations, 3, 1, "Outil selectionne : EXIT                "); 

            if (posY == 9 && 66 <= posX && posX <= 69)
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Start"), wrefresh(windowTools), outil = START,mvwprintw(windowInformations, 3, 1, "Outil selectionne : START                ");

            if (posY == 10 && 66 <= posX && posX <= 69)
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Robot"), wrefresh(windowTools), outil = ROBOT,mvwprintw(windowInformations, 3, 1, "Outil selectionne : ROBOT                ");

            if (posY == 11 && 66 <= posX && posX <= 69)
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Probe"), wrefresh(windowTools), outil = PROBE,mvwprintw(windowInformations, 3, 1, "Outil selectionne : PROBE                ");

            if (posY == 12 && 66 <= posX && posX <= 68)
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Life"), wrefresh(windowTools), outil = LIFE,mvwprintw(windowInformations, 3, 1, "Outil selectionne : LIFE                "); 

            if (posY == 13 && 66 <= posX && posX <= 68)
                init_Tools(windowTools, level, door),wattron(windowTools, COLOR_PAIR(8)),mvwprintw(windowTools, posY, 1, "> Bomb"), wrefresh(windowTools), outil = BOMBE,mvwprintw(windowInformations, 3, 1, "Outil selectionne : BOMB                ");

            if (posY == 17 && posX == 67) // Diminuer
            {
                if (level == 0) {
                    level = 25;
                    mvwprintw(windowTools, 17, 6, "%.3d", level);
                }
                    
                else {
                    level--;
                    mvwprintw(windowTools, 17, 6, "%.3d", level);
                }
                niveau = loadLevel(level, table,nameWorld);
                level_display(windowLevel, niveau);
                afficherDEBUG(niveau, windowDEBUG);
                wrefresh(windowTools);
                wrefresh(windowDEBUG);
                    
            }

            if (posY == 17 && posX == 73) // Augmenter
            {
                if (level == 25) {
                    level = 0; 
                    mvwprintw(windowTools, 17, 6, "%.3d", level);
                }
                    
                else {
                    level++; 
                    mvwprintw(windowTools, 17, 6, "%.3d", level);
                }
                niveau = loadLevel(level, table,nameWorld );
                level_display(windowLevel, niveau);
                afficherDEBUG(niveau, windowDEBUG);
                wrefresh(windowTools);
                wrefresh(windowDEBUG);
                    
            }

            if (posY == 19 && 67 <= posX && posX <= 72)
            {
                init_Level(windowLevel, windowInformations);
                supprimerLevel(table, level, nameWorld);
                clear_windowLevel(windowLevel);
                init_matLevel(&niveau);
                afficherDEBUG(niveau, windowDEBUG);
                mvwprintw(windowInformations, 3, 1, "Niveau supprime                ");
                wrefresh(windowInformations);
                wrefresh(windowLevel);
            }

            wattron(windowInformations, COLOR_PAIR(8));
            afficherDEBUG(niveau, windowDEBUG);
            wrefresh(windowTools);
            wrefresh(windowInformations);
            wrefresh(windowLevel);

            if ((posX >= 1 && posX < 61) && (posY >= 1 && posY < 21))
            {
                switch (outil)
                {
                case -1:
                    mvwprintw(windowInformations, 3, 1, "Aucun outil selectionne                 ");
                    wrefresh(windowInformations);
                    break;
                case DELETE:
                    delete(windowLevel, windowInformations, &niveau,posX,posY);
                    break;
                case BLOCK:
                    place_block(windowLevel, windowInformations, &niveau,posX,posY);
                    break;
                case LADDER:
                    place_ladder(windowLevel, windowInformations, &niveau,posX,posY);
                    break;
                case TRAP:
                    place_Trap(windowLevel, windowInformations, &niveau,posX,posY);
                    break;    
                case GATE:
                    place_Gate(windowLevel, windowInformations, windowTools, &niveau);
                    break;
                case KEY:
                    place_Key(windowLevel, windowInformations, windowTools, &niveau);
                    break;
                case DOOR:
                    place_Door(windowLevel, windowInformations,door, &niveau,posX,posY);
                    break;
                case EXIT:
                    place_Exit(windowLevel, windowInformations, &niveau,posX,posY);
                    break;
                case START:
                    place_Start(windowLevel, windowInformations, &niveau,posX,posY);
                    break;
                case ROBOT:
                    place_Robot(windowLevel, windowInformations, &niveau,posX,posY);
                    break;  
                case PROBE:
                    place_Probe(windowLevel, windowInformations, &niveau,posX,posY);
                    break;
                case LIFE:
                    place_Life(windowLevel, windowInformations, &niveau,posX,posY);
                    life++;
                    break;
                case BOMBE:
                    place_bomb(windowLevel, windowInformations, &niveau,posX,posY); 
                    bomb++;
                    break; 
                }   
            }
            break;

        // Sauvegarde
        case 's':
        case 'S':
            supprimerLevel(table, level, nameWorld);
            ajouterLevel(&niveau, table, nameWorld);
            mvwprintw(windowInformations, 3, 1, "Level sauvegarde                 ");
            wrefresh(windowInformations);
            break;
        }
    }

    // Supprimer fenêtres
    delwin(windowLevel);
    delwin(windowTools);
    delwin(windowInformations);
    delwin(windowDEBUG);

    // Stop ncurses
    ncurses_stop();
}