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
#include "resource.h"
#include "ME_App.h"
#include "ME_Equity_SB.h"


ME_Equity_SB::ME_Equity_SB()
{

	NameCount = 0;
}


ME_Equity_SB::~ME_Equity_SB()
{
}

// *************************************************************************
// *	  				 Start_WE_import	Terry Flanigan				   *
// *************************************************************************
bool ME_Equity_SB::Start_WE_import()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_WEQUICKLOAD, App->MainHwnd, (DLGPROC)WE_import_Proc);
	return 1;
}

// *************************************************************************
// *					WE_import_Proc	Terry Flanigan 					   *
// *************************************************************************
LRESULT CALLBACK ME_Equity_SB::WE_import_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_STWEPATHFILE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTXLFILEPATH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		/*SendDlgItemMessage(hDlg, IDC_STQLOGREFILE, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STQLOGREPATH, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));*/

		SetDlgItemText(hDlg, IDC_STWEPATHFILE, (LPCTSTR)App->CL_Prefs->Pref_WE_Path_FileName);
		SetDlgItemText(hDlg, IDC_STTXLFILEPATH, (LPCTSTR)App->CL_Prefs->Pref_Txl_Path_FileName);

		/*SetDlgItemText(hDlg, IDC_STQLOGREFILE, (LPCTSTR)App->Cl_Vm_Preferences->Pref_Ogre_JustFileName);
		SetDlgItemText(hDlg, IDC_STQLOGREPATH, (LPCTSTR)App->Cl_Vm_Preferences->Pref_Ogre_Path);*/

		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_STQLOGREFILE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STQLOGREPATH) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}*/

		if (GetDlgItem(hDlg, IDC_STWEPATHFILE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STTXLFILEPATH) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STATICTXL) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STATICWE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}


		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDCANCEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_3DSBROWSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TXLBROWSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_3DSBROWSE)
		{
			int Result = App->CL_FileIO->Open_File_Model("RF World   *.rfw\0*.rfw\0", "RF World rfw", NULL);
			if (Result == 0)
			{
				return 1;
			}

			strcpy(App->CL_Prefs->Pref_WE_Path_FileName, App->CL_FileIO->Model_Path_FileName);
			strcpy(App->CL_Prefs->Pref_WE_JustFileName, App->CL_FileIO->Model_FileName);

			SetDlgItemText(hDlg, IDC_STWEPATHFILE, (LPCTSTR)App->CL_Prefs->Pref_WE_Path_FileName);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TXLBROWSE)
		{

			//int test = App->Cl_Vm_WorldEditor->Txt_OpenFile("Texture Libary   *.txl\0*.txl\0", "Texure Editor", NULL);// S_Prefs[0]->TXLFolder);
			//if (test == 0)
			//{
			//	return 1;
			//}

			//strcpy(App->Cl_Vm_Preferences->Pref_Txl_Path_FileName, App->Cl_Vm_WorldEditor->Txt_Path_FileName);

			//SetDlgItemText(hDlg, IDC_STTXLFILEPATH, (LPCTSTR)App->Cl_Vm_Preferences->Pref_Txl_Path_FileName);

			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			//App->Cl_Vm_Preferences->Write_Preferences();

			App->CL_Model->Clear_Model_And_Reset();

			strcpy(App->CL_FileIO->Model_Path_FileName, App->CL_Prefs->Pref_WE_Path_FileName);
			strcpy(App->CL_FileIO->Model_FileName, App->CL_Prefs->Pref_WE_JustFileName);

			App->CL_Model->Set_Paths();

			App->CL_Assimp->SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;

			bool Test = App->CL_Assimp->LoadFile(App->CL_Prefs->Pref_WE_Path_FileName);
			if (Test == 0)
			{
				App->Say("Failed To Load");
				return 0;
			}

			App->CL_Model->Model_Type = Enums::LoadedFile_Assimp;

			App->CL_Equity_SB->LoadTextures_TXL();

			//App->Cl_Vm_WorldEditor->Adjust();

			EndDialog(hDlg, LOWORD(wParam));

			App->CL_Import->Set_Equity();

			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

	}

	break;

	}
	return FALSE;
}

