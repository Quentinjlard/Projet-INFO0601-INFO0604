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

// Lancement du jeu
void playingField(char *);

// Chercher le start
int searchStart(level_t);

// Faire apparaitre le joueur
void spawnPlayer(level_t *, int, int);

// Faire bouger le joueur
void movePlayer(level_t *, level_t, int, int, int);

// Détecter un object au sol
int detectGround(level_t, int);

// Détecter une clé
int detectKey(level_t, int);

// Détecter une sortie
int detectExit(level_t niveau, int pos);

// Détecter une échelle
int detectLadder(level_t, int);

// Ajouter une vide dans l'interface
void addLife(WINDOW *);

// Enlever une vie dans l'interface
void subLife(WINDOW *);

// Ajouter une bombe dans l'interface
void addBomb(WINDOW *);

// Enlever une bombe dans l'interface
void subBomb(WINDOW *);

// Ajouter une clé
void addKey(WINDOW *windowPlayerInformation, int couleur);

#endif
