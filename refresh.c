#include <stdlib.h> 
#include "refresh.h"

/* NAME      : refresh */
/* PURPOSE   : Refresh and clear the map on the terminal screen */
/* IMPORTS   : None */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : The map is printed on the terminal screen */
/*    POST   : The map on the terminal screen will be cleared */
/* REMARKS   : None */

void refresh()
{
	system("clear"); /* clear terminal screen */
}
