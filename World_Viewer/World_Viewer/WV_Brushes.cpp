#include "stdafx.h"
#include "WV_App.h"
#include "WV_Brushes.h"

WV_Brushes::WV_Brushes()
{
}

WV_Brushes::~WV_Brushes()
{
}

struct tag_BrushList
{
	Brush* First;
	Brush* Last;
};

enum BrushFlags
{
	BRUSH_SOLID = 0x0001,
	BRUSH_WINDOW = 0x0002,
	BRUSH_WAVY = 0x0004,
	BRUSH_DETAIL = 0x0008,	//not included in vis calculations
	BRUSH_HOLLOWCUT = 0x0010,
	BRUSH_TRANSLUCENT = 0x0020,
	BRUSH_EMPTY = 0x0040,
	BRUSH_SUBTRACT = 0x0080,
	BRUSH_CLIP = 0x0100,
	BRUSH_FLOCKING = 0x0200,
	BRUSH_HOLLOW = 0x0400,
	BRUSH_SHEET = 0x0800,
	BRUSH_HIDDEN = 0x1000,
	BRUSH_LOCKED = 0x2000,
	BRUSH_HINT = 0x4000,
	BRUSH_AREA = 0x8000
	// All flags larger than 0x8000 (i.e. 0x00010000 through 0x80000000)
	// are reserved for user contents.
};

// *************************************************************************
// *						BrushList_CreateFromFile					   *
// *************************************************************************
BrushList* WV_Brushes::BrushList_CreateFromFile(Parse3dt* Parser, int VersionMajor, int VersionMinor, const char** Expected)
{
	int NumBrushes;
	BrushList* blist = NULL;;

	if (!Parse3dt_GetInt(Parser, (*Expected = "Brushlist"), &NumBrushes))
	{
		return NULL;
	}

	blist = BrushList_Create();

	if (blist != NULL)
	{
		int i;

		for (i = 0; i < NumBrushes; ++i)
		{
			Brush* pBrush;

			pBrush = Brush_CreateFromFile(Parser, VersionMajor, VersionMinor, Expected);

			if (pBrush == NULL)
			{
				BrushList_Destroy(&blist);
				break;
			}
			else
			{
				BrushList_Append(blist, pBrush);
			}
		}
	}

	return blist;
}

