/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "AB_App.h"
#include "resource.h"
#include "SB_Loader.h"


#include "RAM.h"

SB_Loader::SB_Loader(void)
{
	FileName[0] = 0;
	Path_FileName[0] = 0;
	szSelectedDir[0] = 0;

	RightGroups_Hwnd = nullptr;

	NameCount = 0;
}

SB_Loader::~SB_Loader(void)
{
}


// *************************************************************************
// *			Assimp_Loader:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Loader::Assimp_Loader(char* Extension, char* Extension2)
{
	int Result = App->CLSB_FileIO->Open_File_Model(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return;
	}

	App->CLSB_Model->Clear_Model_And_Reset();

	strcpy(App->CLSB_Loader->Path_FileName, App->CLSB_FileIO->PathFileName);
	strcpy(App->CLSB_Loader->FileName, App->CLSB_FileIO->FileName);

	App->CLSB_Model->Set_Paths();

	App->CLSB_Assimp->DoTextures = 1;

	bool Test = App->CLSB_Assimp->LoadFile(App->CLSB_Loader->Path_FileName);
	if (Test == 0)
	{
		App->Say("Failed To Load");
		return;
	}

	App->CLSB_Model->Model_Type = Enums::LoadedFile_Assimp;

	App->CLSB_Model->Set_Equity();

	App->CLSB_Grid->Reset_View();
	App->CLSB_Ogre->RenderListener->RX = 0;
	App->CLSB_Ogre->RenderListener->RZ = 0;


	//App->CL_Recent_Files->RecentFile_Models_History_Update();
	//App->CL_Prefs->Update_User_File(Model_Path_And_File);

	return;
}

// *************************************************************************
// *			Load_Project_File:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_Loader::Read_Project_File(char* Path_And_File)
{
	char chr_Tag1[MAX_PATH];
	char chr_Tag2[MAX_PATH];

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	App->CLSB_Ini->SetPathName(Path_And_File);

	App->CLSB_Ini->GetString("World_Data", "Pref_WE_JustFileName", chr_Tag1, MAX_PATH);
	strcpy(WE_JustFileName, chr_Tag1);

	App->CLSB_Ini->GetString("World_Data", "G3ds_Path_FileName", chr_Tag1, MAX_PATH);
	strcpy(WE_Path_FileName, chr_Tag1);

	App->CLSB_Ini->GetString("World_Data", "Txl_Path_FileName", chr_Tag2, MAX_PATH);
	strcpy(Txl_Path_FileName, chr_Tag2);


	/*if (App->Is_WorldEditor == 1)
	{
		Ogre::Vector4 V4 = Ogre::Vector4::ZERO;

		App->CL_Ini->GetString("Special", "Position", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f %f %f", &V4.x, &V4.y, &V4.z);
		App->CL_Scene->Start_Cam_Pos = Ogre::Vector3(V4.x, V4.y, V4.z);

		App->CL_Ini->GetString("Special", "Angles", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f %f %f", &V4.x, &V4.y, &V4.z);
		App->CL_Scene->Start_Cam_Angles = Ogre::Vector3(V4.x, V4.y+140, V4.z);

	}*/

	return 1;
}

// *************************************************************************
// *			Load_File_Wepf:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Loader::Load_File_Wepf()
{
	App->CLSB_Model->Clear_Model_And_Reset();

	App->CLSB_Assimp->SelectedPreset = 8 + 8388608+64 + aiProcess_PreTransformVertices;

	App->CLSB_Assimp->DoTextures = 0;

	bool Test = App->CLSB_Assimp->LoadFile(WE_Path_FileName);
	if (Test == 0)
	{
		App->Say("Failed To Load");
		return;
	}

	App->CLSB_Model->Set_Paths();

	bool test = LoadTextures_TXL();
	if (test == 0)
	{
		App->Say("Failed Aborting");
		return;
	}

	App->CLSB_Model->Set_Equity();

	Adjust();

	Ogre::Root::getSingletonPtr()->renderOneFrame();
	Ogre::Root::getSingletonPtr()->renderOneFrame();

	App->CLSB_Model->Model_Type = Enums::LoadedFile_Assimp;

	App->CLSB_Camera->Reset_Orientation();
	App->CLSB_Camera->Set_Camera_Mode(Enums::CamDetached);
	//App->CLSB_Camera->Zero_View();

	//App->CL_Recent_Files->RecentFile_Projects_History_Update();*/

	//App->CL_Export_Ogre->Export_AssimpToOgre();

	//App->CL_Player->Create_Player_Object();



	//App->CL_Physics->Reset_Physics();
	//App->CL_Ogre->OgreListener->Dubug_Physics_Draw = 1;

	//App->CL_Scene->B_Area[0]->Area_Node->setPosition(0, 0, 0);

}

