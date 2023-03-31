/**
 * @file item.c
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2023-02-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "item.h"
#include "functions.h"

// Initialisation de la fenêtre de niveau (seulement affichage)
void init_Level(WINDOW *windowLevel, WINDOW *windowInformations)
{

    // wattron(windowLevel, COLOR_PAIR(9));
    // for (int i = 1; i < 61; i++)
    // {
    //     mvwprintw(windowLevel, 1, i, " ");
    //     mvwprintw(windowLevel, 20, i, " ");
    // }
    // for (int i = 1; i < 21; i++)
    // {
    //     mvwprintw(windowLevel, i, 1, " ");
    //     mvwprintw(windowLevel, i, 60, " ");
    // }

    wattron(windowLevel, COLOR_PAIR(1));
    for (int i = 2; i < 60; i++)
        for (int j = 2; j < 20; j++)
            mvwprintw(windowLevel, j, i, " ");

    mvwprintw(windowInformations, 2, 1, "Map Clean");
}

// Initialisation des outils
void init_Tools(WINDOW *windowTools, int level, int door)
{
    wattron(windowTools, COLOR_PAIR(2));
    mvwprintw(windowTools, 1, 1, "  Delete");
    mvwprintw(windowTools, 2, 1, "  Block");
    mvwprintw(windowTools, 3, 1, "  Ladder");
    mvwprintw(windowTools, 4, 1, "  Trap");
    mvwprintw(windowTools, 5, 1, "  Gate");
    wattron(windowTools, COLOR_PAIR(10));
    mvwprintw(windowTools, 5, 10, " ");
    wattron(windowTools, COLOR_PAIR(11));
    mvwprintw(windowTools, 5, 11, " ");
    wattron(windowTools, COLOR_PAIR(12));
    mvwprintw(windowTools, 5, 12, " ");
    wattron(windowTools, COLOR_PAIR(13));
    mvwprintw(windowTools, 5, 13, " ");
    wattron(windowTools, COLOR_PAIR(2));
    mvwprintw(windowTools, 6, 11, " ");
    mvwprintw(windowTools, 6, 12, " ");
    mvwprintw(windowTools, 6, 13, " ");
    wattron(windowTools, COLOR_PAIR(2));
    mvwprintw(windowTools, 6, 1, "  Key");
    mvwprintw(windowTools, 7, 1, "  Door");
    wattron(windowTools, COLOR_PAIR(8));
    mvwprintw(windowTools, 7, 7, "  <%.2i>", door);
    wattron(windowTools, COLOR_PAIR(2));
    mvwprintw(windowTools, 8, 1, "  Exit");
    mvwprintw(windowTools, 9, 1, "  Start");
    mvwprintw(windowTools, 10, 1, "  Robot");
    mvwprintw(windowTools, 11, 1, "  Probe");
    mvwprintw(windowTools, 12, 1, "  Life");
    mvwprintw(windowTools, 13, 1, "  Bomb");
    wattron(windowTools, COLOR_PAIR(8));
    mvwprintw(windowTools, 15, 1, "Current level");
    mvwprintw(windowTools, 17, 3, " < %.3i >", level);
    wattron(windowTools, COLOR_PAIR(2));
    mvwprintw(windowTools, 19, 4, "DELETE");
}

// Supprimer un block
void delete (WINDOW *windowLevel, WINDOW *windowInformations, level_t *niv,int x, int y)
{
    int posX = x, posY = y;

    wattron(windowInformations, COLOR_PAIR(1));

    mvwprintw(windowInformations, 2, 1, "Supprimer ?");
    wrefresh(windowInformations);

    if (posX == 0 || posX == 61 || posY == 0 || posY == 21) 
    {
        mvwprintw(windowInformations, 2, 1, "Impossible de supprimer ici");
        return;
    }
    wattron(windowLevel, COLOR_PAIR(1));
    mvwprintw(windowLevel, posY, posX, " ");
    wrefresh(windowLevel);

    niv->cells[(posX - 1) * nblignes + (posY - 1)] = ' ';
    niv->colors[(posX - 1) * nblignes + (posY - 1)] = 1;

    mvwprintw(windowInformations, 2, 1, "Supprimer ? OK");
    
}

// Placer un block
void place_block(WINDOW *windowLevel, WINDOW *windowInformations, level_t *niv,int x, int y)
{
    int posX = x, posY = y;

    wattron(windowInformations, COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1, "Place Block ?");
    wrefresh(windowInformations);
    
    if (posX == 0 || posX == 61 || posY == 0 || posY == 21) 
    {
        mvwprintw(windowInformations, 2, 1, "Impossible de placer ici");
        return;
    }
    wattron(windowLevel, COLOR_PAIR(9));
    mvwprintw(windowLevel, posY, posX, " ");
    wrefresh(windowLevel);

    niv->cells[(posX - 1) * nblignes + (posY - 1)] = 'B';
    niv->colors[(posX - 1) * nblignes + (posY - 1)] = 9;

    mvwprintw(windowInformations, 2, 1, "Place Block ? OK");
    
}

// Placer une trap
void place_Trap(WINDOW *windowLevel, WINDOW *windowInformations, level_t *niv,int x, int y)
{
    int posX = x, posY = y;

    wattron(windowInformations, COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1, "Place Trap ?");
    wrefresh(windowInformations);
    
    if (posX == 0 || posX == 61 || posY == 0 || posY == 21) 
    {
        mvwprintw(windowInformations, 2, 1, "Impossible de placer ici");
        return;
    }
    wattron(windowLevel, COLOR_PAIR(9));
    mvwprintw(windowLevel, posY, posX, "#");
    wrefresh(windowLevel);

    niv->cells[(posX - 1) * nblignes + (posY - 1)] = '#';
    niv->colors[(posX - 1) * nblignes + (posY - 1)] = 9;

    mvwprintw(windowInformations, 2, 1, "Place Trap ? OK");
    
}

// Placer une vie
void place_Life(WINDOW *windowLevel, WINDOW *windowInformations, level_t *niv,int x, int y)
{
    int posX = x, posY = y;

    wattron(windowInformations, COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1, "Place Life ?");
    wrefresh(windowInformations);
    
    if (posX == 0 || posX == 61 || posY == 0 || posY == 21) 
    {
        mvwprintw(windowInformations, 2, 1, "Impossible de placer ici");
        return;
    }
    wattron(windowLevel, COLOR_PAIR(2));
    mvwprintw(windowLevel, posY, posX, "V");
    wrefresh(windowLevel);

    niv->cells[(posX - 1) * nblignes + (posY - 1)] = 'V';
    niv->colors[(posX - 1) * nblignes + (posY - 1)] = 2;

    mvwprintw(windowInformations, 2, 1, "Place Life ? OK");
    
}

// Placer une bombe
void place_bomb(WINDOW *windowLevel, WINDOW *windowInformations, level_t *niv,int x, int y)
{
    int posX = x, posY = y;

    wattron(windowInformations, COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1, "Place Bomb ?");
    wrefresh(windowInformations);
    
    if (posX == 0 || posX == 61 || posY == 0 || posY == 21) 
    {
        mvwprintw(windowInformations, 2, 1, "Impossible de placer ici");
        return;
    }
    wattron(windowLevel, COLOR_PAIR(8));
    mvwprintw(windowLevel, posY, posX, "o");
    wrefresh(windowLevel);

    niv->cells[(posX - 1) * nblignes + (posY - 1)] = 'o';
    niv->colors[(posX - 1) * nblignes + (posY - 1)] = 8;

    mvwprintw(windowInformations, 2, 1, "Place Bomb ? OK");
    
}

// Placer une échelle
void place_ladder(WINDOW *windowLevel, WINDOW *windowInformations, level_t *niv,int x, int y)
{
    int posX = x, posY = y;

    wattron(windowInformations, COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1, "Place Ladder ?");
    wrefresh(windowInformations);
    
    if (posX<=1 ||  posX>=59 || posY == 0 || posY == 21) 
    {
        mvwprintw(windowInformations, 2, 1, "Impossible de placer ici");
        return;
    }
    wattron(windowLevel, COLOR_PAIR(4));
    mvwaddch(windowLevel, posY, posX, ACS_LTEE);
    mvwaddch(windowLevel, posY, posX + 1, ACS_HLINE);
    mvwaddch(windowLevel, posY, posX + 2, ACS_RTEE);
    wrefresh(windowLevel);

    niv->cells[(posX - 1) * nblignes + posY - 1] = ACS_LTEE;
    niv->cells[(posX)*nblignes + posY - 1] = ACS_HLINE;
    niv->cells[(posX + 1) * nblignes + posY - 1] = ACS_RTEE;

    niv->colors[(posX - 1) * nblignes + posY - 1] = 4;
    niv->colors[(posX)*nblignes + posY - 1] = 4;
    niv->colors[(posX + 1) * nblignes + posY - 1] = 4;

    mvwprintw(windowInformations, 2, 1, "Place Ladder ? OK");
    
}

// Placer un start
void place_Start(WINDOW *windowLevel, WINDOW *windowInformations, level_t *niv,int x, int y)
{
    int posX = x, posY = y;

    wattron(windowInformations, COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1, "Place start ?");
    wrefresh(windowInformations);
    
    if (posX==0 ||  posX>=59 || posY <= 3 || posY == 21) 
    {
        mvwprintw(windowInformations, 2, 1, "Impossible de placer ici");
        return;
    }
    wattron(windowLevel, COLOR_PAIR(10));

    mvwprintw(windowLevel, posY, posX, " ");
    mvwprintw(windowLevel, posY, posX + 1, " ");
    mvwprintw(windowLevel, posY, posX + 2, " ");
    mvwprintw(windowLevel, posY - 1, posX, " ");
    mvwprintw(windowLevel, posY - 1, posX + 1, " ");
    mvwprintw(windowLevel, posY - 1, posX + 2, " ");
    mvwprintw(windowLevel, posY - 2, posX, " ");
    mvwprintw(windowLevel, posY - 2, posX + 1, " ");
    mvwprintw(windowLevel, posY - 2, posX + 2, " ");
    mvwprintw(windowLevel, posY - 3, posX, " ");
    mvwprintw(windowLevel, posY - 3, posX + 1, " ");
    mvwprintw(windowLevel, posY - 3, posX + 2, " ");
    wrefresh(windowLevel);

    niv->cells[(posX-1)* nblignes + (posY-1)] = 'S';
    niv->colors[(posX-1) * nblignes + (posY-1)] = 10;

    niv->cells[(posX)* nblignes + (posY-1)] = 'S';
    niv->colors[(posX) * nblignes + (posY-1)] = 10;

    niv->cells[(posX+1)* nblignes + (posY-1)] = 'S';
    niv->colors[(posX+1) * nblignes + (posY-1)] = 10;

    niv->cells[(posX-1)* nblignes + (posY-2)] = 'S';
    niv->colors[(posX-1) * nblignes + (posY-2)] = 10;

    niv->cells[(posX)* nblignes + (posY-2)] = 'S';
    niv->colors[(posX) * nblignes + (posY-2)] = 10;

    niv->cells[(posX+1)* nblignes + (posY-2)] = 'S';
    niv->colors[(posX+1) * nblignes + (posY-2)] = 10;

    niv->cells[(posX-1)* nblignes + (posY-3)] = 'S';
    niv->colors[(posX-1) * nblignes + (posY-3)] = 10;

    niv->cells[(posX-1)* nblignes + (posY-3)] = 'S';
    niv->colors[(posX-1) * nblignes + (posY-3)] = 10;

    niv->cells[(posX)* nblignes + (posY-3)] = 'S';
    niv->colors[(posX) * nblignes + (posY-3)] = 10;

    niv->cells[(posX+1)* nblignes + (posY-3)] = 'S';
    niv->colors[(posX+1) * nblignes + (posY-3)] = 10;

    niv->cells[(posX-1)* nblignes + (posY-4)] = 'S';
    niv->colors[(posX-1) * nblignes + (posY-4)] = 10;

    niv->cells[(posX)* nblignes + (posY-4)] = 'S';
    niv->colors[(posX) * nblignes + (posY-4)] = 10;

    niv->cells[(posX+1)* nblignes + (posY-4)] = 'S';
    niv->colors[(posX+1) * nblignes + (posY-4)] = 10;

    mvwprintw(windowInformations, 2, 1, "Place start ? OK");
    
}

void place_Exit(WINDOW *windowLevel, WINDOW *windowInformations, level_t *niv,int x, int y)
{
    int posX = x, posY = y;


    wattron(windowInformations, COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1, "Place start ?");
    wrefresh(windowInformations);

    
    if (posX==0 ||  posX>=59 || posY <= 3 || posY == 21) 
    {
        mvwprintw(windowInformations, 2, 1, "Impossible de placer ici");
        return;
    }
    wattron(windowLevel, COLOR_PAIR(12));

    mvwprintw(windowLevel, posY, posX, " ");
    mvwprintw(windowLevel, posY, posX + 1, " ");
    mvwprintw(windowLevel, posY, posX + 2, " ");
    mvwprintw(windowLevel, posY - 1, posX, " ");
    mvwprintw(windowLevel, posY - 1, posX + 1, " ");
    mvwprintw(windowLevel, posY - 1, posX + 2, " ");
    mvwprintw(windowLevel, posY - 2, posX, " ");
    mvwprintw(windowLevel, posY - 2, posX + 1, " ");
    mvwprintw(windowLevel, posY - 2, posX + 2, " ");
    mvwprintw(windowLevel, posY - 3, posX, " ");
    mvwprintw(windowLevel, posY - 3, posX + 1, " ");
    mvwprintw(windowLevel, posY - 3, posX + 2, " ");
    wrefresh(windowLevel);

    niv->cells[(posX-1)* nblignes + (posY-1)] = 'E';
    niv->colors[(posX-1) * nblignes + (posY-1)] = 12;

    niv->cells[(posX)* nblignes + (posY-1)] = 'E';
    niv->colors[(posX) * nblignes + (posY-1)] = 12;

    niv->cells[(posX+1)* nblignes + (posY-1)] = 'E';
    niv->colors[(posX+1) * nblignes + (posY-1)] = 12;

    niv->cells[(posX-1)* nblignes + (posY-2)] = 'E';
    niv->colors[(posX-1) * nblignes + (posY-2)] = 12;

    niv->cells[(posX)* nblignes + (posY-2)] = 'E';
    niv->colors[(posX) * nblignes + (posY-2)] = 12;

    niv->cells[(posX+1)* nblignes + (posY-2)] = 'E';
    niv->colors[(posX+1) * nblignes + (posY-2)] = 12;

    niv->cells[(posX-1)* nblignes + (posY-3)] = 'E';
    niv->colors[(posX-1) * nblignes + (posY-3)] = 12;

    niv->cells[(posX-1)* nblignes + (posY-3)] = 'E';
    niv->colors[(posX-1) * nblignes + (posY-3)] = 12;

    niv->cells[(posX)* nblignes + (posY-3)] = 'E';
    niv->colors[(posX) * nblignes + (posY-3)] = 12;

    niv->cells[(posX+1)* nblignes + (posY-3)] = 'E';
    niv->colors[(posX+1) * nblignes + (posY-3)] = 12;

    niv->cells[(posX-1)* nblignes + (posY-4)] = 'E';
    niv->colors[(posX-1) * nblignes + (posY-4)] = 12;

    niv->cells[(posX)* nblignes + (posY-4)] = 'E';
    niv->colors[(posX) * nblignes + (posY-4)] = 12;

    niv->cells[(posX+1)* nblignes + (posY-4)] = 'E';
    niv->colors[(posX+1) * nblignes + (posY-4)] = 12;

    mvwprintw(windowInformations, 2, 1, "Place start ? OK");
    
}

// Placer une porte
void place_Door(WINDOW *windowLevel, WINDOW *windowInformations, int door, level_t *niv,int x, int y)
{
    int posX = x, posY = y;
    char d; 

    wattron(windowInformations, COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1, "Place Door ?");
    wrefresh(windowInformations);

    
    if (posX==0 ||  posX>=59 || posY <= 3 || posY == 21) 
    {
        mvwprintw(windowInformations, 2, 1, "Impossible de placer ici");
        return;
    }
        
    niv->cells[(posX-1)* nblignes + (posY-1)] = 'D';
    niv->colors[(posX-1) * nblignes + (posY-1)] = 11;

    niv->cells[(posX)* nblignes + (posY-1)] = 'D';
    niv->colors[(posX) * nblignes + (posY-1)] = 11;

    niv->cells[(posX+1)* nblignes + (posY-1)] = 'D';
    niv->colors[(posX+1) * nblignes + (posY-1)] = 11;

    niv->cells[(posX-1)* nblignes + (posY-2)] = 'D';
    niv->colors[(posX-1) * nblignes + (posY-2)] = 11;

    niv->cells[(posX)* nblignes + (posY-2)] = 'D';
    niv->colors[(posX) * nblignes + (posY-2)] = 11;

    niv->cells[(posX+1)* nblignes + (posY-2)] = 'D';
    niv->colors[(posX+1) * nblignes + (posY-2)] = 11;

    niv->cells[(posX-1)* nblignes + (posY-3)] = 'D';
    niv->colors[(posX-1) * nblignes + (posY-3)] = 11;

    niv->cells[(posX-1)* nblignes + (posY-3)] = 'D';
    niv->colors[(posX-1) * nblignes + (posY-3)] = 11;

    niv->cells[(posX)* nblignes + (posY-3)] = 'D';
    niv->colors[(posX) * nblignes + (posY-3)] = 11;

    niv->cells[(posX+1)* nblignes + (posY-3)] = 'D';
    niv->colors[(posX+1) * nblignes + (posY-3)] = 11;

    niv->cells[(posX-1)* nblignes + (posY-4)] = '0';
    niv->colors[(posX-1) * nblignes + (posY-4)] = 8;

    d = door+'0';

    niv->cells[(posX)* nblignes + (posY-4)] = d;
    niv->colors[(posX) * nblignes + (posY-4)] = 8;

    niv->cells[(posX+1)* nblignes + (posY-4)] = 'D';
    niv->colors[(posX+1) * nblignes + (posY-4)] = 11;

    wattron(windowLevel, COLOR_PAIR(8));
    mvwprintw(windowLevel, posY - 3, posX, "%.2d", door);

    wattron(windowLevel, COLOR_PAIR(11));
    mvwprintw(windowLevel, posY, posX, " ");
    mvwprintw(windowLevel, posY, posX + 1, " ");
    mvwprintw(windowLevel, posY, posX + 2, " ");
    mvwprintw(windowLevel, posY - 1, posX, " ");
    mvwprintw(windowLevel, posY - 1, posX + 1, " ");
    mvwprintw(windowLevel, posY - 1, posX + 2, " ");
    mvwprintw(windowLevel, posY - 2, posX, " ");
    mvwprintw(windowLevel, posY - 2, posX + 1, " ");
    mvwprintw(windowLevel, posY - 2, posX + 2, " ");
    mvwprintw(windowLevel, posY - 3, posX + 2, " ");

    wrefresh(windowLevel);
    mvwprintw(windowInformations, 2, 1, "Place Door ? OK");
    
}

// Placer une gate
void place_Gate(WINDOW *windowLevel, WINDOW *windowInformations, WINDOW *windowTools, level_t *niv)
{
    int posX, posY, color = 0,ch; // gateB;

    wattron(windowInformations, COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1, "Select color");
    wrefresh(windowInformations);

    ch = getch();
    switch (ch)
    {
    case KEY_MOUSE:
        if (mouse_getpos(&posX, &posY) == OK)
        {
            posY = posY;
            posX = posX;
        }
    }

    if (posY == 5 && posX == 73)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 10, "^"), color = 6; 

    if (posY == 5 && posX == 74)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 11, "^"), color = 3; 

    if (posY == 5 && posX == 75)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 12, "^"), color = 4; 

    if (posY == 5 && posX == 76)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 13, "^"), color = 5; 

    wrefresh(windowTools);
    mvwprintw(windowInformations, 2, 1, "Place Gate ?");
    wrefresh(windowInformations);

    ch = getch();
    switch (ch)
    {
    case KEY_MOUSE:
        if (mouse_getpos(&posX, &posY) == OK)
        {
            posY = posY;
            posX = posX;
        }
    }

    wattron(windowLevel, COLOR_PAIR(color));
    mvwaddch(windowLevel, posY, posX, ACS_PLUS);
    wrefresh(windowLevel);

    niv->cells[(posX - 1) * nblignes + posY - 1] = ACS_PLUS;
    niv->colors[(posX - 1) * nblignes + posY - 1] = color;


    mvwprintw(windowInformations, 2, 1, "Place Gate ? OK");
    wrefresh(windowInformations);
}

// Placer une clé
void place_Key(WINDOW *windowLevel, WINDOW *windowInformations, WINDOW *windowTools, level_t *niv)
{
    int posX, posY, colorFD, color,ch; // keyB;

    wattron(windowInformations, COLOR_PAIR(8));
    mvwprintw(windowInformations, 2, 1, "Select color");
    wrefresh(windowInformations);

    ch = getch();
    switch (ch)
    {
    case KEY_MOUSE:
        if (mouse_getpos(&posX, &posY) == OK)
        {
            posY = posY;
            posX = posX;
        }
    }
    if (posX==0 ||  posX==61 || posY == 0 || posY >= 20) 
    {
        mvwprintw(windowInformations, 2, 1, "Impossible de placer ici");
        return;
    }

    if (posY == 5 && posX == 73)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 10, "^"), color = 6, colorFD = 10; // keyB = KEYP;

    if (posY == 5 && posX == 74)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 11, "^"), color = 3, colorFD = 11; // keyB = KEYG;

    if (posY == 5 && posX == 75)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 12, "^"), color = 4, colorFD = 12; // keyB = KEYY;

    if (posY == 5 && posX == 76)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 13, "^"), color = 5, colorFD = 13; // keyB = KEYB;

    wrefresh(windowTools);
    mvwprintw(windowInformations, 2, 1, "Place Key ?");
    wrefresh(windowInformations);

    ch = getch();
    switch (ch)
    {
    case KEY_MOUSE:
        if (mouse_getpos(&posX, &posY) == OK)
        {
            posY = posY;
            posX = posX;
        }
    }

    niv->cells[(posX - 1) * nblignes + posY - 1] = 'K';
    niv->cells[(posX - 1) * nblignes + posY] = ACS_LLCORNER;
    niv->colors[(posX - 1) * nblignes + posY - 1] = colorFD;
    niv->colors[(posX - 1) * nblignes + posY] = color;

    wattron(windowLevel, COLOR_PAIR(colorFD));
    mvwprintw(windowLevel, posY, posX, " ");
    wattron(windowLevel, COLOR_PAIR(color));
    mvwaddch(windowLevel, posY + 1, posX, ACS_LLCORNER);
    wrefresh(windowLevel);
    mvwprintw(windowInformations, 2, 1, "Place Key ? OK");
    wrefresh(windowInformations);
}

// Placer une sonde
void place_Probe(WINDOW *windowLevel, WINDOW *windowInformations, level_t *niv,int x, int y)
{
    int posX = x, posY = y;

    wattron(windowInformations, COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1, "Place Probe ?");
    wrefresh(windowInformations);
    
    if (posX<=1 ||  posX>=60 || posY == 0 || posY >= 20) 
    {
        mvwprintw(windowInformations, 2, 1, "Impossible de placer ici");
        return;
    }

    wattron(windowLevel, COLOR_PAIR(8));
    mvwaddch(windowLevel, posY, posX - 1, ACS_LTEE);
    mvwaddch(windowLevel, posY, posX, ACS_HLINE);
    mvwaddch(windowLevel, posY, posX + 1, ACS_RTEE);
    mvwaddch(windowLevel, posY + 1, posX - 1, ACS_LLCORNER);
    mvwaddch(windowLevel, posY + 1, posX, ACS_HLINE);
    mvwaddch(windowLevel, posY + 1, posX + 1, ACS_LRCORNER);
    wrefresh(windowLevel);

    niv->cells[(posX -2) * nblignes + (posY - 1)] = ACS_LTEE;
    niv->cells[(posX-1) * nblignes + (posY - 1)] = ACS_HLINE;
    niv->cells[posX * nblignes + (posY - 1)] = ACS_RTEE;
    niv->cells[(posX - 2) * nblignes + posY] = ACS_LLCORNER;
    niv->cells[(posX-1)*nblignes + posY] = ACS_HLINE;
    niv->cells[posX * nblignes + posY] = ACS_LRCORNER;

    niv->colors[(posX -2) * nblignes + (posY - 1)] = 8;
    niv->colors[(posX-1) * nblignes + (posY - 1)] = 8;
    niv->colors[posX * nblignes + (posY - 1)] = 8;
    niv->colors[(posX - 2) * nblignes + posY] = 8;
    niv->colors[(posX-1)*nblignes + posY] = 8;
    niv->colors[posX * nblignes + posY] = 8;

    mvwprintw(windowInformations, 2, 1, "Place Probe ? OK");
    wrefresh(windowInformations);
}

// Placer un robot
void place_Robot(WINDOW *windowLevel, WINDOW *windowInformations, level_t *niv,int x, int y)
{
    int posX = x, posY = y;

    wattron(windowInformations, COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1, "Place Robot ?");
    wrefresh(windowInformations);

    
    if (posX<=1 ||  posX>=60 || posY <= 2 || posY >= 20) 
    {
        mvwprintw(windowInformations, 2, 1, "Impossible de placer ici");
        return;
    }

    wattron(windowLevel, COLOR_PAIR(8));

    mvwaddch(windowLevel, posY - 2, posX - 1, ACS_ULCORNER);
    mvwaddch(windowLevel, posY - 2, posX, ACS_BTEE);
    mvwaddch(windowLevel, posY - 2, posX + 1, ACS_URCORNER);

    mvwaddch(windowLevel, posY - 1, posX - 1, ACS_LLCORNER);
    mvwaddch(windowLevel, posY - 1, posX, ACS_TTEE);
    mvwaddch(windowLevel, posY - 1, posX + 1, ACS_LRCORNER);

    mvwaddch(windowLevel, posY, posX - 1, ACS_HLINE);
    mvwaddch(windowLevel, posY, posX, ACS_PLUS);
    mvwaddch(windowLevel, posY, posX + 1, ACS_HLINE);

    mvwaddch(windowLevel, posY + 1, posX - 1, ACS_ULCORNER);
    mvwaddch(windowLevel, posY + 1, posX, ACS_BTEE);
    mvwaddch(windowLevel, posY + 1, posX + 1, ACS_URCORNER);
    wrefresh(windowLevel);
    niv->cells[(posX - 2) * nblignes + (posY - 3)] = ACS_ULCORNER;
    niv->cells[(posX - 1)* nblignes + (posY - 3)] = ACS_BTEE;
    niv->cells[posX * nblignes + (posY - 3)] = ACS_URCORNER;

    niv->cells[(posX - 2) * nblignes + (posY - 2)] = ACS_LLCORNER;
    niv->cells[(posX - 1) * nblignes + (posY - 2)] = ACS_TTEE;
    niv->cells[posX * nblignes + (posY - 2)] = ACS_LRCORNER;

    niv->cells[(posX - 2) * nblignes + (posY - 1)] = ACS_HLINE;
    niv->cells[(posX - 1) * nblignes + (posY - 1)] = ACS_PLUS;
    niv->cells[posX * nblignes + (posY - 1)] = ACS_HLINE;

    niv->cells[(posX - 2) * nblignes + (posY)] = ACS_ULCORNER;
    niv->cells[(posX - 1) * nblignes + (posY)] = ACS_BTEE;
    niv->cells[posX * nblignes + (posY)] = ACS_URCORNER;

    niv->colors[(posX - 2) * nblignes + (posY - 3)] = 8 ;
    niv->colors[(posX - 1)* nblignes + (posY - 3)] = 8 ;
    niv->colors[posX * nblignes + (posY - 3)] = 8 ;

    niv->colors[(posX - 2) * nblignes + (posY - 2)] = 8 ;
    niv->colors[(posX - 1) * nblignes + (posY - 2)] = 8 ;
    niv->colors[posX * nblignes + (posY - 2)] = 8;

    niv->colors[(posX - 2) * nblignes + (posY - 1)] = 8 ;
    niv->colors[(posX - 1) * nblignes + (posY - 1)] = 8 ;
    niv->colors[posX * nblignes + (posY - 1)] = 8 ;

    niv->colors[(posX - 2) * nblignes + (posY)] = 8 ;
    niv->colors[(posX - 1) * nblignes + (posY)] = 8 ;
    niv->colors[posX * nblignes + (posY)] = 8 ;

    mvwprintw(windowInformations, 2, 1, "Place Robot ? OK");
    wrefresh(windowInformations);
}

// Initailisation fenêtre d'information
void init_PlayInformations(WINDOW *windowPlayerInformation, char level)
{
    int posX = 0;
    wattron(windowPlayerInformation, COLOR_PAIR(8));
    mvwprintw(windowPlayerInformation, 1, 1, "Keys");

    posX = 1;

    for (int i = 0; i < 4; i++)
    {
        wattron(windowPlayerInformation, COLOR_PAIR(14));
        mvwprintw(windowPlayerInformation, 3, posX, " ");
        wattron(windowPlayerInformation, COLOR_PAIR(2));
        mvwaddch(windowPlayerInformation, 4, posX, ACS_LLCORNER);
        posX += 2;
    }

    wattron(windowPlayerInformation, COLOR_PAIR(8));
    mvwprintw(windowPlayerInformation, 6, 1, "Keys");

    posX = 2;
    for (int i = 0; i < 8; i++)
    {
        mvwprintw(windowPlayerInformation, 8, posX, "V");
        posX += 1;
    }

    mvwprintw(windowPlayerInformation, 10, 1, "Bombs");
    posX = 3;
    for (int i = 0; i < 3; i++)
    {
        mvwprintw(windowPlayerInformation, 12, posX, "o");
        posX += 1;
    }

    mvwprintw(windowPlayerInformation, 14, 1, "Level");
    mvwprintw(windowPlayerInformation, 16, 3, "%2d", level);
}