// *************************************************************************
// *					LoadTextures_TXL  Terry Flanigan 				   *
// *************************************************************************
bool ME_Equity_SB::LoadTextures_TXL()
{
	geVFile *			VFS = NULL;
	geVFile_Finder *	Finder = NULL;
	geVFile_Finder *	FinderCount = NULL;

	NameCount = 0;

	VFS = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_VIRTUAL, App->CL_Prefs->Pref_Txl_Path_FileName, NULL, GE_VFILE_OPEN_READONLY | GE_VFILE_OPEN_DIRECTORY);
	if (!VFS)
	{
		App->Say("Could not open file");
		return 0;
	}

	FinderCount = geVFile_CreateFinder(VFS, "*.*");
	if (!FinderCount)
	{
		App->Say("Could not load textures from");
		geVFile_Close(VFS);
		return 0;
	}

	while (geVFile_FinderGetNextFile(FinderCount) != GE_FALSE)
	{


	}

	Finder = geVFile_CreateFinder(VFS, "*.*");
	if (!Finder)
	{
		App->Say("Could not load textures from 2 ");
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

		/*if (!AddTexture(VFS, Properties.Name))
		{
		geVFile_Close(VFS);
		return 0;
		}*/
	}

	Check_for_Textures(VFS);

	geVFile_Close(VFS);

	return 1;
}

// *************************************************************************
// *	  			Check_for_Textures Terry Bernie						   *
// *************************************************************************
int ME_Equity_SB::Check_for_Textures(geVFile *BaseFile)
{
	int Count = 0;
	int GroupCount = App->CL_Model->GroupCount;

	char JustName[255];

	while (Count < GroupCount)
	{
		strcpy(JustName, App->CL_Model->Group[Count]->Text_FileName);
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
// *	  			Check_in_Txl Terry Bernie							   *
// *************************************************************************
bool ME_Equity_SB::Check_in_Txl(char *FileName)
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
// *						AddTexture  06/06/08 				  		   *
// *************************************************************************
bool ME_Equity_SB::AddTexture(geVFile *BaseFile, const char *Path, int GroupIndex)
{

	geBitmap *		Bitmap;

	geVFile *		File;
	char			FileName[_MAX_FNAME];
	char *			Name;

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

	HWND	PreviewWnd;
	HBITMAP	hbm;
	HDC		hDC;

	PreviewWnd = GetDlgItem(App->CL_Groups->RightGroups_Hwnd, IDC_BASETEXTURE2);
	hDC = GetDC(PreviewWnd);
	hbm = CreateHBitmapFromgeBitmap(Bitmap, hDC);

	App->CL_Model->Group[GroupIndex]->Base_Bitmap = hbm;


	/*if (!Bitmap)
	{
	NonFatalError("%s is not a valid bitmap", Path);
	return TRUE;
	}*/

	char TempTextureFile_BMP[1024];
	strcpy(TempTextureFile_BMP, App->EquityDirecory_FullPath);
	strcat(TempTextureFile_BMP, "\\");
	strcat(TempTextureFile_BMP, "TextureLoad.bmp");

	App->CL_Textures->Genesis_WriteToBmp(Bitmap, TempTextureFile_BMP);

	App->CL_Textures->Soil_Load_Texture(App->CL_Textures->g_Texture, TempTextureFile_BMP, GroupIndex);

	geVFile_Close(File);

	DeleteFile((LPCTSTR)TempTextureFile_BMP);

	return TRUE;
}

// *************************************************************************
// *				CreateHBitmapFromgeBitmap  06/06/08 		  		   *
// *************************************************************************
HBITMAP ME_Equity_SB::CreateHBitmapFromgeBitmap(geBitmap *Bitmap, HDC hdc)
{
	geBitmap * Lock;
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
		void * bits;
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

		if ((info.Stride*pelbytes) == (((info.Stride*pelbytes) + 3)&(~3)))
		{
			bmih.biWidth = info.Stride;
			hbm = CreateDIBitmap(hdc, &bmih, CBM_INIT, bits, (BITMAPINFO *)&bmih, DIB_RGB_COLORS);
		}
		else
		{
			void * newbits;
			int Stride;

			bmih.biWidth = info.Width;
			Stride = (((info.Width*pelbytes) + 3)&(~3));
			newbits = geRam_Allocate(Stride * info.Height);
			if (newbits)
			{
				char *newptr, *oldptr;
				int y;

				newptr = (char *)newbits;
				oldptr = (char *)bits;
				for (y = 0; y < info.Height; y++)
				{
					memcpy(newptr, oldptr, (info.Width)*pelbytes);
					oldptr += info.Stride*pelbytes;
					newptr += Stride;
				}
				hbm = CreateDIBitmap(hdc, &bmih, CBM_INIT, newbits, (BITMAPINFO *)&bmih, DIB_RGB_COLORS);
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
