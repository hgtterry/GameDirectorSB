#include "stdafx.h"
#include "ME_App.h"
#include "resource.h"
#include "ME_Textures.h"

#include "SOIL.h"

#include "il.h"
#include "ilu.h"
#include "ilut.h"

#include "bitmap.h"
#include "bitmap._h"
#include "bitmap.__h"

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
// *						HBITMAP_TO_BmpFile						 	   *
// *************************************************************************
bool ME_Textures::HBITMAP_TO_BmpFile(HBITMAP Bitmap, char* Filename, char* SaveFolder)
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
		+ dwPaletteSize, (BITMAPINFO *)lpbi, DIB_RGB_COLORS);

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
// *							Jpg_To_Tga					  		 	   *
// *************************************************************************
bool ME_Textures::Jpg_To_Tga24(char* File)
{
	char OldFile[1024];
	strcpy(OldFile, File);

	ilLoadImage(File);

	int Len = strlen(File);
	File[Len - 4] = 0;
	strcat(File, ".tga");

	ilSaveImage(File);

	remove(OldFile);
	return 1;
}

// *************************************************************************
// *							Jpg_To_png24					  		 	   *
// *************************************************************************
bool ME_Textures::Jpg_To_png24(char* File)
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
// *							Bmp_To_Jpg					  		 	   *
// *************************************************************************
bool ME_Textures::Bmp_To_Jpg(char* File)
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
		Soil_Load_Texture(App->CL_Ogre->RenderListener->g_Texture, TextureFileName, TextureID);
		return 1;
	}
	// ------------------------------------ JPEG
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".JPG") == 0)
	{
		Soil_Load_Texture(App->CL_Ogre->RenderListener->g_Texture, TextureFileName, TextureID);
		return 1;
	}
	// ------------------------------------ TGA
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".TGA") == 0)
	{
		Soil_Load_Texture(App->CL_Ogre->RenderListener->g_Texture, TextureFileName, TextureID);
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
// *							Texture_To_Bmp				  		 	   *
// *************************************************************************
bool ME_Textures::Texture_To_Bmp(char* File)
{
	ilLoadImage(File);
	ilSaveImage("Etemp.bmp");
	return 1;
}

// *************************************************************************
// *						TexureToWinPreviewFullPath			  	 	   *
// *************************************************************************
bool ME_Textures::TexureToWinPreviewFullPath(int Index, char* FullPath)
{
	
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
// *					LoadDummyTexture Terry Bernie   		 	 	   *
// *************************************************************************
bool ME_Textures::LoadDummyTexture(int Index)
{
	
	App->CL_Model->Group[Index]->Base_Bitmap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_DUMMY));
	
	strcpy(App->CL_Model->Group[Index]->Texture_PathFileName, "Internal Texture Import Failed");
	strcpy(App->CL_Model->Group[Index]->Text_FileName, "Dummy.bmp");

	App->CL_Model->Group[Index]->Depth = 8;
	App->CL_Model->Group[Index]->Width = 256;
	App->CL_Model->Group[Index]->Height = 256;

	App->CL_Model->Group[Index]->Bitmap_Loaded = -1;
	return 1;
}

// *************************************************************************
// *					ChangeTexture_Model Terry Flanigan				   *
// *************************************************************************
bool ME_Textures::ChangeTexture_Model(void)
{

	int test = 0;

	//------------------------------------------------------------ Assimp
	if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
	{

		test = App->CL_FileIO->OpenTextureFile("Equity10 Replace Texture", NULL, NULL);
		if (test == 0) { return 0; }

		// Render Texture
		int Index = App->CL_Groups->Selected_Group;

		TexureToWinPreviewFullPath(Index, App->CL_FileIO->Texture_Path_FileName);
		Soil_Load_Texture(App->CL_Ogre->RenderListener->g_Texture, App->CL_FileIO->Texture_Path_FileName, Index);
																																		
		strcpy(App->CL_Model->Group[Index]->Text_FileName, App->CL_FileIO->Texture_FileName);
		strcpy(App->CL_Model->Group[Index]->Texture_PathFileName, App->CL_FileIO->Texture_Path_FileName);

		App->CL_Groups->Update_Groups();

		return 1;
	}
	return 1;
}

// *************************************************************************
// *				DecompileTextures Terry Bernie Hazel 		   	   	   *
// *************************************************************************
bool ME_Textures::DecompileTextures(char* Path)
{
	int MatCount = App->CL_Model->Get_Groupt_Count();
	char FileName[255];
	char FilePath[1024];

	int Loop = 0;
	while (Loop < MatCount)
	{
		strcpy(FileName, App->CL_Model->Group[Loop]->Text_FileName);

		int Len = strlen(FileName);
		FileName[Len - 4] = 0;
		strcat(FileName, ".jpg");

		strcpy(FilePath, Path);
		strcat(FilePath, FileName);

		HBITMAP Data;

		Data = App->CL_Model->Group[Loop]->Base_Bitmap;

		ilutWinSaveImage(FilePath, Data);

		Loop++;
	}
	return 1;
}

// *************************************************************************
// *					Genesis_WriteTGA Terry Bernie			  		   *
// *************************************************************************
int ME_Textures::Genesis_WriteTGA(const char * pszFile, geBitmap *pBitmap)
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
int ME_Textures::Genesis_WriteToBmp(geBitmap *bmp, char *filename)
{
	BITMAPFILEHEADER 	bmfh;
	BITMAPINFOHEADER	bmih;
	int width, height, bpp;
	int datasize;
	geBitmap_Info Info;
	geBitmap_Info Palette_Info;
	void *data;
	geBitmap_Palette * palette;
	void *palette_data;
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
