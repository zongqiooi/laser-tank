#include <stdlib.h>
#include "enemy.h" 
#include "map.h"
#include "refresh.h"
#include "newSleep.h"

/* NAME      : enemy */
/* PURPOSE   : Allow the enemy to shoot the laser when the player moves in front of the direction that the enemy is facing */
/* IMPORTS   : **cArray (map array in 2D), *mirrorsArray (array of structure for mirrors), mirrorsNum (number of mirrors), row (map row size), col (map column size), playerX (player X coordinate), */
/*             playerY (player Y coordinate), enemyX (enemy X coordinate), enemyY (enemy Y coordinate), playerIcon (player character icon), enemyIcon (enemy character icon), */
/*             laserState (player or enemy shoots laser), loopCount (allow laser to move block by block through calling the map() function by passing the increasing or decreasing loopCount value, */
/*             *end (determine win or lose condition), *reflection (determine whether is there any reflection occurs and determine the type of reflection), */
/*             *bulletDir (direction in which the laser is shooting from), *laserX (laser X coordinate), *laserY (laser Y coordinate), *LL (linked list to store the map array), */
/*             action (player action), *fileName (file name to save the log) */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : The player moves in front of the direction that the enemy is facing */
/*    POST   : The enemy will shoot the laser towards the player */
/* REMARKS   : laserState = 1 (player shoots laser); laserState = 2 (enemy shoots laser) */
/*             end = 1 (player wins); end = 2 (player loses) */
/*             reflection = 0 (no reflection occurs); reflection = 1 (single reflection occurred); reflection = 2 (double or multiple reflections occurred) */

void enemy(char **cArray, Mirrors *mirrorsArray, int mirrorsNum, int row, int col, int playerX, int playerY, int enemyX, int enemyY, char playerIcon, char enemyIcon, int laserState, int loopCount, int *end, int *reflection, char *bulletDir, int *laserX, int *laserY, LinkedList *LL, char action, char *fileName)
{	
	laserState = 2; /* enemy shoots laser */
	
	if(enemyY == playerY) /* enemy and player on the same horizontal line */ 
	{
		if(enemyX > playerX && enemyIcon == '<') /* enemy at right side, shoot to the left */
		{
			do
			{
				refresh();
				map(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, -loopCount, end, reflection, bulletDir, laserX, laserY, LL, action, fileName); /* "-loopCount" is passed because in opposite direction */
				newSleep(0.1); /* delay 0.1 second for laser animation */
				
				if(*end == 2) /* enemy hits player and lose */
				{
					loopCount = 100; /* escape the loop and go back to main function */ 
				}
				
				loopCount++;
			}while(loopCount <= enemyX - 1);
		}
		else if(enemyX < playerX && enemyIcon == '>') /* enemy at left side, shoot to the right */
		{
			do
			{
				refresh();
				map(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, loopCount, end, reflection, bulletDir, laserX, laserY, LL, action, fileName); /* calls the map to output the laser */
				newSleep(0.1); /* delay 0.1 second for laser animation */
				
				if(*end == 2) /* enemy hits player and lose */
				{
					loopCount = 100; /* escape the loop and go back to main function */ 
				}
				
				loopCount++;
			}while(loopCount <= col - 2 - enemyX);
		}
	}
	else if(enemyX == playerX) /* enemy and player on the same vertical line */ 
	{
		if(enemyY > playerY && enemyIcon == '^') /* enemy at bottom, shoot upwards */
		{
			do
			{
				refresh();
				map(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, loopCount, end, reflection, bulletDir, laserX, laserY, LL, action, fileName); /* calls the map to output the laser */
				newSleep(0.1); /* delay 0.1 second for laser animation */
				
				if(*end == 2) /* enemy hits player and lose */
				{
					loopCount = 100; /* escape the loop and go back to main function */ 
				}
				
				loopCount++;
			}while(loopCount <= enemyY - 1);
		}
		else if(enemyY < playerY && enemyIcon == 'v') /* enemy at top, shoot downwards */
		{
			do
			{
				refresh();
				map(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, -loopCount, end, reflection, bulletDir, laserX, laserY, LL, action, fileName); /* "-loopCount" is passed because in opposite direction */
				newSleep(0.1); /* delay 0.1 second for laser animation */
				
				if(*end == 2) /* enemy hits player and lose */
				{
					loopCount = 100; /* escape the loop and go back to main function */ 
				}
				
				loopCount++;
			}while(loopCount <= row - 2 - enemyY);
		}
	}
}