// *************************************************************************
// *						Brush_CreateFromFile						   *
// *************************************************************************
Brush* WV_Brushes::Brush_CreateFromFile(Parse3dt* Parser,int VersionMajor,int VersionMinor,const char** Expected)
{
	FaceList* fl;
	Brush* b;
	int			tmpFlags, tmpModelId, tmpGroupId, tmpType, tmpTranslucency;
	geFloat		tmpHullSize;
	BrushList* blist;
	char		szTemp[_MAX_PATH];

	assert(Parser != NULL);

	b = NULL;

	if ((VersionMajor > 1) || ((VersionMajor == 1) && (VersionMinor >= 24)))
	{
		// version 1.24 and later we quoted the texture names...
		if (!Parse3dt_GetLiteral(Parser, (*Expected = "Brush"), szTemp)) return NULL;
	}
	else
	{
		if (!Parse3dt_GetIdentifier(Parser, (*Expected = "Brush"), szTemp)) return NULL;
	}

	if (!Parse3dt_GetInt(Parser, (*Expected = "Flags"), &tmpFlags)) return NULL;

	if ((VersionMajor == 1) && (VersionMinor <= 10))
	{
		// Clear unused flags from older file versions
		// All brushes are solid by default.
		tmpFlags &= (BRUSH_DETAIL | BRUSH_HOLLOW | BRUSH_SUBTRACT | BRUSH_HOLLOWCUT | BRUSH_HIDDEN | BRUSH_LOCKED);
		tmpFlags |= BRUSH_SOLID;
		tmpFlags &= (~(BRUSH_HINT | BRUSH_CLIP | BRUSH_AREA | BRUSH_TRANSLUCENT | BRUSH_EMPTY));
	}
	if ((VersionMajor == 1) && (VersionMinor < 25))
	{
		// clear flocking flag on old file versions.
		tmpFlags &= ~BRUSH_FLOCKING;
	}
	if ((VersionMajor == 1) && (VersionMinor < 29))
	{
		// clear sheet flag on older file versions
		tmpFlags &= ~BRUSH_SHEET;
	}

	if ((VersionMajor > 1) || ((VersionMajor == 1) && (VersionMinor >= 3)))
	{
		if (!Parse3dt_GetInt(Parser, (*Expected = "ModelId"), &tmpModelId)) return NULL;
		if (!Parse3dt_GetInt(Parser, (*Expected = "GroupId"), &tmpGroupId)) return NULL;
	}
	else
	{
		if (!Parse3dt_GetInt(Parser, (*Expected = "EntityId"), &tmpModelId)) return NULL;
		tmpGroupId = 0;
	}

	if (!Parse3dt_GetFloat(Parser, (*Expected = "HullSize"), &tmpHullSize)) return NULL;
	if (tmpHullSize < 1.0f)
	{
		tmpHullSize = 1.0f;
	}

	if ((VersionMajor == 1) && (VersionMinor <= 16))
	{
		tmpTranslucency = 0;
	}
	else if ((VersionMajor > 1) || ((VersionMajor == 1) && (VersionMinor < 27)))
	{
		if (!Parse3dt_GetInt(Parser, (*Expected = "Translucency"), &tmpTranslucency)) return NULL;
		if (tmpTranslucency > 255) tmpTranslucency = 255;
		if (tmpTranslucency < 0) tmpTranslucency = 0;
	}
	else
	{
		tmpTranslucency = 0;
	}

	tmpType = BRUSH_LEAF;	// default is leaf brush
	if ((VersionMajor > 1) || ((VersionMajor == 1) && (VersionMinor >= 15)))
	{
		if (!Parse3dt_GetInt(Parser, (*Expected = "Type"), &tmpType)) return NULL;
	}

	fl = NULL;
	blist = NULL;
	switch (tmpType)
	{
	case BRUSH_LEAF:
	{
		fl = App->CL_Faces->FaceList_CreateFromFile(Parser, VersionMajor, VersionMinor, Expected);
		if (fl == NULL)
		{
			goto DoneLoad;
		}
		break;
	}
	case BRUSH_MULTI:
		blist = BrushList_CreateFromFile(Parser, VersionMajor, VersionMinor, Expected);
		if (blist == NULL)
		{
			goto DoneLoad;
		}
		break;
	default:
		assert(0);		//bad stuff here
		return NULL;
	}

	//drop trans into faces from old maps
	if ((VersionMajor > 1) || ((VersionMajor == 1) && (VersionMinor < 27)))
	{
		if (fl)
		{
			App->CL_Faces->FaceList_SetTranslucency(fl, (float)tmpTranslucency);
		}
	}

	if (tmpFlags & BRUSH_TRANSLUCENT)
	{
		// set faces as translucent
		if (fl != NULL)
		{
			App->CL_Faces->FaceList_SetTransparent(fl, GE_TRUE);
		}
		tmpFlags &= ~BRUSH_TRANSLUCENT;
	}

	b = Brush_Create(tmpType, fl, blist);
	if (b == NULL)
	{
		if (fl != NULL)
		{
			App->CL_Faces->FaceList_Destroy(&fl);
		}
		if (blist != NULL)
		{
			BrushList_Destroy(&blist);
		}
	}
	else
	{
		b->Flags = tmpFlags;
		b->HullSize = tmpHullSize;
		b->ModelId = tmpModelId;
		b->GroupId = tmpGroupId;
		Brush_SetName(b, szTemp);
	}

DoneLoad:
	return	b;
}

// *************************************************************************
// *			Get_Brush_Count:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
int WV_Brushes::Get_Brush_Count()
{
	BrushList* pList = App->CL_pDoc->pLevel->Brushes;

	int Count = 0;
	Brush* b;
	b = pList->First;

	while (b != NULL)
	{
		Count++;
		b = b->Next;
	}

	return Count;
}

// *************************************************************************
// *			Get_Brush_ByIndex:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
Brush* WV_Brushes::Get_Brush_ByIndex(int Index)
{

	BrushList* pList = App->CL_pDoc->pLevel->Brushes;

	int Count = 0;
	Brush* b;
	b = pList->First;
	while (b != NULL)
	{
		if (Count == Index)
		{
			return b;
		}

		Count++;
		b = b->Next;
	}

	return NULL;
}
