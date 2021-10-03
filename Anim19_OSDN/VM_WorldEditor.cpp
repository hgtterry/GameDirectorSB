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

	NameCount = 0;


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

	PreviewWnd = GetDlgItem(App->CL_Vm_Groups->RightGroups_Hwnd, IDC_BASETEXTURE2);
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