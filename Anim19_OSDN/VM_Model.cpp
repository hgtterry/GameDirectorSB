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

	//strcpy(Model_FullPath, Model_FolderPath);

	strcpy(JustName, FileName);
	int Len = strlen(JustName);
	JustName[Len - 4] = 0;

//	App->Cl_Importer->RecentFileHistory_Update();
}
