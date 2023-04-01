/**
 * @file functions.c
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
#include "functions.h"
#include "includeAll.h"

/**
 * Initialisation d'ncurses
 */
void ncurses_init()
{
  initscr();            // Démarre le mode ncurses
  cbreak();             // Désactive le cache du buffer
  noecho();             // Désactive les touches tapées clavier
  keypad(stdscr, TRUE); // Activations des touches directionnelles
  refresh();            // Rafraîchis l'affichage
  curs_set(FALSE);      // Cache le curseur de la souris
}

/**
 * Arrêt d'ncurses.
 */
void ncurses_stop()
{
  endwin();
}

/**
 * Initialisation des couleurs
 */
void ncurses_colors()
{
  // Vérification si la machine supporte les couleurs dans un terminal
  if (has_colors() == FALSE)
  {
    ncurses_stop();
    fprintf(stderr, "Le terminal ne supporte pas les couleurs\n");
    exit(EXIT_FAILURE);
  }

  // Activation des couleurs
  start_color();
}

/**
 * Activation de la souris
 */
void ncurses_init_mouse()
{
  if (!mousemask(BUTTON1_PRESSED, NULL))
  {
    ncurses_stop();
    fprintf(stderr, "La souris n'est pas supportée\n");
    exit(EXIT_FAILURE);
  }
}

/**
 * Obtenir la position de la souris
 */
int mouse_getpos(int *x, int *y)
{
  MEVENT event;
  int result = getmouse(&event);
  if (result == OK)
  {
    *x = event.x;
    *y = event.y;
  }
  return result;
}

/**
 * @brief Function pour déclarer les différentes couleur de la palette
 *
 */
void palette()
{

  // +----+--------------------------------+
  // | ID |      Lettre     |      Fond    |
  // +----+--------------------------------+
  // | 1  |      Noir       |      Noir    |
  // | 2  |      Rouge      |      Noir    |
  // | 3  |      Vert       |      Noir    |
  // | 4  |      Jaune      |      Noir    |
  // | 5  |      Blue       |      Noir    |
  // | 6  |     Magenta     |      Noir    |
  // | 7  |      Cyan       |      Noir    |
  // | 8  |      Blanc      |      Noir    |
  // | 9  |      Noir       |      Cyan    |
  // | 10 |      Noir       |      Magenta |
  // | 11 |      Noir       |      Vert    |
  // | 12 |      Noir       |      Jaune   |
  // | 13 |      Noir       |      Bleu    |
  // | 14 |      Noir       |      Rouge   |

  init_pair(1, COLOR_BLACK, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  init_pair(5, COLOR_BLUE, COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(7, COLOR_CYAN, COLOR_BLACK);
  init_pair(8, COLOR_WHITE, COLOR_BLACK);
  init_pair(9, COLOR_BLACK, COLOR_CYAN);
  init_pair(10, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(11, COLOR_BLACK, COLOR_GREEN);
  init_pair(12, COLOR_BLACK, COLOR_YELLOW);
  init_pair(13, COLOR_BLACK, COLOR_BLUE);
  init_pair(14, COLOR_BLACK, COLOR_RED);
}