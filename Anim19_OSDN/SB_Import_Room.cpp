#include "stdafx.h"
#include "GD19_App.h"
#include "SB_Import_Room.h"



SB_Import_Room::SB_Import_Room()
{
	Room_FileName[0] = 0,
	Room_Path_FileName[0] = 0,

	TempResourceGroup = "TemporyResourceGroup";
}


SB_Import_Room::~SB_Import_Room()
{
}

// *************************************************************************
// *						Room_Loader Terry Bernie					   *
// *************************************************************************
bool SB_Import_Room::Room_Loader(char* Extension, char* Extension2)
{
	int Result = Open_Room_File(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 1;
	}

	App->SBC_Scene->Clear_Level();

	Set_Paths();

	AddToScene();
	
	//App->CL_Vm_Model->Model_Loaded = 1;

	App->SBC_Scene->Area_Added = 1;

	App->Cl_Grid->Grid_SetVisible(1);

	App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;

	App->SBC_Player->Create_Player_Object();
	strcpy(App->SBC_Scene->SBC_Base_Player[0]->Player_Name, "Player_1");

	App->Cl_Bullet->Reset_Physics();
	App->SBC_Physics->Enable_Physics(1);

	App->SBC_Player->FileViewItem = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Players_Folder,"Player_1", 0);
	App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Areas_Folder,"Area_1", 0);
	App->SBC_FileView->Redraw_FileView();

	App->SBC_Scene->Scene_Loaded = 1;

	App->SBC_Scene->Area_Added = 1;

	App->Say("Model Loaded");
	return 1;
}

// *************************************************************************
// *						Set_Paths Terry Bernie						   *
// *************************************************************************
void SB_Import_Room::Set_Paths(void)
{
	char Model_FolderPath[255];
	char Path_FileName[255];

	strcpy(FileName, Room_FileName);
	strcpy(Path_FileName, Room_Path_FileName);

	// Get Texture path assumed at this point to be where model is
	int len1 = strlen(FileName);
	int len2 = strlen(Path_FileName);
	strcpy(Model_FolderPath, Path_FileName);
	Model_FolderPath[len2 - len1] = 0;

	strcpy(Texture_FolderPath, Model_FolderPath);

}

// *************************************************************************
// *					AddToScene Terry Bernie 						   *
// *************************************************************************
void SB_Import_Room::AddToScene(void)
{
	App->SBC_Aera->Add_Aera_To_Project(0, FileName, Texture_FolderPath);

}

// *************************************************************************
// *					Open_Room_File Terry Bernie						   *
// *************************************************************************
bool SB_Import_Room::Open_Room_File(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(Room_FileName, "");
	strcpy(Room_Path_FileName, "");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Room_Path_FileName;						// full path and file name
	ofn.nMaxFile = sizeof(Room_Path_FileName);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Room_FileName;						// Just File Name
	ofn.nMaxFileTitle = sizeof(Room_FileName);;
	ofn.lpstrInitialDir = StartDirectory;
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return 1;
	}
	return 0;
}