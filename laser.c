#include <stdlib.h> 
#include "laser.h"
#include "map.h"
#include "refresh.h"
#include "newSleep.h"

/* NAME      : laser */
/* PURPOSE   : Allow the player to shoot the laser in the direction that it is facing */
/* IMPORTS   : **cArray (map array in 2D), *mirrorsArray (array of structure for mirrors), mirrorsNum (number of mirrors), row (map row size), col (map column size), playerX (player X coordinate), */
/*             playerY (player Y coordinate), enemyX (enemy X coordinate), enemyY (enemy Y coordinate), playerIcon (player character icon), enemyIcon (enemy character icon), */
/*             laserState (player or enemy shoots laser), loopCount (allow laser to move block by block through calling the map() function by passing the increasing or decreasing loopCount value, */
/*             *end (determine win or lose condition), *reflection (determine whether is there any reflection occurs and determine the type of reflection), */
/*             *bulletDir (direction in which the laser is shooting from), *laserX (laser X coordinate), *laserY (laser Y coordinate), *LL (linked list to store the map array), */
/*             action (player action), *fileName (file name to save the log) */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : The "f" key is entered by the user */
/*    POST   : The player will shoot the laser in the direction that it is facing */
/* REMARKS   : laserState = 1 (player shoots laser); laserState = 2 (enemy shoots laser) */
/*             end = 1 (player wins); end = 2 (player loses) */
/*             reflection = 0 (no reflection occurs); reflection = 1 (single reflection occurred); reflection = 2 (double or multiple reflections occurred) */

