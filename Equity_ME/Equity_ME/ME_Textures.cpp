#include "stdafx.h"
#include "ME_App.h"
#include "resource.h"
#include "ME_Textures.h"

#include "SOIL.h"

#include "il.h"
#include "ilu.h"
#include "ilut.h"

#pragma warning( disable : 4800)

ME_Textures::ME_Textures()
{
	ilInit();

	JustFileName[0] = 0;
	TextureFileName[0] = 0;
}


ME_Textures::~ME_Textures()
{
}

// *************************************************************************
// *					DecodeTextures  Terry Bernie   			  	 	   *
// *************************************************************************
bool ME_Textures::Soil_DecodeTextures(int TextureID)
{
	int Index = 0;
	int Dont = 0;
	int jpg = 0;
	int DontAdd = 0;
	int AddDummy = 0;

	char buf[1024];
	strcpy(buf, App->CL_Model->Texture_FolderPath);
	strcat(buf, "Etemp.bmp");

	// ----------------------------------- Bitmap
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".BMP") == 0)
	{
		Soil_Load_Texture(g_Texture, TextureFileName, TextureID);
		return 1;
	}
	// ------------------------------------ JPEG
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".JPG") == 0)
	{
		Soil_Load_Texture(g_Texture, TextureFileName, TextureID);
		return 1;
	}
	// ------------------------------------ TGA
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".TGA") == 0)
	{
		Soil_Load_Texture(g_Texture, TextureFileName, TextureID);
		return 1;
	}
	//// ------------------------------------ DDS
	//if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".DDS") == 0)
	//{
	//	//S_TextureInfo[Count] = new GLTextureInfo_Type; // Need To Populate

	//	int Test = Soil_Load_Texture(g_Texture, TextureFileName, TextureID);
	//	if (Test == 0)
	//	{
	//		CreateDummyTexture();
	//		Soil_Load_Texture(g_Texture, buf, TextureID);
	//		//remove(buf);
	//	}
	//	return 1;
	//}
	//// ------------------------------------ PNG
	//if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".PNG") == 0)
	//{
	//	//S_TextureInfo[Count] = new GLTextureInfo_Type; // Need To Populate

	//	int Test = Soil_Load_Texture(g_Texture, TextureFileName, TextureID);
	//	if (Test == 0)
	//	{
	//		CreateDummyTexture();
	//		Soil_Load_Texture(g_Texture, buf, TextureID);
	//		//remove(buf);
	//	}
	//	return 1;
	//}

	/*CreateDummyTexture();
	Soil_Load_Texture(g_Texture, buf, TextureID);
	remove(buf);*/

	return 1;
}

// *************************************************************************
// *					Soil_Load_Texture Terry Bernie		  		  	   *
// *************************************************************************
bool ME_Textures::Soil_Load_Texture(UINT textureArray[], LPSTR strFileName, int textureID)
{
	textureArray[textureID] = SOIL_load_OGL_texture
	(
		strFileName,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
	);

	if (textureArray[textureID] == 0) // Fall back attemp to convert and load or Bail
	{
		char File[260];
		strcpy(File, App->EquityDirecory_FullPath);
		strcat(File, "\\");
		strcat(File, "Data\\");
		strcat(File, "Dummy.bmp");
		Soil_Load_Texture(g_Texture, File, textureID);

		textureArray[textureID] = SOIL_load_OGL_texture
		(
			File,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
		);
	}
	
	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	////glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return 1;
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
	if (stricmp(mFileName + strlen(mFileName) - 4, ".tga") == 0)
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