#include "stdafx.h"
#include "GD19_App.h"
#include "VM_Assimp.h"


VM_Assimp::VM_Assimp()
{
	SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;
	mTotalVertices = 0;
}


VM_Assimp::~VM_Assimp()
{
}

// *************************************************************************
// *						logInfo Terry Bernie				  	 	   *
// *************************************************************************
void VM_Assimp::logInfo(std::string logString)
{
	Assimp::DefaultLogger::get()->info(logString.c_str());
}

// *************************************************************************
// *						logDebug Terry Bernie				  	 	   *
// *************************************************************************
void VM_Assimp::logDebug(const char* logString)
{
	Assimp::DefaultLogger::get()->debug(logString);
}

// *************************************************************************
// *						LoadFile Terry Bernie				  	 	   *
// *************************************************************************
bool VM_Assimp::LoadFile(const char* pFile)
{

	//SelectedPreset = GetUserPresets(); // See what user wants

	const aiScene* scene = aiImportFile(pFile, SelectedPreset);

	if (!scene)
	{
		char buf[1024];
		strcpy(buf, aiGetErrorString());
		App->Say(buf);
		return false;
	}
	else
	{

		GetBasicInfo(scene);

		Create_MeshGroups(scene);

		Get_Group_VertCount(scene);

	
		StoreMeshData(scene);

		/*App->Cl_Ogre->Loading_Text("Loading Textures", 1);

		if (App->Cl_Importer->Is_RFEditPro == 1)
		{
			LoadTextures_RFEditPro();
		}
		else
		{
			LoadTextures();
		}

		App->Cl_Ogre->Loading_Text("Loading Creating BBox", 1);
		App->CL_Model_Data->Create_BondingBox_Model();*/

	}

	aiReleaseImport(scene);
	return 1;
}

// *************************************************************************
// *						GetBasicInfo Terry Bernie			  	 	   *
// *************************************************************************
void  VM_Assimp::GetBasicInfo(const aiScene* pScene)
{

	bool test = pScene->HasMeshes();
	if (test == 1)
	{
		App->CL_Vm_Model->GroupCount = pScene->mNumMeshes;
		//App->CL_Vm_Model->HasMesh = 1;
	}

	test = pScene->HasMaterials();
	if (test == 1)
	{
		int Hack = 0;

		Hack = pScene->mNumMaterials;

		if (Hack == 1)
		{
			App->CL_Vm_Model->TextureCount = pScene->mNumMaterials;
		}
		else
		{
			App->CL_Vm_Model->TextureCount = pScene->mNumMaterials - 1;
		}
	}

	test = pScene->HasAnimations();
	if (test == 1)
	{
		App->CL_Vm_Model->MotionCount = pScene->mNumAnimations;
	}
}

// *************************************************************************
// *					Create_MeshGroups_ByIndex Terry Bernie		 	   *
// *************************************************************************
void VM_Assimp::Create_MeshGroups(const aiScene* pScene)
{

	int Count = 0;

	char GroupName[255];
	char MaterialName[255];
	char GroupNum[255];

	while (Count < App->CL_Vm_Model->GroupCount)
	{
		aiMesh* mesh = pScene->mMeshes[Count];

		App->CL_Vm_Model->Create_S_MeshGroup(Count);

		_itoa(Count, GroupNum, 10);
		strcpy(GroupName, "Group_");
		strcat(GroupName, GroupNum);
		strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->GroupName, GroupName);

		strcpy(MaterialName, "Material_");
		strcat(MaterialName, GroupNum);
		strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->MaterialName, MaterialName);

		////---------------

		App->CL_Vm_Model->S_MeshGroup[Count]->GroupVertCount = 0;
		App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex = -1;

		App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex = Count;//= mesh->mMaterialIndex;

		strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName, "No_Texture");

		App->CL_Vm_Model->S_MeshGroup[Count]->HasBones = mesh->HasBones();
		App->CL_Vm_Model->S_MeshGroup[Count]->BoneCount = mesh->mNumBones;

		/*if (App->S_MeshGroup[Count]->HasBones == 1)
		{
		mHasBones = 1;
		}*/

		// Get Texture Path/Name
		aiString texPath;
		aiMaterial* mtl = pScene->mMaterials[mesh->mMaterialIndex];
		if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texPath))
		{
			strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName, texPath.C_Str());
		}
		else
		{
			strcpy(App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName, "No_Texture");
			//App->CL_Model_Data->S_MeshGroup[Count]->MaterialIndex = -1;
		}

		Count++;
	}
}

