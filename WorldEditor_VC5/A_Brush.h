#pragma once

#include "brush.h"
#include "basetype.h"
#include "box3d.h"


class A_Brush
{
public:
	A_Brush(void);
	~A_Brush(void);

	const char* Brush_GetName(const Brush *b);
	const BrushList* Brush_GetBrushList(const Brush *b);
	
	BrushList* BrushList_Create(void);
};