void laser(char **cArray, Mirrors *mirrorsArray, int mirrorsNum, int row, int col, int playerX, int playerY, int enemyX, int enemyY, char playerIcon, char enemyIcon, int laserState, int loopCount, int *end, int *reflection, char *bulletDir, int *laserX, int *laserY, LinkedList *LL, char action, char *fileName)
{
	int flag = 0; /* to ensure the loopCount value is reassigned once only */
	laserState = 1; /* player shoots laser */
	
	if(playerIcon == '>')
	{
		do
		{
			refresh();
			map(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, loopCount, end, reflection, bulletDir, laserX, laserY, LL, action, fileName); /* calls the map to output the laser */
			newSleep(0.1); /* delay 0.1 second for laser animation */
			
			if(*end == 1 || *end == 2) /* player wins or player loses */
			{
				*laserX = 0; /* force to escape the loop and go back to main function */
			}
			else if(*reflection == 1) /* when single reflection occurs */
			{
				if(flag == 0)
				{
					loopCount = 0;				
					flag = 1; /* to reassign loopCount value once only */
				}
				else if(flag == 2) 
				{
					loopCount = 1;
					flag = 1; /* to reassign loopCount value once only */
				}
			}
			else if(*reflection == 2) /* when double or multiple reflections occur */
			{
				*reflection = 1;
				loopCount = 0;
				flag = 2; /* to reassign loopCount value once only */
			}
			
			loopCount++;
		}while(*laserX > 0 && *laserX < col - 1 && *laserY > 0 && *laserY < row - 1); /* repeat the loop until the laser hits the wall or until there is a win or a lose condtion */
		
		*reflection = 0; /* reset to no reflection case after shooting once */
		*laserX = 1; /* reset the laser X coordinate after shooting once */
		*laserY = 1; /* reset the laser Y coordinate after shooting once */
	}
	else if(playerIcon == '<')
	{
		do
		{
			refresh();
			
			if(*reflection == 0)
			{
				map(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, -loopCount, end, reflection, bulletDir, laserX, laserY, LL, action, fileName); /* negative loopCount is passed because in opposite direction */
			}
			else
			{ 
				map(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, loopCount, end, reflection, bulletDir, laserX, laserY, LL, action, fileName); /* calls the map to output the laser */
			}
			
			newSleep(0.1); /* delay 0.1 second for laser animation */
			
			if(*end == 1 || *end == 2) /* player wins or player loses */
			{
				*laserX = 0; /* force to escape the loop and go back to main function */
			}
			else if(*reflection == 1) /* when single reflection occurs */
			{
				if(flag == 0)
				{
					loopCount = 0;				
					flag = 1; /* to reassign loopCount value once only */
				}
				else if(flag == 2) 
				{
					loopCount = 1;
					flag = 1; /* to reassign loopCount value once only */
				}
			}
			else if(*reflection == 2) /* when double or multiple reflections occur */
			{
				*reflection = 1;
				loopCount = 0;
				flag = 2; /* to reassign loopCount value once only */
			}
			
			loopCount++;
		}while(*laserX > 0 && *laserX < col - 1 && *laserY > 0 && *laserY < row - 1); /* repeat the loop until the laser hits the wall or until there is a win or a lose condtion */
		
		*reflection = 0; /* reset to no reflection case after shooting once */
		*laserX = 1; /* reset the laser X coordinate after shooting once */
		*laserY = 1; /* reset the laser Y coordinate after shooting once */
	}
	else if(playerIcon == '^')
	{
		do
		{
			refresh();
			map(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, loopCount, end, reflection, bulletDir, laserX, laserY, LL, action, fileName); /* calls the map to output the laser */
			newSleep(0.1); /* delay 0.1 second for laser animation */
			
			if(*end == 1 || *end == 2) /* player wins or player loses */
			{
				*laserX = 0; /* force to escape the loop and go back to main function */
			}
			else if(*reflection == 1) /* when single reflection occurs */
			{
				if(flag == 0)
				{
					loopCount = 0;				
					flag = 1; /* to reassign loopCount value once only */
				}
				else if(flag == 2)
				{
					loopCount = 1;
					flag = 1; /* to reassign loopCount value once only */
				}
			}
			else if(*reflection == 2) /* when double or multiple reflections occur */
			{
				*reflection = 1;
				loopCount = 0;
				flag = 2; /* to reassign loopCount value once only */
			}
			
			loopCount++;
		}while(*laserX > 0 && *laserX < col - 1 && *laserY > 0 && *laserY < row - 1); /* repeat the loop until the laser hits the wall or until there is a win or a lose condtion */
		
		*reflection = 0; /* reset to no reflection case after shooting once */
		*laserX = 1; /* reset the laser X coordinate after shooting once */
		*laserY = 1; /* reset the laser Y coordinate after shooting once */
	}
	else if(playerIcon == 'v')
	{
		do
		{
			refresh();
			
			if(*reflection == 0)
			{
				map(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, -loopCount, end, reflection, bulletDir, laserX, laserY, LL, action, fileName); /* negative loopCount is passed because in opposite direction*/
			}
			else if(*reflection == 1)
			{
				map(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, loopCount, end, reflection, bulletDir, laserX, laserY, LL, action, fileName); /* calls the map to output the laser */
			}
			
			newSleep(0.1); /* delay 0.1 second for laser animation */
			
			if(*end == 1 || *end == 2) /* player wins or player loses */
			{
				*laserX = 0; /* force to escape the loop and go back to main function */
			}
			else if(*reflection == 1) /* when single reflection occurs */
			{
				if(flag == 0)
				{
					loopCount = 0;				
					flag = 1; /* to reassign loopCount value once only */
				}
				else if(flag == 2)
				{
					loopCount = 1;
					flag = 1; /* to reassign loopCount value once only */
				}
			}
			else if(*reflection == 2) /* when double or multiple reflections occur */
			{
				*reflection = 1;
				loopCount = 0;
				flag = 2; /* to reassign loopCount value once only */
			}
			
			loopCount++;
		}while(*laserX > 0 && *laserX < col - 1 && *laserY > 0 && *laserY < row - 1); /* repeat the loop until the laser hits the wall or until there is a win or a lose condtion */
		
		*reflection = 0; /* reset to no reflection case after shooting once */
		*laserX = 1; /* reset the laser X coordinate after shooting once */
		*laserY = 1; /* reset the laser Y coordinate after shooting once */
	}
}
