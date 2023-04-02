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

// Lancement du jeu
void playingField(char *);

// Inialiser tous les mutex
void initialiser_mutex();

// Routine de thread d'un robot
void *routine_robot(void *);

// Routine de thread d'une sonde
void *routine_probe(void *);

void *routine_trap(void *);

// Chercher le start
int searchStart(level_t);

// Chercher un robot
int searchRobot(level_t, int);

// Chercher une sonde
int searchProbe(level_t, int);

// Chercher une trap
int searchTrap(level_t);

// Chercher la deuxième porte de même niveau
int searchDoorPair(level_t, int, int);

// Faire apparaitre le joueur
void spawnPlayer(level_t *, int, int);

// Faire apparaitre le robot
void spawnRobot(level_t *, int);

// Faire apparaitre une sonde
void spawnProbe(level_t *, int);

// Faire disparaitre le joueur
void dispawnPlayer(level_t *, level_t, int, int);

// Faire disparaitre un robot
void dispawnRobot(level_t *, int);

// Faire disparaitre un Probe
void dispawnProbe(level_t *, int);

// Faire bouger le joueur
void movePlayer(level_t *, level_t, int, int, int);

// Faire bouger un robot
void moveRobot(level_t *, level_t, int, int);

// Faire bouger une sonde
void moveProbe(level_t *, level_t, int, int);

// Détecter un object au sol
int detectGround(level_t, int);

// Détecter une clé
int detectKey(level_t, int);

// Détecter une porte
int detectDoor(level_t, int);

// Détecter une sortie
int detectExit(level_t, int);

// Détecter une échelle
int detectLadder(level_t, int);

// Détecter une bombe dans un rayon de 5 (pour les robots et sondes)
int detectBombe(level_t, int);

// Ajouter une vide dans l'interface
void addLife(WINDOW *);

// Enlever une vie dans l'interface
void subLife(WINDOW *);

// Ajouter une bombe dans l'interface
void addBomb(WINDOW *);

// Enlever une bombe dans l'interface
void subBomb(WINDOW *);

// Ajouter une clé
void addKey(WINDOW *, int);

// Placer une bombe
void *placeBombe(void *);

#endif
