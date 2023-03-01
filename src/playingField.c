/**
 * @file playingField.c
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @brief 
 * @version 0.1
 * @date 2023-02-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "playingField.h"

void playingField()
{
    // Variable arena
    int ch;
    WINDOW *window, *windowLevel, *windowPlayerInformation, *windowInformations;
    //int door = 01, life=00, bomb = 00, fd_World;
    char level = 01;

    // NCurses intialization
    // NCURSES Initialization
    setlocale(LC_ALL, "");
    ncurses_init();
    ncurses_init_mouse();
    ncurses_colors();
    palette();

    // newwin(Size Y , Size X, Position Y, Position X)
    // Create the main window with a box
    window = newwin(29, 78, 0, 0);

    // subwin(WINDOW window,Size Y , Size X, Position Y, Position X)
    // Create the windowLevel
    windowLevel = newwin(22, 62, 0, 0);
    scrollok(windowLevel, TRUE);
    box(windowLevel, 0, 0);
    mvwprintw(windowLevel, 0, 0, "Level");
    
    // Create the windowPlayerInformation
    windowPlayerInformation = newwin(22, 15, 0, 63);
    scrollok(windowPlayerInformation, TRUE);
    box(windowPlayerInformation, 0, 0);
    // mvwprintw(windowPlayerInformation, 0, 0, "Information");

    // Create the windowInformations
    windowInformations = newwin(5, 77, 23, 0);
    scrollok(windowInformations, TRUE);
    box(windowInformations, 0, 0);
    mvwprintw(windowInformations, 0, 0, "Informations");

    init_Level(windowLevel,windowInformations);
    
    init_PlayInformations(windowPlayerInformation, level);

    wrefresh(window);
    wrefresh(windowLevel);
    wrefresh(windowPlayerInformation);
    wrefresh(windowInformations);


    wattron(windowInformations,COLOR_PAIR(2));
    mvwprintw(windowInformations, 1, 1, "Press 'ESQ' to quit ...");
    wrefresh(windowInformations);

    while((ch = getch()) != 27)
    {
    }

    // Delete windows
    delwin(window);
    delwin(windowLevel);
    delwin(windowPlayerInformation);
    delwin(windowInformations);

    // Stop ncurses
    ncurses_stop();  
}