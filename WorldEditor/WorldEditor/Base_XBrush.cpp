#include "stdafx.h"
#include "Base_XBrush.h"

Base_XBrush::Base_XBrush(void)
{
	Vertice_Count = 0;
	Face_Count = 0;
	SubBrush_Count = 0;
	Brush_Count = 0;

	BrushName[0] = 0;

	int Count = 0;
	while (Count < 111999)
	{
		B_Brush[Count] = nullptr;
		Count++;
	}
}

Base_XBrush::~Base_XBrush(void)
{
}

// *************************************************************************
// *		Create_Mesh_Group:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
bool Base_XBrush::Create_Brush(int Index)
{
	if (B_Brush[Index] != NULL)
	{
		delete B_Brush[Index];
		B_Brush[Index] = NULL;
	}

	B_Brush[Index] = NULL;

	B_Brush[Index] = new Brush_type();

	if (B_Brush[Index] == NULL)
	{
		return 0;
	}

	B_Brush[Index]->Vertice_Count = 0;
	B_Brush[Index]->Face_Count = 0;

	Brush_Count++;

	return 1;
}
