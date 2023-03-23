#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

#include "level.h"
#include "tableAdressage.h"
#include "tableVide.h"

/**
 * Initialize a level.
 * @param level the level
 */
void level_init(level_t *level)
{
    int i, j;

    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            level->cells[i][j] = btowc(' ');
            level->colors[i][j] = FG_WHITE;
        }
    }
}

/**
 * Add a robot in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 */
void level_add_robot(level_t *level, int posX, int posY)
{
    int i, j;

    for (i = posY; i < posY + 4; i++)
        for (j = posX; j < posX + 3; j++)
            level->colors[i][j] = FG_WHITE;

    level->cells[posY][posX] = 0x250C; // ┌
    level->cells[posY][posX] = 0x250C;
    level->cells[posY][posX + 1] = 0x2534;     // ┴
    level->cells[posY][posX + 2] = 0x2510;     // ┐
    level->cells[posY + 1][posX] = 0x2514;     // └
    level->cells[posY + 1][posX + 1] = 0x252C; // ┬
    level->cells[posY + 1][posX + 2] = 0x2518; // ┘
    level->cells[posY + 2][posX] = 0x2500;     // ─
    level->cells[posY + 2][posX + 1] = 0x253C; // ┼
    level->cells[posY + 2][posX + 2] = 0x2500; // ─
    level->cells[posY + 3][posX] = 0x250C;     // ┌
    level->cells[posY + 3][posX + 1] = 0x2534; // ┴
    level->cells[posY + 3][posX + 2] = 0x2510; // ┐
}

/**
 * Add a probe in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 */
void level_add_probe(level_t *level, int posX, int posY)
{
    int i, j;

    for (i = posY; i < posY + 2; i++)
        for (j = posX; j < posX + 3; j++)
            level->colors[i][j] = FG_WHITE;

    level->cells[posY][posX] = 0x251C;         // ├
    level->cells[posY][posX + 1] = 0x2500;     // ─
    level->cells[posY][posX + 2] = 0x2524;     // ┤
    level->cells[posY + 1][posX] = 0x2514;     // └
    level->cells[posY + 1][posX + 1] = 0x2500; // ─
    level->cells[posY + 1][posX + 2] = 0x2518; // ┘
}

/**
 * Add a empty block in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 */
void level_add_empty(level_t *level, int posX, int posY)
{
    level->cells[posY][posX] = btowc(' ');
    level->colors[posY][posX] = FG_WHITE;
}

/**
 * Add a block in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 */
void level_add_block(level_t *level, int posX, int posY)
{
    level->cells[posY][posX] = btowc(' ');
    level->colors[posY][posX] = BK_BLUE;
}

/**
 * Add a trap in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 */
void level_add_trap(level_t *level, int posX, int posY)
{
    level->cells[posY][posX] = btowc('#');
    level->colors[posY][posX] = BK_BLUE;
}

/**
 * Add a ladder in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 */
void level_add_ladder(level_t *level, int posX, int posY)
{
    int i;

    for (i = posX; i < posX + 3; i++)
        level->colors[posY][i] = FG_YELLOW;

    level->cells[posY][posX] = 0x251C;     // ├
    level->cells[posY][posX + 1] = 0x2500; // ─
    level->cells[posY][posX + 2] = 0x2524; // ┤
}

/**
 * Add a bomb in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 */
void level_add_bomb(level_t *level, int posX, int posY)
{
    level->cells[posY][posX] = btowc('O');
    level->colors[posY][posX] = FG_WHITE;
}

/**
 * Add a life in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 */
void level_add_life(level_t *level, int posX, int posY)
{
    level->cells[posY][posX] = btowc('V');
    level->colors[posY][posX] = FG_RED;
}

/**
 * Add a key in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 * @param num the number of the key (1 to 4)
 */
void level_add_key(level_t *level, int posX, int posY, int num)
{
    level->cells[posY][posX] = btowc('0' + num);
    level->cells[posY + 1][posX] = 0x2518; // ┘

    switch (num)
    {
    case 1:
        level->colors[posY][posX] = BK_MAGENTA;
        level->colors[posY + 1][posX] = FG_MAGENTA;
        break;
    case 2:
        level->colors[posY][posX] = BK_GREEN;
        level->colors[posY + 1][posX] = FG_GREEN;
        break;
    case 3:
        level->colors[posY][posX] = BK_YELLOW;
        level->colors[posY + 1][posX] = FG_YELLOW;
        break;
    case 4:
        level->colors[posY][posX] = BK_BLUE;
        level->colors[posY + 1][posX] = FG_BLUE;
        break;
    }
}

/**
 * Add a gate in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 * @param num the number of the gate (1 to 4)
 */
void level_add_gate(level_t *level, int posX, int posY, int num)
{
    level->cells[posY][posX] = 0x253C; // ┼
    switch (num)
    {
    case 1:
        level->colors[posY][posX] = FG_MAGENTA;
        break;
    case 2:
        level->colors[posY][posX] = FG_GREEN;
        break;
    case 3:
        level->colors[posY][posX] = FG_YELLOW;
        break;
    case 4:
        level->colors[posY][posX] = FG_BLUE;
        break;
    }
}

