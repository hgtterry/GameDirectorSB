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
#include "WV_App.h"
#include "resource.h"
#include "WV_Loader.h"

#include "RAM.h"

WV_Loader::WV_Loader(void)
{
	FileName[0] = 0;
	Path_FileName[0] = 0;
	szSelectedDir[0] = 0;

	RightGroups_Hwnd = nullptr;

	NameCount = 0;
}

WV_Loader::~WV_Loader(void)
{
}

// *************************************************************************
// *			Load_Project_File:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool WV_Loader::Read_Project_File(char* Path_And_File)
{
	char chr_Tag1[MAX_PATH]{ 0 };
	char chr_Tag2[MAX_PATH]{ 0 };

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	App->CL_Ini->SetPathName(Path_And_File);

	App->CL_Ini->GetString("World_Data", "Pref_WE_JustFileName", chr_Tag1, MAX_PATH);
	strcpy(WE_JustFileName, chr_Tag1);

	App->CL_Ini->GetString("World_Data", "G3ds_Path_FileName", chr_Tag1, MAX_PATH);
	strcpy(WE_Path_FileName, chr_Tag1);

	App->CL_Ini->GetString("World_Data", "Txl_Path_FileName", chr_Tag2, MAX_PATH);
	strcpy(Txl_Path_FileName, chr_Tag2);


	if (App->Is_WorldEditor == 1)
	{
		Ogre::Vector4 V4 = Ogre::Vector4::ZERO;

		App->CL_Ini->GetString("Special", "Position", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f %f %f", &V4.x, &V4.y, &V4.z);
		App->CL_Scene->Start_Cam_Pos = Ogre::Vector3(V4.x, V4.y, V4.z);

		App->CL_Ini->GetString("Special", "Angles", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f %f %f", &V4.x, &V4.y, &V4.z);
		App->CL_Scene->Start_Cam_Angles = Ogre::Vector3(V4.x, V4.y+140, V4.z);

	}

	return 1;
}

// *************************************************************************
// *			Load_File_Wepf:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void WV_Loader::Load_File_Wepf()
{
	//App->CL_Model->Clear_Model_And_Reset();


	App->CL_Assimp->SelectedPreset = 8 + 8388608+64 + aiProcess_PreTransformVertices;

	bool Test = App->CL_Assimp->LoadFile(WE_Path_FileName);
	if (Test == 0)
	{
		App->Say("Failed To Load");
		return;
	}


	App->CL_Scene->Set_Paths();

	bool test = LoadTextures_TXL();
	if (test == 0)
	{
		App->Say("Failed Aborting");
		return;
	}

	Set_Equity();

	Adjust();

	Ogre::Root::getSingletonPtr()->renderOneFrame();
	Ogre::Root::getSingletonPtr()->renderOneFrame();

	//App->CL_Recent_Files->RecentFile_Projects_History_Update();*/

	App->CL_Export_Ogre->Export_AssimpToOgre();

	App->CL_Player->Create_Player_Object();



	App->CL_Physics->Reset_Physics();
	App->CL_Ogre->OgreListener->Dubug_Physics_Draw = 1;

	App->CL_Scene->B_Area[0]->Area_Node->setPosition(0, 0, 0);

	//if(App->Is_WorldEditor == 1)
	//{
	//	App->CL_Ogre->mCamera->setPosition(App->CL_Scene->Start_Cam_Pos);

	//	App->CL_Ogre->mCamera->setOrientation(Ogre::Quaternion(1,0,0,0));
	//	App->CL_Ogre->mCamera->pitch(Ogre::Angle(-App->CL_Scene->Start_Cam_Angles.x));
	//	App->CL_Ogre->mCamera->yaw(Ogre::Angle(App->CL_Scene->Start_Cam_Angles.y));


	//	App->CL_Ogre->mCamera->roll(Ogre::Radian(0));
	//	//App->CL_Ogre->mCamera->yaw(Ogre::Degree(0));
	//}

}

// *************************************************************************
// *						Adjust Terry Flanigan						   *
// *************************************************************************
void WV_Loader::Adjust()
{
	Rotate_Z_Model(90);
	//Rotate_X_Model(-90);
	Centre_Model_Mid();

	//Translate_Model(0,0,-240);

	

	App->CL_Grid->Reset_View();
}

// *************************************************************************
// *						Set_Equity Terry Flanigan					   *
// *************************************************************************
void WV_Loader::Set_Equity(void)
{
	App->CL_Scene->World_Loaded = 1;

	App->CL_Grid->Reset_View();

	char TitleBar[260];
	strcpy(TitleBar, "Equity_ME");
	strcat(TitleBar, "    ");
	strcat(TitleBar, App->CL_Scene->Path_FileName);
	SetWindowText(App->MainHwnd, TitleBar);

	//Set_Equity();
	Ogre::Root::getSingletonPtr()->renderOneFrame();

	//App->CL_FileView->Change_Level_Name();

	//App->CL_TopBar->Set_Loaded();

	//App->CL_FileView->ExpandRoot();

	//App->CL_FileView->SelectItem(App->CL_Model->Group[0]->ListView_Item);  // Select First Group

	//App->CL_Grid->Zoom();

	//App->Say("Model Loaded");
}

// *************************************************************************
// *		LoadTextures_TXL:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_Loader::LoadTextures_TXL()
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
void WV_Loader::Copy_Texture_Names()
{
	int Count = 0;
	int GroupCount = App->CL_Scene->GroupCount;

	while (Count < GroupCount)
	{
		strcpy(App->CL_Scene->Group[Count]->Text_FileName, App->CL_Scene->Group[Count]->Equity_Text_FileName);

		Count++;
	}
}

// *************************************************************************
// *	  	Check_for_Textures:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
int WV_Loader::Check_for_Textures(geVFile* BaseFile)
{
	int Count = 0;
	int GroupCount = App->CL_Scene->GroupCount;

	char JustName[255];

	while (Count < GroupCount)
	{
		strcpy(JustName, App->CL_Scene->Group[Count]->Equity_Text_FileName);
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
bool WV_Loader::AddTexture(geVFile* BaseFile, const char* Path, int GroupIndex)
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
		App->Say_Win("Memory allocation error processing %s");
		return FALSE;
	}

	if (BaseFile)
		File = geVFile_Open(BaseFile, Path, GE_VFILE_OPEN_READONLY);
	else
		File = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, Path, NULL, GE_VFILE_OPEN_READONLY);

	if (!File)
	{
		//NonFatalError("Could not open %s", Path);
		App->Say_Win("Could not open %s");
		return TRUE;
	}


	Bitmap = geBitmap_CreateFromFile(File);

	if (geBitmap_HasAlpha(Bitmap))
	{
		App->CL_Scene->Group[GroupIndex]->RF_Bitmap = Bitmap;
	}


	HWND	PreviewWnd;
	HBITMAP	hbm;
	HDC		hDC;

	PreviewWnd = GetDlgItem(RightGroups_Hwnd, IDC_BASETEXTURE2);
	hDC = GetDC(PreviewWnd);
	hbm = CreateHBitmapFromgeBitmap(Bitmap, hDC);

	App->CL_Scene->Group[GroupIndex]->Base_Bitmap = hbm;

	//char TempTextureFile_BMP[1024];
	//strcpy(TempTextureFile_BMP, App->EquityDirecory_FullPath);
	//strcat(TempTextureFile_BMP, "\\");
	//strcat(TempTextureFile_BMP, "TextureLoad.bmp");

	//App->CL_Textures->Genesis_WriteToBmp(Bitmap, TempTextureFile_BMP);

	//App->CL_Textures->Soil_Load_Texture(App->CL_Ogre->RenderListener->g_Texture, TempTextureFile_BMP, GroupIndex);

	geVFile_Close(File);

	//DeleteFile((LPCTSTR)TempTextureFile_BMP);

	return TRUE;
}

// *************************************************************************
// *	CreateHBitmapFromgeBitmap:- Terry and Hazel Flanigan 2023 		   *
// *************************************************************************
HBITMAP WV_Loader::CreateHBitmapFromgeBitmap(geBitmap* Bitmap, HDC hdc)
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
bool WV_Loader::Check_in_Txl(char* FileName)
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
bool WV_Loader::Open_File_Model(const char* Extension, const char* Title, const char* StartDirectory)
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
bool WV_Loader::Start_Groups_Dialog()
{
	RightGroups_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_RIGHTGROUPS, App->MainHwnd, (DLGPROC)Groups_Proc);
	ShowWindow(RightGroups_Hwnd, 0);
	return 1;
}

