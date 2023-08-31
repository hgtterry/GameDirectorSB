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

#include "FaceList.h"
typedef Gint16 geBody_Index;
// *************************************************************************
// *	  Brush_Create_From_Equity:- Terry and Hazel Flanigan 2023        *
// *************************************************************************
bool A_Brush::Brush_Create_From_Equity()
{
	App->Get_Current_Document();

	geFloat Scale;
	
	Scale = 1.0f;

	FaceList* fl;
	Face* f;

	fl = FaceList_Create(App->CLSB_Model->FaceCount);

	int Count = 0;
	int GroupCount = App->CLSB_Model->Get_Groupt_Count();

	while (Count < GroupCount)
	{
		int FaceCount = 0;
		int A = 0;
		int B = 0;
		int C = 0;

		while (FaceCount < App->CLSB_Model->Group[Count]->GroupFaceCount)
		{
			geVec3d FaceVerts[3];

			C = App->CLSB_Model->Group[Count]->Face_Data[FaceCount].a;
			B = App->CLSB_Model->Group[Count]->Face_Data[FaceCount].b;
			A = App->CLSB_Model->Group[Count]->Face_Data[FaceCount].c;

			FaceVerts[0].X = App->CLSB_Model->Group[Count]->vertex_Data[A].x;
			FaceVerts[0].Y = App->CLSB_Model->Group[Count]->vertex_Data[A].y;
			FaceVerts[0].Z = App->CLSB_Model->Group[Count]->vertex_Data[A].z;
			
			FaceVerts[1].X = App->CLSB_Model->Group[Count]->vertex_Data[B].x;
			FaceVerts[1].Y = App->CLSB_Model->Group[Count]->vertex_Data[B].y;
			FaceVerts[1].Z = App->CLSB_Model->Group[Count]->vertex_Data[B].z;

			FaceVerts[2].X = App->CLSB_Model->Group[Count]->vertex_Data[C].x;
			FaceVerts[2].Y = App->CLSB_Model->Group[Count]->vertex_Data[C].y;
			FaceVerts[2].Z = App->CLSB_Model->Group[Count]->vertex_Data[C].z;

			f = Face_Create(3, FaceVerts, 0);
			if (f)
			{
				Face_SetTextureScale(f, 0.200, 0.200);
				FaceList_AddFace(fl, f);
			}

			FaceCount++;
			
		}

		Count++;
	}

	Brush* pBrush;

	pBrush = Brush_Create(BRUSH_LEAF, fl, NULL);
	if (!pBrush)
	{
		FaceList_Destroy(&fl);
		return NULL;
	}

	// move the brush to the right position

	geVec3d	mOrigin;

	mOrigin.X = 0;
	mOrigin.Y = 0;
	mOrigin.Z = 0;

	Brush_Move(pBrush, &mOrigin);

	Level_AppendBrush(App->m_pDoc->pLevel, pBrush);
	Brush_SetVisible(pBrush, GE_TRUE);
	SelBrushList_Add(App->m_pDoc->pSelBrushes, pBrush);

	App->m_pDoc->SetDefaultBrushTexInfo(pBrush);
	Brush_Bound(pBrush);
	Brush_Center(pBrush, &mOrigin);

	Brush_SetName(pBrush, "Test");

	App->m_pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);
	App->m_pDoc->SetModifiedFlag();

	App->Say("Added New");

	return 1;
}

