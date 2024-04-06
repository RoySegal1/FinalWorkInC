/********************************************/
/*   list.h                                 */
/*   a dynamic  linked list with a header   */
/********************************************/


#ifndef _LIST_
#define _LIST_


/*** Definitions ***/
typedef void* DATA;

typedef enum { False, True } BOOL1;	// a boolean type


// Node
typedef struct node
{
	DATA			key;
	struct node*	next;
}NODE;


// List
typedef struct 
{
	NODE head;
}LIST;


/*** Function prototypes ***/
// create new list
BOOL1 L_init(LIST* pList);

// add new node after *pNode
NODE* L_insert(NODE* pNode, DATA Value);	

// erase node after *pNode
BOOL1 L_delete(NODE* pNode, void freeFunc(void*));

// return a pointer to the node 
const NODE* L_find(const NODE* pNode, DATA Value,int compare(const void*, const void*));

// free list memory
BOOL1 L_free(LIST* pList, void freeFunc(void*));

// print the list content
int L_print(const LIST* pList,void (*print)(const void* ));
#endif
