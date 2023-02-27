#include "item.h"

int MODE = 0;
/**
 * @brief 
 * 
 * @param windowLevel 
 */
void init_Level(WINDOW *windowLevel, WINDOW *windowInformations)
{

    wattron(windowLevel,COLOR_PAIR(9));
    for (int i = 1; i < 61; i++) 
    {
        mvwprintw(windowLevel,1, i, " ");
        mvwprintw(windowLevel,20, i, " ");
    }
    for (int i = 1; i < 21; i++) 
    {
        mvwprintw(windowLevel,i, 1, " ");
        mvwprintw(windowLevel,i, 60, " ");
    }

    wattron(windowLevel,COLOR_PAIR(1));
    for(int i = 2; i < 60; i ++)
        for (int j = 2; j < 20; j++)
            mvwprintw(windowLevel,j, i, " ");

    mvwprintw(windowInformations, 2, 1,"Map Clean");

}

/**
 * @brief 
 * 
 * @param windowTools 
 * @param level 
 * @param door 
 */
void init_Tools(WINDOW *windowTools, int level, int door)
{
    wattron(windowTools,COLOR_PAIR(2));
    mvwprintw(windowTools, 1, 1, "  Delete");
    mvwprintw(windowTools, 2, 1, "  Block");
    mvwprintw(windowTools, 3, 1, "  Ladder");
    mvwprintw(windowTools, 4, 1, "  Trap");
    mvwprintw(windowTools, 5, 1, "  Gate");
    wattron(windowTools,COLOR_PAIR(10));
    mvwprintw(windowTools, 5, 10, " ");
    wattron(windowTools,COLOR_PAIR(11)); 
    mvwprintw(windowTools, 5, 11, " ");
    wattron(windowTools,COLOR_PAIR(12));
    mvwprintw(windowTools, 5, 12, " ");
    wattron(windowTools,COLOR_PAIR(13));
    mvwprintw(windowTools, 5, 13, " ");
    wattron(windowTools,COLOR_PAIR(2));
    // mvwprintw(windowTools, 6, 10, "^");
    mvwprintw(windowTools, 6, 11, " ");
    mvwprintw(windowTools, 6, 12, " ");
    mvwprintw(windowTools, 6, 13, " ");
    wattron(windowTools,COLOR_PAIR(2));
    mvwprintw(windowTools, 6, 1, "  Key");
    mvwprintw(windowTools, 7, 1, "  Door");
    wattron(windowTools,COLOR_PAIR(8));
    mvwprintw(windowTools, 7, 7, "  <%.2i>", door);
    wattron(windowTools,COLOR_PAIR(2));
    mvwprintw(windowTools, 8, 1, "  Exit");
    mvwprintw(windowTools, 9, 1, "  Start");
    mvwprintw(windowTools, 10, 1, "  Robot");
    mvwprintw(windowTools, 11, 1, "  Probe");
    mvwprintw(windowTools, 12, 1, "  Life");
    mvwprintw(windowTools, 13, 1, "  Bomb");

    wattron(windowTools,COLOR_PAIR(8));
    mvwprintw(windowTools, 15, 1, "Current level");
    mvwprintw(windowTools, 17, 3, " < %.3i >", level);

    wattron(windowTools,COLOR_PAIR(2));
    mvwprintw(windowTools, 19, 4, "DELETE");
}

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_block(WINDOW *windowLevel, WINDOW *windowInformations, int fd_World)
{
    int posX, posY, ch;

    wattron(windowInformations,COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1,"Place Block ?");
    wrefresh(windowInformations);
    
    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
                
            }
        wattron(windowLevel,COLOR_PAIR(9));
        mvwprintw(windowLevel, posY, posX, " ");
        wrefresh(windowLevel);
        if( MODE == 0)
            add_item_fileMap(fd_World ,posX,posY,BLOCK);
        mvwprintw(windowInformations, 2, 1,"Place Block ? OK");
    }
}

