/**
 * @file menu.c
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
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
    char ext[4] = ".bin";

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

    mvprintw(2, 5 ,"  _____   _____    ____        _  ______  _______   _       ____   ");
    mvprintw(3, 5 ," |  __ \\ |  __ \\  / __ \\      | ||  ____||__   __| | |     |___ \\  ");
    mvprintw(4, 5 ," | |__)| | |__)| | |  | |     | || |__      | |    | |       __) | ");
    mvprintw(5, 5 ," |  ___/ |  _  / | |  | | _   | ||  __|     | |    | |      |__ <  ");
    mvprintw(6, 5 ," | |     | | \\ \\ | |__| || |__| || |____    | |    | |____  ___) | ");
    mvprintw(7, 5 ," |_|     |_|  \\_\\ \\____/  \\____/ |______|   |_|    |______||____/  ");

    attron(A_UNDERLINE);
    mvprintw(10, 6 ,"Select option :");
    attroff(A_UNDERLINE);
    mvprintw(12, 6 ," [ 1 ] Editor's mode ");
    mvprintw(13, 6 ," [ 2 ] Game mode ");

    attron(A_UNDERLINE);
    mvprintw(16, 6 ,"Credit  :");
    attron(COLOR_PAIR(4));
    attroff(A_UNDERLINE);
    mvprintw(20, 6 ,"Version :     ");
    attron(COLOR_PAIR(8));
    mvprintw(20, 19 ," [ 1.0 ] ");

    attron(COLOR_PAIR(3));
    mvprintw(18, 6 ,"Author :     ");
    attron(COLOR_PAIR(8));
    mvprintw(18, 19 ," [ JUILLIARD Quentin ] ");
    attron(COLOR_PAIR(3));
    mvprintw(19, 6 ,"Author :     ");
    attron(COLOR_PAIR(8));
    mvprintw(19, 19 ," [ COGNE Romain ] ");
    
    attron(COLOR_PAIR(2));
    mvprintw(23, 6 ," [ ESQ ] Exit ");
    attron(COLOR_PAIR(8));


    wrefresh(window);

    while((ch = getch()) != 27)
    {

        if(ch == '1')
        {
            echo();
            curs_set(TRUE);
            mvprintw(25, 6 ," Entering the name of the world : ");
            scanw("%s", nameWorld);
            mvprintw(26, 6 ,"Vous avez entré : %s\n", nameWorld);
            noecho();
            curs_set(FALSE);
            strncat(nameWorld, ext, 4);
            if((fd_World=open(nameWorld, O_WRONLY|O_CREAT|O_EXCL, S_IRUSR|S_IWUSR))==-1)
            {
                if(errno == EEXIST)
                    perror("The file already exists.");
                else
                    perror("Error create.");

                exit(EXIT_FAILURE);
            }else
                mvprintw(27,6,"File created \n");
            
            publisher(fd_World);
        }
        

            
        // 
        
    }

    // Delete windows
    delwin(window);

    // Stop ncurses
    ncurses_stop();  

}