#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "VM_Textures.h"

#include "SOIL.h"

#include "il.h"
#include "ilu.h"
#include "ilut.h"

#include "bitmap.h"
#include "bitmap._h"
#include "bitmap.__h"

VM_Textures::VM_Textures()
{
}


VM_Textures::~VM_Textures()
{
}

// *************************************************************************
// *					Genesis_WriteTGA Terry Bernie			  		   *
// *************************************************************************
int VM_Textures::Genesis_WriteTGA(const char * pszFile, geBitmap *pBitmap)
{
	geBitmap *      pLock = NULL;
	geBitmap *		pLockA = NULL;
	gePixelFormat   Format;
	gePixelFormat   FormatA;
	geBitmap_Info   BitmapInfo;
	int             nErrorCode = TPACKERROR_UNKNOWN;      // Return code
	TGAHEADER		tgah;
	long			footer = 0;
	char			signature[18] = "TRUEVISION-XFILE.";

	Ogre::uint8 *       pPixelData;
	Ogre::uint8 *		pPixelDataA;

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
	if (!WriteFile(hFile, (LPVOID)&tgah, sizeof(TGAHEADER), (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	// write pixels
	pPixelData += 3 * tgah.Width*(tgah.Height - 1);
	pPixelDataA += tgah.Width*(tgah.Height - 1);
	for (i = 0; i<tgah.Height; i++)
	{
		for (j = 0; j<tgah.Width; j++)
		{
			if (!WriteFile(hFile, (LPVOID)pPixelData, 3, (LPDWORD)&nBytesWritten, (NULL)))
			{
				nErrorCode = TPACKERROR_WRITE;
				goto ExitWriteBitmap;
			}

			pPixelData += 3;

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

// *************************************************************************
// *						WriteToBmp Terry Bernie		   		   	   	   *
// *************************************************************************
int VM_Textures::Genesis_WriteToBmp(geBitmap *bmp, char *filename)
{
	BITMAPFILEHEADER 	bmfh;
	BITMAPINFOHEADER	bmih;
	int width, height, bpp;
	int datasize;
	geBitmap_Info Info;
	geBitmap_Info Palette_Info;
	void *data;
	geBitmap_Palette * palette;
	void *palette_data = nullptr;
	int colors = 256;
	int palette_size = 0;
	int myRowWidth, bmpRowWidth, pelBytes;
	data = (void *)&bmp->Data[0];
	geBitmap_GetInfo(bmp, &Info, NULL);
	width = Info.Width;
	height = Info.Height;

	if (Info.Format == GE_PIXELFORMAT_8BIT_PAL)
	{
		palette_data = (void *)malloc(colors * 4);
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
	memset((void *)&bmfh, 0, sizeof(bmfh));
	bmfh.bfType = 'B' + ('M' << 8);
	bmfh.bfSize = sizeof(bmfh) + sizeof(bmih) + datasize;
	bmfh.bfOffBits = sizeof(bmfh) + sizeof(bmih) + palette_size;
	//write the info header bmih  
	memset((void *)&bmih, 0, sizeof(bmih));
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
	FILE *file = fopen(filename, "wb");
	if (!file)
		return -1;
	fwrite((void *)&bmfh, sizeof(bmfh), 1, file);
	fwrite((void *)&bmih, sizeof(bmih), 1, file);
	if (bpp == 1)
		fwrite((void *)palette_data, colors * 4, 1, file);
	pelBytes = bpp;
	myRowWidth = bmp->Info.Stride * pelBytes;
	bmpRowWidth = (((bmih.biWidth * pelBytes) + 3)&(~3));
	if (bmih.biHeight > 0)
	{
		int y;
		char * row;
		row = (char *)bmp->Data[0];
		row += (bmp->Info.Height - 1) * myRowWidth;
		for (y = bmp->Info.Height; y--; )
		{
			fwrite((void *)row, bmpRowWidth, 1, file);
			row -= myRowWidth;
		}
	}
	fclose(file);

	return 1;
}

// *************************************************************************
// *					Soil_Load_Texture Terry Bernie		  		  	   *
// *************************************************************************
bool VM_Textures::Soil_Load_Texture(UINT textureArray[], LPSTR strFileName, int textureID)
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

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return 1;
}

// *************************************************************************
// *							Texture_To_Bmp				  		 	   *
// *************************************************************************
bool VM_Textures::Texture_To_Bmp(char* File)
{
	ilLoadImage(File);
	ilSaveImage("Etemp.bmp");
	return 1;
}

// *************************************************************************
// *						TexureToWinPreviewFullPath			  	 	   *
// *************************************************************************
bool VM_Textures::TexureToWinPreviewFullPath(int Index, char* FullPath)
{
	char mFileName[1024];
	strcpy(mFileName, FullPath);

	// ----------------------------------- Bitmap
	if (_stricmp(mFileName + strlen(mFileName) - 4, ".BMP") == 0)
	{
	
		App->CL_Vm_Model->S_MeshGroup[Index]->Base_Bitmap = (HBITMAP)LoadImage(NULL, mFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		
		App->CL_Vm_Model->S_MeshGroup[Index]->Bitmap_Loaded = 1;
		
		return 1;
	}
	// ------------------------------------ TGA
	if (_stricmp(mFileName + strlen(mFileName) - 4, ".TGA") == 0)
	{
		
		Texture_To_Bmp(mFileName);
		App->CL_Vm_Model->S_MeshGroup[Index]->Base_Bitmap = (HBITMAP)LoadImage(NULL, mFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		App->CL_Vm_Model->S_MeshGroup[Index]->Bitmap_Loaded = 1;

		int test = remove("Etemp.bmp");
		return 1;
	}
	// ------------------------------------ JPEG
	if (_stricmp(mFileName + strlen(mFileName) - 4, ".JPG") == 0)
	{
		Texture_To_Bmp(mFileName);
		
		

		App->CL_Vm_Model->S_MeshGroup[Index]->Bitmap_Loaded = 1;

		remove("Etemp.bmp");
		return 1;
	}
	// ------------------------------------ DDS
	if (_stricmp(mFileName + strlen(mFileName) - 4, ".DDS") == 0)
	{
		Texture_To_Bmp(mFileName);
		
		

		App->CL_Vm_Model->S_MeshGroup[Index]->Bitmap_Loaded = 1;

		remove("Etemp.bmp");
		return 1;
	}
	// ------------------------------------ PNG
	if (_stricmp(mFileName + strlen(mFileName) - 4, ".PNG") == 0)
	{
		Texture_To_Bmp(mFileName);
		

		App->CL_Vm_Model->S_MeshGroup[Index]->Bitmap_Loaded = 1;

		remove("Etemp.bmp");
		return 1;
	}

	
	// if all fails dummy texture here 

	//CreateDummyTexture();

	//char buf[1024];
	//strcpy(buf,App->EquityDirecory_FullPath);
	//strcat(buf,"\\");
	//strcat(buf,"Etemp.bmp");

	//App->CL_Model_Data->S_MeshGroup[Index]->Base_Bitmap = ilutWinLoadImage("Etemp.bmp",hDC);
	////Soil_Load_Texture(g_Texture,buf,TextureID);
	//remove(buf);

	return 1;
}
