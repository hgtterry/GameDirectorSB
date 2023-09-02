#include "stdafx.h"
#include "Base_Brush.h"

Base_Brush::Base_Brush()
{
	Vertice_Count = 0;
	Face_Count = 0;
	Brush_Count = 0;
	SubBrush_Count = 0;

	BrushName[0] = 0;
}

Base_Brush::~Base_Brush()
{
}
