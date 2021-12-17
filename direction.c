#include "direction.h"

/* NAME      : direction */
/* PURPOSE   : Assign the player, enemy, and all the mirrors icon based on the direction that they are facing */
/* IMPORTS   : *icon (player, enemy or mirror icon), dir (player, enemy, or mirror facing direction) */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : The player, enemy, and all the mirrors are facing a direction but they do not have a proper icon */
/*    POST   : The player, enemy, and all the mirrors will be assigned with an icon based on the direction that they are facing */
/* REMARKS   : None */

void direction(char *icon, char dir)
{
	if(dir == 'r')
	{
		*icon = '>'; /* icon for player or enemy character */ 
	}
	else if(dir == 'l')
	{
		*icon = '<'; /* icon for player or enemy character */ 
	}
	else if(dir == 'u')
	{
		*icon = '^'; /* icon for player or enemy character */ 
	}
	else if(dir == 'd')
	{
		*icon = 'v'; /* icon for player or enemy character */
	}
	else if(dir == 'f')
	{
		*icon = '/'; /* icon for mirrors */
	}
	else if(dir == 'b')
	{
		*icon = '\\'; /* icon for mirrors */
	}
}