// *************************************************************************
// *						Adjust Terry Flanigan						   *
// *************************************************************************
void SB_Loader::Adjust()
{
	Rotate_Z_Model(90);
	//Rotate_X_Model(-90);
	Centre_Model_Mid();

	//Translate_Model(0,0,-240);
	//Brush  = (*(Level->Entities))[j].CreateActorBrush(ActorFile, ActorDir, PawnIni);
	
	if (App->CLSB_Equity->mAutoLoad == 0)
	{
		App->CLSB_Grid->Reset_View();
	}
}

// *************************************************************************
// *		LoadTextures_TXL:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Loader::LoadTextures_TXL()
{
	geVFile* VFS = NULL;
	geVFile_Finder* Finder = NULL;
	
	NameCount = 0;

	VFS = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_VIRTUAL, Txl_Path_FileName, NULL, GE_VFILE_OPEN_READONLY | GE_VFILE_OPEN_DIRECTORY);
	if (!VFS)
	{
		App->Say("Could not open TXL file", Txl_Path_FileName);
		return 0;
	}

	Finder = geVFile_CreateFinder(VFS, "*.*");
	if (!Finder)
	{
		App->Say("Could not create Finder *.* ");
		geVFile_Close(VFS);
		return 0;
	}

	
	BitMap_Names.resize(100);

	while (geVFile_FinderGetNextFile(Finder) != GE_FALSE)
	{
		geVFile_Properties	Properties;

		geVFile_FinderGetProperties(Finder, &Properties);

		strcpy(BitMap_Names[NameCount].Name, Properties.Name);

		NameCount++;
	}

	Copy_Texture_Names();

	Check_for_Textures(VFS);

	geVFile_Close(VFS);

	return 1;
}


// *************************************************************************
// *	  	Copy_Texture_Names:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Loader::Copy_Texture_Names()
{
	int Count = 0;
	int GroupCount = App->CLSB_Model->GroupCount;

	while (Count < GroupCount)
	{
		strcpy(App->CLSB_Model->Group[Count]->Text_FileName, App->CLSB_Model->Group[Count]->Equity_Text_FileName);
		Count++;
	}
}

// *************************************************************************
// *	  	Check_for_Textures:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
int SB_Loader::Check_for_Textures(geVFile* BaseFile)
{
	int Count = 0;
	int GroupCount = App->CLSB_Model->GroupCount;

	char JustName[255];

	while (Count < GroupCount)
	{
		strcpy(JustName, App->CLSB_Model->Group[Count]->Equity_Text_FileName);
		int Len = strlen(JustName);
		JustName[Len - 4] = 0;

		bool test = Check_in_Txl(JustName);

		if (test == 1)
		{
			if (!AddTexture(BaseFile, JustName, Count))
			{
				App->Say("Error");
				return 0;
			}
		}
		else
		{
			App->Say("unMatched");
			App->Say(JustName);
		}

		Count++;
	}

	return -1;
}

