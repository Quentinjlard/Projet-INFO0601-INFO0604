#ifndef __ITEM__H__
#define __ITEM__H__

#include "includeAll.h"

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void init_Level(WINDOW *windowLevel, WINDOW *windowInformations);

/**
 * @brief 
 * 
 * @param windowTools 
 * @param level 
 * @param door 
 */
void init_Tools(WINDOW *windowTools, int level, int door);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_block(WINDOW *windowLevel, WINDOW *windowInformations);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_Trap(WINDOW *windowLevel, WINDOW *windowInformations);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 * @param life 
 */
void place_Life(WINDOW *windowLevel, WINDOW *windowInformations, int life);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 * @param bomb 
 */
void place_bomb(WINDOW *windowLevel, WINDOW *windowInformations, int bomb);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_ladder(WINDOW *windowLevel, WINDOW *windowInformations);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_Start(WINDOW *windowLevel, WINDOW *windowInformations);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_Exit(WINDOW *windowLevel, WINDOW *windowInformations);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 * @param door 
 */
void place_Door(WINDOW *windowLevel, WINDOW *windowInformations, int door);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 * @param windowTools 
 * @param color 
 */
void place_Gate(WINDOW *windowLevel, WINDOW *windowInformations,WINDOW *windowTools, int color);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 * @param windowTools 
 * @param color 
 */
void place_Key(WINDOW *windowLevel, WINDOW *windowInformations,WINDOW *windowTools, int color);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_Probe(WINDOW *windowLevel, WINDOW *windowInformations);

/**
 * @brief 
 * 
 * @param windowLevel 
 * @param windowInformations 
 */
void place_Robot(WINDOW *windowLevel, WINDOW *windowInformations);


#endif
