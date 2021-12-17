#include "boundary.h" 

/* NAME      : boundary */
/* PURPOSE   : Ensure the player moves within the boundary of the map */
/* IMPORTS   : row (map row size), col (map column size), *playerX (player X coordinate), *playerY (player Y coordinate) */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : This function will be called for checking whenever the player coordinate is changed or updated */
/*    POST   : If the player coordinate is outside of the map boundary, the player coordinate will be updated immediately to ensure that it does not move outside of the map boundary */
/* REMARKS   : None */

void boundary(int row, int col, int *playerX, int *playerY)
{
	if(*playerX <= 0)
	{
		*playerX = 1; /* change the player X coordinate immediately to the most left position */
	}
	else if(*playerX >= col - 1)
	{
		*playerX = col - 2; /* change the player X coordinate immediately to the most right position */
	}
	else if(*playerY <= 0)
	{
		*playerY = 1; /* change the player Y coordinate immediately to the most top position */
	}
	else if(*playerY >= row - 1)
	{
		*playerY = row - 2; /* change the player Y coordinate immediately to the most bottom position */
	}
}
