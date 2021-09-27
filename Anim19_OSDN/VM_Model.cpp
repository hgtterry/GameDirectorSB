#include "stdafx.h"
#include "GD19_App.h"
#include "VM_Model.h"


VM_Model::VM_Model()
{
	VerticeCount = 0;
	NormalsCount = 0;
	FaceCount = 0;
	UVCount = 0;

	TextureCount = 0;
	MotionCount = 0;
	BoneCount = 0;

	GroupCount = 0;

	Model_Type = 0;
	Model_Loaded = 0;

	S_Texture[0] = NULL;
	S_Texture[0] = new Texture_Type;
	S_Texture[0]->TextureCount = 1;
	S_Texture[0]->UsedTextureCount = 0;
	strcpy(S_Texture[0]->TextureName[0].Name, "Test.bmp");

	strcpy(FileName, "No Model Loaded");
	strcpy(Path_FileName, "No Model Loaded");
	strcpy(JustName, "No Model Loaded");
	strcpy(Texture_FolderPath, "No Model Loaded");
	strcpy(Model_FolderPath, "No Model Loaded");
}


VM_Model::~VM_Model()
{
}

// *************************************************************************
// *					Reset_Class Terry Bernie						   *
// *************************************************************************
void VM_Model::Reset_Class(void)
{
	int Count = 0;

	Model_Loaded = 0;
	Model_Type = LoadedFile_None;

	//--------------------- Clear Local data
	vertex_Data.clear();
	vertex_Data.resize(0);
	Face_Data.resize(0);
	Normal_Data.resize(0);
	MapCord_Data.resize(0);
	MatIndex_Data.resize(0);

	//--------------------- Clear Group data
	while (Count < GroupCount)
	{
		if (S_MeshGroup[Count] != NULL)
		{
			S_MeshGroup[Count]->vertex_Data.clear();
			S_MeshGroup[Count]->vertex_Data.resize(0);


			S_MeshGroup[Count]->Face_Data.resize(0);

			S_MeshGroup[Count]->Normal_Data.resize(0);
			S_MeshGroup[Count]->MapCord_Data.resize(0);

			if (S_MeshGroup[Count]->Base_Bitmap)
			{
				DeleteObject(S_MeshGroup[Count]->Base_Bitmap);
			}

			delete S_MeshGroup[Count];
			S_MeshGroup[Count] = NULL;
		}
		Count++;
	}

	//--------------------- Clear Bone data
	Count = 0;
	while (Count < BoneCount)
	{
		if (S_Bones[Count] != NULL)
		{
			delete S_Bones[Count];
			S_Bones[Count] = NULL;
		}
		Count++;
	}

	//--------------------- Clear Local Texture structure

	Count = 0;

	while (Count < App->CL_Vm_Model->S_Texture[0]->UsedTextureCount)
	{
		if (S_TextureInfo[Count] != NULL)
		{
			delete S_TextureInfo[Count];
			S_TextureInfo[Count] = NULL;
		}

		Count++;
	}

	if (S_Texture[0] != NULL)
	{
		delete S_Texture[0];
		S_Texture[0] = NULL;

		S_Texture[0] = new Texture_Type;
		S_Texture[0]->TextureCount = 1;
		S_Texture[0]->UsedTextureCount = 0;
		strcpy(S_Texture[0]->TextureName[0].Name, "Test.bmp");
	}

	//--------------------- Clear Bounding box data
	if (S_BoundingBox[0] != NULL)
	{
		delete S_BoundingBox[0];
		S_BoundingBox[0] = NULL;
	}

	strcpy(FileName, "No Model Loaded");
	strcpy(Path_FileName, "No Model Loaded");
	strcpy(JustName, "No Model Loaded");
	strcpy(Texture_FolderPath, "No Model Loaded");
	strcpy(Model_FolderPath, "No Model Loaded");

	Reset_Counters();
}

