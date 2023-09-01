/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include "stdafx.h"
#include "AB_App.h"
#include "SB_Scene.h"

SB_Scene::SB_Scene()
{
	FullScreenMode_Flag = 0;

	Selected_Brush = NULL;
}

SB_Scene::~SB_Scene()
{
}

// *************************************************************************
// *		Go_FullScreen_Mode:- Terry and Hazel Flanigan 2022		  	   *
// *************************************************************************
void SB_Scene::Go_FullScreen_Mode(void)
{
	FullScreenMode_Flag = 1;

	//App->SBC_Scene->CurrentCamMode = App->CL_Ogre->OgreListener->GD_CameraMode;

	//App->FullScreen = 1;
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(App->ViewGLhWnd, HWND_TOP, 0, 0, cx, cy, NULL);

	SetParent(App->ViewGLhWnd, NULL);

	App->CLSB_Ogre->mWindow->resize(cx, cy);

	App->CLSB_Ogre->mWindow->windowMovedOrResized();
	App->CLSB_Ogre->mCamera->setAspectRatio((Ogre::Real)App->CLSB_Ogre->mWindow->getWidth() / (Ogre::Real)App->CLSB_Ogre->mWindow->getHeight());

	Root::getSingletonPtr()->renderOneFrame();
}

typedef struct TexInfoTag
{
	geVec3d VecNormal;
	geFloat xScale, yScale;
	int xShift, yShift;
	geFloat	Rotate;			// texture rotation angle in degrees
	TexInfo_Vectors TVecs;
	int Dib;				// index into the wad
	char Name[16];
	geBoolean DirtyFlag;
	geVec3d Pos;
	int txSize, tySize;		// texture size (not currently used)
	geXForm3d XfmFaceAngle;	// face rotation angle
} TexInfo;

typedef struct FaceTag
{
	int			NumPoints;
	int			Flags;
	Plane		Face_Plane;
	int			LightIntensity;
	geFloat		Reflectivity;
	geFloat		Translucency;
	geFloat		MipMapBias;
	geFloat		LightXScale, LightYScale;
	TexInfo		Tex;
	geVec3d* Points;
} Face;

struct tag_FaceList
{
	int NumFaces;
	int Limit;
	Face** Faces;
	geBoolean Dirty;
	Box3d Bounds;
};

// *************************************************************************
// *	  	   Build_BrushData:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Scene::Build_BrushData()
{
	Brush* pBrush;
	BrushIterator bi;

	BrushList* BList;
	geBoolean fResult;

	App->CLSB_Model->XBrushCount = 0;

	int c = App->CL_World->Get_Brush_Count();
	if (c > 0)
	{
		BList = Level_GetBrushes(App->m_pDoc->pLevel);

		pBrush = BrushList_GetFirst(BList, &bi);

		while (pBrush != NULL)
		{
			App->CLSB_Model->Create_XBrush(App->CLSB_Model->XBrushCount);

			Show_Brush_Info(pBrush);
			pBrush = BrushList_GetNext(&bi);


			App->CLSB_Model->XBrushCount++;
		}
	}

}

// *************************************************************************
// *	  	Show_Brush_Info:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
bool SB_Scene::Show_Brush_Info(const Brush* b)
{
	if (b->Type == BRUSH_MULTI)
	{
		return Show_Brush_ListInfo(b->BList);
	}
	if (b->Type == BRUSH_LEAF)
	{
		return Show_Brush_Faces_Info(b->Faces);
	}

	return 1;
}

// *************************************************************************
// *	  	Show_Brush_ListInfo:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Scene::Show_Brush_ListInfo(BrushList* BList)
{
	char buf[MAX_PATH];
	Brush* pBrush;
	BrushIterator bi;
	int Count;

	Count = BrushList_Count(BList, (BRUSH_COUNT_MULTI | BRUSH_COUNT_LEAF | BRUSH_COUNT_NORECURSE));
	
	pBrush = BrushList_GetFirst(BList, &bi);
	while (pBrush != NULL)
	{
		Show_Brush_Info(pBrush);
		pBrush = BrushList_GetNext(&bi);
	}

	return 1;
}

// *************************************************************************
// *	  Show_Brush_Faces_Info:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Scene::Show_Brush_Faces_Info(const FaceList* pList)
{
	int i;
	
	if (pList->NumFaces < 0)
	{
	}
	else
	{
		for (i = 0; i < pList->NumFaces; i++)
		{
			if (!Show_Face_Data(pList->Faces[i])) return 0;
		}
	}

	return 1;
}

// *************************************************************************
// *		  Show_Face_Data:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Scene::Show_Face_Data(const Face* f)
{

	char buf[MAX_PATH];
	int		i, xShift, yShift, Rotate;
	geFloat xScale, yScale, rot;

	
	sprintf(buf, "%s%d", "NumPoints", f->NumPoints);
	

	for (i = 0; i < f->NumPoints; i++)
	{
		sprintf(buf, "XYZ %f %f %f", f->Points[i].X, f->Points[i].Y, f->Points[i].Z);
	}


	const TexInfo_Vectors* TVecs = Face_GetTextureVecs(f);
	geVec3d uVec, vVec;
	geFloat U, V;

	int txSize, tySize;

	Face_GetTextureSize(f, &txSize, &tySize);

	// make sure that the texture size is set correctly (division!)
	if (txSize == 0)
		txSize = 32;
	if (tySize == 0)
		tySize = 32;

	geVec3d_Scale(&TVecs->uVec, 1.f / (geFloat)txSize, &uVec);
	geVec3d_Scale(&TVecs->vVec, -1.f / (geFloat)tySize, &vVec);

	const geVec3d* verts = Face_GetPoints(f);

	int j = 0;
	for (j = 0; j < f->NumPoints; j++)
	{
		U = geVec3d_DotProduct(&(verts[j]), &uVec);
		V = geVec3d_DotProduct(&(verts[j]), &vVec);
		U += (TVecs->uOffset / txSize);
		V -= (TVecs->vOffset / tySize);

		sprintf(buf, "UV %.3f %.3f", U, V);
		
	}

	char buf2[MAX_PATH];
	strcpy(buf, Face_GetTextureName(f));
	sprintf(buf2, "%s%s", "Texture: = ", buf);
	
	return 1;
}
