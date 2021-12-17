#include "overlap.h" 

/* NAME      : overlap */
/* PURPOSE   : Ensure the player does not overlap with the tank and mirrors */
/* IMPORTS   : row (map row size), col (map column size), *playerX (player X coordinate), *playerY (player Y coordinate), enemyX (enemy X coordinate), enemyY (enemy Y coordinate), */
/*             *mirrorsArray (array of structure for mirrors), playerIcon (player character icon), mirrorsNum (number of mirrors) */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : This function will be called for checking whenever the player coordinate is changed or updated */
/*    POST   : If the player coordinate is overlapped with the enemy or mirror coordinate, the player coordinate will be reversed back and will not overlap with the tank or mirror */
/* REMARKS   : None */

void overlap(int row, int col, int *playerX, int *playerY, int enemyX, int enemyY, Mirrors *mirrorsArray, char playerIcon, int mirrorsNum)
{	
	int i = 0;
	
	for(i = 0; i < mirrorsNum; i++) /* to check the player coordinate with the tank coordinate and all the mirrors coordinate on the map */
	{
		if((*playerX == enemyX && *playerY == enemyY) || (*playerX == mirrorsArray[i].mirrorX && *playerY == mirrorsArray[i].mirrorY)) /* reverse back the position if the position for the player and tank or player and mirror are overlapped */
		{
			if(playerIcon == '>')	 
			{
				*playerX -= 1;
			}
			else if(playerIcon == '<')	 
			{
				*playerX += 1;
			}
			else if(playerIcon == '^')	 
			{
				*playerY += 1;
			}
			else if(playerIcon == 'v')	 
			{
				*playerY -= 1; 
			}
		}
	}
}
