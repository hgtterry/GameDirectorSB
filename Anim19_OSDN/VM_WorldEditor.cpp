#include "stdafx.h"
#include "GD19_App.h"
#include "VM_WorldEditor.h"


VM_WorldEditor::VM_WorldEditor()
{
}


VM_WorldEditor::~VM_WorldEditor()
{
}

// *************************************************************************
// *						Adjust Terry Flanigan						   *
// *************************************************************************
void VM_WorldEditor::Adjust()
{

	App->Cl_Vm_Dimensions->Rotate_Z_Model(90);
	App->Cl_Vm_Dimensions->Rotate_X_Model(-90);
	App->Cl_Vm_Dimensions->Centre_Model_Mid();
	App->Cl_Grid->Reset_View();
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

	LoadFile();
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
// *						LoadFile  Terry Flanigan 			  		   *
// *************************************************************************
bool VM_WorldEditor::LoadFile()
{
	geVFile *			VFS = NULL;
	geVFile_Finder *	Finder = NULL;
	geVFile_Finder *	FinderCount = NULL;

	p_Data2 = new TPack_WindowData2;
	p_Data2->hwnd = NULL;
	p_Data2->BitmapCount = 0;

	int TextureCount = 0;


	//App->Say(Txt_FileName);
	//App->Say(Txt_Path_FileName);
	VFS = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_VIRTUAL, Txt_Path_FileName, NULL, GE_VFILE_OPEN_READONLY | GE_VFILE_OPEN_DIRECTORY);
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

		TextureCount++;

	}

	Finder = geVFile_CreateFinder(VFS, "*.*");
	if (!Finder)
	{
		App->Say("Could not load textures from 2 ");
		geVFile_Close(VFS);
		return 0;
	}


	while (geVFile_FinderGetNextFile(Finder) != GE_FALSE)
	{
		geVFile_Properties	Properties;

		geVFile_FinderGetProperties(Finder, &Properties);
		
		Check_for_Name(Properties.Name);
		
		/*if (!AddTexture(VFS, Properties.Name))
		{
			geVFile_Close(VFS);
			return 0;
		}

		App->Say(Properties.Name);*/
	}
	/*strcpy(p_Data->TXLFileName, Txt_FileName);
	p_Data->FileNameIsValid = TRUE;
	p_Data->Dirty = FALSE;*/
	geVFile_Close(VFS);

	//SendDlgItemMessage(p_Data->hwnd, IDC_TEXTURELIST, LB_SETCURSEL, (WPARAM)0, (LPARAM)0);
	//App->CL_Vm_TextLib->SelectBitmap();*/
	return 1;
}

// *************************************************************************
// *	  			Check_for_Name Terry Bernie							   *
// *************************************************************************
int VM_WorldEditor::Check_for_Name(char* Name)
{
	int Count = 0;
	int Total = App->CL_Vm_Model->GroupCount;

	char JustName[255];
	

	while (Count < Total)
	{
		strcpy(JustName, App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName);
		int Len = strlen(JustName);
		JustName[Len - 4] = 0;

		int Result = 1;
		Result = strcmp(JustName, Name);
		if (Result == 0)
		{
			App->Say("Matched");
			App->Say(Name);
			return 1;
		}
		
		Count++;
	}

	App->Say("UnMached");
	
	return -1;
}

// *************************************************************************
// *						AddTexture  06/06/08 				  		   *
// *************************************************************************
bool VM_WorldEditor::AddTexture(geVFile *BaseFile, const char *Path)
{
	geBitmap_Info	PInfo;
	geBitmap_Info	SInfo;
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

	geVFile_Close(File);

	if (!Bitmap)
	{
		NonFatalError("%s is not a valid bitmap", Path);
		return TRUE;
	}

	
	NewBitmapList2[p_Data2->BitmapCount] = new BitmapEntry2;
	if (!NewBitmapList2)
	{
		NonFatalError("Memory allocation error processing %s", Path);
		return TRUE;
	}

	NewBitmapList2[p_Data2->BitmapCount]->Name = Name;
	NewBitmapList2[p_Data2->BitmapCount]->Bitmap = Bitmap;
	NewBitmapList2[p_Data2->BitmapCount]->WinBitmap = NULL;
	NewBitmapList2[p_Data2->BitmapCount]->WinABitmap = NULL;
	NewBitmapList2[p_Data2->BitmapCount]->Flags = 0;
	p_Data2->BitmapCount++;

	//SendDlgItemMessage(p_Data->hwnd, IDC_TEXTURELIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)Name);

	return TRUE;

}