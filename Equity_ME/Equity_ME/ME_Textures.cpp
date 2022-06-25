#include "stdafx.h"
#include "ME_App.h"
#include "resource.h"
#include "ME_Textures.h"

#include "il.h"
#include "ilu.h"
#include "ilut.h"


ME_Textures::ME_Textures()
{
	ilInit();

	JustFileName[0] = 0;
}


ME_Textures::~ME_Textures()
{
}

// *************************************************************************
// *						TexureToWinPreviewFullPath			  	 	   *
// *************************************************************************
bool ME_Textures::TexureToWinPreviewFullPath(int Index, char* FullPath)
{
	//BITMAPINFO    *bmiData;
	//ilutGetBmpInfo(bmiData);

	char mFileName[1024];
	strcpy(mFileName, FullPath);

	HWND PreviewWnd = GetDlgItem(App->CL_Groups->RightGroups_Hwnd, IDC_BASETEXTURE2);
	HDC	hDC = GetDC(PreviewWnd);

	App->CL_Model->Group[Index]->Base_Bitmap = NULL;

	// ----------------------------------- Bitmap
	if (_stricmp(mFileName + strlen(mFileName) - 4, ".BMP") == 0)
	{
		
		App->CL_Model->Group[Index]->Base_Bitmap = ilutWinLoadImage(mFileName, hDC);
		ReleaseDC(PreviewWnd, hDC);

		if (App->CL_Model->Group[Index]->Base_Bitmap == NULL)
		{
			
			LoadDummyTexture(Index);
			App->CL_Model->Group[Index]->Bitmap_Loaded = -1;

			return 1;
		}
		else
		{
			App->CL_Model->Group[Index]->Bitmap_Loaded = 1;
		}

		return 1;
	}

	// ------------------------------------ JPEG
	if (stricmp(mFileName + strlen(mFileName) - 4, ".JPG") == 0)
	{
		App->CL_Model->Group[Index]->Base_Bitmap = ilutWinLoadImage(mFileName, hDC);
		ReleaseDC(PreviewWnd, hDC);

		App->CL_Model->Group[Index]->Bitmap_Loaded = 1;

		return 1;
	}
	
	LoadDummyTexture(Index);
	App->CL_Model->Group[Index]->Bitmap_Loaded = -1;

	return 1;
}

// *************************************************************************
// *						CheckPath Terry Bernie	   					   *
// *************************************************************************
void ME_Textures::Strip_JustFileName(char *pString, char *FileName)
{
	int Count = 0;
	int Mark = 0;
	bool Test = 0;

	JustFileName[0] = 0;

	while (*pString != 0)
	{
		if (*pString == '\\' || *pString == '/')
		{
			Test = 1;
			Mark = Count;
		}

		Count++;
		pString++;
	}

	if (Mark == 0 && Test == 0)
	{
		strcpy(JustFileName, FileName);
	}
	else
	{
		if (Mark == 0 && Test == 1)
		{
			Mark = 1;
			strcpy(JustFileName, (FileName + Mark));
		}
		else
		{
			strcpy(JustFileName, (FileName + Mark) + 1);
		}
	}
}

// *************************************************************************
// *					CreateDummyTexture Terry Bernie   		 	 	   *
// *************************************************************************
bool ME_Textures::LoadDummyTexture(int Index)
{
	char File[MAX_PATH];

	strcpy(File, App->EquityDirecory_FullPath);
	strcat(File, "\\");
	strcat(File, "Data\\");
	strcat(File, "Dummy.bmp");

	HWND PreviewWnd = GetDlgItem(App->CL_Groups->RightGroups_Hwnd, IDC_BASETEXTURE2);
	HDC	hDC = GetDC(PreviewWnd);

	App->CL_Model->Group[Index]->Base_Bitmap = ilutWinLoadImage(File, hDC);

	ReleaseDC(PreviewWnd, hDC);

	return 1;
}
