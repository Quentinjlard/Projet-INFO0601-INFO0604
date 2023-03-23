#ifndef __ITEM__H__
#define __ITEM__H__

#include "includeAll.h"

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void init_Level(WINDOW*, WINDOW*);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void init_PlayInformations(WINDOW*, char);

/**
 * @brief 
 * 
 * @param windowTools 
 * @param level 
 * @param door 
 */
void init_Tools(WINDOW*, int, int);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_block(WINDOW*, WINDOW*, int);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_Trap(WINDOW*, WINDOW*, int);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 * @param life 
 */
void place_Life(WINDOW*, WINDOW*, int);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 * @param bomb 
 */
void place_bomb(WINDOW*, WINDOW*, int);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 * @param file
 */
void place_ladder(WINDOW*, WINDOW*, int);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_Start(WINDOW*, WINDOW*, int);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_Exit(WINDOW*, WINDOW*, int);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 * @param door 
 */
void place_Door(WINDOW*, WINDOW*, int, int);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 * @param windowTools 
 * @param color 
 */
void place_Gate(WINDOW *windowLevel, WINDOW*, WINDOW*, int);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 * @param windowTools 
 * @param color 
 */
void place_Key(WINDOW* , WINDOW* ,WINDOW*, int);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_Probe(WINDOW*, WINDOW* , int);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_Robot(WINDOW* , WINDOW*, int);


#endif
