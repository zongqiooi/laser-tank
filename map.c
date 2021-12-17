#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "result.h"

/* NAME      : map */
/* PURPOSE   : Draw and print out the map of the game on the terminal */
/* IMPORTS   : **cArray (map array in 2D), *mirrorsArray (array of structure for mirrors), mirrorsNum (number of mirrors), row (map row size), col (map column size), playerX (player X coordinate), */
/*             playerY (player Y coordinate), enemyX (enemy X coordinate), enemyY (enemy Y coordinate), playerIcon (player character icon), enemyIcon (enemy character icon), */
/*             laserState (player or enemy shoots laser), loopCount (allow laser to move block by block through calling the map() function by passing the increasing or decreasing loopCount value, */
/*             *end (determine win or lose condition), *reflection (determine whether is there any reflection occurs and determine the type of reflection), */
/*             *bulletDir (direction in which the laser is shooting from), *laserX (laser X coordinate), *laserY (laser Y coordinate), *LL (linked list to store the map array), */
/*             action (player action), *fileName (file name to save the log) */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : This function will be called throughout the game if there is no win or lose condition occurred */
/*    POST   : The map will be drawn and printed out on the terminal */
/* REMARKS   : None */

void map(char **cArray, Mirrors *mirrorsArray, int mirrorsNum, int row, int col, int playerX, int playerY, int enemyX, int enemyY, char playerIcon, char enemyIcon, int laserState, int loopCount, int *end, int *reflection, char *bulletDir, int *laserX, int *laserY, LinkedList *LL, char action, char *fileName)
{
	int i = 0; 		      /* loop variable 1 */
	int j = 0; 		      /* loop variable 2 */
	int k = 0; 		      /* loop variable 3 */
	int front = 0;               /* to indicate whether the player is shooting directly in front of a mirror */
	int colorX = 0;              /* laser X coordinate for laser color change */
	int colorY = 0;              /* laser Y coordinate for laser color change */
	static int hit;              /* to indicate which specific mirror is hit by the laser */
	static int tempX;            /* temporary X coordinate for mirror when reflection occurs */
	static int tempY;            /* temporary Y coordinate for mirror when reflection occurs */
	static char tempBulletDir;   /* temporary variable for storing the bullet moving direction */
	
	/* Drawing the map */
	for(i = 0; i < row; i++) /* loop through every rows */
	{
		for(j = 0; j < col; j++) /* loop through every columns */
		{
			for(k = 0; k < mirrorsNum; k++) /* loop through all mirrors in the map */
			{
				/* Cases when laser is not reflected */
				if(*reflection == 0 && laserState == 1 && i == playerY && j == playerX + loopCount && (playerIcon == '>' || playerIcon == '<')) /* laser shoots by player horizontally */ 
				{
					if(i == enemyY && j == enemyX) /* laser hits enemy */
					{
						cArray[i][j] = 'X'; 
						*end = 1; /* player wins */
					}
					else 
					{
						/* Checking for laser coming from the left or right */
						if(j - 1 == mirrorsArray[k].mirrorX && i == mirrorsArray[k].mirrorY && playerIcon == '<')
						{
							tempBulletDir = 'r';
							front = 0; 
						}
						else if(j + 1 == mirrorsArray[k].mirrorX && i == mirrorsArray[k].mirrorY && playerIcon == '>')
						{
							tempBulletDir = 'l';
							front = 0;
						}
						else if(j == mirrorsArray[k].mirrorX && i == mirrorsArray[k].mirrorY && j + 1 == playerX && i == playerY &&  playerIcon == '<') /* when player shoots at the front of mirror directly from the right side */
						{
							tempBulletDir = 'r';
							front = 1;
						}
						else if(j == mirrorsArray[k].mirrorX && i == mirrorsArray[k].mirrorY && j - 1 == playerX && i == playerY && playerIcon == '>') /* when player shoots at the front of mirror directly from the left side */
						{
							tempBulletDir = 'l';
							front = 1;
						}
						
						if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
						{
							*bulletDir = tempBulletDir;
							*reflection = 1;
							loopCount = 0; /* to reset loopCount value when bullet is shooting from left or right so that the bullet is reflected properly */
							tempX = j; /* the mirror X coordinate hit by laser */ 
							tempY = i; /* the mirror Y coordinate hit by laser */
							hit = k; /* the specific mirror hit by laser */ 							
							
							if(front == 1)
							{
								k = 1001; /* ends the mirrors loop and avoid entering the mirrors reflection case at line 196 */
							}
							else 
							{
								k = 1000; /* ends the mirrors loop */
							}
						}
						else
						{
							cArray[i][j] = '-'; /* horizontal laser, if the laser does not hit the enemy */
							*laserX = j;
							*laserY = i;
							colorX = j;
							colorY = i;
						}
					}
				}
				else if(*reflection == 0 && laserState == 1 && i == playerY - loopCount && j == playerX && (playerIcon == '^' || playerIcon == 'v')) /* laser shoots by player vertically */
				{
					if(i == enemyY && j == enemyX) /* laser hits enemy */
					{
						cArray[i][j] = 'X'; 
						*end = 1; /* player wins */
					}
					else 
					{
						/* Checking for laser coming from the upper or down side */
						if(i - 1 == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX && playerIcon == '^')
						{
							tempBulletDir = 'd';
							front = 0; 
						}
						else if(i + 1 == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX && playerIcon == 'v')
						{
							tempBulletDir = 'u';
							front = 0;
						}
						else if(j == mirrorsArray[k].mirrorX && i == mirrorsArray[k].mirrorY && j == playerX && i + 1 == playerY && playerIcon == '^') /* when player shoots at the front of mirror directly from the down side */
						{
							tempBulletDir = 'd';
							front = 1;
						}
						else if(j == mirrorsArray[k].mirrorX && i == mirrorsArray[k].mirrorY && j == playerX && i - 1 == playerY && playerIcon == 'v') /* when player shoots at the front of mirror directly from the upper side */
						{
							tempBulletDir = 'u';
							front = 1;
						}
						
						if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
						{
							*bulletDir = tempBulletDir;
							*reflection = 1;
							loopCount = 0; /* to reset loopCount value when bullet is shooting from up or down so that the bullet is reflected properly */ 
							tempX = j; /* the mirror X coordinate hit by laser */ 
							tempY = i; /* the mirror Y coordinate hit by laser */
							hit = k; /* the specific mirror hit by laser */
							
							if(front == 1)
							{
								k = 1001; /* ends the mirrors loop and avoid entering the mirrors reflection case at line 196 */
							}
							else 
							{
								k = 1000; /* ends the mirrors loop */
							}
							
						}
						else
						{
							cArray[i][j] = '|'; /* vertical laser, if the laser does not hit the enemy */
							*laserX = j;
							*laserY = i;
							colorX = j;
							colorY = i;
						}
					}
				}
				else if(laserState == 2 && i == enemyY && j == enemyX + loopCount && (enemyIcon == '>' || enemyIcon == '<')) /* laser shoots by enemy horizontal */
				{
					if(i == playerY && j == playerX) /* laser hits player */
					{
						cArray[i][j] = 'X'; 
						*end = 2; /* player loses */
					}
					else 
					{
						cArray[i][j] = '-'; /* horizontal laser, if the laser does not hit the player */
						colorX = j;
						colorY = i;
					}
				}
				else if(laserState == 2 && i == enemyY - loopCount && j == enemyX && (enemyIcon == '^' || enemyIcon == 'v')) /* laser shoots by enemy vertically */
				{
					if(i == playerY && j == playerX) /* laser hits player */
					{
						cArray[i][j] = 'X'; 
						*end = 2; /* player loses*/
					}
					else 
					{
						cArray[i][j] = '|'; /* vertical laser, if the laser does not hit the player */
						colorX = j;
						colorY = i;
					}
				}
				else
				{
					cArray[i][j] = ' '; /* if not laser, everything else on the map will be an empty space */
				}
			}
				
			/* Cases when laser hits and mirrors and the laser is reflected */
			if(*reflection == 1 && k != 1001) /* k != 1001 means when the reflection is first detected, this part will not be run because the laser will not be reflected directly */
			{
				for(k = 0; k < mirrorsNum; k++) /* loop through all mirrors in the map */
				{	
					if(*reflection == 1 && i == tempY - loopCount && j == tempX && mirrorsArray[hit].mirrorIcon == '\\' && *bulletDir == 'r') /* when mirror is '\' and the bullet is coming from the right side */
					{
						if(i == enemyY && j == enemyX) /* laser hits enemy */
						{
							cArray[i][j] = 'X'; 
							*end = 1; /* player wins */
						}
						else if(i == playerY && j == playerX) /* laser hits player */
						{
							cArray[i][j] = 'X';
							*end = 2; /* player loses */
						}
						else
						{
							if(i - 1 == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
							{
								tempBulletDir = 'd';
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
							{
								tempBulletDir = 'd';
							}
							
							if(front == 1) /* for condition when player shoots directly in front of mirror */
							{
								cArray[i][j] = '|';
								*laserX = j;
								*laserY = i; 
								colorX = j;	
								colorY = i;
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX) /* when laser hits a mirror */
							{
								*bulletDir = tempBulletDir;
								*reflection = 2;
								loopCount = 0; /* to reset loopCount value when bullet is shooting from right so that the bullet is reflected properly */ 
								tempX = j; /* the mirror X coordinate hit by laser */ 
								tempY = i; /* the mirror Y coordinate hit by laser */
								hit = k; /* the specific mirror hit by laser */
								k = 1000; /* ends the mirrors loop */ 
							}
							else 
							{
								cArray[i][j] = '|';
								*laserX = j;
								*laserY = i; 
								colorX = j;
								colorY = i;	
							}
						}
					}
					else if(*reflection == 1 && i == tempY + loopCount && j == tempX && mirrorsArray[hit].mirrorIcon == '\\' && *bulletDir == 'l') /* when mirror is '\' and the bullet is coming from the left side */
					{
						if(i == enemyY && j == enemyX) /* laser hits enemy */
						{
							cArray[i][j] = 'X'; 
							*end = 1; /* player wins */
						}
						else if(i == playerY && j == playerX) /* laser hits player */
						{
							cArray[i][j] = 'X';
							*end = 2; /* player loses */
						}
						else
						{
							if(i + 1 == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
							{
								tempBulletDir = 'u';
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
							{
								tempBulletDir = 'u';
							}
							
							if(front == 1) /* for condition when player shoots directly in front of mirror */
							{
								cArray[i][j] = '|';
								*laserX = j;
								*laserY = i; 
								colorX = j;	
								colorY = i;
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX) /* when laser hits a mirror */
							{
								*bulletDir = tempBulletDir;
								*reflection = 2;
								loopCount = 0; /* to reset loopCount value when bullet is shooting from left so that the bullet is reflected properly */ 
								tempX = j; /* the mirror X coordinate hit by laser */ 
								tempY = i; /* the mirror Y coordinate hit by laser */
								hit = k; /* the specific mirror hit by laser */
								k = 1000; /* ends the mirrors loop */ 
							}
							else 
							{
								cArray[i][j] = '|';
								*laserX = j;
								*laserY = i; 
								colorX = j;
								colorY = i;			
							}	
						}
					}
					else if(*reflection == 1 && i == tempY && j == tempX + loopCount && mirrorsArray[hit].mirrorIcon == '\\' && *bulletDir == 'u') /* when mirror is '\' and the bullet is coming from the upper side */
					{
						if(i == enemyY && j == enemyX) /* laser hits enemy */
						{
							cArray[i][j] = 'X'; 
							*end = 1; /* player wins */
						}
						else if(i == playerY && j == playerX) /* laser hits player */
						{
							cArray[i][j] = 'X';
							*end = 2; /* player loses */
						}
						else
						{
							if(j + 1 == mirrorsArray[k].mirrorX && i == mirrorsArray[k].mirrorY)
							{
								tempBulletDir = 'l';
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
							{
								tempBulletDir = 'l';
							}
							
							if(front == 1) /* for condition when player shoots directly in front of mirror */
							{
								cArray[i][j] = '-';
								*laserX = j;
								*laserY = i; 
								colorX = j;	
								colorY = i;
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX) /* when laser hits a mirror */
							{
								*bulletDir = tempBulletDir;
								*reflection = 2;
								loopCount = 0; /* to reset loopCount value when bullet is shooting from upper side so that the bullet is reflected properly */ 
								tempX = j; /* the mirror X coordinate hit by laser */ 
								tempY = i; /* the mirror Y coordinate hit by laser */
								hit = k; /* the specific mirror hit by laser */
								k = 1000; /* ends the mirrors loop */ 
							}
							else 
							{
								cArray[i][j] = '-';
								*laserX = j;
								*laserY = i; 
								colorX = j;
								colorY = i;
							}
							
						}
					}
					else if(*reflection == 1 && i == tempY && j == tempX - loopCount && mirrorsArray[hit].mirrorIcon == '\\' && *bulletDir == 'd') /* when mirror is '\' and the bullet is coming from the down side */
					{
						if(i == enemyY && j == enemyX) /* laser hits enemy */
						{
							cArray[i][j] = 'X'; 
							*end = 1; /* player wins */
						}
						else if(i == playerY && j == playerX) /* laser hits player */
						{
							cArray[i][j] = 'X';
							*end = 2; /* player loses */
						}
						else
						{
							if(j - 1 == mirrorsArray[k].mirrorX && i == mirrorsArray[k].mirrorY)
							{
								tempBulletDir = 'r';
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
							{
								tempBulletDir = 'r';
							}
							
							if(front == 1) /* for condition when player shoots directly in front of mirror */
							{
								cArray[i][j] = '-';
								*laserX = j;
								*laserY = i; 
								colorX = j;	
								colorY = i;
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX) /* when laser hits a mirror */
							{
								*bulletDir = tempBulletDir;
								*reflection = 2;
								loopCount = 0; /* to reset loopCount value when bullet is shooting from down side so that the bullet is reflected properly */ 
								tempX = j; /* the mirror X coordinate hit by laser */ 
								tempY = i; /* the mirror Y coordinate hit by laser */
								hit = k; /* the specific mirror hit by laser */
								k = 1000; /* ends the mirrors loop */ 
							}
							else 
							{
								cArray[i][j] = '-';
								*laserX = j;
								*laserY = i; 
								colorX = j;
								colorY = i;
							}
						}
					}
					else if(*reflection == 1 && i == tempY + loopCount && j == tempX && mirrorsArray[hit].mirrorIcon == '/' && *bulletDir == 'r') /* when mirror is '/' and the bullet is coming from the right side */
					{
						if(i == enemyY && j == enemyX) /* laser hits enemy */
						{
							cArray[i][j] = 'X'; 
							*end = 1; /* player wins */
						}
						else if(i == playerY && j == playerX) /* laser hits player */
						{
							cArray[i][j] = 'X';
							*end = 2; /* player loses */
						}
						else
						{
							if(i + 1 == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
							{
								tempBulletDir = 'u';
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
							{
								tempBulletDir = 'u';
							}
							
							if(front == 1) /* for condition when player shoots directly in front of mirror */
							{
								cArray[i][j] = '|';
								*laserX = j;
								*laserY = i; 
								colorX = j;	
								colorY = i;
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX) /* when laser hits a mirror */
							{
								*bulletDir = tempBulletDir;
								*reflection = 2;
								loopCount = 0; /* to reset loopCount value when bullet is shooting from right so that the bullet is reflected properly */ 
								tempX = j; /* the mirror X coordinate hit by laser */ 
								tempY = i; /* the mirror Y coordinate hit by laser */
								hit = k; /* the specific mirror hit by laser */
								k = 1000; /* ends the mirrors loop */ 
							}
							else 
							{
								cArray[i][j] = '|';
								*laserX = j;
								*laserY = i; 
								colorX = j;
								colorY = i;	
							}
						}
					}
					else if(*reflection == 1 && i == tempY - loopCount && j == tempX && mirrorsArray[hit].mirrorIcon == '/' && *bulletDir == 'l') /* when mirror is '/' and the bullet is coming from the left side */
					{
						if(i == enemyY && j == enemyX) /* laser hits enemy */
						{
							cArray[i][j] = 'X'; 
							*end = 1; /* player wins */
						}
						else if(i == playerY && j == playerX) /* laser hits player */
						{
							cArray[i][j] = 'X';
							*end = 2; /* player loses */
						}
						else
						{	
							if(i - 1 == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
							{
								tempBulletDir = 'd';
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
							{
								tempBulletDir = 'd';
							}
							
							if(front == 1) /* for condition when player shoots directly in front of mirror */
							{
								cArray[i][j] = '|';
								*laserX = j;
								*laserY = i; 
								colorX = j;	
								colorY = i;
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX) /* when laser hits a mirror */
							{
								*bulletDir = tempBulletDir;
								*reflection = 2;
								loopCount = 0; /* to reset loopCount value when bullet is shooting from left so that the bullet is reflected properly */ 
								tempX = j; /* the mirror X coordinate hit by laser */ 
								tempY = i; /* the mirror Y coordinate hit by laser */
								hit = k; /* the specific mirror hit by laser */
								k = 1000; /* ends the mirrors loop */ 
							}
							else 
							{
								cArray[i][j] = '|';
								*laserX = j;
								*laserY = i; 
								colorX = j;
								colorY = i;	
							}
						}
					}
					else if(*reflection == 1 && i == tempY && j == tempX - loopCount && mirrorsArray[hit].mirrorIcon == '/' && *bulletDir == 'u') /* when mirror is '/' and the bullet is coming from the upper side */
					{
						if(i == enemyY && j == enemyX) /* laser hits enemy */
						{
							cArray[i][j] = 'X'; 
							*end = 1; /* player wins */
						}
						else if(i == playerY && j == playerX) /* laser hits player */
						{
							cArray[i][j] = 'X';
							*end = 2; /* player loses */
						}
						else
						{
							if(j - 1 == mirrorsArray[k].mirrorX && i == mirrorsArray[k].mirrorY)
							{
								tempBulletDir = 'r';
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
							{
								tempBulletDir = 'r';
							}
							
							if(front == 1) /* for condition when player shoots directly in front of mirror */
							{
								cArray[i][j] = '-';
								*laserX = j;
								*laserY = i; 
								colorX = j;	
								colorY = i;
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX) /* when laser hits a mirror */
							{
								*bulletDir = tempBulletDir;
								*reflection = 2;
								loopCount = 0; /* to reset loopCount value when bullet is shooting from upper side so that the bullet is reflected properly */ 
								tempX = j; /* the mirror X coordinate hit by laser */ 
								tempY = i; /* the mirror Y coordinate hit by laser */
								hit = k; /* the specific mirror hit by laser */
								k = 1000; /* ends the mirrors loop */ 
							}
							else 
							{
								cArray[i][j] = '-';
								*laserX = j;
								*laserY = i; 
								colorX = j;
								colorY = i;	
							}
						}
					}
					else if(*reflection == 1 && i == tempY && j == tempX + loopCount && mirrorsArray[hit].mirrorIcon == '/' && *bulletDir == 'd') /* when mirror is '/' and the bullet is coming from the down side */
					{
						if(i == enemyY && j == enemyX) /* laser hits enemy */
						{
							cArray[i][j] = 'X'; 
							*end = 1; /* player wins */
						}
						else if(i == playerY && j == playerX) /* laser hits player */
						{
							cArray[i][j] = 'X';
							*end = 2; /* player loses */
						}
						else
						{
							if(j + 1 == mirrorsArray[k].mirrorX && i == mirrorsArray[k].mirrorY)
							{
								tempBulletDir = 'l';
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
							{
								tempBulletDir = 'l';
							}
							
							if(front == 1) /* for condition when player shoots directly in front of mirror */
							{
								cArray[i][j] = '-';
								*laserX = j;
								*laserY = i; 
								colorX = j;	
								colorY = i;
							}
							else if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX) /* when laser hits a mirror */
							{
								*bulletDir = tempBulletDir;
								*reflection = 2;
								loopCount = 0; /* to reset loopCount value when bullet is shooting from down side so that the bullet is reflected properly */ 
								tempX = j; /* the mirror X coordinate hit by laser */ 
								tempY = i; /* the mirror Y coordinate hit by laser */
								hit = k; /* the specific mirror hit by laser */
								k = 1000; /* ends the mirrors loop */ 
							}
							else 
							{
								cArray[i][j] = '-';
								*laserX = j;
								*laserY = i; 
								colorX = j;
								colorY = i;	
							}
						}
					}
				}
			} 
			
			/* Assigning map border, enemy coordinate, player coordinate, and mirrors coordinate */		
			if(i == 0 || i == row - 1)
			{
				cArray[i][j] = '*'; /* if it is the first and last row, every column will be the map border */
			}	
			else if(j == 0 || j == col - 1)
			{
				cArray[i][j] = '*'; /* every first and last column in the particular row will be the map border */
			}
			else if(i == enemyY && j == enemyX && (*end == 0 || *end == 2))
			{
				cArray[i][j] = enemyIcon; /* if the element is the enemy coordinate, it will be assigned to the enemy character icon */
			}
			else if(i == playerY && j == playerX && (*end == 0 || *end == 1))
			{
				cArray[i][j] = playerIcon; /* if the element is the player coordinate, it will be assigned to the player character icon */
			}
			else /* assigning mirrors */
			{
				for(k = 0; k < mirrorsNum; k++)
				{
					if(i == mirrorsArray[k].mirrorY && j == mirrorsArray[k].mirrorX)
					{
						if(mirrorsArray[k].mirrorIcon == '\\')
						{
							cArray[i][j] = mirrorsArray[k].mirrorIcon; 
						}
						else if(mirrorsArray[k].mirrorIcon == '/')
						{
							cArray[i][j] = mirrorsArray[k].mirrorIcon;
						}
					}
				}
			}	
		}
	}

	/* Printing out the map */
	static int colorChange = 1;
	
	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			if(i == colorY && j == colorX && i == mirrorsArray[hit].mirrorY && j == mirrorsArray[hit].mirrorX) 
			{
				printf("%c", cArray[i][j]); /* if element is mirror, it will be printed by default white color */
			}
			else if(i == colorY && j == colorX && i != 0 && j != 0 && i != row - 1 && j != col - 1) /* for all the laser X coordinate and laser Y coordinate with color change */
			{	
				if(colorChange % 6 == 0) /* first time will be red color */
				{
					printf("\033[0;31m"); 
				}	
				else if(colorChange % 6 == 1) /* second time will be orange color */
				{
					printf("\033[0;33m");
				}
				else if(colorChange % 6 == 2) /* third time will be green color */
				{
					printf("\033[0;32m");
				}
				else if(colorChange % 6 == 3) /* fourth time will be blue color */  
				{
					printf("\033[0;34m");
				}
				else if(colorChange % 6 == 4) /* fifth time will be cyan color */
				{
					printf("\033[0;36m");
				}
				else if(colorChange % 6 == 5) /* sixth time will be purple color */
				{
					printf("\033[0;35m");
				}
				printf("%c", cArray[i][j]);
				printf("\033[0m");
				colorChange++; /* change the color every time to create the rainbow color effect */
			}
			else
			{
				printf("%c", cArray[i][j]); /* if element is not laser, it will be printed by default white color */
			}
			
			if(j == col - 1)
			{
				printf("\n"); /* go to next line after every row */
			}
		}
	}
	
	/* Inserting map into linked list nodes and print the data in the linked list node directly into log.txt */
	if(action == 'd' || action == 'a' || action == 'w' || action == 's' || action == 'f') /* map will not be inserted into linked list node when action == 'l' */
	{
		if(*laserX > 0 && *laserX < col - 1 && *laserY > 0 && *laserY < row - 1) /* when laser is within the map, the map will be inserted into linked list node */
		{
			Result *record = NULL; 
			record = (Result *)malloc(sizeof(Result)); /* create a struct to store all the information for the linked list node */
			record->cArrayCopy = (char **)malloc(row * sizeof(char *)); /* creating a copy of 2D char array in struct */
			
			for(i = 0; i < row; i++)
		    	{
				record->cArrayCopy[i] = (char *)malloc(col * sizeof(char));
			}
			
			for(i = 0; i < row; i++)
			{
				for(j = 0; j < col; j++)
				{
					record->cArrayCopy[i][j] = cArray[i][j]; /* assign and store the values for each elements into the copy of 2D char array in struct */
				}
			}
			
			record->row = row; /* assign and store the row value into the row variable in struct */
			record->col = col; /* assign and store the col value into the col variable in struct */
			insertLast(LL, record);  /* inserting a new linked list node */
			printLinkedList(LL, &printResult, fileName); /* if force quit the game, the data in all the linked list nodes will still be saved into the file properly */
		}
	}
} 
