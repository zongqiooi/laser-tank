#include <stdio.h>
#include <stdlib.h>
#include "check.h"

/* NAME      : check */
/* PURPOSE   : Read in data from the input text file and check for all the game configurations to determine whether to stop or run the game */
/* IMPORTS   : *row (map row size), *col (map column size), *playerX (player X coordinate), *playerY (player Y coordinate), *enemyX (enemy X coordinate), *enemyY (enemy Y coordinate), */
/*             *playerDir (player facing direction), *enemyDir (enemy facing direction) */
/* EXPORTS   : boolean (determine game will stop or run) */
/* ASSERTIONS: */
/*    PRE    : The data for the game configurations will be read in from the input text file called "map.txt" */
/*    POST   : The data for the game configurations will be checked to determine whether to stop or run the game */
/* REMARKS   : boolean = 0 (game will stop); boolean = 1 (game will run) */

int check(int *row, int *col, int *playerX, int *playerY, int *enemyX, int *enemyY, char *playerDir, char *enemyDir)
{
	int i = 0;
	int boolean = 1; /* if there is no errors, boolean will remain 1 and game will run */
	FILE *inPtr2 = NULL;
	
	inPtr2 = fopen("map.txt", "r"); /* open the input file for reading */
	
	if(inPtr2 == NULL)
	{
		perror("Error in opening the file"); /* output error message when the file does not exist or cannot be opened */ 
		boolean = 0; /* if file does not exist, the program will not run */
	}
	else 
	{
		/* Read the first 3 lines in the input text file and assign it to the respective variables for the game configurations */
		for(i = 0; i < 3; i++) 
	 	{
	 		if(i == 0)
			{
				fscanf(inPtr2, "%d %d\n", row, col);
			}
			else if(i == 1)
			{
				fscanf(inPtr2, "%d %d %c\n", playerY, playerX, playerDir);
			}
			else if(i == 2)
			{
				fscanf(inPtr2, "%d %d %c\n", enemyY, enemyX, enemyDir);
			}
	 	}
	}
	 
	/* Check for all the values for game configurations that are read in from the input text file */	
	if(*row < 5 || *row > 25 || *col < 5 || *col > 25)
	{
		printf("Please enter a valid row or column number of 5 to 25 only!\n"); 
		boolean = 0; 
	}
	
	if(*playerX < 1 || *playerX > *col - 2 || *playerY < 1 || *playerY > *row -2)
	{
		printf("Please enter a valid position within the map for the player!\n"); 
		boolean = 0; 
	}
	
	if(*enemyX < 1 || *enemyX > *col - 2 || *enemyY < 1 || *enemyY > *row -2)
	{
		printf("Please enter a valid position within the map for the enemy!\n"); 
		boolean = 0; 
	}
	
	if(*playerDir != 'u' && *playerDir != 'd' && *playerDir != 'l' && *playerDir != 'r')
	{
		printf("Please enter a valid direction of 'u', 'd', 'l', or 'r' only for the player!\n"); 
		boolean = 0; 
	}
	
	if(*enemyDir != 'u' && *enemyDir != 'd' && *enemyDir != 'l' && *enemyDir != 'r')
	{
		printf("Please enter a valid direction of 'u', 'd', 'l', or 'r' only for the enemy!\n"); 
		boolean = 0; 
	}
	
	fclose(inPtr2); /* close the file after reading */
	
	return boolean; 
} 
