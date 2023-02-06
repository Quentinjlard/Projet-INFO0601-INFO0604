/**
 * @file interface.c
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @brief 
 * @version 0.1
 * @date 2022-12-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "publisher.h"

void publisher(char* nameWorld)
{
    //Variable Arena
    WINDOW *window, *windowLevel, *windowTools, *windowInformations;
    int door = 01, level = 01, ch, posX, posY, color = 9, life=00, bomb = 0, fd_World;

    if((fd_World=open(nameWorld, O_WRONLY|O_RDONLY))==-1)
    {
        if(errno == EEXIST)
            perror("The file already exists.");
        else 
        {
            perror("Error create.");
            //exit(EXIT_FAILURE);
        }
            exit(EXIT_FAILURE); //Il faudrait mettre celui du dessus pour que l'on ouvre le fichier 
    }

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
    
    // Create the windowTools
    windowTools = newwin(22, 15, 0, 63);
    scrollok(windowTools, TRUE);
    box(windowTools, 0, 0);
    mvwprintw(windowTools, 0, 0, "Tools");

    // Create the windowInformations
    windowInformations = newwin(5, 77, 23, 0);
    scrollok(windowInformations, TRUE);
    box(windowInformations, 0, 0);
    mvwprintw(windowInformations, 0, 0, "Informations");

    init_Level(windowLevel,windowInformations);
    
    init_Tools(windowTools, level, door);

    wrefresh(window);
    wrefresh(windowLevel);
    wrefresh(windowTools);
    wrefresh(windowInformations);


    wattron(windowInformations,COLOR_PAIR(2));
    mvwprintw(windowInformations, 1, 1, "Press 'ESQ' to quit ...");
    wrefresh(windowInformations);

    /**
     * Erreur ici lors de l'ouverture d'un fichier
     */
    lseek(fd_World,0,SEEK_SET);
    if(write(fd_World, &level, sizeof(int)) == -1) 
    {
        perror("Error writing integer");
        exit(EXIT_FAILURE);
    }
    lseek(fd_World,64,SEEK_CUR);
    if(write(fd_World, &level, sizeof(int)) == -1) 
    {
        perror("Error writing integer");
        exit(EXIT_FAILURE);
    }

    // Stop 'ESP'
    while((ch = getch()) != 27)
    {
        color = 9;
        mvwprintw(windowInformations, 2, 1,"                                       ");
        wrefresh(windowInformations);
        init_Tools(windowTools, level, door);
        wrefresh(windowTools);
        switch(ch) 
        {
            case KEY_MOUSE:
                if(mouse_getpos(&posX, &posY) == OK)
                {
                    posY = posY;
                    posX = posX;
                    
                }
        }
            wattron(windowTools,COLOR_PAIR(8));
            if(posY == 1 && 66 <= posX && posX <=71)
                mvwprintw(windowTools, posY, 1, "> Delete");
            
            if(posY == 2 && 66 <= posX && posX <=70)
                mvwprintw(windowTools, posY, 1, "> Block"), wrefresh(windowTools), place_block(windowLevel,windowInformations);

            if(posY == 3 && 66 <= posX && posX <=71)
                mvwprintw(windowTools, posY, 1, "> Ladder"), wrefresh(windowTools), place_ladder(windowLevel, windowInformations);
            
            if(posY == 4 && 66 <= posX && posX <=69)
                mvwprintw(windowTools, posY, 1, "> Trap"), wrefresh(windowTools), place_Trap(windowLevel,windowInformations);

            if(posY == 5 && 66 <= posX && posX <=69)
                mvwprintw(windowTools, posY, 1, "> Gate"), wrefresh(windowTools), place_Gate(windowLevel,windowInformations,windowTools,color);


            if(posY == 6 && 66 <= posX && posX <=68)
                mvwprintw(windowTools, posY, 1, "> Key"), wrefresh(windowTools), place_Key(windowLevel, windowInformations, windowTools, color);

            if(posY == 7 && posX == 72)
            {   
                if (door == 1)
                    door = 99, mvwprintw(windowTools, 7, 10, "%.2d",door);
                else
                    door -- , mvwprintw(windowTools, 7, 10, "%.2d",door);
            }
            
            if(posY == 7 && posX == 75)
            {   
                if (door == 99)
                    door = 1, mvwprintw(windowTools, 7, 10, "%.2d",door);
                else
                    door ++ , mvwprintw(windowTools, 7, 10, "%.2d",door);
            }

            if(posY == 7 && 66 <= posX && posX <=69)
                mvwprintw(windowTools, posY, 1, "> Door"), wrefresh(windowTools), place_Door(windowLevel, windowInformations, door);

            if(posY == 8 && 66 <= posX && posX <=68)
                mvwprintw(windowTools, posY, 1, "> Exit"),  wrefresh(windowTools), place_Exit(windowLevel, windowInformations);

            if(posY == 9 && 66 <= posX && posX <=69)
                mvwprintw(windowTools, posY, 1, "> Start"),  wrefresh(windowTools), place_Start(windowLevel, windowInformations);

            if(posY == 10 && 66 <= posX && posX <=69)
                mvwprintw(windowTools, posY, 1, "> Robot"),  wrefresh(windowTools), place_Robot(windowLevel, windowInformations);

            if(posY == 11 && 66 <= posX && posX <=69)
                mvwprintw(windowTools, posY, 1, "> Probe"), wrefresh(windowTools), place_Probe(windowLevel, windowInformations);

            if(posY == 12 && 66 <= posX && posX <=68)
                mvwprintw(windowTools, posY, 1, "> Life"), wrefresh(windowTools), place_Life( windowLevel, windowInformations, life), life++ ;

            if(posY == 13 && 66 <= posX && posX <=68)
                mvwprintw(windowTools, posY, 1, "> Bomb"), wrefresh(windowTools), place_bomb( windowLevel, windowInformations, bomb), bomb++;

            if(posY == 17 && posX == 67)
            {   
                if (level == 1)
                    level = 999,mvwprintw(windowTools, 17, 6, "%.3d",level);
                else
                    level -- , mvwprintw(windowTools, 17, 6, "%.3d",level);
            }

            if(posY == 17 && posX == 73)
            {   
                if (level == 999)
                    level = 1,mvwprintw(windowTools, 17, 6, "%.3d",level);
                else
                    level ++ , mvwprintw(windowTools, 17, 6, "%.3d",level);
            }

            if(posY == 19 && 67 <= posX && posX <=72)
                init_Level(windowLevel, windowInformations);

            wattron(windowInformations,COLOR_PAIR(8));
            // mvwprintw(windowInformations, 3, 1,"Color %.2d - life %.2d - Bomb %.2d ", color,life,bomb);

            wrefresh(windowTools);
            wrefresh(windowInformations);
            wrefresh(windowLevel);
        
    }

    // Delete windows
    delwin(window);
    delwin(windowLevel);
    delwin(windowTools);
    delwin(windowInformations);

    // Stop ncurses
    ncurses_stop();  

    if(close(fd_World) != 0){
        perror("Error closed");
        exit(EXIT_FAILURE);
    }
    
}