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
#include "SB_Textures.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "il.h"
#include "ilu.h"
#include "ilut.h"

#include "bitmap.h"
#include "bitmap._h"
#include "bitmap.__h"

SB_Textures::SB_Textures()
{
	TextureFileName[0] = 0;

	VFS = NULL;
}

SB_Textures::~SB_Textures()
{
}


// *************************************************************************
// *		Load_Textures_Assimp:- Terry and Hazel Flanigan 2023	  	   *
// *************************************************************************
void SB_Textures::Load_Textures_Assimp()
{
	int v = 0;
	int Count = 0;
	bool DummyCreated = 0;

	int mGroupCount = App->CLSB_Model->Get_Groupt_Count();

	while (Count < mGroupCount)
	{
		char JustFileName[MAX_PATH];
		GetFileTitleA(App->CLSB_Model->Group[Count]->Text_FileName, JustFileName, MAX_PATH);
		strcpy(App->CLSB_Model->Group[Count]->Text_FileName, JustFileName);

		int Test = strcmp(JustFileName, "No_Texture");
		if (Test != 0) // not a match
		{

			char ImageFullPath[MAX_PATH];
			strcpy(ImageFullPath, App->CLSB_Model->Texture_FolderPath);
			strcat(ImageFullPath, App->CLSB_Model->Group[Count]->Text_FileName);

			strcpy(App->CLSB_Model->Group[v]->Texture_PathFileName, ImageFullPath);

			strcpy(TextureFileName, ImageFullPath);

			//Windows_Preview_FullPath(v, ImageFullPath);

			bool test = Load_OpenGL_Textures(App->CLSB_Model->Group[Count]->MaterialIndex);
			if (test == 0)
			{
				App->Error_ToFile("Loading Dummy Texture Instead");
				App->CLSB_Textures->Create_DummyTexture(App->CLSB_Model->Texture_FolderPath);

				char buf[MAX_PATH];
				strcpy(buf, App->CLSB_Model->Texture_FolderPath);
				strcat(buf, "TTemp.bmp");
				UINT* Texture_List = App->CLSB_Ogre->RenderListener->g_Texture;
				Soil_Load_Texture(Texture_List, buf, App->CLSB_Model->Group[Count]->MaterialIndex);

				App->CLSB_Loader->LoadError = 1;
				DummyCreated = 1;
			}
			v++;
		}
		else
		{
			App->Error_ToFile("No Texture in File");
			App->Error_ToFile("Loading Dummy Texture Instead");
			App->CLSB_Textures->Create_DummyTexture(App->CLSB_Model->Texture_FolderPath);

			char buf[MAX_PATH];
			strcpy(buf, App->CLSB_Model->Texture_FolderPath);
			strcat(buf, "TTemp.bmp");
			UINT* Texture_List = App->CLSB_Ogre->RenderListener->g_Texture;
			Soil_Load_Texture(Texture_List, buf, App->CLSB_Model->Group[Count]->MaterialIndex);

			App->CLSB_Loader->LoadError = 1;
			DummyCreated = 1;

			v++;
		}

		Count++;
	}

	if (DummyCreated == 1)
	{
		char buf[MAX_PATH];
		strcpy(buf, App->CLSB_Model->Texture_FolderPath);
		strcat(buf, "TTemp.bmp");
		remove(buf);
	}
}