void place_Trap(WINDOW *windowLevel, WINDOW *windowInformations, int fd_World)
{
    int posX, posY, ch;

    wattron(windowInformations,COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1,"Place Trap ?");
    wrefresh(windowInformations);
    
    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
                
            }
        wattron(windowLevel,COLOR_PAIR(9));
        mvwprintw(windowLevel, posY, posX, "#");
        wrefresh(windowLevel);
        if(MODE == 0 )
            add_item_fileMap(fd_World ,posX,posY,TRAP);
        mvwprintw(windowInformations, 2, 1,"Place Trap ? OK");
    }
}

void place_Life(WINDOW *windowLevel, WINDOW *windowInformations, int fd_World)
{
    int posX, posY, ch;

    wattron(windowInformations,COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1,"Place Life ?");
    wrefresh(windowInformations);
        
    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
                
            }
        wattron(windowLevel,COLOR_PAIR(2));
        mvwprintw(windowLevel, posY, posX, "V");
        wrefresh(windowLevel);
        if(MODE == 0 )
            add_item_fileMap(fd_World ,posX,posY,LIFE);
        mvwprintw(windowInformations, 2, 1,"Place Life ? OK");
    }
}

void place_bomb(WINDOW *windowLevel, WINDOW *windowInformations, int fd_World)
{
    int posX, posY, ch;

    wattron(windowInformations,COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1,"Place Life ?");
    wrefresh(windowInformations);
        
    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
            }
        wattron(windowLevel,COLOR_PAIR(8));
        mvwprintw(windowLevel, posY, posX, "o");
        wrefresh(windowLevel);
        if(MODE == 0 )
            add_item_fileMap(fd_World ,posX,posY,BOMBE);
        mvwprintw(windowInformations, 2, 1,"Place Life ? OK");
    }
}


void place_ladder(WINDOW *windowLevel, WINDOW *windowInformations, int fd_World)
{
    int posX, posY, ch;

    wattron(windowInformations,COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1,"Place Ladder ?");
    wrefresh(windowInformations);
        
    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
                
            }
        wattron(windowLevel,COLOR_PAIR(4));
        mvwaddch(windowLevel,posY, posX, ACS_LTEE);
        mvwaddch(windowLevel,posY, posX+1, ACS_HLINE);
        mvwaddch(windowLevel,posY, posX+2, ACS_RTEE);
        wrefresh(windowLevel);
        add_item_fileMap(fd_World ,posX,posY,LADDER);
        mvwprintw(windowInformations, 2, 1,"Place Ladder ? OK");
    }
}

void place_Start(WINDOW *windowLevel, WINDOW *windowInformations, int fd_World)
{
    int posX, posY, ch;
    // int i, j;

    wattron(windowInformations,COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1,"Place start ?");
    wrefresh(windowInformations);
        
    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
                
            }
        wattron(windowLevel,COLOR_PAIR(10));

        mvwprintw(windowLevel, posY, posX, " ");
        mvwprintw(windowLevel, posY, posX+1, " ");
        mvwprintw(windowLevel, posY, posX+2, " ");
        mvwprintw(windowLevel, posY-1, posX, " ");
        mvwprintw(windowLevel, posY-1, posX+1, " ");
        mvwprintw(windowLevel, posY-1, posX+2, " ");
        mvwprintw(windowLevel, posY-2, posX, " ");
        mvwprintw(windowLevel, posY-2, posX+1, " ");
        mvwprintw(windowLevel, posY-2, posX+2, " ");
        mvwprintw(windowLevel, posY-3, posX, " ");
        mvwprintw(windowLevel, posY-3, posX+1, " ");
        mvwprintw(windowLevel, posY-3, posX+2, " ");
        wrefresh(windowLevel);
        add_item_fileMap(fd_World ,posX,posY,LADDER);
        mvwprintw(windowInformations, 2, 1,"Place start ? OK");
    }
}

