#include "stdafx.h"
#include "GD19_App.h"
#include "VM_Model.h"


VM_Model::VM_Model()
{
	VerticeCount = 0;
	NormalsCount = 0;
	FaceCount = 0;

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
}


VM_Model::~VM_Model()
{
}

// *************************************************************************
// *						Set_Paths Terry Bernie						   *
// *************************************************************************
void VM_Model::Set_Paths(void)
{
	strcpy(FileName, App->Cl_File_IO->Model_FileName);
	strcpy(Path_FileName, App->Cl_File_IO->Model_Path_FileName);

	// Get Texure path assumed at this point to be where model is
	int len1 = strlen(FileName);
	int len2 = strlen(Path_FileName);
	strcpy(Model_FolderPath, Path_FileName);
	Model_FolderPath[len2 - len1] = 0;

	strcpy(Texture_FolderPath, Model_FolderPath);

	strcpy(JustName, FileName);
	int Len = strlen(JustName);
	JustName[Len - 4] = 0;

//	App->Cl_Importer->RecentFileHistory_Update();
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