// *************************************************************************
// *	  				Load_Textures_Ogre3D Terry Bernie				   *
// *************************************************************************
void SB_Textures::Load_Textures_Ogre3D(void)
{
	//int SubMeshCount = App->CL_Ogre3D->OgreModel_Ent->getNumSubEntities();

	//int mMaterialindex = 0;
	//int Count = 0;
	//char MatName[255];
	//char TextureName[255];
	//char SubMeshName[255];
	//char buf[255];

	//strcpy(SubMeshName, "SubMesh_");

	//while (Count < SubMeshCount)
	//{
	//	Ogre::SubMesh const* subMesh = App->CL_Ogre3D->OgreModel_Ent->getSubEntity(Count)->getSubMesh();
	//	strcpy(MatName, subMesh->getMaterialName().c_str());

	//	itoa(Count, buf, 10);
	//	strcpy(SubMeshName, "SubMesh_");
	//	strcat(SubMeshName, buf);

	//	Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(MatName);

	//	if (material.isNull())
	//	{
	//		App->CL_Ogre3D->NoMaterialFileFound = 1; // Flag we dont have a texture yet
	//		//App->Say_Int(NoMaterialFileFound);
	//	}
	//	else
	//	{
	//		Ogre::Technique* technique = material->getTechnique(0);
	//		if (technique == NULL)
	//		{

	//		}
	//		else
	//		{
	//			Ogre::Pass* pass;
	//			pass = technique->getPass(0);
	//			if (pass == NULL)
	//			{
	//			}
	//			else
	//			{
	//				int TextureUnitCount = pass->getNumTextureUnitStates();
	//				if (TextureUnitCount == 0)
	//				{
	//					strcpy(App->CL_Model->Group[Count]->Text_FileName, "No_Texture");
	//					//App->S_MeshGroup[Count]->IsValid = 0;
	//					App->CL_Ogre3D->NoTexture = 1;
	//				}
	//				else
	//				{
	//					Ogre::TextureUnitState* textureUnit = pass->getTextureUnitState(0);

	//					Ogre::String TxtName = textureUnit->getTextureName();

	//					strcpy(TextureName, TxtName.c_str());

	//					strcpy(App->CL_Model->Group[Count]->Text_FileName, TextureName);

	//					App->CL_Ogre3D->NoTexture = 0;

	//					bool result = 0;

	//					//result = App->CL_FileIO->SearchFolders(App->CL_Model->Texture_FolderPath, TextureName);

	//					if (result == 0) // Texture Found in Mesh Folder
	//					{
	//						//App->Say_Win(App->CL_Model->Texture_FolderPath);

	//						char ImageFullPath[MAX_PATH];
	//						strcpy(ImageFullPath, App->CL_Model->Texture_FolderPath);
	//						strcat(ImageFullPath, TextureName);

	//						strcpy(App->CL_Load_Textures->TextureFileName, ImageFullPath);

	//						strcpy(App->CL_Model->Group[Count]->Texture_FolderPath, ImageFullPath);
	//						strcpy(App->CL_Model->Group[Count]->Text_FileName, TextureName);

	//						App->CL_Load_Textures->Windows_Preview_FullPath(Count, ImageFullPath);

	//						//App->CL_Textures->TexureToWinPreviewFullPath(Count, TextureName);
	//						App->CL_Model->Group[Count]->MaterialIndex = mMaterialindex;

	//						App->CL_Load_Textures->Load_OpenGL_Textures(mMaterialindex);
	//						//App->CL_Textures->Soil_DecodeTextures(mMaterialindex);
	//						mMaterialindex++;
	//					}
	//					else
	//					{
	//						//if (ExternalResourceLoaded == 1) // Search for texture via resource file
	//						//{
	//						//	Scan_ResourcesNew(ResourcePathAndFile, Count);

	//						//	strcpy(App->CL_Textures->TextureFileName, App->CL_Model->Group[Count]->Texture_FolderPath);

	//						//	App->CL_Model->Group[Count]->MaterialIndex = mMaterialindex;

	//						//	App->CL_Textures->Soil_DecodeTextures(mMaterialindex);
	//						//	mMaterialindex++;
	//						//}
	//					}
	//				}
	//			}
	//		}
	//	}

	//	Count++;
	//}
}