void place_Exit(WINDOW *windowLevel, WINDOW *windowInformations, int fd_World)
{
    int posX, posY, ch;
    // int i, j;

    wattron(windowInformations,COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1,"Place start ?");
    wrefresh(windowInformations);
        
    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
                
            }
        wattron(windowLevel,COLOR_PAIR(12));

        mvwprintw(windowLevel, posY, posX, " ");
        mvwprintw(windowLevel, posY, posX+1, " ");
        mvwprintw(windowLevel, posY, posX+2, " ");
        mvwprintw(windowLevel, posY-1, posX, " ");
        mvwprintw(windowLevel, posY-1, posX+1, " ");
        mvwprintw(windowLevel, posY-1, posX+2, " ");
        mvwprintw(windowLevel, posY-2, posX, " ");
        mvwprintw(windowLevel, posY-2, posX+1, " ");
        mvwprintw(windowLevel, posY-2, posX+2, " ");
        mvwprintw(windowLevel, posY-3, posX, " ");
        mvwprintw(windowLevel, posY-3, posX+1, " ");
        mvwprintw(windowLevel, posY-3, posX+2, " ");
        wrefresh(windowLevel);
        if (MODE == 0)
            add_item_fileMap(fd_World ,posX,posY,EXIT);
        mvwprintw(windowInformations, 2, 1,"Place start ? OK");
    }
}

void place_Door(WINDOW *windowLevel, WINDOW *windowInformations, int door, int fd_World)
{
    int posX, posY, ch, doorBin = 0;
    
    switch(door)
    {
        case 1 :
            doorBin = DOOR1;
            break;
        case 2 :
            doorBin = DOOR2;
            break;
        case 3 :
            doorBin = DOOR3;
            break;
        case 4 :
            doorBin = DOOR4;
            break;
        case 5 :
            doorBin = DOOR5;
            break;
    }

    wattron(windowInformations,COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1,"Place Door ?");
    wrefresh(windowInformations);
        
    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
                
            }

        if (MODE == 0)
            add_item_fileMap(fd_World ,posX,posY,doorBin);

        wattron(windowLevel,COLOR_PAIR(8));
        mvwprintw(windowLevel, posY-3, posX, "%.2d", door);

        wattron(windowLevel,COLOR_PAIR(11));
        mvwprintw(windowLevel, posY, posX, " ");
        mvwprintw(windowLevel, posY, posX+1, " ");
        mvwprintw(windowLevel, posY, posX+2, " ");
        mvwprintw(windowLevel, posY-1, posX, " ");
        mvwprintw(windowLevel, posY-1, posX+1, " ");
        mvwprintw(windowLevel, posY-1, posX+2, " ");
        mvwprintw(windowLevel, posY-2, posX, " ");
        mvwprintw(windowLevel, posY-2, posX+1, " ");
        mvwprintw(windowLevel, posY-2, posX+2, " ");
        mvwprintw(windowLevel, posY-3, posX+2, " ");

        wrefresh(windowLevel);
        mvwprintw(windowInformations, 2, 1,"Place Door ? OK");
    }
}

void place_Gate(WINDOW *windowLevel, WINDOW *windowInformations,WINDOW *windowTools, int fd_World)
{
    int posX, posY, ch, gateB, color = 0 ;


    wattron(windowInformations,COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1,"Select color");
    wrefresh(windowInformations);
        
    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
                
            }
    }

    if(posY == 5 && posX == 73)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 10, "^"), color = 6, gateB = GATEP;
            
    if(posY == 5 && posX == 74)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 11, "^"), color = 3, gateB = GATEG;

    if(posY == 5 && posX == 75)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 12, "^"), color = 4, gateB = GATEY;

    if(posY == 5 && posX == 76)
        mvwprintw(windowTools, 6, 10, " "),  mvwprintw(windowTools, 6, 13, "^"), color = 5, gateB = GATEB;

    wrefresh(windowTools);
    mvwprintw(windowInformations, 2, 1,"Place Gate ?");
    wrefresh(windowInformations);

    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
                
            }
    }

    wattron(windowLevel,COLOR_PAIR(color));
    mvwaddch(windowLevel, posY, posX, ACS_PLUS);
    wrefresh(windowLevel);
    if (MODE == 0)
        add_item_fileMap(fd_World ,posX,posY,gateB);
    mvwprintw(windowInformations, 2, 1,"Place Gate ? OK");
    wrefresh(windowInformations);
}

