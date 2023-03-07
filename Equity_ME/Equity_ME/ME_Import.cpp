/*
Copyright (c) 2022 Equity_ME Model Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "ME_Import.h"


ME_Import::ME_Import()
{
}


ME_Import::~ME_Import()
{
}

// *************************************************************************
// *						Set_Equity Terry Flanigan					   *
// *************************************************************************
void ME_Import::Set_Equity(void)
{
	App->CL_Model->Model_Loaded = 1;

	App->CL_Grid->Zoom();

	char TitleBar[260];
	strcpy(TitleBar, "Equity_ME");
	strcat(TitleBar, "    ");
	strcat(TitleBar, App->CL_Model->Path_FileName);
	SetWindowText(App->MainHwnd, TitleBar);

	////Set_Equity();
	Ogre::Root::getSingletonPtr()->renderOneFrame();

	App->CL_FileView->Change_Level_Name();

	App->CL_TopBar->Set_Loaded();

	App->CL_FileView->ExpandRoot();

	App->CL_FileView->SelectItem(App->CL_Model->Group[0]->ListView_Item);  // Select First Group

	App->CL_Grid->Zoom();

	//App->Say("Model Loaded");
}

// *************************************************************************
// *						Assimp_Loader Terry Bernie					   *
// *************************************************************************
bool ME_Import::Assimp_Loader(char* Extension, char* Extension2)
{
	int Result = App->CL_FileIO->Open_File_Model(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 0;
	}

	App->CL_Model->Clear_Model_And_Reset();

	char Model_Path_And_File[MAX_PATH];
	strcpy(Model_Path_And_File, App->CL_FileIO->Get_Model_Path_File_Name().c_str());

	App->CL_Model->Set_Paths();

	bool Test = App->CL_Assimp->LoadFile(Model_Path_And_File);
	if (Test == 0)
	{
		App->Say_Win("Failed To Load");
		return 0;
	}

	App->CL_Model->Model_Type = Enums::LoadedFile_Assimp;

	Set_Equity();
	
	App->CL_Recent_Files->RecentFile_Models_History_Update();

	App->CL_Prefs->Update_User_File(Model_Path_And_File);

	return 1;
}

// *************************************************************************
// *					RFActor_Loader Terry Terry Berine				   *
// *************************************************************************
bool ME_Import::RFActor_Loader(void)
{
	int Result = App->CL_FileIO->Open_File_Model("RF Actor   *.act\0*.act\0", "RF Actor", NULL);
	if (Result == 0)
	{
		return 0;
	}

	
	App->CL_Model->Clear_Model_And_Reset();

	char Model_Path_And_File[MAX_PATH];
	strcpy(Model_Path_And_File, App->CL_FileIO->Get_Model_Path_File_Name().c_str());

	App->CL_Model->Set_Paths();

	App->CL_Genesis3D->LoadActor();

	App->CL_Model->Model_Type = Enums::LoadedFile_Actor;

	Set_Equity();

	App->CL_Recent_Files->RecentFile_Models_History_Update();
	App->CL_Prefs->Update_User_File(Model_Path_And_File);
	return 1;
}

// *************************************************************************
// *						Ogre_Loader Terry Bernie					   *
// *************************************************************************
bool ME_Import::Ogre_Loader(char* Extension, char* Extension2)
{
	int Result = App->CL_FileIO->Open_File_Model(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 1;
	}

	App->CL_Model->Clear_Model_And_Reset();

	char Model_Path_And_File[MAX_PATH];
	strcpy(Model_Path_And_File, App->CL_FileIO->Get_Model_Path_File_Name().c_str());

	App->CL_Model->Set_Paths();

	// Just for Ogre3d
	strcpy(App->CL_Model->JustName, App->CL_Model->FileName);
	int Len = strlen(App->CL_Model->JustName);
	App->CL_Model->JustName[Len - 5] = 0;


	App->CL_Ogre3D->Load_OgreModel(); // Load Ogre Model

	App->CL_Model->Model_Type = Enums::LoadedFile_Assimp;

	//App->CL_Model_Data->Render_Mode = Render_As_Assimp;

	App->CL_Model->ItsAnOgreModel = 1;

	App->CL_Model->Model_Loaded = 1;

	Set_Equity();

	Ogre::Root::getSingletonPtr()->renderOneFrame();
	Ogre::Root::getSingletonPtr()->renderOneFrame();

	App->CL_Recent_Files->RecentFile_Models_History_Update();
	App->CL_Prefs->Update_User_File(Model_Path_And_File);
	//-------------------------------
	//if (App->CL_Import_Ogre->NoMaterialFileFound == 1)
	//{
	//	App->CL_Dialogs->YesNo("No Textures", "Do you want to load an Ogre Config File now");
	//	bool Doit = App->CL_Dialogs->Canceled;
	//	if (Doit == 0)
	//	{
	//		/*char LookBuf[1024];
	//		strcpy(LookBuf,App->CL_Model_Data->Model_FullPath);

	//		int test = App->CL_FileIO->SearchFolders(LookBuf,"resources.cfg");
	//		if (test == 1)*/
	//		{
	//			App->Cl_Importer->Ogre_ResourceFile_Loader("Ogre Config   *.cfg\0*.cfg\0", "Ogre Config");
	//		}
	//	}
	//	else
	//	{
	//		return 1;
	//	}
	//}

	return 1;
}