// *************************************************************************
// *					CLear_ModelData Terry Bernie					   *
// *************************************************************************
void VM_Model::Clear_ModelData(void)
{
	
	//--------------------- Stop Motion Play if Active
	
	/*App->Cl_Ogre->OgreListener->Animate_Ogre = 0;
	App->Cl_Ogre->RenderListener->Show_Crosshair = 0;*/

	//--------------------- Clear Ogre Model if one was loaded
	/*if (App->Cl_Ogre->OgreModel_Ent && App->Cl_Ogre->OgreModel_Node)
	{
		App->Cl_Ogre->OgreModel_Node->detachAllObjects();
		App->Cl_Ogre->mSceneMgr->destroySceneNode(App->Cl_Ogre->OgreModel_Node);
		App->Cl_Ogre->mSceneMgr->destroyEntity(App->Cl_Ogre->OgreModel_Ent);
		App->Cl_Ogre->OgreModel_Ent = NULL;
		App->Cl_Ogre->OgreModel_Node = NULL;
		App->CL_Model_Data->ItsAnOgreModel = 0;
	}*/

	//--------------------- Reset Class Data

	App->Cl19_Ogre->RenderListener->Reset_Class();
	App->Cl19_Ogre->OgreListener->Reset_Class();

	Reset_Class(); // Here
	App->Cl_Grid->Reset_Class();
	App->CL_Vm_Genesis3D->Reset_Class();
	App->CL_Vm_ImGui->Reset_Class();
	App->CL_Vm_TopBar->Reset_Class();

	App->Set_Main_TitleBar();

	//--------------------- Reset Equity
	//App->CL_FileView->HideRightPanes(1);

	//SetDlgItemText(App->ModelGlobal_Hwnd, IDC_STMODELNAME, (LPCTSTR)"No Model Loaded");


	// ----------------- Motions Panel
	/*SetDlgItemText(App->CentralView_Hwnd, IDC_STMOTIONNAME, "Model has no Motions");
	App->CL_Motions->MotionsDialog_Active = 0;
	ShowWindow(App->CentralView_Hwnd, 0);
	CheckMenuItem(App->mMenu, ID_WINDOW_SHOWMOTIONSPANEL, MF_BYCOMMAND | MF_UNCHECKED);*/
}

// *************************************************************************
// *						Reset_Counters Terry						   *
// *************************************************************************
void VM_Model::Reset_Counters(void)
{
	VerticeCount = 0;
	NormalsCount = 0;
	FaceCount = 0;
	UVCount = 0;

	TextureCount = 0;
	MotionCount = 0;
	BoneCount = 0;

	GroupCount = 0;

	Model_Type = 0;
	Model_Loaded = 0;
}

// *************************************************************************
// *						Set_Paths Terry Bernie						   *
// *************************************************************************
void VM_Model::Set_Paths(void)
{
	strcpy(FileName, App->CL_Vm_FileIO->Model_FileName);
	strcpy(Path_FileName, App->CL_Vm_FileIO->Model_Path_FileName);

	// Get Texure path assumed at this point to be where model is
	int len1 = strlen(FileName);
	int len2 = strlen(Path_FileName);
	strcpy(Model_FolderPath, Path_FileName);
	Model_FolderPath[len2 - len1] = 0;

	strcpy(Texture_FolderPath, Model_FolderPath);

	strcpy(JustName, FileName);
	int Len = strlen(JustName);
	JustName[Len - 4] = 0;

	App->CL_Vm_FileIO->RecentFileHistory_Update();
}

