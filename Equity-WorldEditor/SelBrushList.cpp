/****************************************************************************************/
/*  SelBrushList.c                                                                      */
/*                                                                                      */
/*  Author:       Jim Mischel                                                           */
/*  Description:  Selected brush list stuff                                             */
/*                                                                                      */
/*  The contents of this file are subject to the Genesis3D Public License               */
/*  Version 1.01 (the "License"); you may not use this file except in                   */
/*  compliance with the License. You may obtain a copy of the License at                */
/*  http://www.genesis3d.com                                                            */
/*                                                                                      */
/*  Software distributed under the License is distributed on an "AS IS"                 */
/*  basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See                */
/*  the License for the specific language governing rights and limitations              */
/*  under the License.                                                                  */
/*                                                                                      */
/*  The Original Code is Genesis3D, released March 25, 1999.                            */
/*  Copyright (C) 1996-1999 Eclipse Entertainment, L.L.C. All Rights Reserved           */
/*                                                                                      */
/****************************************************************************************/
#pragma warning(disable : 4514 4711)
#include "SelBrushList.h"
#include "array.h"
#include "ram.h"
#include <assert.h>

struct tag_SelBrushList
{
	Array *pItems;
	int FirstFree;
};


SelBrushList *SelBrushList_Create (void)
{
	SelBrushList *pList;
	
	pList = GE_RAM_ALLOCATE_STRUCT (SelBrushList);
	if (pList != NULL)
	{
		pList->pItems = Array_Create (10, sizeof (Brush *));
		if (pList->pItems != NULL)
		{
			pList->FirstFree = 0;
		}
		else
		{
			SelBrushList_Destroy (&pList);
		}
	}
	return pList;
}

void SelBrushList_Destroy (SelBrushList **ppList)
{
	SelBrushList *pList;

	assert (ppList != NULL);
	assert (*ppList != NULL);
	pList = *ppList;

	if (pList->pItems != NULL)
	{
		Array_Destroy (&pList->pItems);
	}
	geRam_Free (*ppList);
}


geBoolean SelBrushList_Find (SelBrushList *pList, const Brush *pBrush)
{
	int i;

	// go through list to see if this Brush is already in the list
	for (i = 0; i < pList->FirstFree; ++i)
	{
		Brush *pRet;

		pRet= SelBrushList_GetBrush (pList, i);
		if (pRet == pBrush)
		{
			// Brush already in list
			return GE_TRUE;
		}
	}
	return GE_FALSE;
}

geBoolean SelBrushList_Add (SelBrushList *pList, Brush *pBrush)
{
	int Size;

	if (SelBrushList_Find (pList, pBrush))
	{
		return GE_FALSE;
	}

	Size = Array_GetSize (pList->pItems);
	assert (pList->FirstFree <= Size);

	// Brush isn't already in list.  Put it at the end...
	if (pList->FirstFree == Size)
	{
		int NewSize;
		// Need to allocate more space
		NewSize = Array_Resize (pList->pItems, 2*Size);
		if (NewSize == Size)
		{
			// couldn't resize.  Guess I can't add the Brush
			return GE_FALSE;
		}
	}
	Array_PutAt (pList->pItems, pList->FirstFree, &pBrush, sizeof (pBrush));
	++(pList->FirstFree);

	return GE_TRUE;
}

geBoolean SelBrushList_Remove (SelBrushList *pList, Brush *pBrush)
{
	int i;

	// find the item in the list
	for (i = 0; i < pList->FirstFree; ++i)
	{
		Brush *pRet;

		pRet = SelBrushList_GetBrush (pList, i);
		if (pRet == pBrush)
		{
			Array_DeleteAt (pList->pItems, i);
			--(pList->FirstFree);
			return GE_TRUE;
		}
	}
	return GE_FALSE;	// not found
}

void SelBrushList_RemoveAll (SelBrushList *pList)
{
	pList->FirstFree = 0;
}

int SelBrushList_GetSize (SelBrushList *pList)
{
	return pList->FirstFree;
}

Brush *SelBrushList_GetBrush (SelBrushList *pList, int BrushIndex)
{
	Brush **ppBrush;

	ppBrush = (Brush **)Array_ItemPtr (pList->pItems, BrushIndex);

	return *ppBrush;
}

void SelBrushList_Enum (SelBrushList *pList, SelBrushList_Callback Callback, void *lParam)
{
	int i;

	for (i = 0; i < pList->FirstFree; ++i)
	{
		Brush *pBrush;

		pBrush = SelBrushList_GetBrush (pList, i);
		Callback (pBrush, lParam);
	}
}

static geBoolean SelBrushList_CenterEnum (Brush *b, void *lParam)
{
	geVec3d *center;
	geVec3d newcenter;

	center = (geVec3d*)lParam;
	Box3d_GetCenter (&b->BoundingBox, &newcenter);
	geVec3d_Add(center, &newcenter, center);

	return GE_TRUE;
}

void	SelBrushList_Center(SelBrushList *pList, geVec3d *center)
{
	int listcount;
	geVec3d average;

	assert(pList && center);

	listcount = SelBrushList_GetSize(pList);
	if (!listcount)
	{
		geVec3d_Clear(center);
		return;
	}
	
	geVec3d_Clear(&average);

	SelBrushList_Enum(pList, SelBrushList_CenterEnum, &average);
	
	geVec3d_Scale(&average, (1 / (float)listcount), center);
}

void	SelBrushList_GetBoundingBox(SelBrushList *pList, Box3d *pBounds)
{
	Box3d	BrushBounds;
	Brush	*pBrush;	
	int i;

	assert(pList != NULL);
	assert(pBounds != NULL);

	if (!pList->FirstFree)
		return;

	pBrush = SelBrushList_GetBrush (pList, 0);
	(*pBounds) = pBrush->BoundingBox;

	for (i = 1; i < pList->FirstFree; ++i)
	{
		pBrush = SelBrushList_GetBrush(pList, i);
		BrushBounds	= pBrush->BoundingBox;
		Box3d_Union(pBounds, &BrushBounds, pBounds);
	}
}