// *************************************************************************
// *			Groups_Proc:- Terry and Hazel Flanigan 2023		  		   *
// *************************************************************************
LRESULT CALLBACK WV_Loader::Groups_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
void WV_Loader::Rotate_Z_Model(float Z)
{
	if (App->CL_Scene->World_Loaded == 1)
	{

		Ogre::Vector3 Centre;

		Centre.x = App->CL_Scene->S_BoundingBox[0]->Centre[0].x;
		Centre.y = App->CL_Scene->S_BoundingBox[0]->Centre[0].y;
		Centre.z = App->CL_Scene->S_BoundingBox[0]->Centre[0].z;

		Ogre::Vector3 Rotate;
		Rotate.x = 0;
		Rotate.y = 0;
		Rotate.z = Z;


		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CL_Scene->Get_Groupt_Count();

		while (Count < GroupCount)
		{
			VertCount = 0;
			while (VertCount < App->CL_Scene->Group[Count]->GroupVertCount)
			{
				Ogre::Vector3 VertPos;
				Ogre::Vector3 RotatedVert;

				VertPos.x = App->CL_Scene->Group[Count]->vertex_Data[VertCount].x;
				VertPos.y = App->CL_Scene->Group[Count]->vertex_Data[VertCount].y;
				VertPos.z = App->CL_Scene->Group[Count]->vertex_Data[VertCount].z;

				if (Rotate.z != 0) // Dont bother if Zero
				{
					RotatedVert = (Ogre::Quaternion(Ogre::Degree(Rotate.z), Ogre::Vector3::UNIT_X) * (VertPos - Centre));
				}
				else
				{
					RotatedVert = VertPos - Centre;
				}

				RotatedVert += Centre;

				App->CL_Scene->Group[Count]->vertex_Data[VertCount].x = RotatedVert.x;
				App->CL_Scene->Group[Count]->vertex_Data[VertCount].y = RotatedVert.y;
				App->CL_Scene->Group[Count]->vertex_Data[VertCount].z = RotatedVert.z;

				VertCount++;
			}
			Count++;
		}

		App->CL_Scene->Set_BondingBox_Model(0);
	}
}

