/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "ME_Model.h"


ME_Model::ME_Model()
{
	GroupCount = 0;
	TextureCount = 0;
	VerticeCount = 0;			// Model Vertice Count 
	FaceCount = 0;				// Model Face Count 

	MotionCount = 0;

	Model_Loaded = 0;
	Model_Type = Enums::LoadedFile_None;

	strcpy (FileName,"No Model Loaded");
	strcpy (Path_FileName, "No Model Loaded");
	strcpy (Model_FolderPath, "No Model Loaded");
	strcpy (Texture_FolderPath, "No Model Loaded");
	JustName[0] = 0;

	S_BoundingBox[0] = nullptr;

	int Count = 0;
	while (Count < 99)
	{
		Group[Count] = nullptr;
		Count++;
	}
}


ME_Model::~ME_Model()
{

}

// *************************************************************************
// *					Reaet_Class Terry Flanigan						   *
// *************************************************************************
void ME_Model::Reset_Class(void)
{
	Model_Loaded = 0;
	Model_Type = Enums::LoadedFile_None;

	int Count = 0;
	int Index = GroupCount;

	//--------------------- Clear Groups
	while (Count < Index)
	{
		if (Group[Count] != nullptr)
		{
			Group[Count]->vertex_Data.clear();
			Group[Count]->vertex_Data.resize(0);
			Group[Count]->Face_Data.resize(0);
			Group[Count]->Normal_Data.resize(0);
			Group[Count]->MapCord_Data.resize(0);


			if (Group[Count]->Base_Bitmap)
			{
				DeleteObject(Group[Count]->Base_Bitmap);
			}

			delete Group[Count];
			Group[Count] = nullptr;
		}
		Count++;
	}

	//--------------------- Clear Bounding box data
	if (S_BoundingBox[0] != nullptr)
	{
		delete S_BoundingBox[0];
		S_BoundingBox[0] = nullptr;
	}

	FileName[0] = 0;
	Path_FileName[0] = 0;
	Model_FolderPath[0] = 0;
	Texture_FolderPath[0] = 0;
	JustName[0] = 0;
	GroupCount = 0;
	TextureCount = 0;
	VerticeCount = 0;
	FaceCount = 0;
	MotionCount = 0;
}
// *************************************************************************
// *						Set_Groupt_Count Terry Flanigan		  	 	   *
// *************************************************************************
void ME_Model::Set_Groupt_Count(int Count)
{
	GroupCount = Count;
}

// *************************************************************************
// *						Get_Groupt_Count Terry Flanigan		  	 	   *
// *************************************************************************
int ME_Model::Get_Groupt_Count()
{
	return GroupCount;
}

// *************************************************************************
// *						Set_Groupt_Count Terry Flanigan		  	 	   *
// *************************************************************************
void ME_Model::Set_Texture_Count(int Count)
{
	TextureCount = Count;
}

// *************************************************************************
// *						Set_Groupt_Count Terry Flanigan		  	 	   *
// *************************************************************************
void ME_Model::Set_Motion_Count(int Count)
{
	MotionCount = Count;
}

// *************************************************************************
// *						Set_Paths Terry Bernie						   *
// *************************************************************************
void ME_Model::Set_Paths(void)
{
	strcpy(FileName, App->CL_FileIO->Model_FileName);
	strcpy(Path_FileName, App->CL_FileIO->Model_Path_FileName);

	// Get Texture path assumed at this point to be where model is
	int len1 = strlen(FileName);
	int len2 = strlen(Path_FileName);
	strcpy(Model_FolderPath, Path_FileName);
	Model_FolderPath[len2 - len1] = 0;

	strcpy(Texture_FolderPath, Model_FolderPath); // Back Slash remains
	
	strcpy(JustName, FileName);
	int Len = strlen(JustName);
	JustName[Len - 4] = 0;

	//App->CL_Vm_FileIO->RecentFileHistory_Update();
}

// *************************************************************************
// *					Create_Mesh_Group Terry Flanigan		  	 	   *
// *************************************************************************
void ME_Model::Create_Mesh_Group(int Index)
{
	if (Group[Index] != nullptr)
	{
		delete Group[Index];
		Group[Index] = nullptr;
	}

	App->CL_Model->Group[Index] = new Base_Group();

}

// *************************************************************************
// *				Create_BondingBox_Model Terry Bernie				   *
// *************************************************************************
void ME_Model::Create_BondingBox_Model(void)
{

	S_BoundingBox[0] = new AABB_Type;

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

// *************************************************************************
// *				GetBoundingBoxModel_Update Terry Bernie				   *
// *************************************************************************
bool ME_Model::GetBoundingBoxModel_Update(void)
{
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

	return 1;
}

// *************************************************************************
// *					Clear Model and Reste Terry Flanigan			   *
// *************************************************************************
void ME_Model::Clear_Model_And_Reset(void)
{
	Reset_Class(); // Reset this Class
	
	App->CL_FileView->Reset_Class(); // Reset List View

	App->CL_Groups->Reset_Class();
	
	App->CL_Grid->Reset_Class();

	App->CL_TopBar->Reset_Class();

	SetWindowText(App->MainHwnd, "Equity_ME");
}

