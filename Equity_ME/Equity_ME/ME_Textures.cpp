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
	//ilutGetBmpInfo(BITMAPINFO *Info);
	
	char mFileName[1024];
	strcpy(mFileName, FullPath);

	HWND PreviewWnd = GetDlgItem(App->CL_Groups->RightGroups_Hwnd, IDC_BASETEXTURE2);
	HDC	hDC = GetDC(PreviewWnd);

	// ----------------------------------- Bitmap
	if (_stricmp(mFileName + strlen(mFileName) - 4, ".BMP") == 0)
	{
		App->CL_Model->Group[Index]->Base_Bitmap = NULL;

		App->CL_Model->Group[Index]->Base_Bitmap = ilutWinLoadImage(mFileName, hDC);
		ReleaseDC(PreviewWnd, hDC);

		if (App->CL_Model->Group[Index]->Base_Bitmap == NULL)
		{
			//CreateDummyTexture();
			//App->CL_Model->Group[Index]->Base_Bitmap = (HBITMAP)LoadImage(NULL, "Etemp.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			//remove("Etemp.bmp");

			//App->CL_Model->Group[Index]->Bitmap_Loaded = 1;
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
	
	// if all fails dummy texture here 

	//CreateDummyTexture();

	//char buf[1024];
	//strcpy(buf,App->EquityDirecory_FullPath);
	//strcat(buf,"\\");
	//strcat(buf,"Etemp.bmp");

	////App->CL_Vm_Model->S_MeshGroup[Index]->Base_Bitmap = ilLoadImage("Etemp.bmp");
	////Soil_Load_Texture(g_Texture,buf,TextureID);
	//remove(buf);

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
