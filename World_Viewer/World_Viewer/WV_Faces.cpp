#include "stdafx.h"
#include "WV_App.h"
#include "WV_Faces.h"

#include "ram.h"

WV_Faces::WV_Faces()
{
}

WV_Faces::~WV_Faces()
{
}


// *************************************************************************
// *						FaceList_CreateFromFile						   *
// *************************************************************************
FaceList* WV_Faces::FaceList_CreateFromFile(Parse3dt* Parser,int VersionMajor,int VersionMinor,const char** Expected)
{
	int NumFaces;
	FaceList* pList;

	assert(Parser != NULL);

	if (!Parse3dt_GetInt(Parser, (*Expected = "BrushFaces"), &NumFaces)) return NULL;

	pList = FaceList_Create(NumFaces);
	if (pList != NULL)
	{
		int i;
		for (i = 0; i < NumFaces; i++)
		{
			Face* pFace;

			pFace = Face_CreateFromFile(Parser, VersionMajor, VersionMinor, Expected);
			if (pFace != NULL)
			{
				FaceList_AddFace(pList, pFace);
			}
		}
		if (pList->NumFaces < 4)
		{
			FaceList_Destroy(&pList);
			return NULL;
		}
		pList->Dirty = GE_TRUE;
	}
	return pList;
}

// *************************************************************************
// *							FaceList_Create							   *
// *************************************************************************
FaceList* WV_Faces::FaceList_Create(int NumFaces)
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
// *						FaceList_AddFace							   *
// *************************************************************************
void WV_Faces::FaceList_AddFace(FaceList* pList, Face* pFace)
{
	assert(pList != NULL);
	assert(pFace != NULL);
	assert(pList->NumFaces < pList->Limit);

	// here we could grow the list if we want...

	pList->Faces[pList->NumFaces] = pFace;
	++(pList->NumFaces);
	pList->Dirty = GE_TRUE;
}

// *************************************************************************
// *						FaceList_AddFace							   *
// *************************************************************************
void WV_Faces::FaceList_Destroy(FaceList** ppList)
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
// *					FaceList_SetTranslucency						   *
// *************************************************************************
void WV_Faces::FaceList_SetTranslucency(const FaceList* fl, geFloat trans)
{
	int			i;

	assert(fl != NULL);

	for (i = 0; i < fl->NumFaces; i++)
	{
		Face_SetTranslucency(fl->Faces[i], trans);
	}
}

// *************************************************************************
// *						FaceList_SetTransparent						   *
// *************************************************************************
void WV_Faces::FaceList_SetTransparent(const FaceList* fl, geBoolean trans)
{
	int			i;

	assert(fl != NULL);

	for (i = 0; i < fl->NumFaces; i++)
	{
		Face_SetTransparent(fl->Faces[i], trans);
	}
}