// *************************************************************************
// *			AddTexture:- Terry and Hazel Flanigan 2023		  		   *
// *************************************************************************
bool SB_Loader::AddTexture(geVFile* BaseFile, const char* Path, int GroupIndex)
{

	geBitmap* Bitmap;

	geVFile* File;
	char			FileName[_MAX_FNAME];
	char* Name;

	Bitmap = NULL;
	File = NULL;

	_splitpath(Path, NULL, NULL, FileName, NULL);
	Name = _strdup(FileName);
	if (!Name)
	{
		App->Say("Memory allocation error processing %s");
		return FALSE;
	}

	if (BaseFile)
		File = geVFile_Open(BaseFile, Path, GE_VFILE_OPEN_READONLY);
	else
		File = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, Path, NULL, GE_VFILE_OPEN_READONLY);

	if (!File)
	{
		//NonFatalError("Could not open %s", Path);
		App->Say("Could not open %s");
		return TRUE;
	}


	Bitmap = geBitmap_CreateFromFile(File);

	if (geBitmap_HasAlpha(Bitmap))
	{
		App->CLSB_Model->Group[GroupIndex]->RF_Bitmap = Bitmap;
	}


	HWND	PreviewWnd;
	HBITMAP	hbm;
	HDC		hDC;

	PreviewWnd = GetDlgItem(RightGroups_Hwnd, IDC_BASETEXTURE2);
	hDC = GetDC(PreviewWnd);
	hbm = CreateHBitmapFromgeBitmap(Bitmap, hDC);

	App->CLSB_Model->Group[GroupIndex]->Base_Bitmap = hbm;

	char TempTextureFile_BMP[1024];
	strcpy(TempTextureFile_BMP, App->WorldEditor_Directory);
	strcat(TempTextureFile_BMP, "\\");
	strcat(TempTextureFile_BMP, "TextureLoad.bmp");

	App->CLSB_Textures->Genesis_WriteToBmp(Bitmap, TempTextureFile_BMP);

	App->CLSB_Textures->Soil_Load_Texture(App->CLSB_Ogre->RenderListener->g_Texture, TempTextureFile_BMP, GroupIndex);

	geVFile_Close(File);

	DeleteFile((LPCTSTR)TempTextureFile_BMP);
	return TRUE;
}

// *************************************************************************
// *	CreateHBitmapFromgeBitmap:- Terry and Hazel Flanigan 2023 		   *
// *************************************************************************
HBITMAP SB_Loader::CreateHBitmapFromgeBitmap(geBitmap* Bitmap, HDC hdc)
{
	geBitmap* Lock;
	gePixelFormat Format;
	geBitmap_Info info;
	HBITMAP hbm = NULL;

	// <> choose format to be 8,16,or 24, whichever is closest to Bitmap
	Format = GE_PIXELFORMAT_24BIT_BGR;

	if (geBitmap_GetBits(Bitmap))
	{
		Lock = Bitmap;
	}
	else
	{
		if (!geBitmap_LockForRead(Bitmap, &Lock, 0, 0, Format, GE_FALSE, 0))
		{
			return NULL;
		}
	}

	geBitmap_GetInfo(Lock, &info, NULL);

	if (info.Format != Format)
		return NULL;

	{
		void* bits;
		BITMAPINFOHEADER bmih;
		int pelbytes;

		pelbytes = gePixelFormat_BytesPerPel(Format);
		bits = geBitmap_GetBits(Lock);

		bmih.biSize = sizeof(bmih);
		bmih.biHeight = -info.Height;
		bmih.biPlanes = 1;
		bmih.biBitCount = 24;
		bmih.biCompression = BI_RGB;
		bmih.biSizeImage = 0;
		bmih.biXPelsPerMeter = bmih.biYPelsPerMeter = 10000;
		bmih.biClrUsed = bmih.biClrImportant = 0;

		if ((info.Stride * pelbytes) == (((info.Stride * pelbytes) + 3) & (~3)))
		{
			bmih.biWidth = info.Stride;
			hbm = CreateDIBitmap(hdc, &bmih, CBM_INIT, bits, (BITMAPINFO*)&bmih, DIB_RGB_COLORS);
		}
		else
		{
			void* newbits;
			int Stride;

			bmih.biWidth = info.Width;
			Stride = (((info.Width * pelbytes) + 3) & (~3));
			newbits = geRam_Allocate(Stride * info.Height);
			if (newbits)
			{
				char* newptr, * oldptr;
				int y;

				newptr = (char*)newbits;
				oldptr = (char*)bits;
				for (y = 0; y < info.Height; y++)
				{
					memcpy(newptr, oldptr, (info.Width) * pelbytes);
					oldptr += info.Stride * pelbytes;
					newptr += Stride;
				}
				hbm = CreateDIBitmap(hdc, &bmih, CBM_INIT, newbits, (BITMAPINFO*)&bmih, DIB_RGB_COLORS);
				geRam_Free(newbits);
			}
		}
	}

	if (Lock != Bitmap)
	{
		geBitmap_UnLock(Lock);
	}

	return hbm;
}

