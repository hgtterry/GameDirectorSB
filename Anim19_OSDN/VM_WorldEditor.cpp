#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "VM_WorldEditor.h"


VM_WorldEditor::VM_WorldEditor()
{
}


VM_WorldEditor::~VM_WorldEditor()
{
}

// *************************************************************************
// *	  				 Start_WE_import	Terry Flanigan				   *
// *************************************************************************
bool VM_WorldEditor::Start_WE_import()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_WEQUICKLOAD, App->MainHwnd, (DLGPROC)WE_import_Proc);
	return 1;
}

// *************************************************************************
// *					WE_import_Proc	Terry Flanigan 					   *
// *************************************************************************
LRESULT CALLBACK VM_WorldEditor::WE_import_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_STWEPATHFILE, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTXLFILEPATH, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STQLOGREFILE, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STQLOGREPATH, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_STWEPATHFILE, (LPCTSTR)App->Cl_Vm_Preferences->Pref_WE_Path_FileName);
		SetDlgItemText(hDlg, IDC_STTXLFILEPATH, (LPCTSTR)App->Cl_Vm_Preferences->Pref_Txl_Path_FileName);

		SetDlgItemText(hDlg, IDC_STQLOGREFILE, (LPCTSTR)App->Cl_Vm_Preferences->Pref_Ogre_JustFileName);
		SetDlgItemText(hDlg, IDC_STQLOGREPATH, (LPCTSTR)App->Cl_Vm_Preferences->Pref_Ogre_Path);



		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STQLOGREFILE) == (HWND)lParam)
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
		}

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
			int Result = App->CL_Vm_FileIO->Vm_OpenFile("RF World   *.rfw\0*.rfw\0", "RF World rfw", NULL);
			if (Result == 0)
			{
				return 1;
			}

			strcpy(App->Cl_Vm_Preferences->Pref_WE_Path_FileName, App->CL_Vm_FileIO->Model_Path_FileName);
			strcpy(App->Cl_Vm_Preferences->Pref_WE_JustFileName, App->CL_Vm_FileIO->Model_FileName);

			SetDlgItemText(hDlg, IDC_STWEPATHFILE, (LPCTSTR)App->Cl_Vm_Preferences->Pref_WE_Path_FileName);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TXLBROWSE)
		{

			int test = App->Cl_Vm_WorldEditor->Txt_OpenFile("Texture Libary   *.txl\0*.txl\0", "Texure Editor", NULL);// S_Prefs[0]->TXLFolder);
			if (test == 0)
			{
				return 1;
			}

			strcpy(App->Cl_Vm_Preferences->Pref_Txl_Path_FileName, App->Cl_Vm_WorldEditor->Txt_Path_FileName);

			SetDlgItemText(hDlg, IDC_STTXLFILEPATH, (LPCTSTR)App->Cl_Vm_Preferences->Pref_Txl_Path_FileName);
			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			
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
// *						Adjust Terry Flanigan						   *
// *************************************************************************
void VM_WorldEditor::Adjust()
{
	App->Cl_Vm_Dimensions->Rotate_Z_Model(90);
	App->Cl_Vm_Dimensions->Rotate_X_Model(-90);
	App->Cl_Vm_Dimensions->Centre_Model_Mid();
}

// *************************************************************************
// *						Change_Textures Terry Flanigan				   *
// *************************************************************************
void VM_WorldEditor::Change_Textures()
{

	int test = Txt_OpenFile("Texture Libary   *.txl\0*.txl\0", "Texure Editor", NULL);// S_Prefs[0]->TXLFolder);
	if (test == 0)
	{
		return;
	}

	LoadTextures_TXL();
}

// *************************************************************************
// *					Txt_OpenFile Terry Flanigan						   *
// *************************************************************************
bool VM_WorldEditor::Txt_OpenFile(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(Txt_FileName, "");
	strcpy(Txt_Path_FileName, "");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Txt_Path_FileName;						// full path and file name
	ofn.nMaxFile = sizeof(Txt_Path_FileName);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Txt_FileName;						// Just File Name
	ofn.nMaxFileTitle = sizeof(Txt_FileName);;
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
// *						NonFatalError   					  		   *
// *************************************************************************
bool VM_WorldEditor::NonFatalError(const char *Msg, ...)
{
	char Buffer[1024];
	va_list argptr;

	va_start(argptr, Msg);
	vsprintf(Buffer, Msg, argptr);
	va_end(argptr);

	MessageBox(NULL, Buffer, "Error", MB_ICONEXCLAMATION | MB_OK);
	return 1;
}

// *************************************************************************
// *					LoadTextures_TXL  Terry Flanigan 				   *
// *************************************************************************
bool VM_WorldEditor::LoadTextures_TXL()
{
	geVFile *			VFS = NULL;
	geVFile_Finder *	Finder = NULL;
	geVFile_Finder *	FinderCount = NULL;

	NameCount = 0;

	VFS = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_VIRTUAL, App->Cl_Vm_Preferences->Pref_Txl_Path_FileName, NULL, GE_VFILE_OPEN_READONLY | GE_VFILE_OPEN_DIRECTORY);
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
int VM_WorldEditor::Check_for_Textures(geVFile *BaseFile)
{
	int Count = 0;
	int GroupCount = App->CL_Vm_Model->GroupCount;

	char JustName[255];
	
	while (Count < GroupCount)
	{
		strcpy(JustName, App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName);
		int Len = strlen(JustName);
		JustName[Len - 4] = 0;

		bool test = Check_in_Txl(JustName);

		if (test == 1)
		{
			if (!AddTexture(BaseFile, JustName,Count))
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
bool VM_WorldEditor::Check_in_Txl(char *FileName)
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
bool VM_WorldEditor::AddTexture(geVFile *BaseFile, const char *Path,int GroupIndex)
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
		NonFatalError("Memory allocation error processing %s", Path);
		return FALSE;
	}

	if (BaseFile)
		File = geVFile_Open(BaseFile, Path, GE_VFILE_OPEN_READONLY);
	else
		File = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, Path, NULL, GE_VFILE_OPEN_READONLY);

	if (!File)
	{
		NonFatalError("Could not open %s", Path);
		return TRUE;
	}

	Bitmap = geBitmap_CreateFromFile(File);

	HWND	PreviewWnd;
	HBITMAP	hbm;
	HDC		hDC;

	PreviewWnd = 0;//GetDlgItem(App->EBC_Groups->RightGroups_Hwnd, IDC_BASETEXTURE2);
	hDC = GetDC(PreviewWnd);
	hbm = CreateHBitmapFromgeBitmap(Bitmap, hDC);

	App->CL_Vm_Model->S_MeshGroup[GroupIndex]->Base_Bitmap = hbm;
	

	/*if (!Bitmap)
	{
		NonFatalError("%s is not a valid bitmap", Path);
		return TRUE;
	}*/

	char TempTextureFile_BMP[1024];
	strcpy(TempTextureFile_BMP, App->EquityDirecory_FullPath);
	strcat(TempTextureFile_BMP, "\\");
	strcat(TempTextureFile_BMP, "TextureLoad.bmp");

	App->CL_Vm_Textures->Genesis_WriteToBmp(Bitmap, TempTextureFile_BMP);

	App->CL_Vm_Textures->Soil_Load_Texture(App->CL_Vm_Textures->g_Texture, TempTextureFile_BMP, GroupIndex);
	
	geVFile_Close(File);

	DeleteFile((LPCTSTR)TempTextureFile_BMP);
	return TRUE;

}

// *************************************************************************
// *				CreateHBitmapFromgeBitmap  06/06/08 		  		   *
// *************************************************************************
HBITMAP VM_WorldEditor::CreateHBitmapFromgeBitmap(geBitmap *Bitmap, HDC hdc)
{

	HBITMAP hbm = NULL;

	return hbm;
}