// *************************************************************************
// *					Get_Group_VertCount Terry Bernie		  	 	   *
// *************************************************************************
void VM_Assimp::Get_Group_VertCount(const aiScene* pScene)
{
	int Count = 0;
	unsigned int t = 0;
	unsigned int i = 0;
	int VC = 0;
	int mTotalVertices = 0;
	int mTotalFaces = 0;

	while (Count < App->CL_Vm_Model->GroupCount)
	{
		aiMesh* mesh = pScene->mMeshes[Count];

		VC = 0;
		t = 0;

		mTotalFaces = mTotalFaces + mesh->mNumFaces;

		App->CL_Vm_Model->S_MeshGroup[Count]->GroupFaceCount = mesh->mNumFaces;

		while (t < mesh->mNumFaces)
		{
			aiFace* face = &mesh->mFaces[t];

			i = 0;
			while (i<face->mNumIndices)
			{
				VC++;
				i++;
			}

			t++;
		}

		App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data.resize(VC);
		App->CL_Vm_Model->S_MeshGroup[Count]->Normal_Data.resize(VC);
		App->CL_Vm_Model->S_MeshGroup[Count]->MapCord_Data.resize(VC);
		App->CL_Vm_Model->S_MeshGroup[Count]->Face_Data.resize(VC);

		mTotalVertices = mTotalVertices + mesh->mNumVertices;
		Count++;
	}

	App->CL_Vm_Model->VerticeCount = mTotalVertices;
	App->CL_Vm_Model->FaceCount = mTotalFaces;

}

// *************************************************************************
// *					StoreMeshData Terry Bernie Hazel			   	   *
// *************************************************************************
void VM_Assimp::StoreMeshData(const aiScene* pScene)
{
	int FaceNum = 0;
	int FaceIndexNum = 0;
	mTotalVertices = 0;
	int GroupCount = 0;
	unsigned int t = 0;
	unsigned int i = 0;
	int VC = 0;

	while (GroupCount < App->CL_Vm_Model->GroupCount)
	{
		aiMesh* mesh = pScene->mMeshes[GroupCount];

		VC = 0;
		t = 0;

		App->CL_Vm_Model->S_MeshGroup[GroupCount]->GroupFaceCount = mesh->mNumFaces;
		App->CL_Vm_Model->S_MeshGroup[GroupCount]->FaceIndex_Data.resize(mesh->mNumFaces * 3);

		App->CL_Vm_Model->S_MeshGroup[GroupCount]->Face_Data.resize(mesh->mNumFaces);

		while (t < mesh->mNumFaces)
		{
			aiFace* face = &mesh->mFaces[t];

			i = 0;
			while (i<face->mNumIndices) // Triangulated Each face has 3 Indices
			{
				int vertexIndex = face->mIndices[i];

				App->CL_Vm_Model->S_MeshGroup[GroupCount]->vertex_Data[vertexIndex].x = mesh->mVertices[vertexIndex].x;
				App->CL_Vm_Model->S_MeshGroup[GroupCount]->vertex_Data[vertexIndex].y = mesh->mVertices[vertexIndex].y;
				App->CL_Vm_Model->S_MeshGroup[GroupCount]->vertex_Data[vertexIndex].z = mesh->mVertices[vertexIndex].z;


				if (mesh->HasNormals())
				{
					App->CL_Vm_Model->S_MeshGroup[GroupCount]->Normal_Data[vertexIndex].x = mesh->mNormals[vertexIndex].x;
					App->CL_Vm_Model->S_MeshGroup[GroupCount]->Normal_Data[vertexIndex].y = mesh->mNormals[vertexIndex].y;
					App->CL_Vm_Model->S_MeshGroup[GroupCount]->Normal_Data[vertexIndex].z = mesh->mNormals[vertexIndex].z;
				}

				//		App->CL_Model_Data->S_MeshGroup[Count]->FaceIndices[VC] = FaceNum;

				if (mesh->HasTextureCoords(0))
				{
					App->CL_Vm_Model->S_MeshGroup[GroupCount]->MapCord_Data[vertexIndex].u = mesh->mTextureCoords[0][vertexIndex].x;
					App->CL_Vm_Model->S_MeshGroup[GroupCount]->MapCord_Data[vertexIndex].v = 1 - mesh->mTextureCoords[0][vertexIndex].y;
				}

				VC++;
				i++;
				FaceNum++;
			}

			App->CL_Vm_Model->S_MeshGroup[GroupCount]->Face_Data[t].a = face->mIndices[0];
			App->CL_Vm_Model->S_MeshGroup[GroupCount]->Face_Data[t].b = face->mIndices[1];
			App->CL_Vm_Model->S_MeshGroup[GroupCount]->Face_Data[t].c = face->mIndices[2];

			App->CL_Vm_Model->S_MeshGroup[GroupCount]->FaceIndex_Data[t].Index = FaceIndexNum;

			FaceIndexNum++;

			t++;
		}

		App->CL_Vm_Model->S_MeshGroup[GroupCount]->GroupVertCount = mesh->mNumVertices;

		mTotalVertices = mTotalVertices + mesh->mNumVertices;
		GroupCount++;
	}
}