// *************************************************************************
// *						Windows_Preview_FullPath			  	 	   *
// *************************************************************************
bool SB_Textures::Windows_Preview_FullPath(int Index, char* FullPath)
{

	//char mFileName[MAX_PATH];
	//strcpy(mFileName, FullPath);

	//HWND PreviewWnd = GetDlgItem(App->CL_Groups->RightGroups_Hwnd, IDC_BASETEXTURE2);
	//HDC	hDC = GetDC(PreviewWnd);

	//App->CL_Model->Group[Index]->Base_Bitmap = NULL;

	//// ----------------------------------- Bitmap
	//if (_stricmp(mFileName + strlen(mFileName) - 4, ".BMP") == 0)
	//{

	//	App->CL_Model->Group[Index]->Base_Bitmap = ilutWinLoadImage(mFileName, hDC);
	//	ReleaseDC(PreviewWnd, hDC);

	//	if (App->CL_Model->Group[Index]->Base_Bitmap == NULL)
	//	{

	//		LoadDummyTexture(Index);

	//		return 1;
	//	}
	//	else
	//	{
	//		BITMAPINFO    bmiData;
	//		ilutGetBmpInfo(&bmiData);

	//		App->CL_Model->Group[Index]->Depth = bmiData.bmiHeader.biBitCount;
	//		App->CL_Model->Group[Index]->Width = bmiData.bmiHeader.biWidth;
	//		App->CL_Model->Group[Index]->Height = bmiData.bmiHeader.biHeight;
	//		App->CL_Model->Group[Index]->Bitmap_Loaded = 1;
	//	}

	//	return 1;
	//}

	//// ------------------------------------ JPEG
	//if (stricmp(mFileName + strlen(mFileName) - 4, ".JPG") == 0)
	//{
	//	App->CL_Model->Group[Index]->Base_Bitmap = ilutWinLoadImage(mFileName, hDC);
	//	ReleaseDC(PreviewWnd, hDC);

	//	if (App->CL_Model->Group[Index]->Base_Bitmap == NULL)
	//	{

	//		LoadDummyTexture(Index);

	//		return 1;
	//	}
	//	else
	//	{
	//		BITMAPINFO    bmiData;
	//		ilutGetBmpInfo(&bmiData);

	//		App->CL_Model->Group[Index]->Depth = bmiData.bmiHeader.biBitCount;
	//		App->CL_Model->Group[Index]->Width = bmiData.bmiHeader.biWidth;
	//		App->CL_Model->Group[Index]->Height = bmiData.bmiHeader.biHeight;
	//		App->CL_Model->Group[Index]->Bitmap_Loaded = 1;
	//	}

	//	return 1;
	//}

	//// ------------------------------------ DDS
	//if (stricmp(mFileName + strlen(mFileName) - 4, ".DDS") == 0)
	//{
	//	App->CL_Model->Group[Index]->Base_Bitmap = ilutWinLoadImage(mFileName, hDC);
	//	ReleaseDC(PreviewWnd, hDC);
	//	
	//	if (App->CL_Model->Group[Index]->Base_Bitmap == NULL)
	//	{

	//		LoadDummyTexture(Index);

	//		return 1;
	//	}
	//	else
	//	{
	//		BITMAPINFO    bmiData;
	//		ilutGetBmpInfo(&bmiData);

	//		App->CL_Model->Group[Index]->Depth = bmiData.bmiHeader.biBitCount;
	//		App->CL_Model->Group[Index]->Width = bmiData.bmiHeader.biWidth;
	//		App->CL_Model->Group[Index]->Height = bmiData.bmiHeader.biHeight;
	//		App->CL_Model->Group[Index]->Bitmap_Loaded = 1;
	//	}

	//	return 1;
	//}

	//// ------------------------------------ TGA
	//if (stricmp(mFileName + strlen(mFileName) - 4, ".TGA") == 0)
	//{
	//	App->CL_Model->Group[Index]->Base_Bitmap = ilutWinLoadImage(mFileName, hDC);
	//	ReleaseDC(PreviewWnd, hDC);

	//	if (App->CL_Model->Group[Index]->Base_Bitmap == NULL)
	//	{
	//		
	//		LoadDummyTexture(Index);

	//		return 1;
	//	}
	//	else
	//	{
	//		BITMAPINFO    bmiData;
	//		ilutGetBmpInfo(&bmiData);

	//		App->CL_Model->Group[Index]->Depth = bmiData.bmiHeader.biBitCount;
	//		App->CL_Model->Group[Index]->Width = bmiData.bmiHeader.biWidth;
	//		App->CL_Model->Group[Index]->Height = bmiData.bmiHeader.biHeight;
	//		App->CL_Model->Group[Index]->Bitmap_Loaded = 1;
	//	}

	//	return 1;
	//}

	//// ------------------------------------ PNG
	//if (stricmp(mFileName + strlen(mFileName) - 4, ".PNG") == 0)
	//{
	//	App->CL_Model->Group[Index]->Base_Bitmap = ilutWinLoadImage(mFileName, hDC);
	//	ReleaseDC(PreviewWnd, hDC);

	//	if (App->CL_Model->Group[Index]->Base_Bitmap == NULL)
	//	{
	//		LoadDummyTexture(Index);

	//		return 1;
	//	}
	//	else
	//	{
	//		BITMAPINFO    bmiData;
	//		ilutGetBmpInfo(&bmiData);

	//		App->CL_Model->Group[Index]->Depth = bmiData.bmiHeader.biBitCount;
	//		App->CL_Model->Group[Index]->Width = bmiData.bmiHeader.biWidth;
	//		App->CL_Model->Group[Index]->Height = bmiData.bmiHeader.biHeight;
	//		App->CL_Model->Group[Index]->Bitmap_Loaded = 1;
	//	}

	//	return 1;
	//}

	//LoadDummyTexture(Index);
	//App->CL_Model->Group[Index]->Bitmap_Loaded = -1;

	return 1;
}

// *************************************************************************
// *		Load_OpenGL_Textures:- Terry and Hazel Flanigan 2023   	  	   *
// *************************************************************************
bool SB_Textures::Load_OpenGL_Textures(int TextureID)
{
	int Index = 0;
	int Dont = 0;
	int jpg = 0;
	int DontAdd = 0;
	int AddDummy = 0;

	char buf[1024];
	strcpy(buf, App->CLSB_Model->Texture_FolderPath);
	strcat(buf, "Etemp.bmp");

	UINT* Texture_List = App->CLSB_Ogre->RenderListener->g_Texture;

	// ----------------------------------- Bitmap
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".BMP") == 0)
	{
		bool test = Soil_Load_Texture(Texture_List, TextureFileName, TextureID);
		if (test == 0)
		{
			return 0;
		}

		return 1;
	}
	// ------------------------------------ JPEG
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".JPG") == 0)
	{
		bool test = Soil_Load_Texture(Texture_List, TextureFileName, TextureID);

		if (test == 0)
		{
			App->Error_ToFile("Failed to load JPG", TextureFileName);
			return 0;
		}

		return 1;
	}
	// ------------------------------------ TGA
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".TGA") == 0)
	{
		Soil_Load_Texture(Texture_List, TextureFileName, TextureID);
		return 1;
	}
	//// ------------------------------------ DDS
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".DDS") == 0)
	{
		Soil_Load_Texture(Texture_List, TextureFileName, TextureID);
		return 1;
	}
	//// ------------------------------------ PNG
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".PNG") == 0)
	{
		Soil_Load_Texture(Texture_List, TextureFileName, TextureID);
		return 1;
	}

	/*CreateDummyTexture();
	Soil_Load_Texture(g_Texture, buf, TextureID);
	remove(buf);*/

	return 1;
}

