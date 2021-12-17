#include <stdio.h>
#include "instruction.h" 

/* NAME      : instruction */
/* PURPOSE   : Print out the instructions of the game below the map and read a single character user input for the player's next action */
/* IMPORTS   : *action (player action) */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : This function will be called every time when the map is printed on the screen */
/*    POST   : The instructions of the game will be printed below the map and ask for the user input for the player's next action */
/* REMARKS   : None */

void instruction(char *action)
{
	printf("w to go/face up\n");
	printf("s to go/face down\n");
	printf("a to go/face left\n");
	printf("d to go/face right\n");
	printf("f to shoot laser\n");
	printf("l to save the Log\n");
	printf("action: ");
	scanf(" %c", action); /* read a single character for the input only */
}
