#include "stdafx.h"
#include "WV_App.h"
#include "CList.h"

typedef struct tag_ListIterator ListNode;
struct tag_ListIterator
{
	ListNode* Next;		// next node in list
	ListNode* Prev;		// previous node in list
	void* Data;			// data being held by the node
};

struct tag_List
{
	ListNode* Head;		// pointer to first node in list
	ListNode* Tail;		// pointer to last node in list (makes appending much faster)
	int nItems;			// number of items in the list
};

CList::CList()
{
}

CList::~CList()
{
}

// *************************************************************************
// * 						Level_Create								   *
// *************************************************************************
List* CList::List_Create(void)
{
	List* pList;

	pList = (List*)malloc(sizeof(List));
	if (pList != NULL)
	{
		pList->nItems = 0;
		pList->Head = NULL;
		pList->Tail = NULL;
	}
	return pList;
}