// *************************************************************************
// *	  		Check_in_Txl:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Loader::Check_in_Txl(char* FileName)
{
	int loop = 0;
	int TxlNameCount = NameCount;

	while (loop < TxlNameCount)
	{
		int Result = 1;
		Result = strcmp(FileName, BitMap_Names[loop].Name);
		if (Result == 0)
		{
			return 1;
		}

		loop++;
	}

	return 0;
}

// *************************************************************************
// *				OpenFile:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Loader::Open_File_Model(const char* Extension, const char* Title, const char* StartDirectory)
{

	FileName[0] = 0;
	Path_FileName[0] = 0;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Path_FileName;						// full path and file name
	ofn.nMaxFile = sizeof(Path_FileName);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = FileName;						// Just File Name
	ofn.nMaxFileTitle = sizeof(FileName);;
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

// *************************************************************************
// *			Start_Groups:- Terry and Hazel Flanigan 2023	  		   *
// *************************************************************************
bool SB_Loader::Start_Groups_Dialog()
{
//	RightGroups_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_RIGHTGROUPS, App->MainHwnd, (DLGPROC)Groups_Proc);
	ShowWindow(RightGroups_Hwnd, 0);
	return 1;
}

// *************************************************************************
// *			Groups_Proc:- Terry and Hazel Flanigan 2023		  		   *
// *************************************************************************
LRESULT CALLBACK SB_Loader::Groups_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		
	}

	case WM_CTLCOLORSTATIC:
	{
		
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_CLOSE:
	{
		/*ShowWindow(App->CL_Groups->RightGroups_Hwnd, 0);
		App->CL_Groups->RightGroups_Visable = 0;
		CheckMenuItem(App->mMenu, ID_WINDOWS_GROUPS, MF_BYCOMMAND | MF_UNCHECKED);*/
		break;
	}


	case WM_NOTIFY:
	{
		

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		
	}

	}
	return FALSE;
}

// *************************************************************************
// *	  				Rotate_Z_Model Terry Bernie						   *
// *************************************************************************
void SB_Loader::Rotate_Z_Model(float Z)
{
	if (App->CLSB_Model->Model_Loaded == 1)
	{

		Ogre::Vector3 Centre;

		Centre.x = App->CLSB_Model->S_BoundingBox[0]->Centre[0].x;
		Centre.y = App->CLSB_Model->S_BoundingBox[0]->Centre[0].y;
		Centre.z = App->CLSB_Model->S_BoundingBox[0]->Centre[0].z;

		Ogre::Vector3 Rotate;
		Rotate.x = 0;
		Rotate.y = 0;
		Rotate.z = Z;


		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CLSB_Model->Get_Groupt_Count();

		while (Count < GroupCount)
		{
			VertCount = 0;
			while (VertCount < App->CLSB_Model->Group[Count]->GroupVertCount)
			{
				Ogre::Vector3 VertPos;
				Ogre::Vector3 RotatedVert;

				VertPos.x = App->CLSB_Model->Group[Count]->vertex_Data[VertCount].x;
				VertPos.y = App->CLSB_Model->Group[Count]->vertex_Data[VertCount].y;
				VertPos.z = App->CLSB_Model->Group[Count]->vertex_Data[VertCount].z;

				if (Rotate.z != 0) // Dont bother if Zero
				{
					RotatedVert = (Ogre::Quaternion(Ogre::Degree(Rotate.z), Ogre::Vector3::UNIT_X) * (VertPos - Centre));
				}
				else
				{
					RotatedVert = VertPos - Centre;
				}

				RotatedVert += Centre;

				App->CLSB_Model->Group[Count]->vertex_Data[VertCount].x = RotatedVert.x;
				App->CLSB_Model->Group[Count]->vertex_Data[VertCount].y = RotatedVert.y;
				App->CLSB_Model->Group[Count]->vertex_Data[VertCount].z = RotatedVert.z;

				VertCount++;
			}
			Count++;
		}

		App->CLSB_Model->Set_BondingBox_Model(0);
	}
}

