#ifndef ENEMY_H
#define ENEMY_H

#include "mirror.h" /* for the function prototype in this file to understand the "Mirrors" struct declared in the "mirror.h" header file */
#include "linkedList.h" /* for the function prototype in this file to understand the "LinkedList" struct declared in the "linkedList.h" header file */

void enemy(char **cArray, Mirrors *mirrorsArray, int mirrorsNum, int row, int col, int playerX, int playerY, int enemyX, int enemyY, char playerIcon, char enemyIcon, int laserState, int loopCount, int *end, int *reflection, char *bulletDir, int *laserX, int *laserY, LinkedList *LL, char action, char *fileName);

#endif
