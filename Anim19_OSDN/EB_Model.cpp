/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "GD19_App.h"
#include "EB_Model.h"


EB_Model::EB_Model()
{
}


EB_Model::~EB_Model()
{
}

// *************************************************************************
// *					CLear_ModelData Terry Bernie					   *
// *************************************************************************
void EB_Model::Clear_ModelData(void)
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

	//App->Cl19_Ogre->RenderListener->Reset_Class();
	//App->Cl19_Ogre->OgreListener->Reset_Class();

	Reset_Class(); // Here
				   //App->Cl_Grid->Reset_Class();
	App->CL_Vm_Genesis3D->Reset_Class();
	App->CL_Vm_ImGui->Reset_Class();
	App->SBC_TopTabs->Reset_Class();

	App->Set_Main_TitleBar(" ");

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
// *					Reset_Class Terry Bernie						   *
// *************************************************************************
void EB_Model::Reset_Class(void)
{
	int Count = 0;

	App->CL_Vm_Model->Model_Loaded = 0;
	App->CL_Vm_Model->Model_Type = LoadedFile_None;

	//--------------------- Clear Local data
	App->CL_Vm_Model->vertex_Data.clear();
	App->CL_Vm_Model->vertex_Data.resize(0);
	App->CL_Vm_Model->Face_Data.resize(0);
	App->CL_Vm_Model->Normal_Data.resize(0);
	App->CL_Vm_Model->MapCord_Data.resize(0);
	App->CL_Vm_Model->MatIndex_Data.resize(0);

	//--------------------- Clear Group data
	while (Count < App->CL_Vm_Model->GroupCount)
	{
		if (App->CL_Vm_Model->S_MeshGroup[Count] != NULL)
		{
			App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data.clear();
			App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data.resize(0);


			App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data.resize(0);

			App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data.resize(0);
			App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data.resize(0);

			if (App->CL_Vm_Model->S_MeshGroup[Count]->Base_Bitmap)
			{
				DeleteObject(App->CL_Vm_Model->S_MeshGroup[Count]->Base_Bitmap);
			}

			delete App->CL_Vm_Model->S_MeshGroup[Count];
			App->CL_Vm_Model->S_MeshGroup[Count] = NULL;
		}
		Count++;
	}

	//--------------------- Clear Bone data
	Count = 0;
	while (Count < App->CL_Vm_Model->BoneCount)
	{
		if (App->CL_Vm_Model->S_Bones[Count] != NULL)
		{
			delete App->CL_Vm_Model->S_Bones[Count];
			App->CL_Vm_Model->S_Bones[Count] = NULL;
		}
		Count++;
	}

	//--------------------- Clear Local Texture structure

	Count = 0;

	while (Count < App->CL_Vm_Model->S_Texture[0]->UsedTextureCount)
	{
		if (App->CL_Vm_Model->S_TextureInfo[Count] != NULL)
		{
			delete App->CL_Vm_Model->S_TextureInfo[Count];
			App->CL_Vm_Model->S_TextureInfo[Count] = NULL;
		}

		Count++;
	}

	if (App->CL_Vm_Model->S_Texture[0] != NULL)
	{
		delete App->CL_Vm_Model->S_Texture[0];
		App->CL_Vm_Model->S_Texture[0] = NULL;

		App->CL_Vm_Model->S_Texture[0] = new Texture_Type;
		App->CL_Vm_Model->S_Texture[0]->TextureCount = 1;
		App->CL_Vm_Model->S_Texture[0]->UsedTextureCount = 0;
		strcpy(App->CL_Vm_Model->S_Texture[0]->TextureName[0].Name, "Test.bmp");
	}

	//--------------------- Clear Bounding box data
	if (App->CL_Vm_Model->S_BoundingBox[0] != NULL)
	{
		delete App->CL_Vm_Model->S_BoundingBox[0];
		App->CL_Vm_Model->S_BoundingBox[0] = NULL;
	}

	strcpy(App->CL_Vm_Model->FileName, "No Model Loaded");
	strcpy(App->CL_Vm_Model->Path_FileName, "No Model Loaded");
	strcpy(App->CL_Vm_Model->JustName, "No Model Loaded");
	strcpy(App->CL_Vm_Model->Texture_FolderPath, "No Model Loaded");
	strcpy(App->CL_Vm_Model->Model_FolderPath, "No Model Loaded");

	Reset_Counters();
}

// *************************************************************************
// *						Reset_Counters Terry						   *
// *************************************************************************
void EB_Model::Reset_Counters(void)
{
	App->CL_Vm_Model->VerticeCount = 0;
	App->CL_Vm_Model->NormalsCount = 0;
	App->CL_Vm_Model->FaceCount = 0;
	App->CL_Vm_Model->UVCount = 0;

	App->CL_Vm_Model->TextureCount = 0;
	App->CL_Vm_Model->MotionCount = 0;
	App->CL_Vm_Model->BoneCount = 0;

	App->CL_Vm_Model->GroupCount = 0;

	App->CL_Vm_Model->Model_Type = 0;
	App->CL_Vm_Model->Model_Loaded = 0;
}

