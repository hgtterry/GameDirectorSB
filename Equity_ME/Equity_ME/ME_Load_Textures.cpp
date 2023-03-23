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
#include "ME_App.h"
#include "resource.h"
#include "ME_Load_Textures.h"

#include "SOIL.h"

#include "il.h"
#include "ilu.h"
#include "ilut.h"

ME_Load_Textures::ME_Load_Textures()
{
	TextureFileName[0] = 0;
}

ME_Load_Textures::~ME_Load_Textures()
{
}

// *************************************************************************
// *			Load_Textures_Assimp Terry Bernie Hazel			  	 	   *
// *************************************************************************
void ME_Load_Textures::Load_Textures_Assimp()
{
	int v = 0;
	int Count = 0;

	int mGroupCount = App->CL_Model->Get_Groupt_Count();

	while (Count < mGroupCount)
	{
		char JustFileName[MAX_PATH];
		GetFileTitleA(App->CL_Model->Group[Count]->Text_FileName, JustFileName, MAX_PATH);
		strcpy(App->CL_Model->Group[Count]->Text_FileName,JustFileName);

		int Test = strcmp(JustFileName, "No_Texture");
		if (Test != 0) // not a match
		{

			char ImageFullPath[MAX_PATH];
			strcpy(ImageFullPath, App->CL_Model->Texture_FolderPath);
			strcat(ImageFullPath, App->CL_Model->Group[Count]->Text_FileName);

			strcpy(App->CL_Model->Group[v]->Texture_PathFileName, ImageFullPath);

			strcpy(TextureFileName, ImageFullPath);

			Windows_Preview_FullPath(v, ImageFullPath);

			Load_OpenGL_Textures(App->CL_Model->Group[Count]->MaterialIndex);

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
void ME_Load_Textures::Load_Textures_Ogre3D(void)
{
	int SubMeshCount = App->CL_Ogre3D->OgreModel_Ent->getNumSubEntities();

	int mMaterialindex = 0;
	int Count = 0;
	char MatName[255];
	char TextureName[255];
	char SubMeshName[255];
	char buf[255];

	strcpy(SubMeshName, "SubMesh_");

	while (Count < SubMeshCount)
	{
		Ogre::SubMesh const* subMesh = App->CL_Ogre3D->OgreModel_Ent->getSubEntity(Count)->getSubMesh();
		strcpy(MatName, subMesh->getMaterialName().c_str());

		itoa(Count, buf, 10);
		strcpy(SubMeshName, "SubMesh_");
		strcat(SubMeshName, buf);

		Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().getByName(MatName);

		if (material.isNull())
		{
			App->CL_Ogre3D->NoMaterialFileFound = 1; // Flag we dont have a texture yet
			//App->Say_Int(NoMaterialFileFound);
		}
		else
		{
			Ogre::Technique* technique = material->getTechnique(0);
			if (technique == NULL)
			{

			}
			else
			{
				Ogre::Pass* pass;
				pass = technique->getPass(0);
				if (pass == NULL)
				{
				}
				else
				{
					int TextureUnitCount = pass->getNumTextureUnitStates();
					if (TextureUnitCount == 0)
					{
						strcpy(App->CL_Model->Group[Count]->Text_FileName, "No_Texture");
						//App->S_MeshGroup[Count]->IsValid = 0;
						App->CL_Ogre3D->NoTexture = 1;
					}
					else
					{
						Ogre::TextureUnitState* textureUnit = pass->getTextureUnitState(0);

						Ogre::String TxtName = textureUnit->getTextureName();

						strcpy(TextureName, TxtName.c_str());

						strcpy(App->CL_Model->Group[Count]->Text_FileName, TextureName);

						App->CL_Ogre3D->NoTexture = 0;

						bool result = 0;

						//result = App->CL_FileIO->SearchFolders(App->CL_Model->Texture_FolderPath, TextureName);

						if (result == 0) // Texture Found in Mesh Folder
						{
							//App->Say_Win(App->CL_Model->Texture_FolderPath);

							char ImageFullPath[MAX_PATH];
							strcpy(ImageFullPath, App->CL_Model->Texture_FolderPath);
							strcat(ImageFullPath, TextureName);

							strcpy(App->CL_Load_Textures->TextureFileName, ImageFullPath);

							strcpy(App->CL_Model->Group[Count]->Texture_FolderPath, ImageFullPath);
							strcpy(App->CL_Model->Group[Count]->Text_FileName, TextureName);

							App->CL_Load_Textures->Windows_Preview_FullPath(Count, ImageFullPath);

							//App->CL_Textures->TexureToWinPreviewFullPath(Count, TextureName);
							App->CL_Model->Group[Count]->MaterialIndex = mMaterialindex;

							App->CL_Load_Textures->Load_OpenGL_Textures(mMaterialindex);
							//App->CL_Textures->Soil_DecodeTextures(mMaterialindex);
							mMaterialindex++;
						}
						else
						{
							//if (ExternalResourceLoaded == 1) // Search for texture via resource file
							//{
							//	Scan_ResourcesNew(ResourcePathAndFile, Count);

							//	strcpy(App->CL_Textures->TextureFileName, App->CL_Model->Group[Count]->Texture_FolderPath);

							//	App->CL_Model->Group[Count]->MaterialIndex = mMaterialindex;

							//	App->CL_Textures->Soil_DecodeTextures(mMaterialindex);
							//	mMaterialindex++;
							//}
						}
					}
				}
			}
		}

		Count++;
	}
}

// *************************************************************************
// *						Windows_Preview_FullPath			  	 	   *
// *************************************************************************
bool ME_Load_Textures::Windows_Preview_FullPath(int Index, char* FullPath)
{

	char mFileName[MAX_PATH];
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

			return 1;
		}
		else
		{
			BITMAPINFO    bmiData;
			ilutGetBmpInfo(&bmiData);

			App->CL_Model->Group[Index]->Depth = bmiData.bmiHeader.biBitCount;
			App->CL_Model->Group[Index]->Width = bmiData.bmiHeader.biWidth;
			App->CL_Model->Group[Index]->Height = bmiData.bmiHeader.biHeight;
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

			return 1;
		}
		else
		{
			BITMAPINFO    bmiData;
			ilutGetBmpInfo(&bmiData);

			App->CL_Model->Group[Index]->Depth = bmiData.bmiHeader.biBitCount;
			App->CL_Model->Group[Index]->Width = bmiData.bmiHeader.biWidth;
			App->CL_Model->Group[Index]->Height = bmiData.bmiHeader.biHeight;
			App->CL_Model->Group[Index]->Bitmap_Loaded = 1;
		}

		return 1;
	}

	// ------------------------------------ DDS
	if (stricmp(mFileName + strlen(mFileName) - 4, ".DDS") == 0)
	{
		App->CL_Model->Group[Index]->Base_Bitmap = ilutWinLoadImage(mFileName, hDC);
		ReleaseDC(PreviewWnd, hDC);
		
		if (App->CL_Model->Group[Index]->Base_Bitmap == NULL)
		{

			LoadDummyTexture(Index);

			return 1;
		}
		else
		{
			BITMAPINFO    bmiData;
			ilutGetBmpInfo(&bmiData);

			App->CL_Model->Group[Index]->Depth = bmiData.bmiHeader.biBitCount;
			App->CL_Model->Group[Index]->Width = bmiData.bmiHeader.biWidth;
			App->CL_Model->Group[Index]->Height = bmiData.bmiHeader.biHeight;
			App->CL_Model->Group[Index]->Bitmap_Loaded = 1;
		}

		return 1;
	}

	// ------------------------------------ TGA
	if (stricmp(mFileName + strlen(mFileName) - 4, ".TGA") == 0)
	{
		App->CL_Model->Group[Index]->Base_Bitmap = ilutWinLoadImage(mFileName, hDC);
		ReleaseDC(PreviewWnd, hDC);

		if (App->CL_Model->Group[Index]->Base_Bitmap == NULL)
		{
			
			LoadDummyTexture(Index);

			return 1;
		}
		else
		{
			BITMAPINFO    bmiData;
			ilutGetBmpInfo(&bmiData);

			App->CL_Model->Group[Index]->Depth = bmiData.bmiHeader.biBitCount;
			App->CL_Model->Group[Index]->Width = bmiData.bmiHeader.biWidth;
			App->CL_Model->Group[Index]->Height = bmiData.bmiHeader.biHeight;
			App->CL_Model->Group[Index]->Bitmap_Loaded = 1;
		}

		return 1;
	}

	// ------------------------------------ PNG
	if (stricmp(mFileName + strlen(mFileName) - 4, ".PNG") == 0)
	{
		App->CL_Model->Group[Index]->Base_Bitmap = ilutWinLoadImage(mFileName, hDC);
		ReleaseDC(PreviewWnd, hDC);

		if (App->CL_Model->Group[Index]->Base_Bitmap == NULL)
		{
			LoadDummyTexture(Index);

			return 1;
		}
		else
		{
			BITMAPINFO    bmiData;
			ilutGetBmpInfo(&bmiData);

			App->CL_Model->Group[Index]->Depth = bmiData.bmiHeader.biBitCount;
			App->CL_Model->Group[Index]->Width = bmiData.bmiHeader.biWidth;
			App->CL_Model->Group[Index]->Height = bmiData.bmiHeader.biHeight;
			App->CL_Model->Group[Index]->Bitmap_Loaded = 1;
		}

		return 1;
	}

	LoadDummyTexture(Index);
	App->CL_Model->Group[Index]->Bitmap_Loaded = -1;

	return 1;
}

// *************************************************************************
// *		Load_OpenGL_Textures:- Terry and Hazel Flanigan 2023   	  	   *
// *************************************************************************
bool ME_Load_Textures::Load_OpenGL_Textures(int TextureID)
{
	int Index = 0;
	int Dont = 0;
	int jpg = 0;
	int DontAdd = 0;
	int AddDummy = 0;

	char buf[1024];
	strcpy(buf, App->CL_Model->Texture_FolderPath);
	strcat(buf, "Etemp.bmp");

	UINT  *Texture_List = App->CL_Ogre->RenderListener->g_Texture;

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
bool  ME_Load_Textures::Soil_Load_Texture(UINT textureArray[], LPSTR strFileName, int textureID)
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
		Texture_To_Bmp(strFileName);

		textureArray[textureID] = SOIL_load_OGL_texture
		(
			"Etemp.bmp",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
		);
		remove("Etemp.bmp");

		if (textureArray[textureID] == 0)
		{
			const char* test = SOIL_last_result();
			char buff[255];
			strcpy(buff, test);
			App->Say(buff);
			return 0;
		}

	}

	glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	return 1;
}

// *************************************************************************
// *			Texture_To_Bmp:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool ME_Load_Textures::Texture_To_Bmp(char* File)
{
	ilLoadImage(File);
	ilSaveImage("Etemp.bmp");
	return 1;
}

// *************************************************************************
// *					CreateDummyTexture Terry Bernie   		 	 	   *
// *************************************************************************
bool ME_Load_Textures::LoadDummyTexture(int Index)
{

	App->CL_Model->Group[Index]->Base_Bitmap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_DUMMY));

	strcpy(App->CL_Model->Group[Index]->Texture_PathFileName, "Internal Dummy BMP");
	strcpy(App->CL_Model->Group[Index]->Text_FileName, "Dummy.bmp");

	App->CL_Model->Group[Index]->Depth = 8;
	App->CL_Model->Group[Index]->Width = 256;
	App->CL_Model->Group[Index]->Height = 256;

	App->CL_Model->Group[Index]->Bitmap_Loaded = -1;
	return 1;
}
