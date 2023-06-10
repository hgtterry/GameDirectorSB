/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

#include "StdAfx.h"
#include "AB_App.h"
#include "SB_Export_Ogre3D.h"
#include "direct.h"

SB_Export_Ogre3D::SB_Export_Ogre3D(void)
{
	mDecompileFolder[0] = 0;
	mOgreMeshFileName[0] = 0;
	mOgreScriptFileName[0] = 0;
	mOgreSkellFileName[0] = 0;
	mOgreSkellTagName[0] = 0;
	NewDirectory[0] = 0;
	Directory_Name[0] = 0;
	mCurrentFolder[0] = 0;

	Add_Sub_Folder = 1;
}

SB_Export_Ogre3D::~SB_Export_Ogre3D(void)
{
}

// *************************************************************************
// *					Export_AssimpToOgre Terry Bernie  			 	   *
// *************************************************************************
bool SB_Export_Ogre3D::Export_AssimpToOgre(void)
{
	mDecompileFolder[0] = 0;
	mOgreMeshFileName[0] = 0;
	mOgreScriptFileName[0] = 0;
	mOgreSkellFileName[0] = 0;
	mOgreSkellTagName[0] = 0;
	Directory_Name[0] = 0;

	strcpy(Directory_Name, App->CLSB_Model->JustName);
	strcat(Directory_Name, "_Ogre");

	strcpy(App->CLSB_FileIO->BrowserMessage, "Select Folder To Place Ogre Files a sub folder will be created");
	int Test = App->CLSB_FileIO->StartBrowser(App->CLSB_Model->Model_FolderPath);
	if (Test == 0) { return 1; }

	App->CLSB_Exporter->Start_Export_Dlg();
	if (App->CLSB_Exporter->Is_Canceled == 1) { return 1; }

	//App->CL_PB->StartNewProgressBar();
	//App->CL_PB->Set_Progress("Building Scene/Game", 15);

	//App->CL_PB->Nudge("CreateDirectoryMesh");

	Test = CreateDirectoryMesh();
	if (Test == 0) { return 1; }

	strcpy(mOgreMeshFileName, App->CLSB_Model->JustName);
	strcpy(mOgreScriptFileName, App->CLSB_Model->JustName);
	strcpy(mOgreSkellFileName, App->CLSB_Model->JustName);
	strcpy(mOgreSkellTagName, App->CLSB_Model->JustName);

	strcat(mOgreMeshFileName, ".mesh");
	strcat(mOgreScriptFileName, ".material");
	strcat(mOgreSkellFileName, ".skeleton");

	//App->CL_PB->Nudge("DecompileTextures");

	DecompileTextures();

	//App->CL_PB->Nudge("CreateMaterialFile");
	//CreateMaterialFile(mOgreScriptFileName);

	//App->CL_PB->Nudge("Write_XML_File");
	//Write_XML_File();

	//// ---------------------------------------------------- 
	//char SourceFile[1024];
	//char OldFile[1024];

	//App->CL_PB->Nudge("Transfer");
	//strcpy(OldFile, XmlMeshFileName);

	//strcpy(SourceFile, mCurrentFolder);
	//strcat(SourceFile, "\\");
	//strcat(SourceFile, XmlMeshFileName);

	//strcpy(Source_Path_FileName, SourceFile);

	//int Len = strlen(XmlMeshFileName);
	//XmlMeshFileName[Len - 4] = 0;

	//char DestFile[1024];
	//strcpy(DestFile, mCurrentFolder);
	//strcat(DestFile, "\\");
	//strcat(DestFile, XmlMeshFileName);

	//strcpy(Dest_Path_FileName, DestFile);

	//App->CL_PB->Nudge("Convert_To_Mesh");
	//Convert_To_Mesh();

	//App->CL_PB->Nudge("Remove Temp Files");
	//remove(OldFile);

	//App->CL_PB->Nudge("Convert_To_Mesh");
	//App->CL_PB->Nudge("Convert_To_Mesh");
	//App->CL_PB->Nudge("Convert_To_Mesh");
	//App->CL_PB->Nudge("Convert_To_Mesh");

	//App->CL_PB->Stop_Progress_Bar("Export to Ogre Format Completed");

	return 1;
}

