#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "check.h"
#include "laser.h"
#include "enemy.h"
#include "mirror.h"
#include "overlap.h"
#include "refresh.h"
#include "boundary.h"
#include "direction.h"
#include "linkedList.h"
#include "instruction.h"

/* NAME      : main */
/* PURPOSE   : Check for all the initial conditions to run the game and then initialize all the variables. Also, contain the while loop that will run the game continuosly */
/* IMPORTS   : None */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : The program will run the main function first */
/*    POST   : The main function will run the game continuosly until there is a win or lose condition occurred */
/* REMARKS   : boolean = 0 (game will stop); boolean = 1 (game will run) */
/*             end = 1 (player wins); end = 2 (player loses) */
/*             reflection = 0 (no reflection occurs); reflection = 1 (single reflection occurred); reflection = 2 (double or multiple reflections occurred) */

int main(int argc, char *argv[])
{		
	int i = 0;               /* loop variable */
	int ch = 0;              /* for tracking the file pointer until EOF */
	int row = 0;             /* map row size */
	int col = 0;             /* map column size */
	int end = 0;             /* for determining win or lose condition */
	int lines = 0;           /* number of lines in input file */
	int laserX = 1;          /* laser X coordinate */
	int laserY = 1;          /* laser Y coordinate */
	int enemyX = 0;          /* enemy X coordinate */
	int enemyY = 0;          /* enemy Y coordinate */
	int playerX = 0;         /* player X coordinate */
	int playerY = 0;         /* player Y coordinate */
	int boolean = 1;         /* for stopping or running the game */
	int loopCount = 0;       /* for laser animation */
	int laserState = 0;      /* for laser animation */ 
	int reflection = 0;      /* for determining reflection cases */
	int mirrorsNum = 0;      /* number of mirrors in input file */
	int maxMirrors = 0;      /* maximum number of mirrors allowed in map */
	int mirrorsError = 0;    /* for mirrors error checking */
	char action = 'd';       /* user input for player action */
	char enemyDir = '0';     /* enemy facing direction */
	char playerDir = '0';    /* player facing direction */
	char bulletDir = '0';    /* bullet moving direction */
	char enemyIcon = '0';    /* enemy character icon on terminal */
	char playerIcon = '0';   /* player character icon on terminal */
	char **cArray = NULL;    /* 2D character array to store map */
	
	FILE *inPtr = NULL;             /* file pointer for the input text file */
	LinkedList *LL = NULL;          /* linked list */
	Mirrors *mirrorsArray = NULL;   /* array of struct for mirrors */
	
	if(argc != 3) /* program will not run because there is not enough 3 command line arguments */
	{
		printf("Please enter exactly 3 command line arguments only!\n");
		boolean = 0; 
	}
	else /* program will run because there are 3 command line arguments */
	{
		inPtr = fopen(argv[1], "r");
		
		if(inPtr == NULL) /* program will not run because file cannot be opened successfully */
		{
			perror("Error in opening the file"); /* output error message when the file does not exist */
			boolean = 0;
		}
		else /* program will run because file can be opened successfully */ 
		{	
		 	boolean = check(&row, &col, &playerX, &playerY, &enemyX, &enemyY, &playerDir, &enemyDir);  /* error checking for all the game configurations */
		 	
			if(boolean == 1)
			{
				rewind(inPtr); /* relocate the file pointer to the first position */
			 	ch = getc(inPtr);
			 	
				while(ch != EOF) /* keep reading until end of the file */
				{
					if(ch == '\n')
					{
						lines += 1; 
					}
					
					ch = getc(inPtr); 
					mirrorsNum = lines - 3; 
				}
				
				if(mirrorsNum != 0) /* cases when there is one or more mirrors in input text file */
				{	
					mirrorsArray = (Mirrors *)malloc((mirrorsNum) * sizeof(Mirrors)); /* creating array of struct for mirrors */
					rewind(inPtr); /* relocate the file pointer to the first position */
					
					for(i = 0; i < lines; i++)
					{
						if(i == 0)
						{
							fscanf(inPtr, "%d %d\n", &row, &col);
						}
						else if(i == 1)
						{
							fscanf(inPtr, "%d %d %c\n", &playerY, &playerX, &playerDir);
						}
						else if(i == 2)
						{
							fscanf(inPtr, "%d %d %c\n", &enemyY, &enemyX, &enemyDir);
						}
						else
						{
							fscanf(inPtr, "%d %d %c\n", &mirrorsArray[i-3].mirrorY, &mirrorsArray[i-3].mirrorX, &mirrorsArray[i-3].mirrorDir);
						}
					}
					
					/* All errors checking for mirrors, such as maximum number, coordinates, and facing direction */
					maxMirrors = (row - 2) * (col - 2) - 2; 
					
					if(mirrorsNum > maxMirrors) /* checking for whether the number of mirrors in input text file is more than the maximum number of mirrors allowed */
					{
						printf("The number of mirrors are too much!\n");		
						mirrorsError = 1; 
						boolean = 0;
					}
					
					for(i = 0; i < mirrorsNum; i++)
					{
						if(mirrorsArray[i].mirrorX < 1 || mirrorsArray[i].mirrorX > col - 2 || mirrorsArray[i].mirrorY < 1 || mirrorsArray[i].mirrorY > row - 2) /* checking for mirrors coordinate */
						{
							mirrorsError = 2; 
						}
						
						if(mirrorsArray[i].mirrorDir != 'f' && mirrorsArray[i].mirrorDir != 'b') /* checking for mirrors facing direction */
						{
							mirrorsError = 3; 
						}
					}
					
					if(mirrorsError == 2)
					{
						printf("Please enter a valid position within the map for the mirrors!\n"); 
						boolean = 0; 
					}
					else if(mirrorsError == 3)
					{
						printf("Please enter a valid direction of 'f' or 'b' only for the mirrors!\n"); 
						boolean = 0; 
					}
					
				}
				else /* cases when there is no mirror in input text file */
				{
					mirrorsNum = 1; 
					mirrorsArray = (Mirrors *)malloc(mirrorsNum * sizeof(Mirrors)); /* creating a fake array of struct for mirrors */
					mirrorsArray[0].mirrorY = 1000; /* place the fake mirror outside of the map */
					mirrorsArray[0].mirrorX = 1000; 
					mirrorsArray[0].mirrorDir = 'f';
				}
				
				LL = createLinkedList(); /* creating a linked list by calling the function */
				cArray = (char **)malloc(row * sizeof(char *)); /* creating 2D character array */
				
			    	for(i = 0; i < row; i++)
			    	{
					cArray[i] = (char *)malloc(col * sizeof(char));
				}
				
				for(i = 0; i < mirrorsNum; i++) 
				{
					direction(&mirrorsArray[i].mirrorIcon, mirrorsArray[i].mirrorDir); /* assign mirrors icon */
				}
				
				direction(&playerIcon, playerDir); /* assign player character icon */
				direction(&enemyIcon, enemyDir); /* assign enemy character icon */
			}
		}
	}
	
	while(boolean)
	{
		refresh(); /* clear the screen */
		map(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, loopCount, &end, &reflection, &bulletDir, &laserX, &laserY, LL, action, argv[2]); /* draw and print out the map */
		instruction(&action); /* print all the instructions */
		
		if(action == 'd')
		{	
			if(playerIcon == '>')	 
			{
				playerX += 1; /* if player is facing to the right, the player will move to the right */
			}
			else 
			{
				direction(&playerIcon, 'r'); /* if player is not facing to the right, change the player character icon facing to the right */ 
			}
		}
		else if(action == 'a')
		{
			if(playerIcon == '<')	 
			{
				playerX -= 1; /* if player is facing to the left, the player will move to the left */
			}
			else 
			{
				direction(&playerIcon, 'l'); /* if player is not facing to the left, change the player character icon facing to the left */ 
			}
		}
		else if(action == 'w')
		{
			if(playerIcon == '^')	 
			{
				playerY -= 1; /* if player is facing upwards, the player will move upwards */
			}
			else 
			{
				direction(&playerIcon, 'u'); /* if player is not facing upwards, change the player character icon facing upwards */  
			}
		}
		else if(action == 's')
		{
			if(playerIcon == 'v')	 
			{
				playerY += 1; /* if player is facing downwards, the player will move downwards */
			}
			else 
			{
				direction(&playerIcon, 'd'); /* if player is not facing downwards, change the player character icon facing downwards */ 
			}
		}
		else if(action == 'f')
		{
			loopCount = 1;
			laser(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, loopCount, &end, &reflection, &bulletDir, &laserX, &laserY, LL, action, argv[2]); /* shoots laser */ 
			
			if(end == 1) /* player wins */
			{
				printf("You win!\n");
				printLinkedList(LL, &printResult, argv[2]); /* printing the map array copy in all linked list nodes to log file */
				boolean = 0; /* escape the game loop and end the program */	
			}
		}
		else if(action == 'l')
		{
			printLinkedList(LL, &printResult, argv[2]); /* printing the map array copy in all linked list nodes to log file */
		}
		
		boundary(row, col, &playerX, &playerY); /* ensure the player moves within the map boundary */
		overlap(row, col, &playerX, &playerY, enemyX, enemyY, mirrorsArray, playerIcon, mirrorsNum); /* ensure player does not overlap with tank and mirrors */
		loopCount = 1;
		enemy(cArray, mirrorsArray, mirrorsNum, row, col, playerX, playerY, enemyX, enemyY, playerIcon, enemyIcon, laserState, loopCount, &end, &reflection, &bulletDir, &laserX, &laserY, LL, action, argv[2]); /* check for enemy to shoot */
		
		if(end == 2) /* player loses */
		{
			printf("You lose!\n");
			printLinkedList(LL, &printResult, argv[2]); /* printing the map array copy in all linked list nodes to log file */
			boolean = 0; /* escape the game loop and end the program */
		}
	}
	
	if(boolean == 0 && inPtr != NULL) /* closing the opened input text file */
	{
		fclose(inPtr);
	}
	
	if(end == 1 || end == 2 || mirrorsError == 1 || mirrorsError == 2 || mirrorsError == 3) /* freeing all the memories */
	{
		for(i = 0; i < row; i++)
		{
			free(cArray[i]); /* free the memories of every rows in the cArray */
		}
		
		free(cArray); /* free the memories of cArray */
		free(mirrorsArray); /* free the memories of array of struct for the mirrors */
		freeLinkedList(LL, &freeNode, argv[2]); /* free all the linked list and linked list nodes */
	}
	
	return 0; 
}
