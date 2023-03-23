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
#include "includeAll.h"

int main()
{
    // Variable Arena
    WINDOW *window;
    int ch;
    // int statut = 0;
    // fileMap_t fileMap;
    char nameWorld[100];
    int fd_World;
    char ext[] = ".bin";

    // fileMap = (fileMap_t*) malloc(sizeof(fileMap_t));

    // statut = open()

    // NCURSES Initialization
    setlocale(LC_ALL, "");
    ncurses_init();
    ncurses_init_mouse();
    ncurses_colors();
    palette();

    // newwin(Size Y , Size X, Position Y, Position X)
    // Create the main window with a box
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
            // MODE = 0;
            echo();
            curs_set(TRUE);
            mvprintw(25, 6, " Entering the name of the world : ");
            scanw("%s", nameWorld);
            // mvprintw(26, 6 ,"Vous avez entré : %s\n", nameWorld);
            noecho();
            curs_set(FALSE);

            size_t total_len = strlen(nameWorld) + strlen(ext);
            if (total_len < 100)
                strncat(nameWorld, ext, 100 - strlen(nameWorld));
            else
                mvprintw(27, 6, "Error: insufficient buffer size\n");

            if ((fd_World = open(nameWorld, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR)) == -1)
            {
                if (errno == EEXIST)
                    perror("The file already exists.");
                else
                {
                    perror("Error create.");
                    exit(EXIT_FAILURE);
                }
                // exit(EXIT_FAILURE); //Il faudrait mettre celui du dessus pour que l'on ouvre le fichier
            }
            else
                mvprintw(27, 6, "File created \n");

            if (close(fd_World) == -1)
            {
                perror("Error closing file");
                exit(EXIT_FAILURE);
            }

            publisher(nameWorld);

            // Delete windows
            delwin(window);

            // Stop ncurses
            ncurses_stop();
        }
        if (ch == '2')
        {
            // MODE = 1;
            // echo();
            // curs_set(TRUE);
            // mvprintw(25, 6, " Enter number of players : ");
            // scanw("%s", nameWorld);
            // mvprintw(26, 6, "Vous avez entre : %s\n", nameWorld);
            // noecho();
            // curs_set(FALSE);

            // struct dirent *file;
            // // opendir() renvoie un pointeur de type DIR.
            // DIR *dir = opendir(".");
            // if (!dir)
            // {
            //     printf("Erreur : Impossible d'ouvrir le dossier.\n");
            //     return 1;
            // }

            // int i = 1;
            // int ligne = 27;
            // if (dir)
            // {
            //     while ((file = readdir(dir)) != NULL)
            //     {
            //         if (file->d_type == DT_REG && strstr(file->d_name, ".bin") != NULL)
            //         {
            //             char *filename = strtok(file->d_name, ".");
            //             mvprintw(ligne, 6, "[%2d] %s \t", i, filename);
            //             i++;
            //             ligne++;
            //         }
            //     }
            //     closedir(dir);
            // }

            // echo();
            // curs_set(TRUE);
            // mvprintw(ligne, 6, " Entering the name of the world : ");
            // scanw("%s", nameWorld);
            // // mvprintw(26, 6 ,"Vous avez entré : %s\n", nameWorld);
            // noecho();
            // curs_set(FALSE);

            // size_t total_len = strlen(nameWorld) + strlen(ext);
            // if (total_len < 100)
            //     strncat(nameWorld, ext, 100 - strlen(nameWorld));
            // else
            //     mvprintw(27, 6, "Error: insufficient buffer size\n");

            // mvprintw(ligne + 1, 6, "Vous avez entre : %s \n", nameWorld);

            // playingField();

            // Delete windows
            delwin(window);

            // Stop ncurses
            ncurses_stop();
            // Lancement du client
            client();
        }
    }
}