// *************************************************************************
// *		 Soil_Load_Texture:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
bool  SB_Textures::Soil_Load_Texture(UINT textureArray[], LPSTR strFileName, int textureID)
{
	int image_width = 0;
	int image_height = 0;
	int channels = 0;
	int force_channels = 4;

	unsigned char* image_data = stbi_load(strFileName, &image_width, &image_height, &channels, force_channels);
	if (image_data == NULL)
	{
		//App->Say("Cant Create Texture");
		return 0;
	}

	if ((force_channels >= 1) && (force_channels <= 4))
	{
		channels = force_channels;
	}

	bool INVERT_Y = 1;
	if (INVERT_Y == 1)
	{
		int i, j;
		for (j = 0; j * 2 < image_height; ++j)
		{
			int index1 = j * image_width * channels;
			int index2 = (image_height - 1 - j) * image_width * channels;
			for (i = image_width * channels; i > 0; --i)
			{
				unsigned char temp = image_data[index1];
				image_data[index1] = image_data[index2];
				image_data[index2] = temp;
				++index1;
				++index2;
			}
		}
	}

	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	textureArray[textureID] = image_texture;

	stbi_image_free(image_data);



	/*textureArray[textureID] = SOIL_load_OGL_texture
	(
		strFileName,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
	);*/

	if (textureArray[textureID] == 0) // Fall back attemp to convert and load or Bail
	{
		Texture_To_Bmp(strFileName);

		/*textureArray[textureID] = SOIL_load_OGL_texture
		(
			"Etemp.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
		);*/
		remove("Etemp.bmp");

		/*if (textureArray[textureID] == 0)
		{
			const char* test = SOIL_last_result();
			char buff[255];
			strcpy(buff, test);
			App->Say(buff);
			return 0;
		}*/

	}

	/*glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);*/

	return 1;
}

// *************************************************************************
// *			Texture_To_Bmp:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Textures::Texture_To_Bmp(char* File)
{
	ilLoadImage(File);
	ilSaveImage("Etemp.bmp");
	return 1;
}

// *************************************************************************
// *					CreateDummyTexture Terry Bernie   		 	 	   *
// *************************************************************************
bool SB_Textures::LoadDummyTexture(int Index)
{

	/*App->CLSB_Model->Group[Index]->Base_Bitmap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_DUMMY));

	strcpy(App->CLSB_Model->Group[Index]->Texture_PathFileName, "Internal Dummy BMP");
	strcpy(App->CLSB_Model->Group[Index]->Text_FileName, "Dummy.bmp");

	App->CLSB_Model->Group[Index]->Depth = 8;
	App->CLSB_Model->Group[Index]->Width = 256;
	App->CLSB_Model->Group[Index]->Height = 256;

	App->CLSB_Model->Group[Index]->Bitmap_Loaded = -1;*/
	return 1;
}

// *************************************************************************
// *					Genesis_WriteToBmp Terry Bernie   		 	 	   *
// *************************************************************************
int SB_Textures::Genesis_WriteToBmp(geBitmap* bmp, char* filename)
{
	BITMAPFILEHEADER 	bmfh;
	BITMAPINFOHEADER	bmih;
	int width, height, bpp;
	int datasize;
	geBitmap_Info Info;
	geBitmap_Info Palette_Info;
	void* data;
	geBitmap_Palette* palette;
	void* palette_data;
	int colors = 256;
	int palette_size = 0;
	int myRowWidth, bmpRowWidth, pelBytes;
	data = (void*)&bmp->Data[0];
	geBitmap_GetInfo(bmp, &Info, NULL);
	width = Info.Width;
	height = Info.Height;

	if (Info.Format == GE_PIXELFORMAT_8BIT_PAL)
	{
		palette_data = (void*)malloc(colors * 4);
		palette = geBitmap_GetPalette(bmp);
		geBitmap_Palette_GetInfo(palette, &Palette_Info);
		geBitmap_Palette_GetData(palette, palette_data, GE_PIXELFORMAT_32BIT_XRGB, colors);
		palette_size = colors * 4;
		bpp = 1;
	}

	else if (Info.Format == GE_PIXELFORMAT_16BIT_565_RGB || Info.Format == GE_PIXELFORMAT_16BIT_555_RGB)
	{

		bpp = 2;
	}
	else if ((Info.Format == GE_PIXELFORMAT_24BIT_RGB) || (Info.Format == GE_PIXELFORMAT_24BIT_BGR))
	{
		bpp = 3;
	}
	else if (Info.Format == GE_PIXELFORMAT_32BIT_ARGB)
	{
		bpp = 4;
	}

	else if (Info.Format == GE_PIXELFORMAT_32BIT_RGBA)
	{
		bpp = 4;
	}
	else if (Info.Format == GE_PIXELFORMAT_32BIT_XRGB)
	{
		bpp = 4;
	}
	else if (Info.Format == GE_PIXELFORMAT_32BIT_XBGR)
	{
		bpp = 4;
	}
	else
		return 0;

	datasize = width * height * bpp;  //write the file header bmfh  
	memset((void*)&bmfh, 0, sizeof(bmfh));
	bmfh.bfType = 'B' + ('M' << 8);
	bmfh.bfSize = sizeof(bmfh) + sizeof(bmih) + datasize;
	bmfh.bfOffBits = sizeof(bmfh) + sizeof(bmih) + palette_size;
	//write the info header bmih  
	memset((void*)&bmih, 0, sizeof(bmih));
	bmih.biSize = sizeof(bmih);
	bmih.biWidth = width;
	bmih.biHeight = height;
	bmih.biPlanes = 1;
	bmih.biBitCount = bpp * 8;

	if (bpp == 1)
	{
		bmih.biClrUsed = 0;
		bmih.biCompression = 0;
	}
	else
	{
		bmih.biCompression = BI_RGB;
	}

	bmih.biXPelsPerMeter = 2834;
	bmih.biYPelsPerMeter = 2834;
	FILE* file = fopen(filename, "wb");
	if (!file)
		return -1;
	fwrite((void*)&bmfh, sizeof(bmfh), 1, file);
	fwrite((void*)&bmih, sizeof(bmih), 1, file);
	if (bpp == 1)
		fwrite((void*)palette_data, colors * 4, 1, file);
	pelBytes = bpp;
	myRowWidth = bmp->Info.Stride * pelBytes;
	bmpRowWidth = (((bmih.biWidth * pelBytes) + 3) & (~3));
	if (bmih.biHeight > 0)
	{
		int y;
		char* row;
		row = (char*)bmp->Data[0];
		row += (bmp->Info.Height - 1) * myRowWidth;
		for (y = bmp->Info.Height; y--; )
		{
			fwrite((void*)row, bmpRowWidth, 1, file);
			row -= myRowWidth;
		}
	}
	fclose(file);

	return 1;
}

