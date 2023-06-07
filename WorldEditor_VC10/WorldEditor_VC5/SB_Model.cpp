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

#include "StdAfx.h"
#include "AB_App.h"
#include "SB_Model.h"

SB_Model::SB_Model(void)
{
	VerticeCount = 0;
	FaceCount = 0;
	GroupCount = 0;
	TextureCount = 0;
	MotionCount = 0;

	Model_Loaded = 0;

	strcpy(FileName, "No Model Loaded");
	strcpy(Path_FileName, "No Model Loaded");
	strcpy(Model_FolderPath, "No Model Loaded");
	strcpy(Texture_FolderPath, "No Model Loaded");
	JustName[0] = 0;
}

SB_Model::~SB_Model(void)
{
}

// *************************************************************************
// *		Create_Mesh_Group:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
void SB_Model::Create_Mesh_Group(int Index)
{
	if (Group[Index] != nullptr)
	{
		delete Group[Index];
		Group[Index] = nullptr;
	}

	Group[Index] = new Base_Group();

}

// *************************************************************************
// *		Get_Groupt_Count:- Terry and Hazel Flanigan 2023		   	   *
// *************************************************************************
int SB_Model::Get_Groupt_Count()
{
	return GroupCount;
}

// *************************************************************************
// *			Set_Groupt_Count:- Terry and Hazel Flanigan 2023	 	   *
// *************************************************************************
void SB_Model::Set_Groupt_Count(int Count)
{
	GroupCount = Count;
}

// *************************************************************************
// *		Set_Groupt_Count:- Terry and Hazel Flanigan 2023	  		   *
// *************************************************************************
void SB_Model::Set_Texture_Count(int Count)
{
	TextureCount = Count;
}

// *************************************************************************
// *			Set_Groupt_Count:- Terry and Hazel Flanigan 2023	   	   *
// *************************************************************************
void SB_Model::Set_Motion_Count(int Count)
{
	MotionCount = Count;
}

// *************************************************************************
// *			Set_Paths:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_Model::Set_Paths(void)
{
	strcpy(FileName, App->CLSB_Loader->FileName);
	strcpy(Path_FileName, App->CLSB_Loader->Path_FileName);

	// Get Texture path assumed at this point to be where model is
	int len1 = strlen(FileName);
	int len2 = strlen(Path_FileName);
	strcpy(Model_FolderPath, Path_FileName);
	Model_FolderPath[len2 - len1] = 0;

	strcpy(Texture_FolderPath, Model_FolderPath); // Back Slash remains

	if (_stricmp(FileName + strlen(FileName) - 5, ".Wepf") == 0)
	{
		char JustFileName[MAX_PATH];
		GetFileTitleA(App->CLSB_Loader->Path_FileName, JustFileName, MAX_PATH);

		strcpy(JustName, JustFileName);
		int Len = strlen(JustFileName);
		JustName[Len - 5] = 0;
	}
	else
	{
		App->Say("Wrong File Type");
	}


	//App->CL_Recent_Files->RecentFileHistory_Update();
}

// *************************************************************************
// *		Create_BondingBox_Model:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Model::Set_BondingBox_Model(bool Create)
{
	if (Create == 1)
	{
		S_BoundingBox[0] = new AABB_Type;
	}

	S_BoundingBox[0]->BB_Min[0].x = Group[0]->vertex_Data[0].x;
	S_BoundingBox[0]->BB_Min[0].y = Group[0]->vertex_Data[0].y;
	S_BoundingBox[0]->BB_Min[0].z = Group[0]->vertex_Data[0].z;

	S_BoundingBox[0]->BB_Max[0].x = Group[0]->vertex_Data[0].x;
	S_BoundingBox[0]->BB_Max[0].y = Group[0]->vertex_Data[0].y;
	S_BoundingBox[0]->BB_Max[0].z = Group[0]->vertex_Data[0].z;

	int Count = 0;
	int VertCount = 0;

	while (Count < GroupCount)
	{
		VertCount = 0;
		while (VertCount < Group[Count]->GroupVertCount)
		{
			if (Group[Count]->vertex_Data[VertCount].x < S_BoundingBox[0]->BB_Min[0].x) S_BoundingBox[0]->BB_Min[0].x = Group[Count]->vertex_Data[VertCount].x;
			if (Group[Count]->vertex_Data[VertCount].y < S_BoundingBox[0]->BB_Min[0].y) S_BoundingBox[0]->BB_Min[0].y = Group[Count]->vertex_Data[VertCount].y;
			if (Group[Count]->vertex_Data[VertCount].z < S_BoundingBox[0]->BB_Min[0].z) S_BoundingBox[0]->BB_Min[0].z = Group[Count]->vertex_Data[VertCount].z;
			if (Group[Count]->vertex_Data[VertCount].x > S_BoundingBox[0]->BB_Max[0].x) S_BoundingBox[0]->BB_Max[0].x = Group[Count]->vertex_Data[VertCount].x;
			if (Group[Count]->vertex_Data[VertCount].y > S_BoundingBox[0]->BB_Max[0].y) S_BoundingBox[0]->BB_Max[0].y = Group[Count]->vertex_Data[VertCount].y;
			if (Group[Count]->vertex_Data[VertCount].z > S_BoundingBox[0]->BB_Max[0].z) S_BoundingBox[0]->BB_Max[0].z = Group[Count]->vertex_Data[VertCount].z;
			VertCount++;
		}
		Count++;
	}

	S_BoundingBox[0]->Size[0].x = (fabs(S_BoundingBox[0]->BB_Max[0].x - S_BoundingBox[0]->BB_Min[0].x));
	S_BoundingBox[0]->Size[0].y = (fabs(S_BoundingBox[0]->BB_Max[0].y - S_BoundingBox[0]->BB_Min[0].y));
	S_BoundingBox[0]->Size[0].z = (fabs(S_BoundingBox[0]->BB_Max[0].z - S_BoundingBox[0]->BB_Min[0].z));

	S_BoundingBox[0]->radius = (S_BoundingBox[0]->Size[0].x > S_BoundingBox[0]->Size[0].z) ? S_BoundingBox[0]->Size[0].z / 2.0f : S_BoundingBox[0]->Size[0].x / 2.0f;

	S_BoundingBox[0]->Centre[0].x = (S_BoundingBox[0]->BB_Min[0].x + S_BoundingBox[0]->BB_Max[0].x) / 2.0f;
	S_BoundingBox[0]->Centre[0].y = (S_BoundingBox[0]->BB_Min[0].y + S_BoundingBox[0]->BB_Max[0].y) / 2.0f;
	S_BoundingBox[0]->Centre[0].z = (S_BoundingBox[0]->BB_Min[0].z + S_BoundingBox[0]->BB_Max[0].z) / 2.0f;
}