// *************************************************************************
// *					Create_S_MeshGroup  Terry Bernie   		  	 	   *
// *************************************************************************
void VM_Model::Create_S_MeshGroup(int Index)
{
	S_MeshGroup[Index] = new MeshGroup_Type;

	S_MeshGroup[Index]->Base_Bitmap = NULL;

	S_MeshGroup[Index]->BasePicHeight = 0;
	S_MeshGroup[Index]->BasePicWidth = 0;

	S_MeshGroup[Index]->Alpha_Bitmap = NULL;
	S_MeshGroup[Index]->AlphaPicHeight = 0;
	S_MeshGroup[Index]->AlphaPicWidth = 0;

	S_MeshGroup[Index]->Soil_TextureIndex = 0;
	S_MeshGroup[Index]->Bitmap_Loaded = 0;
	strcpy(S_MeshGroup[Index]->GroupName, "");

	S_MeshGroup[Index]->GroupVertCount = 0;
	S_MeshGroup[Index]->GroupFaceCount = 0;
	S_MeshGroup[Index]->MaterialIndex = -1;
	//	S_MeshGroup[Index]->EqIndex = Index+1;

	strcpy(S_MeshGroup[Index]->Text_FileName, "No_Texture");
	strcpy(S_MeshGroup[Index]->Text_PathFileName, "No_Texture");
	strcpy(S_MeshGroup[Index]->Text_JustName, "No_Texture");

	strcpy(S_MeshGroup[Index]->MaterialName, "No_Material");

	S_MeshGroup[Index]->HasBones = 0;
	S_MeshGroup[Index]->BoneCount = 0;
	S_MeshGroup[Index]->IsDirty = 0;
	S_MeshGroup[Index]->IsTextureValid = 0;
	S_MeshGroup[Index]->BoneAssignMentCount = 0;
}

// *************************************************************************
// *				Create_BondingBox_Model Terry Bernie				   *
// *************************************************************************
bool VM_Model::Create_BondingBox_Model(void)
{

	S_BoundingBox[0] = new AABB_Type;

	S_BoundingBox[0]->BB_Min[0].x = S_MeshGroup[0]->vertex_Data[0].x;
	S_BoundingBox[0]->BB_Min[0].y = S_MeshGroup[0]->vertex_Data[0].y;
	S_BoundingBox[0]->BB_Min[0].z = S_MeshGroup[0]->vertex_Data[0].z;

	S_BoundingBox[0]->BB_Max[0].x = S_MeshGroup[0]->vertex_Data[0].x;
	S_BoundingBox[0]->BB_Max[0].y = S_MeshGroup[0]->vertex_Data[0].y;
	S_BoundingBox[0]->BB_Max[0].z = S_MeshGroup[0]->vertex_Data[0].z;

	int Count = 0;
	int VertCount = 0;

	while (Count < GroupCount)
	{
		VertCount = 0;
		while (VertCount < S_MeshGroup[Count]->GroupVertCount)
		{
			if (S_MeshGroup[Count]->vertex_Data[VertCount].x < S_BoundingBox[0]->BB_Min[0].x) S_BoundingBox[0]->BB_Min[0].x = S_MeshGroup[Count]->vertex_Data[VertCount].x;
			if (S_MeshGroup[Count]->vertex_Data[VertCount].y < S_BoundingBox[0]->BB_Min[0].y) S_BoundingBox[0]->BB_Min[0].y = S_MeshGroup[Count]->vertex_Data[VertCount].y;
			if (S_MeshGroup[Count]->vertex_Data[VertCount].z < S_BoundingBox[0]->BB_Min[0].z) S_BoundingBox[0]->BB_Min[0].z = S_MeshGroup[Count]->vertex_Data[VertCount].z;
			if (S_MeshGroup[Count]->vertex_Data[VertCount].x > S_BoundingBox[0]->BB_Max[0].x) S_BoundingBox[0]->BB_Max[0].x = S_MeshGroup[Count]->vertex_Data[VertCount].x;
			if (S_MeshGroup[Count]->vertex_Data[VertCount].y > S_BoundingBox[0]->BB_Max[0].y) S_BoundingBox[0]->BB_Max[0].y = S_MeshGroup[Count]->vertex_Data[VertCount].y;
			if (S_MeshGroup[Count]->vertex_Data[VertCount].z > S_BoundingBox[0]->BB_Max[0].z) S_BoundingBox[0]->BB_Max[0].z = S_MeshGroup[Count]->vertex_Data[VertCount].z;
			VertCount++;
		}
		Count++;
	}


	S_BoundingBox[0]->Size[0].x = (fabs(S_BoundingBox[0]->BB_Max[0].x - S_BoundingBox[0]->BB_Min[0].x));
	S_BoundingBox[0]->Size[0].y = (fabs(S_BoundingBox[0]->BB_Max[0].y - S_BoundingBox[0]->BB_Min[0].y));
	S_BoundingBox[0]->Size[0].z = (fabs(S_BoundingBox[0]->BB_Max[0].z - S_BoundingBox[0]->BB_Min[0].z));

	S_BoundingBox[0]->radius = (S_BoundingBox[0]->Size[0].x>S_BoundingBox[0]->Size[0].z) ? S_BoundingBox[0]->Size[0].z / 2.0f : S_BoundingBox[0]->Size[0].x / 2.0f;

	S_BoundingBox[0]->Centre[0].x = (S_BoundingBox[0]->BB_Min[0].x + S_BoundingBox[0]->BB_Max[0].x) / 2.0f;
	S_BoundingBox[0]->Centre[0].y = (S_BoundingBox[0]->BB_Min[0].y + S_BoundingBox[0]->BB_Max[0].y) / 2.0f;
	S_BoundingBox[0]->Centre[0].z = (S_BoundingBox[0]->BB_Min[0].z + S_BoundingBox[0]->BB_Max[0].z) / 2.0f;

	return 1;
}

