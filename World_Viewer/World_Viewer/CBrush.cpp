#include "stdafx.h"
#include "WV_App.h"
#include "CBrush.h"

#include "ram.h"

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

struct tag_BrushList
{
	Brush* First;
	Brush* Last;
};

CBrush::CBrush()
{
}

CBrush::~CBrush()
{
}

// *************************************************************************
// * 						Brush_IsDetail								   *
// *************************************************************************
geBoolean CBrush::Brush_IsDetail(const Brush* b)
{
	assert(b != NULL);

	return	(b->Flags & BRUSH_DETAIL) ? GE_TRUE : GE_FALSE;
}

// *************************************************************************
// * 						BrushList_Create							   *
// *************************************************************************
BrushList* CBrush::BrushList_Create(void)
{
	BrushList* pList;

	pList = (BrushList*)geRam_Allocate(sizeof(BrushList));
	if (pList != NULL)
	{
		pList->First = NULL;
		pList->Last = NULL;
	}
	return pList;
}

// *************************************************************************
// * 						Brush_IsDetail								   *
// *************************************************************************
BrushList* CBrush::BrushList_CreateFromFile(Parse3dt* Parser,int VersionMajor,int VersionMinor,const char** Expected)
{
	int NumBrushes;
	BrushList* blist;

	if (!Parse3dt_GetInt(Parser, (*Expected = "Brushlist"), &NumBrushes)) return NULL;
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
// *							BrushList_Destroy						   *
// *************************************************************************
void CBrush::BrushList_Destroy(BrushList** ppList)
{
	BrushList* pList;

	assert(ppList != NULL);
	assert(*ppList != NULL);

	pList = *ppList;
	BrushList_DeleteAll(pList);

	geRam_Free(*ppList);
	*ppList = NULL;
}

// *************************************************************************
// *							BrushList_DeleteAll						   *
// *************************************************************************
void CBrush::BrushList_DeleteAll(BrushList* pList)
{
	Brush* pBrush;
	BrushIterator bi;

	assert(pList != NULL);

	pBrush = BrushList_GetFirst(pList, &bi);
	while (pBrush != NULL)
	{
		BrushList_Remove(pList, pBrush);
		Brush_Destroy(&pBrush);
		pBrush = BrushList_GetNext(&bi);
	}
}

// *************************************************************************
// *							Brush_Destroy							   *
// *************************************************************************
void CBrush::Brush_Destroy(Brush** b)
{
	assert(b != NULL);
	assert(*b != NULL);
	assert((*b)->Prev == NULL);
	assert((*b)->Next == NULL);

	if ((*b)->Type != BRUSH_CSG)
	{
		if ((*b)->BList)
		{
			BrushList_Destroy(&((*b)->BList));
		}
	}
	if ((*b)->Type != BRUSH_MULTI)
	{
		if ((*b)->Faces)
		{
			App->CL_CFaceList->FaceList_Destroy(&((*b)->Faces));
		}
	}

	if ((*b)->Name)
	{
		geRam_Free((*b)->Name);
	}
	geRam_Free(*b);
	*b = NULL;
}

// *************************************************************************
// *							BrushList_Remove						   *
// *************************************************************************
void CBrush::BrushList_Remove(BrushList* pList,Brush* pBrush)
{
	Brush* pPrev;
	Brush* pNext;

	assert(pList != NULL);
	assert(pBrush != NULL);
	assert(pBrush->Prev != pBrush);

	pPrev = pBrush->Prev;
	pNext = pBrush->Next;

	// unlink the brush from the list
	pBrush->Prev = NULL;
	pBrush->Next = NULL;

	// update neighbors' previous/next links
	if (pPrev != NULL)
	{
		pPrev->Next = pNext;
	}
	if (pNext != NULL)
	{
		pNext->Prev = pPrev;
	}

	// if this is the first brush in the list,
	// then update the First pointer
	if (pList->First == pBrush)
	{
		assert(pPrev == NULL);
		pList->First = pNext;
	}
	// if it's the last brush in the list,
	// then update the Last pointer
	if (pList->Last == pBrush)
	{
		assert(pNext == NULL);
		pList->Last = pPrev;
	}
}

// *************************************************************************
// *							BrushList_GetNext						   *
// *************************************************************************
Brush* CBrush::BrushList_GetNext(BrushIterator* bi)
{
	assert(bi != NULL);

	if (*bi == NULL)
	{
		return NULL;
	}
	else
	{
		Brush* b;

		b = *bi;
		*bi = (*bi)->Next;

		return b;
	}
}

// *************************************************************************
// *							BrushList_GetLast						   *
// *************************************************************************
Brush* CBrush::BrushList_GetLast(BrushList* pList,BrushIterator* bi)
{
	assert(pList != NULL);
	assert(bi != NULL);

	if (pList->Last == NULL)
	{
		*bi = NULL;
	}
	else
	{
		*bi = pList->Last->Prev;
	}
	return pList->Last;
}

// *************************************************************************
// *							BrushList_GetFirst						   *
// *************************************************************************
Brush* CBrush::BrushList_GetFirst(BrushList* pList,BrushIterator* bi)
{
	assert(pList != NULL);
	assert(bi != NULL);

	if (pList->First == NULL)
	{
		*bi = NULL;
	}
	else
	{
		*bi = pList->First->Next;
	}
	return pList->First;
}

// *************************************************************************
// *							BrushList_Append						   *
// *************************************************************************
void CBrush::BrushList_Append(BrushList* pList,Brush* pBrush)
{
	assert(pList != NULL);
	assert(pBrush != NULL);

	if (pList->First == NULL)
	{
		// the list is empty
		assert(pList->Last == NULL);
		pList->First = pBrush;
		pList->Last = pBrush;
		pBrush->Next = NULL;
		pBrush->Prev = NULL;
	}
	else
	{
		// add it to the end of the list
		assert(pList->Last != NULL);
		assert(pList->Last->Next == NULL);

		pBrush->Next = NULL;			// it's the end of the list
		pBrush->Prev = pList->Last;		// point back to previous end
		pList->Last->Next = pBrush;		// previous end points to me
		pList->Last = pBrush;			// and we're now the list end
	}
}


// *************************************************************************
// *						Brush_CreateFromFile						   *
// *************************************************************************
Brush* CBrush::Brush_CreateFromFile(Parse3dt* Parser, int VersionMajor, int VersionMinor, const char** Expected)
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
// *						Brush_SetName								   *
// *************************************************************************
void CBrush::Brush_SetName(Brush* b, const char* newname)
{
	assert(b != NULL);
	assert(newname != NULL);

	//empty names ok?  should I check?  Should I assert?
	if (b->Name != NULL)
	{
		geRam_Free(b->Name);
	}

	b->Name = App->CL_CUtil->Util_Strdup(newname);
}

// *************************************************************************
// *						Brush_Create								   *
// *************************************************************************
Brush* CBrush::Brush_Create(int Type, const FaceList* fl, const BrushList* BList)
{
	Brush* pBrush;

	pBrush = (Brush*)geRam_Allocate(sizeof(Brush));
	if (pBrush != NULL)
	{
		pBrush->Prev = NULL;
		pBrush->Next = NULL;
		pBrush->ModelId = 0;
		pBrush->GroupId = 0;
		pBrush->HullSize = 1.0f;
		pBrush->Color = 0;
		pBrush->Name = App->CL_CUtil->Util_Strdup("NoName");
		pBrush->Type = Type;
		switch (Type)
		{
		case	BRUSH_MULTI:
			assert(fl == NULL);
			assert(BList);

			pBrush->Faces = NULL;
			pBrush->BList = (BrushList*)BList;
			pBrush->Flags = BRUSH_SOLID;
			BrushList_GetBounds(BList, &pBrush->BoundingBox);
			break;

		case	BRUSH_LEAF:
		case	BRUSH_CSG:
			assert(fl);
			assert(BList == NULL);	//shouldn't create leaf from multiple

			pBrush->Faces = (FaceList*)fl;
			pBrush->BList = NULL;
			pBrush->Flags = BRUSH_SOLID;
			App->CL_CFaceList->FaceList_GetBounds(fl, &pBrush->BoundingBox);
			break;

		default:
			assert(0);
		}
	}
	return pBrush;
}

// *************************************************************************
// *						BrushList_GetBounds							   *
// *************************************************************************
void CBrush::BrushList_GetBounds(const BrushList* BList, Box3d* pBounds)
{
	Box3d	Bounds;
	Box3d	BrushBounds;
	Brush* b;

	assert(BList != NULL);
	assert(pBounds != NULL);

	b = BList->First;
	Brush_Bound(b);
	Bounds = b->BoundingBox;

	for (; b; b = b->Next)
	{
		Brush_Bound(b);
		BrushBounds = b->BoundingBox;

		App->CL_CBox3d->Box3d_Union(&Bounds, &BrushBounds, &Bounds);
	}
	*pBounds = Bounds;
}

// *************************************************************************
// *							Brush_Bound								   *
// *************************************************************************
void CBrush::Brush_Bound(Brush* b)
{
	assert(b);

	App->CL_CBox3d->Box3d_SetBogusBounds(&b->BoundingBox);
	if (b->Type == BRUSH_MULTI)
	{
		BrushList_GetBounds(b->BList, &b->BoundingBox);
	}
	else
	{
		App->CL_CFaceList->FaceList_GetBounds(b->Faces, &b->BoundingBox);
	}
}

// *************************************************************************
// *						BrushList_MakeHollowsMulti					   *
// *************************************************************************
void CBrush::BrushList_MakeHollowsMulti(BrushList* inList)
{
	Brush* b, * cb, * b2;

	assert(inList != NULL);

	for (b = inList->First; b; b = b->Next)
	{
		if (b->Type == BRUSH_MULTI)	//recurse multibrushes
		{
			assert(b->BList);

			BrushList_MakeHollowsMulti(b->BList);
			continue;
		}
		if (b->Flags & BRUSH_HOLLOW)
		{
			BrushList* bl;

			if (b->Next)	//check for additional brushes, or hollowcuts
			{
				if (b->Next->Flags & BRUSH_HOLLOWCUT)
				{
					continue;	//valid
				}
			}
			//make this a multi
			bl = BrushList_Create();
			b2 = b->Prev;

			BrushList_Remove(inList, b);
			BrushList_Append(bl, b);

			cb = Brush_Create(BRUSH_MULTI, NULL, bl);
			if (b2)
			{
				BrushList_InsertAfter(inList, b2, cb);
			}
			else
			{
				BrushList_Prepend(inList, cb);
			}
			b = cb;
		}
	}
}

// *************************************************************************
// *						BrushList_InsertAfter						   *
// *************************************************************************
void CBrush::BrushList_InsertAfter(BrushList* pList, Brush* pBMarker, Brush* pBrush)
{
	assert(pList != NULL);
	assert(pBMarker != NULL);
	assert(pBrush != NULL);
	assert(pList->First != NULL); //must be at least one
	assert(pList->Last != NULL);
	assert(pList->Last->Next == NULL);

	pBrush->Next = pBMarker->Next;
	pBrush->Prev = pBMarker;

	if (pBrush->Next == NULL)	//last in list?
	{
		pList->Last = pBrush;
	}
	else
	{
		pBrush->Next->Prev = pBrush;
	}
	pBMarker->Next = pBrush;
}

// *************************************************************************
// *							BrushList_Prepend						   *
// *************************************************************************
void CBrush::BrushList_Prepend(BrushList* pList,Brush* pBrush)
{
	assert(pList != NULL);
	assert(pBrush != NULL);

	if (pList->First == NULL)
	{
		// it's the first brush in the list
		assert(pList->Last == NULL);
		pList->First = pBrush;
		pList->Last = pBrush;
		pBrush->Next = NULL;
		pBrush->Prev = NULL;
	}
	else
	{
		// put it at the head of the list
		assert(pList->Last != NULL);
		assert(pList->First->Prev == NULL);

		pBrush->Prev = NULL;			// nothing before me
		pBrush->Next = pList->First;	// point to previous head
		pList->First->Prev = pBrush;	// previous head points to me
		pList->First = pBrush;			// and now we're the head of the list
	}
}

// *************************************************************************
// *			Get_Brush_Count:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
int CBrush::Get_Brush_Count()
{
	BrushList* pList = App->CL_CLevel->Level_GetBrushes(App->CL_CFusionDoc->pLevel);

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
Brush* CBrush::Get_Brush_ByIndex(int Index)
{
	BrushList* pList = App->CL_CLevel->Level_GetBrushes(App->CL_CFusionDoc->pLevel);

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
