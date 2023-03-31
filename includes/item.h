/**
 * @file item.h
 * @author JUILLIARD Quentin (quentin.juilliard@etudiant.univ-reims.fr)
 * @author COGNE Romain (romain.cogne@etudiant.univ-reims.fr)
 * @brief
 * @version 0.1
 * @date 2023-02-02
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef __ITEM__H__
#define __ITEM__H__

#include "level.h"

void init_Level(WINDOW *, WINDOW *);

void init_PlayInformations(WINDOW *, char);

void init_Tools(WINDOW *, int, int);

void delete(WINDOW *, WINDOW *, level_t *,int , int );

void place_block(WINDOW *, WINDOW *, level_t *,int , int );

void place_Trap(WINDOW *, WINDOW *, level_t *,int , int );

void place_Life(WINDOW *, WINDOW *, level_t *,int , int );

void place_bomb(WINDOW *, WINDOW *, level_t *,int , int );

void place_ladder(WINDOW *, WINDOW *, level_t *,int , int );

void place_Start(WINDOW *, WINDOW *, level_t *,int, int );

void place_Exit(WINDOW *, WINDOW *, level_t *,int , int );

void place_Door(WINDOW *, WINDOW *, int, level_t *,int , int );

void place_Gate(WINDOW *, WINDOW *, WINDOW *, level_t *);

void place_Key(WINDOW *, WINDOW *, WINDOW *, level_t *);

void place_Probe(WINDOW *, WINDOW *, level_t *,int , int );

void place_Robot(WINDOW *, WINDOW *, level_t *,int , int );

#endif