// *************************************************************************
// *					Reload_FromResentFiles Terry Bernie				   *
// *************************************************************************
void ME_Import::Reload_FromResentFiles(char* ResentPathAndFile)
{

	// Check Recent File Exsists
	bool Result = App->CL_FileIO->Search_For_Folder(ResentPathAndFile);
	if (Result == 0)
	{
		App->Say(" Can Not Find File:- This may be due to it has been deleted or renamed");
		return;
	}

	App->CL_Model->Clear_Model_And_Reset();

	strcpy(App->CL_FileIO->Model_Path_FileName, ResentPathAndFile);

	char mPathAndFile[1024];
	char mJustFileName[1024];

	strcpy(mPathAndFile, ResentPathAndFile); // Full Path and File

	char TestName;
	App->CL_FileIO->CheckPath(mPathAndFile, mPathAndFile, &TestName);

	strcpy(mJustFileName, &TestName); // Just File Name

	strcpy(App->CL_FileIO->Model_FileName, mJustFileName);

	App->CL_Model->Set_Paths();

	//--------------------------------------------------------------- Genesis Actor
	if (_stricmp(mJustFileName + strlen(mJustFileName) - 5, ".Wepf") == 0)
	{

		App->CL_Equity_SB->Read_Project_File(App->CL_FileIO->Model_Path_FileName);
		App->CL_Equity_SB->Load_File_Wepf();

		App->CL_Prefs->Update_User_File(App->CL_FileIO->Model_Path_FileName);
		return;
	}
	
	//--------------------------------------------------------------- Genesis Actor
	if (_stricmp(mJustFileName + strlen(mJustFileName) - 4, ".act") == 0)
	{

		App->CL_Genesis3D->LoadActor();
		
		App->CL_Model->Model_Type = Enums::LoadedFile_Actor;

		Set_Equity();

		App->CL_Recent_Files->RecentFile_Models_History_Update();
		App->CL_Prefs->Update_User_File(App->CL_FileIO->Model_Path_FileName);
		return;
	}

	//--------------------------------------------------------------- Orge3D Model
	if (stricmp(mJustFileName + strlen(mJustFileName) - 5, ".mesh") == 0)
	{
		
		App->CL_Ogre3D->Load_OgreModel(); // Load Ogre Model

											   // Just for Ogre3d
		strcpy(App->CL_Model->JustName, App->CL_Model->FileName);
		int Len = strlen(App->CL_Model->JustName);
		App->CL_Model->JustName[Len - 5] = 0;

		App->CL_Model->Model_Type = Enums::LoadedFile_Assimp;
		
		App->CL_Model->ItsAnOgreModel = 1;
		
		Set_Equity();

		App->CL_Recent_Files->RecentFile_Models_History_Update();
		App->CL_Prefs->Update_User_File(App->CL_FileIO->Model_Path_FileName);

		Ogre::Root::getSingletonPtr()->renderOneFrame();
		Ogre::Root::getSingletonPtr()->renderOneFrame();

		//-------------------------------
		//if (App->CL_Import_Ogre->NoMaterialFileFound == 1)
		//{
		//	App->CL_Dialogs->YesNo("No Textures", "Do you want to load an Ogre Config File now");
		//	bool Doit = App->CL_Dialogs->Canceled;
		//	if (Doit == 0)
		//	{
		//		/*char LookBuf[1024];
		//		strcpy(LookBuf,App->CL_Model_Data->Model_FullPath);

		//		int test = App->CL_FileIO->SearchFolders(LookBuf,"resources.cfg");
		//		if (test == 1)*/
		//		{
		//			App->Cl_Importer->Ogre_ResourceFile_Loader("Ogre Config   *.cfg\0*.cfg\0", "Ogre Config");
		//		}
		//	}
		//	else
		//	{
		//		return;
		//	}
		//}

		return;
	}

	// Fall through for assimp
	bool Test = App->CL_Assimp->LoadFile(ResentPathAndFile);
	if (Test == 0)
	{
		App->Say("Can Not Load File");
		return;
	}

	App->CL_Model->Model_Type = Enums::LoadedFile_Assimp;

	Set_Equity();

	App->CL_Recent_Files->RecentFile_Models_History_Update();
	App->CL_Prefs->Update_User_File(App->CL_FileIO->Model_Path_FileName);
}

// *************************************************************************
// *					WorldEditor_Loader Terry Terry Berine			   *
// *************************************************************************
bool ME_Import::WorldEditor_Loader(void)
{

	App->CL_Equity_SB->Start_WE_import();

	return 1;
}