// *************************************************************************
// *				GetBoundingBoxModel_Update Terry Bernie				   *
// *************************************************************************
bool VM_Model::GetBoundingBoxModel_Update(void)
{
	S_BoundingBox[0]->BB_Min[0].x = S_MeshGroup[0]->vertex_Data[0].x;
	S_BoundingBox[0]->BB_Min[0].y = S_MeshGroup[0]->vertex_Data[0].y;
	S_BoundingBox[0]->BB_Min[0].z = S_MeshGroup[0]->vertex_Data[0].z;

	S_BoundingBox[0]->BB_Max[0].x = S_MeshGroup[0]->vertex_Data[0].x;
	S_BoundingBox[0]->BB_Max[0].y = S_MeshGroup[0]->vertex_Data[0].y;
	S_BoundingBox[0]->BB_Max[0].z = S_MeshGroup[0]->vertex_Data[0].z;

	int Count = 0;
	int VertCount = 0;
	while (Count < GroupCount)
	{
		VertCount = 0;
		while (VertCount < S_MeshGroup[Count]->GroupVertCount)
		{
			if (S_MeshGroup[Count]->vertex_Data[VertCount].x < S_BoundingBox[0]->BB_Min[0].x) S_BoundingBox[0]->BB_Min[0].x = S_MeshGroup[Count]->vertex_Data[VertCount].x;
			if (S_MeshGroup[Count]->vertex_Data[VertCount].y < S_BoundingBox[0]->BB_Min[0].y) S_BoundingBox[0]->BB_Min[0].y = S_MeshGroup[Count]->vertex_Data[VertCount].y;
			if (S_MeshGroup[Count]->vertex_Data[VertCount].z < S_BoundingBox[0]->BB_Min[0].z) S_BoundingBox[0]->BB_Min[0].z = S_MeshGroup[Count]->vertex_Data[VertCount].z;
			if (S_MeshGroup[Count]->vertex_Data[VertCount].x > S_BoundingBox[0]->BB_Max[0].x) S_BoundingBox[0]->BB_Max[0].x = S_MeshGroup[Count]->vertex_Data[VertCount].x;
			if (S_MeshGroup[Count]->vertex_Data[VertCount].y > S_BoundingBox[0]->BB_Max[0].y) S_BoundingBox[0]->BB_Max[0].y = S_MeshGroup[Count]->vertex_Data[VertCount].y;
			if (S_MeshGroup[Count]->vertex_Data[VertCount].z > S_BoundingBox[0]->BB_Max[0].z) S_BoundingBox[0]->BB_Max[0].z = S_MeshGroup[Count]->vertex_Data[VertCount].z;
			VertCount++;
		}
		Count++;
	}

	S_BoundingBox[0]->Size[0].x = (fabs(S_BoundingBox[0]->BB_Max[0].x - S_BoundingBox[0]->BB_Min[0].x));
	S_BoundingBox[0]->Size[0].y = (fabs(S_BoundingBox[0]->BB_Max[0].y - S_BoundingBox[0]->BB_Min[0].y));
	S_BoundingBox[0]->Size[0].z = (fabs(S_BoundingBox[0]->BB_Max[0].z - S_BoundingBox[0]->BB_Min[0].z));

	S_BoundingBox[0]->radius = (S_BoundingBox[0]->Size[0].x>S_BoundingBox[0]->Size[0].z) ? S_BoundingBox[0]->Size[0].z / 2.0f : S_BoundingBox[0]->Size[0].x / 2.0f;

	S_BoundingBox[0]->Centre[0].x = (S_BoundingBox[0]->BB_Min[0].x + S_BoundingBox[0]->BB_Max[0].x) / 2.0f;
	S_BoundingBox[0]->Centre[0].y = (S_BoundingBox[0]->BB_Min[0].y + S_BoundingBox[0]->BB_Max[0].y) / 2.0f;
	S_BoundingBox[0]->Centre[0].z = (S_BoundingBox[0]->BB_Min[0].z + S_BoundingBox[0]->BB_Max[0].z) / 2.0f;

	return 1;
}