/**
 * Add a door in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 * @param num the number of the door (1 to 99)
 */
void level_add_door(level_t *level, int posX, int posY, int num)
{
    int i, j;

    level->cells[posY][posX] = btowc('0' + num / 10);
    level->colors[posY][posX] = FG_WHITE;
    level->cells[posY][posX + 1] = btowc('0' + num % 10);
    level->colors[posY][posX + 1] = FG_WHITE;
    level->cells[posY][posX + 2] = btowc(' ');
    level->colors[posY][posX + 2] = BK_GREEN;

    for (i = posY + 1; i < posY + 4; i++)
        for (j = posX; j < posX + 3; j++)
        {
            level->cells[i][j] = btowc(' ');
            level->colors[i][j] = BK_GREEN;
        }
}

/**
 * Add a start door in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 * @param num the number of the door (1 to 99)
 */
void level_add_start(level_t *level, int posX, int posY)
{
    int i, j;

    for (i = posY; i < posY + 4; i++)
        for (j = posX; j < posX + 3; j++)
        {
            level->cells[i][j] = btowc(' ');
            level->colors[i][j] = BK_MAGENTA;
        }
}

/**
 * Add an exit door in a level.
 * @param level the level
 * @param posX the X position
 * @param posY the Y position
 */
void level_add_exit(level_t *level, int posX, int posY)
{
    int i, j;

    for (i = posY; i < posY + 4; i++)
        for (j = posX; j < posX + 3; j++)
        {
            level->cells[i][j] = btowc(' ');
            level->colors[i][j] = BK_YELLOW;
        }
}

void sample_1(TableAdressage_s *Tab, TableVide_s *TabVide)
{
    int i;
    level_t level;

    level_init(&level);

    for (i = 0; i < WIDTH; i++)
    {
        level_add_block(&level, i, 0);
        level_add_block(&level, i, 1);
        level_add_block(&level, i, 2);
        level_add_block(&level, i, 3);
        level_add_block(&level, i, 9);
        level_add_block(&level, i, 10);
        level_add_block(&level, i, 16);
        level_add_block(&level, i, 17);
        level_add_block(&level, i, 18);
        level_add_block(&level, i, 19);
    }
    for (i = 0; i < HEIGHT; i++)
    {
        level_add_block(&level, 0, i);
        level_add_block(&level, WIDTH - 1, i);
    }

    level_add_robot(&level, 21, 5);

    for (i = 9; i <= 15; i++)
        level_add_ladder(&level, 16, i);

    level_add_start(&level, 3, 12);
    level_add_bomb(&level, 39, 8);
    level_add_door(&level, 49, 5, 1);
    level_add_key(&level, 45, 14, 1);
    ajouterLevel(&level, Tab, TabVide);
}

void sample_2(TableAdressage_s *Tab, TableVide_s *TabVide)
{
    level_t level;
    int i;

    level_init(&level);

    for (i = 0; i < WIDTH; i++)
    {
        level_add_block(&level, i, 0);
        level_add_block(&level, i, 5);
        level_add_block(&level, i, 10);
        level_add_block(&level, i, 15);
        level_add_block(&level, i, 19);
    }
    for (i = 0; i < HEIGHT; i++)
    {
        level_add_block(&level, 0, i);
        level_add_block(&level, WIDTH - 1, i);
    }
    for (i = 7; i <= 11; i++)
        level_add_empty(&level, i, 15);
    for (i = 48; i <= 52; i++)
        level_add_empty(&level, i, 15);

    for (i = 15; i <= 18; i++)
    {
        level_add_ladder(&level, 4, i);
        level_add_ladder(&level, 12, i);
        level_add_ladder(&level, 45, i);
        level_add_ladder(&level, 53, i);
    }
    for (i = 10; i <= 14; i++)
        level_add_ladder(&level, 28, i);
    level_add_door(&level, 1, 11, 1);
    level_add_door(&level, 56, 11, 2);
    level_add_door(&level, 56, 6, 3);
    level_add_door(&level, 1, 1, 3);
    level_add_door(&level, 56, 1, 4);

    for (i = 1; i <= 4; i++)
        level_add_gate(&level, 29, i, 1);

    level_add_robot(&level, 37, 11);
    level_add_probe(&level, 18, 7);

    level_display(&level);
    ajouterLevel(&level, Tab, TabVide);
}

int main()
{
    if (setlocale(LC_ALL, "") == NULL)
        printf("setlocale failed.\n");

    TableAdressage_s *Tab = (TableAdressage_s *)malloc(sizeof(TableAdressage_s));
    TableVide_s *TabVide = (TableVide_s *)malloc(sizeof(TableVide_s));
    sample_1(Tab, TabVide);

    level_t lev = loadLevel(0, Tab);
    level_display(&lev);
    // affichage_table_adressage(Tab);
    // affichage_table_vide(TabVide);
    // supprimerLevel(Tab, TabVide, 4);
    affichage_table_adressage(Tab);
    affichage_table_vide(TabVide);
    return EXIT_SUCCESS;
}
