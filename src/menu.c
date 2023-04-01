/**
 * @file menu.c
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2023-02-02
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

#include "includeAll.h"
#include "publisher.h"
#include "functions.h"

int main()
{
    // Variables
    WINDOW *window;
    int ch;
    char nameWorld[100];
    int fd_World = 0;
    char ext[] = ".bin";

    // Initialisation d'ncurses
    setlocale(LC_ALL, "");
    ncurses_init();
    ncurses_init_mouse();
    ncurses_colors();
    palette();

    // Créer la fenêtre principale
    window = newwin(29, 78, 0, 0);

    mvprintw(2, 5, "  _____   _____    ____        _  ______  _______   _       ____   ");
    mvprintw(3, 5, " |  __ \\ |  __ \\  / __ \\      | ||  ____||__   __| | |     |___ \\  ");
    mvprintw(4, 5, " | |__)| | |__)| | |  | |     | || |__      | |    | |       __) | ");
    mvprintw(5, 5, " |  ___/ |  _  / | |  | | _   | ||  __|     | |    | |      |__ <  ");
    mvprintw(6, 5, " | |     | | \\ \\ | |__| || |__| || |____    | |    | |____  ___) | ");
    mvprintw(7, 5, " |_|     |_|  \\_\\ \\____/  \\____/ |______|   |_|    |______||____/  ");

    attron(A_UNDERLINE);
    mvprintw(10, 6, "Select option :");
    attroff(A_UNDERLINE);
    mvprintw(12, 6, " [ 1 ] Editor's mode ");
    mvprintw(13, 6, " [ 2 ] Game mode ");

    attron(A_UNDERLINE);
    mvprintw(16, 6, "Credit  :");
    attron(COLOR_PAIR(4));
    attroff(A_UNDERLINE);
    mvprintw(20, 6, "Version :     ");
    attron(COLOR_PAIR(8));
    mvprintw(20, 19, " [ 1.0 ] ");

    attron(COLOR_PAIR(3));
    mvprintw(18, 6, "Author :     ");
    attron(COLOR_PAIR(8));
    mvprintw(18, 19, " [ JUILLIARD Quentin ] ");
    attron(COLOR_PAIR(3));
    mvprintw(19, 6, "Author :     ");
    attron(COLOR_PAIR(8));
    mvprintw(19, 19, " [ COGNE Romain ] ");

    attron(COLOR_PAIR(2));
    mvprintw(23, 6, " [ ESQ ] Exit ");
    attron(COLOR_PAIR(8));

    wrefresh(window);

    while ((ch = getch()) != 27)
    {

        if (ch == '1')
        {
            echo();
            curs_set(TRUE);
            mvprintw(25, 6, " Entre le nom du monde : ");
            scanw("%s", nameWorld);
            noecho();
            curs_set(FALSE);

            size_t total_len = strlen(nameWorld) + strlen(ext);
            if (total_len < 100)
                strncat(nameWorld, ext, 100 - strlen(nameWorld));
            else
                mvprintw(27, 6, "Erreur : taille buffer insuffisante\n");

            if ((fd_World = open(nameWorld, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
            {
                perror("Erreur ouverture du fichier");
                exit(EXIT_FAILURE);
            }
            if (close(fd_World) == -1)
            {
                perror("Erreur fermeture du fichier");
                exit(EXIT_FAILURE);
            }

            publisher(nameWorld);

            // Supprimer fenêtre
            delwin(window);

            // Stop ncurses
            ncurses_stop();
        }

        if (ch == '2')
        {
            // Supprimer fenêtre
            delwin(window);

            // Stop ncurses
            ncurses_stop();

            // Lancement du client
            client();
        }
    }
}