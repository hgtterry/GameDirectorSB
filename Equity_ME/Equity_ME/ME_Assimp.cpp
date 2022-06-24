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
	
	LoadTextures();
		
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

		App->CL_Model->Group[Count]->GroupVertCount = 0;
		App->CL_Model->Group[Count]->MaterialIndex = -1;

		App->CL_Model->Group[Count]->MaterialIndex = Count;

		strcpy(App->CL_Model->Group[Count]->Text_FileName, "No_Texture");

		//App->CL_Vm_Model->S_MeshGroup[Count]->HasBones = mesh->HasBones();
		//App->CL_Vm_Model->S_MeshGroup[Count]->BoneCount = mesh->mNumBones;

		/*if (App->S_MeshGroup[Count]->HasBones == 1)
		{
		mHasBones = 1;
		}*/

		// Get Texture Path/Name
		strcpy(App->CL_Model->Group[Count]->Texture_FolderPath, App->CL_Model->Texture_FolderPath); // Back Slash remains

		aiString texPath;
		aiMaterial* mtl = pScene->mMaterials[mesh->mMaterialIndex];
		if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texPath))
		{
			strcpy(App->CL_Model->Group[Count]->Text_FileName, texPath.C_Str());
		}
		else
		{
			strcpy(App->CL_Model->Group[Count]->Text_FileName, "No_Texture");
			App->CL_Model->Group[Count]->MaterialIndex = -1;
		}

		// FileView
		App->CL_FileView->Add_Group(App->CL_Model->Group[Count]->GroupName, Count);

		Count++;
	}
}

// *************************************************************************
// *					LoadTextures Terry Bernie Hazel			  	 	   *
// *************************************************************************
void ME_Assimp::LoadTextures()
{
	
	int v = 0;
	int Count = 0;

	int mGroupCount = App->CL_Model->Get_Groupt_Count();

	while (Count < mGroupCount)
	{
		char FullName[1024];
		strcpy(FullName, App->CL_Model->Group[Count]->Text_FileName);

		App->CL_Textures->Strip_JustFileName(FullName, FullName);

		strcpy(App->CL_Model->Group[Count]->Text_FileName, App->CL_Textures->JustFileName);


	//	strcpy(App->CL_Vm_Model->Texture_FolderPath, App->CL_Vm_Model->Texture_FolderPath);
	//	//	strcat(App->CL_Vm_Model->Texture_FullPath, App->CL_Vm_Textures->JustFileName);


		int Test = strcmp(App->CL_Textures->JustFileName, "No_Texture");
		if (Test != 0) // Dose not equal 
		{
			int MatIndex = App->CL_Model->Group[Count]->MaterialIndex;

	//		App->CL_Vm_Model->S_TextureInfo[Count]->ActorMaterialIndex = MatIndex;

	//		strcpy(App->CL_Vm_Model->S_TextureInfo[Count]->MaterialName, App->CL_Vm_Textures->JustFileName);


	//		App->CL_Vm_Model->S_MeshGroup[v]->Soil_TextureIndex = MatIndex;

	//		strcpy(App->CL_Vm_Model->S_MeshGroup[v]->Text_FileName, App->CL_Vm_Textures->JustFileName);

			char ImageFullPath[1024];
			strcpy(ImageFullPath, App->CL_Model->Texture_FolderPath);
			strcat(ImageFullPath, App->CL_Model->Group[Count]->Text_FileName);

			App->Say_Win(ImageFullPath);

			strcpy(App->CL_Model->Group[v]->Texture_PathFileName, ImageFullPath);
			//strcpy(App->CL_Textures->TextureFileName, ImageFullPath);

			App->CL_Textures->TexureToWinPreviewFullPath(v, ImageFullPath);
	//		App->CL_Vm_Textures->Soil_DecodeTextures(MatIndex); // ??

			v++;
		}
		else
		{

	//		App->CL_Vm_Textures->CreateDummyTexture();

	//		int MatIndex = App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex;
	//		App->CL_Vm_Model->S_TextureInfo[Count]->ActorMaterialIndex = MatIndex;

	//		//App->CL_Vm_Model->S_MeshGroup[v]->Soil_TextureIndex = MatIndex;

	//		strcpy(App->CL_Vm_Model->S_MeshGroup[v]->Text_FileName, "Etemp.bmp");
	//		strcpy(App->CL_Vm_Model->S_TextureInfo[Count]->MaterialName, "Etemp.bmp");

	//		char ImageFullPath[1024];
	//		strcpy(ImageFullPath, App->CL_Vm_Model->Texture_FolderPath);
	//		strcat(ImageFullPath, "Etemp.bmp");

	//		strcpy(App->CL_Vm_Model->S_MeshGroup[v]->Text_PathFileName, ImageFullPath);
	//		strcpy(App->CL_Vm_Textures->TextureFileName, ImageFullPath);

	//		App->CL_Vm_Textures->TexureToWinPreviewFullPath(v, ImageFullPath);
	//		App->CL_Vm_Textures->Soil_DecodeTextures(MatIndex); // ??


	//		remove(ImageFullPath);

			v++;
		}
		Count++;
	}

}