// *************************************************************************
// *					Convert_To_GlobalMesh  Terry Bernie   	  	 	   *
// *************************************************************************
void VM_Model::Convert_To_GlobalMesh(void)
{
	int Count = 0;
	int GroupVertCount = 0;
	int GroupFaceCount = 0;
	int VC = 0;

	int Offset = 0;

	vertex_Data.resize(VerticeCount);
	Face_Data.resize(FaceCount);

	Normal_Data.resize(VerticeCount);
	MapCord_Data.resize(VerticeCount);
	MatIndex_Data.resize(FaceCount);

	/*if (App->CL_Model_Data->ItsAnOgreModel == 1)
	{
		App->CL_Model_Data->BoneIndex_Data.resize(App->CL_Model_Data->VertCount);
	}*/

	while (Count < GroupCount)
	{
		GroupVertCount = 0;

		while (GroupVertCount < S_MeshGroup[Count]->GroupVertCount)
		{
			vertex_Data[VC].x = S_MeshGroup[Count]->vertex_Data[GroupVertCount].x;
			vertex_Data[VC].y = S_MeshGroup[Count]->vertex_Data[GroupVertCount].y;
			vertex_Data[VC].z = S_MeshGroup[Count]->vertex_Data[GroupVertCount].z;

			/*if (App->CL_Model_Data->ItsAnOgreModel == 1)
			{
				App->CL_Model_Data->BoneIndex_Data[VC].Index = App->CL_Model_Data->S_MeshGroup[Count]->BoneIndex_Data[GroupVertCount].Index;
			}*/

			MapCord_Data[VC].u = S_MeshGroup[Count]->MapCord_Data[GroupVertCount].u;
			MapCord_Data[VC].v = S_MeshGroup[Count]->MapCord_Data[GroupVertCount].v;

			Normal_Data[VC].x = S_MeshGroup[Count]->Normal_Data[GroupVertCount].x;
			Normal_Data[VC].y = S_MeshGroup[Count]->Normal_Data[GroupVertCount].y;
			Normal_Data[VC].z = S_MeshGroup[Count]->Normal_Data[GroupVertCount].z;

			VC++;

			GroupVertCount++;
		}

		Count++;
	}


	VC = 0;
	Count = 0;
	int mFaceCount = 0;
	while (Count < GroupCount)
	{
		mFaceCount = 0;
		while (mFaceCount < S_MeshGroup[Count]->GroupFaceCount)
		{

			Face_Data[VC].Group = Count;

			Face_Data[VC].a = S_MeshGroup[Count]->Face_Data[mFaceCount].a + Offset;
			Face_Data[VC].b = S_MeshGroup[Count]->Face_Data[mFaceCount].b + Offset;
			Face_Data[VC].c = S_MeshGroup[Count]->Face_Data[mFaceCount].c + Offset;

			VC++;
			mFaceCount++;
		}

		Offset = Offset + S_MeshGroup[Count]->GroupVertCount;
		Count++;

	}


	VC = 0;
	Count = 0;
	while (Count < GroupCount)
	{
		GroupFaceCount = 0;

		while (GroupFaceCount < S_MeshGroup[Count]->GroupFaceCount)
		{
			MatIndex_Data[VC] = S_MeshGroup[Count]->MaterialIndex;

			VC++;
			GroupFaceCount++;
		}

		Count++;
	}
}

