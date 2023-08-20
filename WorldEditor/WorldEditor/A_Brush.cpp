#include "StdAfx.h"
#include "AB_App.h"
#include "A_Brush.h"
#include "ram.h"

struct tag_BrushList
{
	Brush* First;
	Brush* Last;
};

#pragma warning(disable : 4201 4214 4115 4514 4711)

A_Brush::A_Brush(void)
{
}

A_Brush::~A_Brush(void)
{
}


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

// *************************************************************************
// *						Get_Brush_Count								   *
// *************************************************************************
int A_Brush::Get_Brush_Count(void)
{
	App->Get_Current_Document();

	int Count = 0;
	Brush* b;

	Level* pLevel = App->m_pDoc->pLevel;
	BrushList* pList = Level_GetBrushes(App->m_pDoc->pLevel);

	b = pList->First;
	while (b != NULL)
	{
		Count++;
		b = b->Next;
	}

	return Count;
}

// *************************************************************************
// *							Get_By_Name								   *
// *************************************************************************
Brush* A_Brush::Get_By_Name(char* BrushName)
{
	App->Get_Current_Document();

	int Count = 0;
	int Result = 1;
	Brush* b;

	Level* pLevel = App->m_pDoc->pLevel;
	BrushList* pList = Level_GetBrushes(App->m_pDoc->pLevel);

	b = pList->First;
	while (b != NULL)
	{
		Result = strcmp(b->Name, "XYZ");
		if (Result == 0)
		{
			return b;
		}
		Count++;
		b = b->Next;
	}

	return NULL;
}


