/*
Copyright (c) 2022- 2023 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Load_Textures.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "il.h"
#include "ilu.h"
#include "ilut.h"

#include "bitmap.h"
#include "bitmap._h"
#include "bitmap.__h"

SB_Load_Textures::SB_Load_Textures()
{
	TextureFileName[0] = 0;
}

SB_Load_Textures::~SB_Load_Textures()
{
}

// *************************************************************************
// *			Load_Textures_Assimp Terry Bernie Hazel			  	 	   *
// *************************************************************************
void SB_Load_Textures::Load_Textures_Assimp()
{
	int v = 0;
	int Count = 0;

	int mGroupCount = App->CLSB_Model->Get_Groupt_Count();

	while (Count < mGroupCount)
	{
		char JustFileName[MAX_PATH];
		GetFileTitleA(App->CLSB_Model->Group[Count]->Text_FileName, JustFileName, MAX_PATH);
		strcpy(App->CLSB_Model->Group[Count]->Text_FileName,JustFileName);

		int Test = strcmp(JustFileName, "No_Texture");
		if (Test != 0) // not a match
		{

			char ImageFullPath[MAX_PATH];
			strcpy(ImageFullPath, App->CLSB_Model->Texture_FolderPath);
			strcat(ImageFullPath, App->CLSB_Model->Group[Count]->Text_FileName);

			strcpy(App->CLSB_Model->Group[v]->Texture_PathFileName, ImageFullPath);

			strcpy(TextureFileName, ImageFullPath);

			Windows_Preview_FullPath(v, ImageFullPath);

			Load_OpenGL_Textures(App->CLSB_Model->Group[Count]->MaterialIndex);

			v++;
		}
		else
		{
			//LoadDummyTexture();

			//int MatIndex = App->CL_Vm_Model->S_MeshGroup[Count]->MaterialIndex;
			//App->CL_Vm_Model->S_TextureInfo[Count]->ActorMaterialIndex = MatIndex;

			//App->CL_Vm_Model->S_MeshGroup[v]->Soil_TextureIndex = MatIndex;

			//strcpy(App->CL_Vm_Model->S_MeshGroup[v]->Text_FileName, "Etemp.bmp");
			//strcpy(App->CL_Vm_Model->S_TextureInfo[Count]->MaterialName, "Etemp.bmp");

			//char ImageFullPath[1024];
			//strcpy(ImageFullPath, App->CL_Vm_Model->Texture_FolderPath);
			//strcat(ImageFullPath, "Etemp.bmp");

			//strcpy(App->CL_Vm_Model->S_MeshGroup[v]->Text_PathFileName, ImageFullPath);
			//strcpy(App->CL_Vm_Textures->TextureFileName, ImageFullPath);

			//App->CL_Vm_Textures->TexureToWinPreviewFullPath(v, ImageFullPath);
			//App->CL_Vm_Textures->Soil_DecodeTextures(MatIndex); // ??

			//		remove(ImageFullPath);

			v++;
		}
		Count++;
	}
}

// *************************************************************************
// *	  				Load_Textures_Ogre3D Terry Bernie				   *
// *************************************************************************
void SB_Load_Textures::Load_Textures_Ogre3D(void)
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
bool SB_Load_Textures::Windows_Preview_FullPath(int Index, char* FullPath)
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
bool SB_Load_Textures::Load_OpenGL_Textures(int TextureID)
{
	int Index = 0;
	int Dont = 0;
	int jpg = 0;
	int DontAdd = 0;
	int AddDummy = 0;

	char buf[1024];
	strcpy(buf, App->CLSB_Model->Texture_FolderPath);
	strcat(buf, "Etemp.bmp");

	UINT  *Texture_List = App->CLSB_Ogre->RenderListener->g_Texture;

	// ----------------------------------- Bitmap
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".BMP") == 0)
	{
		Soil_Load_Texture(Texture_List, TextureFileName, TextureID);
		return 1;
	}
	// ------------------------------------ JPEG
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".JPG") == 0)
	{
		Soil_Load_Texture(Texture_List, TextureFileName, TextureID);
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
bool  SB_Load_Textures::Soil_Load_Texture(UINT textureArray[], LPSTR strFileName, int textureID)
{
	int image_width = 0;
	int image_height = 0;
	int channels = 0;
	int force_channels = 4;

	unsigned char* image_data = stbi_load(strFileName, &image_width, &image_height, &channels, force_channels);
	if (image_data == NULL)
	{
		App->Say("Cant Create Texture");
		return false;
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
bool SB_Load_Textures::Texture_To_Bmp(char* File)
{
	ilLoadImage(File);
	ilSaveImage("Etemp.bmp");
	return 1;
}

// *************************************************************************
// *					CreateDummyTexture Terry Bernie   		 	 	   *
// *************************************************************************
bool SB_Load_Textures::LoadDummyTexture(int Index)
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
int SB_Load_Textures::Genesis_WriteToBmp(geBitmap* bmp, char* filename)
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