// *************************************************************************
// *	  					Rotate_X_Model Terry Bernie					   *
// *************************************************************************
void SB_Loader::Rotate_X_Model(float X)
{
	if (App->CLSB_Model->Model_Loaded == 1)
	{

		Ogre::Vector3 Centre;

		Centre.x = App->CLSB_Model->S_BoundingBox[0]->Centre[0].x;
		Centre.y = App->CLSB_Model->S_BoundingBox[0]->Centre[0].y;
		Centre.z = App->CLSB_Model->S_BoundingBox[0]->Centre[0].z;

		Ogre::Vector3 Rotate;
		Rotate.x = X;
		Rotate.y = 0;
		Rotate.z = 0;

		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CLSB_Model->Get_Groupt_Count();

		while (Count < GroupCount)
		{
			VertCount = 0;
			while (VertCount < App->CLSB_Model->Group[Count]->GroupVertCount)
			{
				Ogre::Vector3 VertPos;
				Ogre::Vector3 RotatedVert;

				VertPos.x = App->CLSB_Model->Group[Count]->vertex_Data[VertCount].x;
				VertPos.y = App->CLSB_Model->Group[Count]->vertex_Data[VertCount].y;
				VertPos.z = App->CLSB_Model->Group[Count]->vertex_Data[VertCount].z;

				if (Rotate.x != 0) // Dont bother if Zero
				{
					RotatedVert = (Ogre::Quaternion(Ogre::Degree(Rotate.x), Ogre::Vector3::UNIT_Y) * (VertPos - Centre));
				}
				else
				{
					RotatedVert = VertPos - Centre;
				}

				RotatedVert += Centre;

				App->CLSB_Model->Group[Count]->vertex_Data[VertCount].x = RotatedVert.x;
				App->CLSB_Model->Group[Count]->vertex_Data[VertCount].y = RotatedVert.y;
				App->CLSB_Model->Group[Count]->vertex_Data[VertCount].z = RotatedVert.z;

				VertCount++;
			}
			Count++;
		}

		App->CLSB_Model->Set_BondingBox_Model(0);
	}
}

// *************************************************************************
// *	  				Centre_Model_Mid Terry Bernie					   *
// *************************************************************************
void SB_Loader::Centre_Model_Mid(void)
{
	if (App->CLSB_Model->Model_Loaded == 1)
	{
		float X = -App->CLSB_Model->S_BoundingBox[0]->Centre[0].x;
		float Y = -App->CLSB_Model->S_BoundingBox[0]->Centre[0].y;
		float Z = -App->CLSB_Model->S_BoundingBox[0]->Centre[0].z;

		int Count = 0;
		int VertCount = 0;
		int Index = App->CLSB_Model->Get_Groupt_Count();

		while (Count < Index)
		{
			VertCount = 0;
			while (VertCount < App->CLSB_Model->Group[Count]->GroupVertCount)
			{
				App->CLSB_Model->Group[Count]->vertex_Data[VertCount].x += X;
				App->CLSB_Model->Group[Count]->vertex_Data[VertCount].y += Y;
				App->CLSB_Model->Group[Count]->vertex_Data[VertCount].z += Z;
				VertCount++;
			}
			Count++;
		}

		App->CLSB_Model->Set_BondingBox_Model(0);

	}
}

// *************************************************************************
// *	  				Translate_Model Terry Bernie					   *
// *************************************************************************
void SB_Loader::Translate_Model(float X, float Y, float Z)
{
	if (App->CLSB_Model->Model_Loaded == 1)
	{
		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CLSB_Model->Get_Groupt_Count();

		while (Count < GroupCount)
		{
			VertCount = 0;
			while (VertCount < App->CLSB_Model->Group[Count]->GroupVertCount)
			{
				App->CLSB_Model->Group[Count]->vertex_Data[VertCount].x += X;
				App->CLSB_Model->Group[Count]->vertex_Data[VertCount].y += Y;
				App->CLSB_Model->Group[Count]->vertex_Data[VertCount].z += Z;
				VertCount++;
			}
			Count++;
		}

		App->CLSB_Model->Set_BondingBox_Model(0);
	}
}

#include "FaceList.h"

