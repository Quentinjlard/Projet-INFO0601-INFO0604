/**
 * @file level.h
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2023-02-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <wchar.h>
#include <ncurses.h>
#include "includeAll.h"
#include "tableAdressage.h"

#define nblignes 20
#define nbCols 60

// Structure d'un niveau
typedef struct
{
    wint_t cells[nblignes * nbCols];
    int colors[nblignes * nbCols];
} level_t;

level_t loadLevel(int, tableAdressage_t *, char *);
void init_matLevel(level_t *);
void level_display(WINDOW *, level_t);
void clear_windowLevel(WINDOW *);
int supprimerLevel(tableAdressage_t *, int, char *);
int ajouterLevel(level_t *, tableAdressage_t *, char *);
off_t rechercheEspaceVide(int, tableAdressage_t *);
void afficherDEBUG(level_t, WINDOW *);
#endif