// *************************************************************************
// *							CreateDirectoryMesh			   		   	   *
// *************************************************************************
bool SB_Export_Ogre3D::CreateDirectoryMesh(void)
{
	/*if (App->CL_Export_Ogre3D->Export_As_RF)
	{
		strcpy(App->CL_Equity_SB->Pref_Ogre_Path, App->CL_FileIO->szSelectedDir);
		App->CL_Equity_SB->Write_Project_File()
	}*/

	if (Add_Sub_Folder == 0)
	{
		strcpy(NewDirectory, "");
		_chdir(App->CLSB_FileIO->szSelectedDir);
	}
	else
	{
		strcpy(NewDirectory, "\\");
		strcat(NewDirectory, Directory_Name);

		strcat(App->CLSB_FileIO->szSelectedDir, NewDirectory);

		if (_mkdir(App->CLSB_FileIO->szSelectedDir) == 0)
		{
			strcpy(mDecompileFolder, App->CLSB_FileIO->szSelectedDir);
			_chdir(App->CLSB_FileIO->szSelectedDir);
		}
		else
		{
			/*App->CL_Dialogs->YesNo("File Exsits", "Do you want to update File");

			bool Doit = App->CL_Dialogs->Canceled;
			if (Doit == 0)
			{
				strcpy(mDecompileFolder, App->CLSB_FileIO->szSelectedDir);
				_chdir(App->CLSB_FileIO->szSelectedDir);
			}
			else
			{
				return 0;
			}*/
		}

	}

	_getcwd(mCurrentFolder, MAX_PATH);

	return 1;
}

// *************************************************************************
// *			DecompileTextures  30/03/04   					   	   	   *
// *************************************************************************
bool SB_Export_Ogre3D::DecompileTextures(void)
{
	int MatCount = App->CLSB_Model->GroupCount;

	char FileName[255];

	int Loop = 0;
	while (Loop < MatCount)
	{
		strcpy(FileName, App->CLSB_Model->Group[Loop]->Text_FileName);

		HBITMAP Data;

		Data = App->CLSB_Model->Group[Loop]->Base_Bitmap;

		if (_stricmp(FileName + strlen(FileName) - 4, ".tga") == 0)
		{

			char mDirectory[MAX_PATH];
			_getcwd(mDirectory, MAX_PATH);
			strcat(mDirectory, "\\");
			strcat(mDirectory, FileName);

			//App->CL_Texture_Lib->WriteTGA(mDirectory, App->CLSB_Model->Group[Loop]->RF_Bitmap);

			//int Len = strlen(FileName);
			//FileName[Len - 4] = 0;
			//strcat(FileName, ".jpg");
			//
			//App->CL_Textures->HBITMAP_TO_BmpFile(Data, FileName, "");
			//geBitmap* Bitmap = geBitmap_CreateFromFile(FileName);

			//App->CL_Textures->Jpg_To_Tga24(FileName);

		}
		else if (_stricmp(FileName + strlen(FileName) - 4, ".png") == 0)
		{
			int Len = strlen(FileName);
			FileName[Len - 4] = 0;
			strcat(FileName, ".jpg");

			//App->CL_Textures->HBITMAP_TO_BmpFile(Data, FileName, "");
			//App->CL_Textures->Jpg_To_png24(FileName);
		}
		else if (_stricmp(FileName + strlen(FileName) - 4, ".jpg") == 0)
		{
			int Len = strlen(FileName);
			FileName[Len - 4] = 0;
			strcat(FileName, ".bmp");

			//App->CL_Textures->HBITMAP_TO_BmpFile(Data, FileName, "");
			//App->CL_Textures->Bmp_To_Jpg(FileName);
		}
		else
		{

			//App->CL_Textures->HBITMAP_TO_BmpFile(Data, FileName, "");
		}

		Loop++;
	}
	return 1;
}
