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
#include "ME_Assimp.h"


ME_Assimp::ME_Assimp()
{
	SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;
	mTotalVertices = 0;
}


ME_Assimp::~ME_Assimp()
{
}

// *************************************************************************
// *						logInfo Terry Bernie				  	 	   *
// *************************************************************************
void ME_Assimp::logInfo(std::string logString)
{
	Assimp::DefaultLogger::get()->info(logString.c_str());
}

// *************************************************************************
// *						logDebug Terry Bernie				  	 	   *
// *************************************************************************
void ME_Assimp::logDebug(const char* logString)
{
	Assimp::DefaultLogger::get()->debug(logString);
}

// *************************************************************************
// *						LoadFile Terry Bernie				  	 	   *
// *************************************************************************
bool ME_Assimp::LoadFile(const char* pFile)
{

	//SelectedPreset = GetUserPresets(); // See what user wants

	const aiScene* scene = aiImportFile(pFile, SelectedPreset);

	if (!scene)
	{
		char buf[1024];
		strcpy(buf, aiGetErrorString());
		App->Say_Win(buf);
		return false;
	}
	else
	{

	GetBasicInfo(scene);

	Create_MeshGroups(scene);

////		Get_Group_VertCount(scene);

////		StoreMeshData(scene);
	
////		LoadTextures();
		
////		App->CL_Vm_Model->Create_BondingBox_Model();

	}

	aiReleaseImport(scene);
	return 1;
}

// *************************************************************************
// *						GetBasicInfo Terry Bernie			  	 	   *
// *************************************************************************
void  ME_Assimp::GetBasicInfo(const aiScene* pScene)
{

	bool test = pScene->HasMeshes();
	if (test == 1)
	{
		App->CL_Model->Set_Groupt_Count(pScene->mNumMeshes);
		//App->CL_Vm_Model->HasMesh = 1;
	}

	test = pScene->HasMaterials();
	if (test == 1)
	{
		int Mat = 0;

		Mat = pScene->mNumMaterials;

		if (Mat > 0)
		{
			App->CL_Model->Set_Texture_Count(pScene->mNumMaterials);
		}
		else
		{
			App->CL_Model->Set_Texture_Count(-1);
		}
	}

	test = pScene->HasAnimations();
	if (test == 1)
	{
		App->CL_Model->Set_Motion_Count(pScene->mNumAnimations);
	}
}

// *************************************************************************
// *					Create_MeshGroups_ByIndex Terry Flanigan	 	   *
// *************************************************************************
void ME_Assimp::Create_MeshGroups(const aiScene* pScene)
{

	int Count = 0;

	char GroupName[255];
	char MaterialName[255];
	char GroupNum[255];

	//App->CL_Vm_Model->S_Texture[0]->UsedTextureCount = App->CL_Vm_Model->GroupCount;
	//App->CL_Vm_Textures->CreateTextureInfo();

	int mGroupCount = App->CL_Model->Get_Groupt_Count();

	while (Count < mGroupCount)
	{
		aiMesh* mesh = pScene->mMeshes[Count];

		App->CL_Model->Group[Count] = new Base_Group();

		_itoa(Count, GroupNum, 10);
		strcpy(GroupName, "Group_");
		strcat(GroupName, GroupNum);
		strcpy(App->CL_Model->Group[Count]->GroupName, GroupName);

		strcpy(MaterialName, "Material_");
		strcat(MaterialName, GroupNum);
		strcpy(App->CL_Model->Group[Count]->MaterialName, MaterialName);

		////---------------

		//App->CL_Vm_Model->S_MeshGroup[Count]->GroupVertCount = 0;
		//App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex = -1;

		//App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex = Count;//= mesh->mMaterialIndex;

		//strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName, "No_Texture");

		//App->CL_Vm_Model->S_MeshGroup[Count]->HasBones = mesh->HasBones();
		//App->CL_Vm_Model->S_MeshGroup[Count]->BoneCount = mesh->mNumBones;

		/*if (App->S_MeshGroup[Count]->HasBones == 1)
		{
		mHasBones = 1;
		}*/

		// Get Texture Path/Name
		//aiString texPath;
		//aiMaterial* mtl = pScene->mMaterials[mesh->mMaterialIndex];
		//if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texPath))
		//{
		//	strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName, texPath.C_Str());
		//}
		//else
		//{
		//	strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName, "No_Texture");
		//	//App->CL_Model_Data->S_MeshGroup[Count]->MaterialIndex = -1;
		//}

		App->CL_FileView->Add_Group(App->CL_Model->Group[Count]->GroupName, Count);

		Count++;
	}
}
