/**
 * @file functions.h
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2023-02-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

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