typedef Gint16 geBody_Index;
// *************************************************************************
// *	  			Load_ActorWorld:- Terry and Hazel Flanigan 2023        *
// *************************************************************************
bool SB_Loader::Load_ActorWorld()
{
	char* ActorFile;

	char filename[255];
	geVFile* ActFile;
	geActor_Def* mActorDef;
	geActor* Actor;
	CString ActorRotStr;
	geVec3d ActorRotation;
	geXForm3d thePosition;
	geFloat Scale;
	CString ActorScale;

	ActFile = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, filename, NULL, GE_VFILE_OPEN_READONLY);
	if (ActFile)
	{
		mActorDef = geActor_DefCreateFromFile(ActFile);
		if (!mActorDef)
		{
			geVFile_Close(ActFile);
			AfxMessageBox("Failed to create ActorDef", MB_ICONEXCLAMATION | MB_OK);
			return NULL;
		}
	}
	else
	{
		//		AfxMessageBox("Can't open actor file", MB_ICONEXCLAMATION | MB_OK);
		return NULL;
	}
	geVFile_Close(ActFile);

	Actor = geActor_Create(mActorDef);

	geVec3d_Clear(&ActorRotation);	// Initialize
	Scale = 1.0f;
	geXForm3d_SetIdentity(&thePosition);

	geBody* B = geActor_GetBody(mActorDef);

	if (!B)
	{
		if (mActorDef != NULL)
			geActor_DefDestroy(&mActorDef);

		if (Actor != NULL)
			geActor_Destroy(&Actor);

		return NULL;
	}


	FaceList* fl;
	Face* f;

	{
		int i, NumFaces = 0;
		geBody_Index Index;
		geBody_Index BoneIndex;
		char BoneName[255];
		geXForm3d Transform;
		const char* BName;


		//		NumFaces = B->SkinFaces[0].FaceCount;

		// create the facelist for the brush
		fl = FaceList_Create(NumFaces);
		if (!fl)
		{
			char szError[256];
			sprintf(szError, "Error creating FaceList: '%s'", ActorFile);
			AfxMessageBox(szError, MB_ICONEXCLAMATION | MB_OK);

			if (mActorDef != NULL)
				geActor_DefDestroy(&mActorDef);
			if (Actor != NULL)
				geActor_Destroy(&Actor);

			return NULL;
		}

		for (i = 0; i < NumFaces; i++)
		{
			geVec3d FaceVerts[3];

			for (int j = 0; j < 3; j++)
			{
				// have to reverse vertex order for some reason
//				Index = B->SkinFaces[0].FaceArray[i].VtxIndex[j];
//				geVec3d_Copy(&(B->XSkinVertexArray[Index].XPoint),&(FaceVerts[2-j]));

				// transform vertex point by bone transformation
//				BoneIndex = B->XSkinVertexArray[Index].BoneIndex;
//				BName = geStrBlock_GetString(B->BoneNames, BoneIndex);
//				strcpy(BoneName,BName);
//				geActor_GetBoneTransform(Actor, BoneName, &Transform);
//				geXForm3d_Transform(&Transform,&(FaceVerts[2-j]),&(FaceVerts[2-j]));

//				geVec3d_Scale(&FaceVerts[2-j], Scale, &FaceVerts[2-j]);
			}

			// create faces and add them to the facelist
			f = Face_Create(3, FaceVerts, 0);

			if (f)
				FaceList_AddFace(fl, f);
			else
			{
				// hack; if original face has no normal create a valid face instead
				geVec3d_Set(&(FaceVerts[0]), 10000.0f, 10000.0f, 10000.0f);
				geVec3d_Set(&(FaceVerts[1]), 10001.0f, 10000.0f, 10000.0f);
				geVec3d_Set(&(FaceVerts[2]), 10000.0f, 10001.0f, 10000.0f);

				f = Face_Create(3, FaceVerts, 0);

				if (f)
					FaceList_AddFace(fl, f);
			}
		}
	}

	Brush* mActorBrush;

	mActorBrush = Brush_Create(BRUSH_LEAF, fl, NULL);
	if (!mActorBrush)
	{
		char szError[256];
		sprintf(szError, "Error creating brush: '%s'", ActorFile);
		AfxMessageBox(szError, MB_ICONEXCLAMATION | MB_OK);

		FaceList_Destroy(&fl);

		if (mActorDef != NULL)
			geActor_DefDestroy(&mActorDef);

		if (Actor != NULL)
			geActor_Destroy(&Actor);

		return NULL;
	}

	Brush_SetName(mActorBrush, ActorFile);

	if (mActorDef != NULL)
		geActor_DefDestroy(&mActorDef);

	if (Actor != NULL)
		geActor_Destroy(&Actor);

	// move the brush to the right position

	geVec3d	mOrigin;
	Brush_Move(mActorBrush, &mOrigin);

	return 1;
}