void place_Key(WINDOW *windowLevel, WINDOW *windowInformations,WINDOW *windowTools, int fd_World)
{
    int posX, posY, ch, colorFD, color , keyB;


    wattron(windowInformations,COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1,"Select color");
    wrefresh(windowInformations);
        
    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
                
            }
    }

    if(posY == 5 && posX == 73)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 10, "^"), color = 6, colorFD = 10, keyB = KEYP;
            
    if(posY == 5 && posX == 74)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 11, "^"), color = 3, colorFD = 11, keyB = KEYG;

    if(posY == 5 && posX == 75)
        mvwprintw(windowTools, 6, 10, " "), mvwprintw(windowTools, 6, 12, "^"), color = 4, colorFD = 12, keyB = KEYY;

    if(posY == 5 && posX == 76)
        mvwprintw(windowTools, 6, 10, " "),  mvwprintw(windowTools, 6, 13, "^"), color = 5, colorFD = 13, keyB = KEYB;

    wrefresh(windowTools);
    mvwprintw(windowInformations, 2, 1,"Place Key ?");
    wrefresh(windowInformations);

    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
                
            }
    }
    if (MODE == 0)
        add_item_fileMap(fd_World ,posX,posY,keyB);
    wattron(windowLevel,COLOR_PAIR(colorFD));
    mvwprintw(windowLevel, posY, posX, " ");
    wattron(windowLevel,COLOR_PAIR(color));
    mvwaddch(windowLevel, posY+1, posX, ACS_LLCORNER);
    wrefresh(windowLevel);
    mvwprintw(windowInformations, 2, 1,"Place Key ? OK");
    wrefresh(windowInformations);
}

void place_Probe(WINDOW *windowLevel, WINDOW *windowInformations, int fd_World)
{
    int posX, posY, ch;


    wattron(windowInformations,COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1,"Place Probe ?");
    wrefresh(windowInformations);
        
    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
            }
    }
    if (MODE == 0)
        add_item_fileMap(fd_World ,posX,posY,PROBE);

    wattron(windowLevel,COLOR_PAIR(8));
    mvwaddch(windowLevel, posY, posX-1, ACS_LTEE);
    mvwaddch(windowLevel, posY, posX, ACS_HLINE);
    mvwaddch(windowLevel, posY, posX+1, ACS_RTEE);
    mvwaddch(windowLevel, posY+1, posX-1, ACS_LLCORNER);
    mvwaddch(windowLevel, posY+1, posX, ACS_HLINE);
    mvwaddch(windowLevel, posY+1, posX+1, ACS_LRCORNER );
    wrefresh(windowLevel);
    
    mvwprintw(windowInformations, 2, 1,"Place Probe ? OK");
    wrefresh(windowInformations);
}

void place_Robot(WINDOW *windowLevel, WINDOW *windowInformations, int fd_World)
{
    int posX, posY, ch;


    wattron(windowInformations,COLOR_PAIR(8));

    mvwprintw(windowInformations, 2, 1,"Place Robot ?");
    wrefresh(windowInformations);
        
    ch = getch();
    switch(ch) 
    {
        case KEY_MOUSE:
            if(mouse_getpos(&posX, &posY) == OK)
            {
                posY = posY;
                posX = posX;
            }
    }
    if (MODE == 0)
        add_item_fileMap(fd_World ,posX,posY,ROBOT);

    wattron(windowLevel,COLOR_PAIR(8));

    mvwaddch(windowLevel, posY-2, posX-1, ACS_ULCORNER);
    mvwaddch(windowLevel, posY-2, posX, ACS_BTEE);
    mvwaddch(windowLevel, posY-2, posX+1, ACS_URCORNER);

    mvwaddch(windowLevel, posY-1, posX-1, ACS_LLCORNER);
    mvwaddch(windowLevel, posY-1, posX, ACS_TTEE);
    mvwaddch(windowLevel, posY-1, posX+1, ACS_LRCORNER );

    mvwaddch(windowLevel, posY, posX-1, ACS_HLINE);
    mvwaddch(windowLevel, posY, posX, ACS_PLUS);
    mvwaddch(windowLevel, posY, posX+1, ACS_HLINE  );

    mvwaddch(windowLevel, posY+1, posX-1, ACS_ULCORNER);
    mvwaddch(windowLevel, posY+1, posX, ACS_BTEE);
    mvwaddch(windowLevel, posY+1, posX+1, ACS_URCORNER  );
    wrefresh(windowLevel);

    mvwprintw(windowInformations, 2, 1,"Place Robot ? OK");
    wrefresh(windowInformations);
}

