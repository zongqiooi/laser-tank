#ifndef OVERLAP_H
#define OVERLAP_H

#include "mirror.h" /* for the function prototype in this file to understand the "Mirrors" struct declared in the "mirror.h" header file */

void overlap(int row, int col, int *playerX, int *playerY, int enemyX, int enemyY, Mirrors *mirrorsArray, char playerIcon, int mirrorsNum);

#endif
