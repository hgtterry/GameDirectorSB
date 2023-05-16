#include "stdafx.h"
#include "AB_App.h"
#include "A_Brush.h"
#include "ram.h"

#pragma warning(disable : 4201 4214 4115 4514 4711)

A_Brush::A_Brush(void)
{
}

A_Brush::~A_Brush(void)
{
}

struct tag_BrushList
{
	Brush *First;
	Brush *Last;
};

// *************************************************************************
// *							Brush_GetName							   *
// *************************************************************************
const char* A_Brush::Brush_GetName(const Brush *b)
{
	if(b == 0)
	{
		App->Say("Null Brush");
		assert(b != NULL);
	}

	return	b->Name;
}

// *************************************************************************
// *						Brush_GetBrushList							   *
// *************************************************************************
const BrushList* A_Brush::Brush_GetBrushList(const Brush *b)
{
	if(b == 0)
	{
		App->Say("Null Brush");
		assert(b != NULL);
	}

	return	b->BList;
}

// *************************************************************************
// *						BrushList_Create							   *
// *************************************************************************
BrushList* A_Brush::BrushList_Create(void)
{
	BrushList *pList;

	pList = (BrushList *)geRam_Allocate (sizeof (BrushList));
	if (pList != NULL)
	{
		pList->First = NULL;
		pList->Last = NULL;
	}
	return pList;
}


