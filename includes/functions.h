#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#include "includeAll.h"

/**
 * ncurses initialisation.
 */
void ncurses_init();

/**
 * Stop ncurses.
 */
void ncurses_stop();

/**
 * Colors initialisation.
 */
void ncurses_colors();

/**
 * Mouse initialisation.
 */
void ncurses_init_mouse();

/**
 * Get the mouse position.
 */
int mouse_getpos(int *x, int *y);

/**
 * @brief Function to declare the different colours in the palette.
 *
 */
void palette();

#endif