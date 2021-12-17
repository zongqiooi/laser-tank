#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include "result.h"

/* There is a total of 6 functions in this linkedList.c file */

/* NAME      : createLinkedList */
/* PURPOSE   : Create a linked list with head and count to store the map array copy for the log file */
/* IMPORTS   : None */
/* EXPORTS   : LL (linked list) */
/* ASSERTIONS: */
/*    PRE    : This function is called from the main.c to create a linked list */
/*    POST   : The linked list is created to store all the map array copy for the log file */
/* REMARKS   : This algorithm is obtained from Practical 6 */

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

/* NAME      : insertLast */
/* PURPOSE   : Create a new linked list node and insert the map array copy into the new linked list node when an action is occurred */
/* IMPORTS   : *list (linked list), *entry (data of the linked list node) */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : This function is called by the map() function in map.c when an action is occurred */
/*    POST   : The new linked list node is created and the data from the map array copy will be stored inside the new linked list node */
/* REMARKS   : This algorithm is obtained from Practical 6 */

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

/* NAME      : printLinkedList */
/* PURPOSE   : Print the map array copy contained in all the linked list nodes into log.txt */
/* IMPORTS   : *list (linked list), funcPtr (function pointer), *fileName (file name to save the log) */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : The printResult() function will be called to print the map array copy into log.txt */
/*    POST   : The values in the map array copy in all the linked list nodes are printed and saved into log.txt */
/* REMARKS   : This algorithm is obtained from Practical 6 */

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

/* NAME      : freeLinkedList */
/* PURPOSE   : Free the memories contained in all the linked list nodes and linked list */
/* IMPORTS   : *list (linked list), funcPtr (function pointer), *fileName (file name to save the log) */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : The freeNode() function will be called to free all the memories */
/*    POST   : The memories contained in all the linked list nodes and linked list are freed */
/* REMARKS   : This algorithm is obtained from Practical 6 */

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

/* NAME      : printResult */
/* PURPOSE   : Print the map array copy contained in all the linked list nodes into log.txt */
/* IMPORTS   : *data (data that points to the map array copy), *outPtr (file pointer for the output file) */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : This function is called by the printLinkedList() function */
/*    POST   : The values in the map array copy in all the linked list nodes are printed and saved into log.txt */
/* REMARKS   : This algorithm is obtained from Practical 6 */

/*----------------------------------------------------------------------------------------------------------------------------------------------------*/

/* NAME      : freeNode */
/* PURPOSE   : Free the memories contained in all the linked list nodes */
/* IMPORTS   : *data (data that points to the map array copy), *outPtr (file pointer for the output file) */
/* EXPORTS   : None */
/* ASSERTIONS: */
/*    PRE    : This function is called by the freeLinkedList() function */
/*    POST   : The memories in all the linked list nodes are freed */
/* REMARKS   : This algorithm is obtained from Practical 6 */

LinkedList *createLinkedList()
{
	LinkedList *LL = NULL; 
	LL = (LinkedList *)malloc(sizeof(LinkedList)); /* create a linked list */
	LL->head = NULL;
	LL->count = 0; 
	
	return LL;
} 

void insertLast(LinkedList *list, void *entry)
{
	LinkedListNode *newNode = NULL;
	newNode = (LinkedListNode *)malloc(sizeof(LinkedListNode)); /* create a new linked list node */
	newNode->data = entry; 
	newNode->next = NULL;  
	
	if(list->head == NULL) /* when there is no linked list node in the linked list */
	{
		list->head = newNode; /* points the head of the linked list to the new linked list node */
	}
	else /* when there is one or more linked list node in the linked list */
	{
		LinkedListNode *curr = NULL; /* create a current pointer for the purpose of pointing to next linked list node */
		curr = list->head; /* points the current pointer to where the head of the linked list points to */
		
		while(curr->next != NULL) 
		{
			curr = curr->next; /* the current pointer will point to the next linked list node until the last linked list node is reached */
		}
	
		curr->next = newNode; /* insert new linked list node into the linked list when last linked list node is reached */
	}

	list->count++;
}

void printLinkedList(LinkedList *list, listFunc funcPtr, char *fileName) 
{
	LinkedListNode *curr = NULL; /* create a current pointer for the purpose of pointing to next linked list node */
	curr = list->head; 
	FILE *outPtr = NULL; /* create a file pointer for the output file */
	outPtr = fopen(fileName, "w"); /* open the output file for writting and the contents in the file will be overwritten every time */
	
	while(curr != NULL) 
	{	
		(*funcPtr)(curr->data, outPtr); /* call the printResult() function to print the contents of every linked list node to log file */
		curr = curr->next; /* the current pointer will point to the next linked list node  */
	}
	
	fclose(outPtr); /* close the file after writting */
}

void freeLinkedList(LinkedList *list, listFunc funcPtr, char *fileName)
{
	LinkedListNode *curr = NULL; /* create a current pointer for the purpose of pointing to next linked list node */
	LinkedListNode *nextCurr = NULL; /* create a next current pointer */
	curr = list->head; 
	FILE *outPtr = NULL; /* pass a dummy outPtr because printLinkedList() also contain FILE pointer as one of the parameters, need to match parameters for function pointer declaration */
	
	while(curr != NULL) 
	{
		nextCurr = curr->next; /* the next current pointer will point to where the next of the current pointer points to */
		(*funcPtr)(curr->data, outPtr); /* call the freeNode() function to free the memories for every linked list node */
		free(curr); /* free the linked list node */
		curr = nextCurr; /* the current pointer will point to where the next current pointer points to */
	}
	
	free(list); /* free the main linked list at the front */
}

void printResult(void *data, FILE *outPtr)
{	
	int i = 0;
	int j = 0; 
	
	for(i = 0; i < ((Result *)data)->row; i++) /* typecast "data" and access the row value pointed by data to loop through every rows */
	{
		for(j = 0; j < ((Result *)data)->col; j++) /* typecast "data" and access the column value pointed by data to loop through every columns */
		{
			fprintf(outPtr, "%c", ((Result *)data)->cArrayCopy[i][j]); /* typecast "data" and access the element of cArrayCopy pointed by data */
			
			if(j == (((Result *)data)->col - 1)) 
			{
				fprintf(outPtr, "\n"); /* go to next line after every row */
			}
		}
	}
	
	fprintf(outPtr, "\n");
	
	for(i = 0; i < ((Result *)data)->col; i++)
	{
		fprintf(outPtr, "-"); /* print the dashes that separate every map in the log file */
	}
	
	fprintf(outPtr, "\n\n");
}

void freeNode(void *data, FILE *outPtr)
{
	int i = 0;
	
	for(i = 0; i < ((Result *)data)->row; i++) /* typecast "data" and access the row value pointed by data to loop through every rows */
	{
		free(((Result *)data)->cArrayCopy[i]); /* typecast "data" and free the memories of every row from the cArrayCopy pointed by data */
	}
	
	free(((Result *)data)->cArrayCopy); /* typecast "data" and free the memories of cArrayCopy pointed by data */
	free((Result *)data); /* typecast "data" and free the memories of "Result" struct pointed by data */
}