// *************************************************************************
// *	  					Rotate_X_Model Terry Bernie					   *
// *************************************************************************
void WV_Loader::Rotate_X_Model(float X)
{
	if (App->CL_Scene->World_Loaded == 1)
	{

		Ogre::Vector3 Centre;

		Centre.x = App->CL_Scene->S_BoundingBox[0]->Centre[0].x;
		Centre.y = App->CL_Scene->S_BoundingBox[0]->Centre[0].y;
		Centre.z = App->CL_Scene->S_BoundingBox[0]->Centre[0].z;

		Ogre::Vector3 Rotate;
		Rotate.x = X;
		Rotate.y = 0;
		Rotate.z = 0;

		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CL_Scene->Get_Groupt_Count();

		while (Count < GroupCount)
		{
			VertCount = 0;
			while (VertCount < App->CL_Scene->Group[Count]->GroupVertCount)
			{
				Ogre::Vector3 VertPos;
				Ogre::Vector3 RotatedVert;

				VertPos.x = App->CL_Scene->Group[Count]->vertex_Data[VertCount].x;
				VertPos.y = App->CL_Scene->Group[Count]->vertex_Data[VertCount].y;
				VertPos.z = App->CL_Scene->Group[Count]->vertex_Data[VertCount].z;

				if (Rotate.x != 0) // Dont bother if Zero
				{
					RotatedVert = (Ogre::Quaternion(Ogre::Degree(Rotate.x), Ogre::Vector3::UNIT_Y) * (VertPos - Centre));
				}
				else
				{
					RotatedVert = VertPos - Centre;
				}

				RotatedVert += Centre;

				App->CL_Scene->Group[Count]->vertex_Data[VertCount].x = RotatedVert.x;
				App->CL_Scene->Group[Count]->vertex_Data[VertCount].y = RotatedVert.y;
				App->CL_Scene->Group[Count]->vertex_Data[VertCount].z = RotatedVert.z;

				VertCount++;
			}
			Count++;
		}

		App->CL_Scene->Set_BondingBox_Model(0);
	}
}

// *************************************************************************
// *	  				Centre_Model_Mid Terry Bernie					   *
// *************************************************************************
void WV_Loader::Centre_Model_Mid(void)
{
	if (App->CL_Scene->World_Loaded == 1)
	{
		float X = -App->CL_Scene->S_BoundingBox[0]->Centre[0].x;
		float Y = -App->CL_Scene->S_BoundingBox[0]->Centre[0].y;
		float Z = -App->CL_Scene->S_BoundingBox[0]->Centre[0].z;

		int Count = 0;
		int VertCount = 0;
		int Index = App->CL_Scene->Get_Groupt_Count();

		while (Count < Index)
		{
			VertCount = 0;
			while (VertCount < App->CL_Scene->Group[Count]->GroupVertCount)
			{
				App->CL_Scene->Group[Count]->vertex_Data[VertCount].x += X;
				App->CL_Scene->Group[Count]->vertex_Data[VertCount].y += Y;
				App->CL_Scene->Group[Count]->vertex_Data[VertCount].z += Z;
				VertCount++;
			}
			Count++;
		}

		App->CL_Scene->Set_BondingBox_Model(0);

	}
}

// *************************************************************************
// *	  				Translate_Model Terry Bernie					   *
// *************************************************************************
void WV_Loader::Translate_Model(float X, float Y, float Z)
{
	if (App->CL_Scene->World_Loaded == 1)
	{
		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CL_Scene->Get_Groupt_Count();

		while (Count < GroupCount)
		{
			VertCount = 0;
			while (VertCount < App->CL_Scene->Group[Count]->GroupVertCount)
			{
				App->CL_Scene->Group[Count]->vertex_Data[VertCount].x += X;
				App->CL_Scene->Group[Count]->vertex_Data[VertCount].y += Y;
				App->CL_Scene->Group[Count]->vertex_Data[VertCount].z += Z;
				VertCount++;
			}
			Count++;
		}

		App->CL_Scene->Set_BondingBox_Model(0);
	}
}