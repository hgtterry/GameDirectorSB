#include "stdafx.h"
#include "WV_App.h"
#include "CFaceList.h"

#include "ram.h"

CFaceList::CFaceList()
{
}

CFaceList::~CFaceList()
{
}

// *************************************************************************
// *							FaceList_Create							   *
// *************************************************************************
FaceList* CFaceList::FaceList_Create(int NumFaces)
{
	FaceList* pList;

	assert(NumFaces > 0);

	// allocate the structure
	pList = (FaceList*)geRam_Allocate(sizeof(FaceList));
	if (pList != NULL)
	{
		pList->NumFaces = 0;
		pList->Limit = NumFaces;
		// allocate space for NumFaces pointers
		pList->Faces = (struct FaceTag**)geRam_Allocate(NumFaces * sizeof(Face*));
		if (pList->Faces != NULL)
		{
			int i;
			// set the pointers to NULL
			for (i = 0; i < pList->Limit; i++)
			{
				pList->Faces[i] = NULL;
			}
		}
		pList->Dirty = GE_TRUE;
	}

	return pList;
}

// *************************************************************************
// *							FaceList_Destroy						   *
// *************************************************************************
void CFaceList::FaceList_Destroy(FaceList** ppList)
{
	int i;
	FaceList* pList;

	assert(ppList != NULL);
	assert(*ppList != NULL);

	pList = *ppList;
	for (i = 0; i < pList->NumFaces; i++)
	{
		Face_Destroy(&pList->Faces[i]);
	}
	geRam_Free(pList->Faces);
	geRam_Free(*ppList);
	*ppList = NULL;
}

// *************************************************************************
// *							FaceList_GetBounds						   *
// *************************************************************************
void CFaceList::FaceList_GetBounds(const FaceList* pList, Box3d* pBounds)
{
	int i;

	assert(pList != NULL);
	assert(pBounds != NULL);
	assert(pList->NumFaces > 0);

	if (pList->Dirty)
	{
		Box3d	Bounds;

		Face_GetBounds(pList->Faces[0], &Bounds);
		for (i = 1; i < pList->NumFaces; i++)
		{
			Box3d FaceBounds;

			Face_GetBounds(pList->Faces[i], &FaceBounds);
			App->CL_CBox3d->Box3d_Union(&Bounds, &FaceBounds, &Bounds);
		}
		// The casts are necessary because pList is const
		// The idea here is that Bounds and Dirty are implementation
		// details rather than interface data.  So it's OK to change
		// them here.  Like C++'s mutable keyword.
		((FaceList*)pList)->Bounds = Bounds;
		((FaceList*)pList)->Dirty = GE_FALSE;
	}
	*pBounds = pList->Bounds;
}
