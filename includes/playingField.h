/**
 * @file playingFiled.h
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2023-02-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __playingField_H__
#define __playingField_H__

#include "item.h"
/**
 * @brief
 *
 */

void playingField(char *);
int searchStart(level_t);
void spawnPlayer(level_t *, int);
void movePlayer(level_t *niveau, level_t buff, int pos, int direction);

#endif
