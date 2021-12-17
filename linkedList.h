#ifndef LL_H
#define LL_H

#include <stdio.h> /* for the compiler to understand the FILE pointer data type when declaring the function pointer */

typedef struct LinkedListNode{
	void *data; /* generic linked list */
	struct LinkedListNode *next;
} LinkedListNode; /* struct for every linked list nodes */

typedef struct{
	LinkedListNode *head; 
	int count;
} LinkedList; /* struct for the start of linked list */

typedef void (*listFunc)(void *data, FILE *outPtr); /* for the function pointer */

LinkedList *createLinkedList(); /* functions prototypes for the functions in linkedList.c */
void insertLast(LinkedList *list, void *entry);
void printLinkedList(LinkedList *list, listFunc funcPtr, char *fileName);
void freeLinkedList(LinkedList *list, listFunc funcPtr, char *fileName);
void printResult(void *data, FILE *outPtr);
void freeNode(void *data, FILE *outPtr);

#endif