// *************************************************************************
// *				WriteTGA:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
int SB_Textures::WriteTGA(const char* pszFile, geBitmap* pBitmap)
{
	geBitmap* pLock = NULL;
	geBitmap* pLockA = NULL;
	gePixelFormat   Format;
	gePixelFormat   FormatA;
	geBitmap_Info   BitmapInfo;
	int             nErrorCode = TPACKERROR_UNKNOWN;      // Return code
	TGAHEADER2		tgah;
	long			footer = 0;
	char			signature[18] = "TRUEVISION-XFILE.";

	Ogre::uint8* pPixelData;
	Ogre::uint8* pPixelDataA;

	int             i, j;
	HANDLE          hFile = NULL;
	DWORD           nBytesWritten;

	// Create the .TGA file.
	hFile = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return TPACKERROR_CREATEFILE;

	// get 24-bit bitmap
	Format = GE_PIXELFORMAT_24BIT_BGR;
	FormatA = GE_PIXELFORMAT_8BIT_GRAY;

	if (geBitmap_GetBits(pBitmap))
	{
		pLock = pBitmap;
	}
	else
	{
		if (!geBitmap_LockForRead(pBitmap, &pLock, 0, 0, Format, GE_FALSE, 0))
		{
			return FALSE;
		}
	}

	if (geBitmap_GetBits(geBitmap_GetAlpha(pBitmap)))
	{
		pLockA = geBitmap_GetAlpha(pBitmap);
	}
	else
	{
		if (!geBitmap_LockForRead(geBitmap_GetAlpha(pBitmap), &pLockA, 0, 0, FormatA, GE_FALSE, 0))
		{
			App->Say("No Alpha");
			return FALSE;
		}
	}

	geBitmap_GetInfo(pLock, &BitmapInfo, NULL);
	if (BitmapInfo.Format != Format)
	{
		nErrorCode = TPACKERROR_UNKNOWN;
		goto ExitWriteBitmap;
	}


	tgah.IDLength = 0;
	tgah.ColorMapType = 0;
	tgah.ImageType = 2; // we create an uncompressed, true color image
	tgah.CMFirstEntry = 0;
	tgah.CMLength = 0;
	tgah.CMEntrySize = 0;
	tgah.Xorigin = 0;
	tgah.Yorigin = 0;

	tgah.Width = (Ogre::uint16)BitmapInfo.Width;
	tgah.Height = (Ogre::uint16)BitmapInfo.Height;

	tgah.PixelDepth = 32;
	tgah.ImageDescriptor = 8; //00001000 - not flipped, 8 alpha bits


	pPixelData = (Ogre::uint8*)geBitmap_GetBits(pLock);

	pPixelDataA = (Ogre::uint8*)geBitmap_GetBits(pLockA);

	// Write the tga header
	if (!WriteFile(hFile, (LPVOID)&tgah, sizeof(TGAHEADER2), (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	// write pixels
	pPixelData += 3 * tgah.Width * (tgah.Height - 1);
	pPixelDataA += tgah.Width * (tgah.Height - 1);
	for (i = 0; i < tgah.Height; i++)
	{
		for (j = 0; j < tgah.Width; j++)
		{
			if (!WriteFile(hFile, (LPVOID)pPixelData, 3, (LPDWORD)&nBytesWritten, (NULL)))
			{
				nErrorCode = TPACKERROR_WRITE;
				goto ExitWriteBitmap;
			}

			pPixelData +=3;


			if (!WriteFile(hFile, (LPVOID)pPixelDataA, 1, (LPDWORD)&nBytesWritten, (NULL)))
			{
				nErrorCode = TPACKERROR_WRITE;
				goto ExitWriteBitmap;
			}
			pPixelDataA++;
		}

		pPixelData -= 2 * 3 * tgah.Width;
		pPixelDataA -= 2 * tgah.Width;
	}

	// write the signature
	if (!WriteFile(hFile, (LPVOID)&footer, 4, (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	if (!WriteFile(hFile, (LPVOID)&footer, 4, (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	if (!WriteFile(hFile, (LPVOID)signature, 18, (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	CloseHandle(hFile);
	hFile = NULL;

	// Success!
	nErrorCode = TPACKERROR_OK;

ExitWriteBitmap:

	// Clean-up
	//------------------------------------
	// Make sure the file gets closed
	if (hFile)
		CloseHandle(hFile);

	// Unlock the geBitmap
	if (pLock != pBitmap)
	{
		geBitmap_UnLock(pLock);
	}

	if (pLockA != geBitmap_GetAlpha(pBitmap))
	{
		geBitmap_UnLock(pLockA);
	}
	
	return nErrorCode;
}

int SB_Textures::WriteBMP8(const char* pszFile, geBitmap* pBitmap)
{
	geBitmap* pLock = NULL;
	gePixelFormat    Format;
	geBitmap_Info    BitmapInfo;
	int              nErrorCode = TPACKERROR_UNKNOWN;      // Return code
	BITMAPFILEHEADER BmpHeader;                            // bitmap file-header 
	MY_BITMAPINFO    BmInfo;
	Ogre::uint32           nBytesPerPixel;
	void* pPixelData;
	Ogre::uint8* pOut = NULL;
	Ogre::uint8* pTmp = NULL;
	int              nNewStride = 0;
	int              nOldStride = 0;
	int              i;
	HANDLE           hFile = NULL;
	DWORD            nBytesWritten;
	Ogre::uint8* pNew;
	Ogre::uint8* pOld;
	int    y;

	// Create the .BMP file.
	hFile = CreateFile(pszFile,
		GENERIC_READ | GENERIC_WRITE,
		(DWORD)0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);

	if (hFile == INVALID_HANDLE_VALUE)

		return TPACKERROR_CREATEFILE;

	// get 8-bit palettized bitmap
	Format = GE_PIXELFORMAT_8BIT;

	if (geBitmap_GetBits(pBitmap))
	{
		pLock = pBitmap;
	}
	else
	{
		if (!geBitmap_LockForRead(pBitmap, &pLock, 0, 0, Format, GE_FALSE, 0))
		{
			return FALSE;
		}
	}

	geBitmap_GetInfo(pLock, &BitmapInfo, NULL);
	if (BitmapInfo.Format != Format)
	{
		nErrorCode = TPACKERROR_UNKNOWN;
		goto ExitWriteBitmap;
	}


	for (i = 0; i < 256; i++)
	{
		int r, g, b, a;
		geBitmap_Palette_GetEntryColor(BitmapInfo.Palette, i, &r, &g, &b, &a);

		BmInfo.bmiColors[i].rgbRed = (Ogre::uint8)r;
		BmInfo.bmiColors[i].rgbGreen = (Ogre::uint8)g;
		BmInfo.bmiColors[i].rgbBlue = (Ogre::uint8)b;
		BmInfo.bmiColors[i].rgbReserved = (Ogre::uint8)0;
	}

	nBytesPerPixel = gePixelFormat_BytesPerPel(Format);
	pPixelData = geBitmap_GetBits(pLock);

	// Build bitmap info
	BmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BmInfo.bmiHeader.biWidth = BitmapInfo.Width;
	BmInfo.bmiHeader.biHeight = BitmapInfo.Height;    // Bitmap are bottom-up
	BmInfo.bmiHeader.biPlanes = 1;
	BmInfo.bmiHeader.biBitCount = (WORD)8;
	BmInfo.bmiHeader.biCompression = BI_RGB;
	BmInfo.bmiHeader.biSizeImage = 0;
	BmInfo.bmiHeader.biXPelsPerMeter = BmInfo.bmiHeader.biYPelsPerMeter = 0;   // 10000;

	if (BmInfo.bmiHeader.biBitCount < 24)
		BmInfo.bmiHeader.biClrUsed = (1 << BmInfo.bmiHeader.biBitCount);
	else
		BmInfo.bmiHeader.biClrUsed = 0;

	BmInfo.bmiHeader.biClrImportant = 0;

	nNewStride = PAD32(BitmapInfo.Width * BmInfo.bmiHeader.biBitCount);
	nOldStride = BitmapInfo.Width * nBytesPerPixel;

	BmInfo.bmiHeader.biSizeImage = nNewStride * BitmapInfo.Height;

	if (nNewStride == nOldStride)
	{
		pTmp = (Ogre::uint8*)pPixelData;
	}

	// Allocate new pixel buffer.
	else
	{
		pTmp = (Ogre::uint8*)geRam_Allocate(nNewStride * BitmapInfo.Height);
		if (pTmp == (Ogre::uint8*)0)
		{
			// Memory allocation error
			nErrorCode = TPACKERROR_MEMORYALLOCATION;
			goto ExitWriteBitmap;
		}


		pNew = (Ogre::uint8*)pTmp;
		pOld = (Ogre::uint8*)pPixelData;

		// Copy old to new
		for (y = 0; y < BitmapInfo.Height; y++)
		{
			memcpy(pNew, pOld, nOldStride);

			// Next row
			pOld += nOldStride;
			pNew += nNewStride;
		}
	}

	pOut = (Ogre::uint8*)geRam_Allocate(nNewStride * BitmapInfo.Height);
	if (pOut == (Ogre::uint8*)0)
	{
		// Memory allocation error
		nErrorCode = TPACKERROR_MEMORYALLOCATION;
		goto ExitWriteBitmap;
	}

	pNew = (Ogre::uint8*)pOut;
	pOld = (Ogre::uint8*)(pTmp + (nNewStride * (BitmapInfo.Height - 1)));

	// Copy old to new
	for (y = 0; y < BitmapInfo.Height; y++)
	{
		memcpy(pNew, pOld, nNewStride);

		// Next row
		pOld -= nNewStride;
		pNew += nNewStride;
	}

	if (pTmp && nNewStride != nOldStride)
		geRam_Free(pTmp);

	// Build the file header
	BmpHeader.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 

	// Compute the size of the entire file. 
	BmpHeader.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		BmInfo.bmiHeader.biSize +
		(BmInfo.bmiHeader.biClrUsed * sizeof(RGBQUAD)) +
		(nNewStride * BitmapInfo.Height));
	BmpHeader.bfReserved1 = 0;
	BmpHeader.bfReserved2 = 0;

	// Compute the offset to the array of color indices. 
	BmpHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) +
		BmInfo.bmiHeader.biSize +
		(BmInfo.bmiHeader.biClrUsed * sizeof(RGBQUAD));

	// Write the BMP file header
	if (!WriteFile(hFile, (LPVOID)&BmpHeader, sizeof(BITMAPFILEHEADER), (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	// Write the Bitmap infor header and palette
	if (!WriteFile(hFile, (LPVOID)&BmInfo, sizeof(MY_BITMAPINFO), (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	// Write the pixel data
	if (!WriteFile(hFile, (LPVOID)pOut, nNewStride * BitmapInfo.Height, (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	CloseHandle(hFile);
	hFile = NULL;

	// Success!
	nErrorCode = TPACKERROR_OK;

ExitWriteBitmap:

	// Clean-up
	//------------------------------------
	// Make sure the file gets closed
	if (hFile)
		CloseHandle(hFile);

	geRam_Free(pOut);

	// Unlock the geBitmap
	if (pLock != pBitmap)
	{
		geBitmap_UnLock(pLock);
	}
	return nErrorCode;
}

// *************************************************************************
// *		HBITMAP_TO_BmpFile:- Terry and Hazel Flanigan 2023		 	   *
// *************************************************************************
bool SB_Textures::HBITMAP_TO_BmpFile(HBITMAP Bitmap, char* Filename, char* SaveFolder)
{
	HDC hDC;
	int iBits;
	WORD wBitCount;
	DWORD dwPaletteSize = 0, dwBmBitsSize = 0, dwDIBSize = 0, dwWritten = 0;
	BITMAP Bitmap0;
	BITMAPFILEHEADER bmfHdr;
	BITMAPINFOHEADER bi;
	LPBITMAPINFOHEADER lpbi;
	HANDLE fh, hDib, hPal, hOldPal2 = NULL;
	hDC = CreateDC(TEXT("DISPLAY"), NULL, NULL, NULL);
	iBits = GetDeviceCaps(hDC, BITSPIXEL) * GetDeviceCaps(hDC, PLANES);
	DeleteDC(hDC);
	if (iBits <= 1)
		wBitCount = 1;
	else if (iBits <= 4)
		wBitCount = 4;
	else if (iBits <= 8)
		wBitCount = 8;
	else
		wBitCount = 24;
	GetObject(Bitmap, sizeof(Bitmap0), (LPSTR)&Bitmap0);
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = Bitmap0.bmWidth;
	bi.biHeight = -Bitmap0.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = wBitCount;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrImportant = 0;
	bi.biClrUsed = 256;
	dwBmBitsSize = ((Bitmap0.bmWidth * wBitCount + 31) & ~31) / 8
		* Bitmap0.bmHeight;
	hDib = GlobalAlloc(GHND, dwBmBitsSize + dwPaletteSize + sizeof(BITMAPINFOHEADER));
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	hPal = GetStockObject(DEFAULT_PALETTE);
	if (hPal)
	{
		hDC = GetDC(NULL);
		hOldPal2 = SelectPalette(hDC, (HPALETTE)hPal, FALSE);
		RealizePalette(hDC);
	}


	GetDIBits(hDC, Bitmap, 0, (UINT)Bitmap0.bmHeight, (LPSTR)lpbi + sizeof(BITMAPINFOHEADER)
		+ dwPaletteSize, (BITMAPINFO*)lpbi, DIB_RGB_COLORS);

	if (hOldPal2)
	{
		SelectPalette(hDC, (HPALETTE)hOldPal2, TRUE);
		RealizePalette(hDC);
		ReleaseDC(NULL, hDC);
	}

	fh = CreateFile(Filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (fh == INVALID_HANDLE_VALUE)
		return FALSE;

	bmfHdr.bfType = 0x4D42; // "BM"
	dwDIBSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dwPaletteSize + dwBmBitsSize;
	bmfHdr.bfSize = dwDIBSize;
	bmfHdr.bfReserved1 = 0;
	bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER) + dwPaletteSize;

	WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

	WriteFile(fh, (LPSTR)lpbi, dwDIBSize, &dwWritten, NULL);
	GlobalUnlock(hDib);
	GlobalFree(hDib);
	CloseHandle(fh);

	return 1;
}

// *************************************************************************
// *							Jpg_To_png24					  		 	   *
// *************************************************************************
bool SB_Textures::Jpg_To_png24(char* File)
{
	char OldFile[1024];
	strcpy(OldFile, File);

	ilLoadImage(File);

	int Len = strlen(File);
	File[Len - 4] = 0;
	strcat(File, ".png");

	ilSaveImage(File);

	remove(OldFile);
	return 1;
}

// *************************************************************************
// *			Bmp_To_Jpg:- Terry and Hazel Flanigan 2023		  	 	   *
// *************************************************************************
bool SB_Textures::Bmp_To_Jpg(char* File)
{
	char OldFile[1024];
	strcpy(OldFile, File);

	bool test = ilLoadImage(File);
	if (test == 0)
	{
		App->Say("Failed to load Texture Bmp_To_Jpg");
	}

	int Len = strlen(File);
	File[Len - 4] = 0;
	strcat(File, ".jpg");

	ilSaveImage(File);

	remove(OldFile);
	return 1;
}

// *************************************************************************
// *		Create_DummyTexture:- Terry and Hazel Flanigan 2023    	 	   *
// *************************************************************************
bool SB_Textures::Create_DummyTexture(char* Folder)
{
	HBITMAP hbmpTemp;
	hbmpTemp = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_DUMMY));

	char OutFile[MAX_PATH];
	strcpy(OutFile, Folder);
	strcat(OutFile, "TTemp.bmp");
	
	HBITMAP_TO_BmpFile(hbmpTemp, OutFile, "");
	return 1;
}

// ----------------------------------------
// 
// *************************************************************************
// *		Extract_TXL_Texture:- Terry and Hazel Flanigan 2023    	 	   *
// *************************************************************************
bool SB_Textures::Extract_TXL_Texture(char* Name, char* Folder)
{
	App->Get_Current_Document();
	WadFileEntry* BitmapPtr = App->m_pDoc->GetDibBitmap(Name);

	int nErrorCode;

	char Name2[MAX_PATH];
	strcpy(Name2, Folder);

	if (geBitmap_HasAlpha(BitmapPtr->bmp))
	{
		LoadTextures_TXL(Name);

		//App->Say(BitmapPtr->Name);

		char Buf1[200];
		strcpy(Buf1, BitmapPtr->Name);
		strcat(Buf1, ".tga");

		strcat(Name2, Buf1);
		//App->CL_TxlEditor->WriteTGA(Name2, BitmapPtr->bmp);
		nErrorCode = WriteTGA(Name2, Temp_RF_Bitmap);
	}
	else
	{
		char Buf1[200];
		strcpy(Buf1, BitmapPtr->Name);
		strcat(Buf1, ".bmp");

		strcat(Name2, Buf1);

		nErrorCode = WriteBMP8(Name2, BitmapPtr->bmp);
	}

	if (nErrorCode != TPACKERROR_OK)
	{
		// Error writing this bitmap
		switch (nErrorCode)
		{
		case TPACKERROR_CREATEFILE:
			App->Say("Unable to create output file %s");
			break;
		case TPACKERROR_WRITE:
			App->Say("I/O error writing %s");
			break;
		case TPACKERROR_MEMORYALLOCATION:
			App->Say("Memory allocation error writing %s");
			break;
		case TPACKERROR_UNKNOWN:
		default:
			App->Say("UInknown error writing %s");
		}
	}

	return 1;
}

// *************************************************************************
// *			LoadTextures_TXL:- Terry and Hazel Flanigan 2023 		   *
// *************************************************************************
bool SB_Textures::LoadTextures_TXL(char* Name)
{
	VFS = NULL;

	geVFile* File = NULL;
	geVFile_Finder* Finder = NULL;

	//NameCount = 0;

	VFS = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_VIRTUAL, App->CL_World->mCurrent_TXL_FilePath, NULL, GE_VFILE_OPEN_READONLY | GE_VFILE_OPEN_DIRECTORY);
	if (!VFS)
	{
		App->Say("Could not open file", App->CL_World->mCurrent_TXL_FilePath);
		return 0;
	}

	Finder = geVFile_CreateFinder(VFS, "*.*");
	if (!Finder)
	{
		App->Say("Could not create Finder *.* ");

		geVFile_Close(VFS);
		return 0;
	}


	if (VFS)
	{
		File = geVFile_Open(VFS, Name, GE_VFILE_OPEN_READONLY);
	}

	if (!File)
	{
		App->Say("Could not open", Name);
		return 0;
	}

	Temp_RF_Bitmap = geBitmap_CreateFromFile(File);

	App->Say("Loaded TXL");
	/*BitMap_Names.resize(100);

	while (geVFile_FinderGetNextFile(Finder) != GE_FALSE)
	{
		geVFile_Properties	Properties;

		geVFile_FinderGetProperties(Finder, &Properties);

		strcpy(BitMap_Names[NameCount].Name, Properties.Name);

		NameCount++;
	}

	Copy_Texture_Names();

	Check_for_Textures(VFS);*/

	geVFile_Close(File);
	geVFile_Close(VFS);

	return 1;
}
