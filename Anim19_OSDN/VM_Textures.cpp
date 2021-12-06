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

#pragma warning( disable : 4800)

VM_Textures::VM_Textures()
{
	ilInit();
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
// *					DecodeTextures  Terry Bernie   			  	 	   *
// *************************************************************************
bool VM_Textures::Soil_DecodeTextures(int TextureID)
{
	int Index = 0;
	int Dont = 0;
	int jpg = 0;
	int DontAdd = 0;
	int AddDummy = 0;

	char buf[1024];
	strcpy(buf, App->CL_Vm_Model->Texture_FolderPath);
	strcat(buf, "Etemp.bmp");

	// ----------------------------------- Bitmap
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".BMP") == 0)
	{
		////S_TextureInfo[Count] = new GLTextureInfo_Type; // Need To Populate

		int Test = Soil_Load_Texture(g_Texture, TextureFileName, TextureID);
		if (Test == 0)
		{
			CreateDummyTexture();
			Soil_Load_Texture(g_Texture, buf, TextureID);
			//remove(buf);
		}

		return 1;
	}
	// ------------------------------------ JPEG
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".JPG") == 0)
	{
		//S_TextureInfo[Count] = new GLTextureInfo_Type; // Need To Populate

		int Test = Soil_Load_Texture(g_Texture, TextureFileName, TextureID);
		if (Test == 0)
		{
			CreateDummyTexture();
			Soil_Load_Texture(g_Texture, buf, TextureID);
			//remove(buf);
		}

		return 1;
	}
	// ------------------------------------ TGA
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".TGA") == 0)
	{
		//S_TextureInfo[Count] = new GLTextureInfo_Type; // Need To Populate

		int Test = Soil_Load_Texture(g_Texture, TextureFileName, TextureID);
		if (Test == 0)
		{
			CreateDummyTexture();
			Soil_Load_Texture(g_Texture, buf, TextureID);
			//remove(buf);
		}

		return 1;
	}
	// ------------------------------------ DDS
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".DDS") == 0)
	{
		//S_TextureInfo[Count] = new GLTextureInfo_Type; // Need To Populate

		int Test = Soil_Load_Texture(g_Texture, TextureFileName, TextureID);
		if (Test == 0)
		{
			CreateDummyTexture();
			Soil_Load_Texture(g_Texture, buf, TextureID);
			//remove(buf);
		}
		return 1;
	}
	// ------------------------------------ PNG
	if (_stricmp(TextureFileName + strlen(TextureFileName) - 4, ".PNG") == 0)
	{
		//S_TextureInfo[Count] = new GLTextureInfo_Type; // Need To Populate

		int Test = Soil_Load_Texture(g_Texture, TextureFileName, TextureID);
		if (Test == 0)
		{
			CreateDummyTexture();
			Soil_Load_Texture(g_Texture, buf, TextureID);
			//remove(buf);
		}
		return 1;
	}

	CreateDummyTexture();
	Soil_Load_Texture(g_Texture, buf, TextureID);
	remove(buf);

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
		//App->Say("Soil Fail 2");
		
		CreateDummyTexture();
		char buf[1024];
		strcpy(buf, App->CL_Vm_Model->Texture_FolderPath);
		strcat(buf, "Etemp.bmp");

		textureArray[textureID] = SOIL_load_OGL_texture
		(

			buf,
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_TEXTURE_REPEATS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS
			
		);

		remove(buf);

		if (textureArray[textureID] == 0)
		{
			const char* test = SOIL_last_result();
			char buff[255];
			strcpy(buff, test);
			strcat(buff, "- Soil Message");
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

//// *************************************************************************
//// *							Texture_To_Bmp				  		 	   *
//// *************************************************************************
//bool VM_Textures::Texture_To_Bmp(char* File)
//{
//	int test = ilLoadImage(File);
//	if (test == 0)
//	{
//		App->Say("Cant Load Image");
//	}
//
//	ilSaveImage("Etemp.bmp");
//
//	return 1;
//}

// *************************************************************************
// *								Ogre_LoadImage				  	 	   *
// *************************************************************************
bool VM_Textures::Ogre_LoadImage(const Ogre::String& tex_ext, const Ogre::String& texture_path,int Index)
{
	bool image_loaded = false;

	std::ifstream ifs(texture_path.c_str(), std::ios::binary | std::ios::in);
	if (ifs.is_open())
	{
		{
			Ogre::DataStreamPtr data_stream(new Ogre::FileStreamDataStream(texture_path, &ifs, false));
			Ogre::Image img;
			img.load(data_stream, tex_ext);
			
			img.save("Etemp.bmp");

			App->CL_Vm_Model->S_TextureInfo[Index]->HasGEBitmap = 1;
			App->CL_Vm_Model->S_TextureInfo[Index]->GEWitdth = img.getWidth();
			App->CL_Vm_Model->S_TextureInfo[Index]->GEHeight = img.getHeight();

			App->CL_Vm_Model->S_TextureInfo[Index]->GEFormat = img.getFormat();

			img.freeMemory();
			data_stream->close();
			
			image_loaded = true;
		}

		ifs.close();
	}

	return image_loaded;
}

// *************************************************************************
// *						HBITMAP_TO_BmpFile						 	   *
// *************************************************************************
bool VM_Textures::HBITMAP_TO_BmpFile(HBITMAP Bitmap, char* Filename, char* SaveFolder)
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
// *						TexureToWinPreviewFullPath			  	 	   *
// *************************************************************************
bool VM_Textures::TexureToWinPreviewFullPath(int Index, char* FullPath)
{
	//ilutGetBmpInfo(BITMAPINFO *Info);

	char mFileName[1024];
	strcpy(mFileName, FullPath);

	HWND PreviewWnd = GetDlgItem(App->CL_Vm_Groups->RightGroups_Hwnd, IDC_BASETEXTURE2);
	HDC	hDC = GetDC(PreviewWnd);

	// ----------------------------------- Bitmap
	if (_stricmp(mFileName + strlen(mFileName) - 4, ".BMP") == 0)
	{
		App->CL_Vm_Model->S_MeshGroup[Index]->Base_Bitmap = NULL;

		App->CL_Vm_Model->S_MeshGroup[Index]->Base_Bitmap = ilutWinLoadImage(mFileName, hDC);
		ReleaseDC(PreviewWnd, hDC);

		if (App->CL_Vm_Model->S_MeshGroup[Index]->Base_Bitmap == NULL)
		{
			CreateDummyTexture();
			App->CL_Vm_Model->S_MeshGroup[Index]->Base_Bitmap = (HBITMAP)LoadImage(NULL, "Etemp.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			remove("Etemp.bmp");

			App->CL_Vm_Model->S_MeshGroup[Index]->Bitmap_Loaded = 1;
		}
		else
		{
			App->CL_Vm_Model->S_MeshGroup[Index]->Bitmap_Loaded = 1;
		}
		
		return 1;
	}
	// ------------------------------------ TGA
	if (_stricmp(mFileName + strlen(mFileName) - 4, ".TGA") == 0)
	{
		
		int Test = Ogre_LoadImage("tga", mFileName, Index);
		if (Test == 0)
		{
			App->Say("Failed to load image tga");
		}

		App->CL_Vm_Model->S_MeshGroup[Index]->Base_Bitmap = (HBITMAP)LoadImage(NULL, "Etemp.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		remove("Etemp.bmp");
		return 1;
	}
	// ------------------------------------ JPEG
	if (_stricmp(mFileName + strlen(mFileName) - 4, ".JPG") == 0)
	{
		
		int Test = Ogre_LoadImage("jpg", mFileName, Index);
		if (Test == 0)
		{
			App->Say("Failed to load image jpg");
		}

		App->CL_Vm_Model->S_MeshGroup[Index]->Base_Bitmap = (HBITMAP)LoadImage(NULL,"Etemp.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		
		remove("Etemp.bmp");
		return 1;
	}
	// ------------------------------------ DDS
	if (_stricmp(mFileName + strlen(mFileName) - 4, ".DDS") == 0)
	{
		int Test = Ogre_LoadImage("dds", mFileName, Index);
		if (Test == 0)
		{
			App->Say("Failed to load image dds");
		}

		App->CL_Vm_Model->S_MeshGroup[Index]->Base_Bitmap = (HBITMAP)LoadImage(NULL, "Etemp.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		remove("Etemp.bmp");
		return 1;
	}
	// ------------------------------------ PNG
	if (_stricmp(mFileName + strlen(mFileName) - 4, ".PNG") == 0)
	{
		int Test = Ogre_LoadImage("png", mFileName, Index);
		if (Test == 0)
		{
			App->Say("Failed to load image png");
		}

		App->CL_Vm_Model->S_MeshGroup[Index]->Base_Bitmap = (HBITMAP)LoadImage(NULL, "Etemp.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

		remove("Etemp.bmp");
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

//// *************************************************************************
//// *					GetHBITMAPFromImageFile Terry Bernie   		 	   *
//// *************************************************************************
//HBITMAP VM_Textures::GetHBITMAPFromImageFile(const WCHAR* pFilePath)
//{
//	Gdiplus:: GdiplusStartupInput gpStartupInput;
//	ULONG_PTR gpToken;
//	GdiplusStartup(&gpToken, &gpStartupInput, NULL);
//	HBITMAP result = NULL;
//	Gdiplus::Bitmap* bitmap = Gdiplus::Bitmap::FromFile(pFilePath, false);
//	if (bitmap)
//	{
//		bitmap->GetHBITMAP(RGB(255, 255, 255), &result);
//		delete bitmap;
//	}
//	Gdiplus::GdiplusShutdown(gpToken);
//	return result;
//}

// *************************************************************************
// *						RemoveFile Terry Bernie					 	   *
// *************************************************************************
bool VM_Textures::RemoveFile(char* Filename, char* Folder)
{
	remove(Filename);
	return 1;
}

// *************************************************************************
// *					CreateDummyTexture Terry Bernie   		 	 	   *
// *************************************************************************
bool VM_Textures::CreateDummyTexture(void)
{
	HBITMAP hbmpTemp;
	hbmpTemp = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_DUMMY));

	HDC	hdcTemp;
	BITMAP bmp;
	PBITMAPINFO pbmi;
	WORD cClrBits;
	HANDLE hf;
	BITMAPFILEHEADER hdr;
	PBITMAPINFOHEADER pbih;
	LPBYTE lpBits;
	DWORD dwTotal;
	DWORD cb;
	BYTE *hp;
	DWORD dwTmp;

	hdcTemp = CreateCompatibleDC(GetDC(0));
	if (!hdcTemp)
	{
		App->Say("Compatible Faild");
		return 0;
	}

	if (!GetObject(hbmpTemp, sizeof(BITMAP), (LPSTR)&bmp))

	{
		App->Say("Failed 3");
		return 0;
	}

	cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
	if (cClrBits == 1)
		cClrBits = 1;
	else if (cClrBits <= 4)
		cClrBits = 4;
	else if (cClrBits <= 8)
		cClrBits = 8;
	else if (cClrBits <= 16)
		cClrBits = 16;
	else if (cClrBits <= 24)
		cClrBits = 24;
	else cClrBits = 32;


	if (cClrBits != 24)
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
			sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * (1 << cClrBits));
	else
		pbmi = (PBITMAPINFO)LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER));

	// Initialize the fields in the BITMAPINFO structure. 

	pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	pbmi->bmiHeader.biWidth = bmp.bmWidth;
	pbmi->bmiHeader.biHeight = bmp.bmHeight;
	pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
	pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
	if (cClrBits < 24)
		pbmi->bmiHeader.biClrUsed = (1 << cClrBits);


	pbmi->bmiHeader.biCompression = BI_RGB;

	pbmi->bmiHeader.biSizeImage = (pbmi->bmiHeader.biWidth + 7) / 8 * pbmi->bmiHeader.biHeight * cClrBits;

	pbmi->bmiHeader.biClrImportant = 0;

	pbih = (PBITMAPINFOHEADER)pbmi;
	lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

	if (!lpBits)
	{
		App->Say("writeBMP::Could not allocate memory");
		return 0;
	}

	if (!GetDIBits(hdcTemp, HBITMAP(hbmpTemp), 0, (WORD)pbih->biHeight, lpBits, pbmi,
		DIB_RGB_COLORS))
	{
		App->Say("writeBMP::GetDIB error");
		return 0;
	}

	char buf[1024];
	strcpy(buf, App->CL_Vm_Model->Texture_FolderPath);
	strcat(buf, "Etemp.bmp");

	hf = CreateFile(buf, GENERIC_READ | GENERIC_WRITE, (DWORD)0,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);

	/*hf = CreateFile(App->ETemp_Folder, GENERIC_READ | GENERIC_WRITE, (DWORD)0,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);*/

	if (hf == INVALID_HANDLE_VALUE)
	{
		App->Say("Could not create file for writing");
		return 0;
	}
	hdr.bfType = 0x4d42; // 0x42 = "B" 0x4d = "M" 

	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD) + pbih->biSizeImage);
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;


	hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
		pbih->biSize + pbih->biClrUsed
		* sizeof(RGBQUAD);

	if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
		(LPDWORD)&dwTmp, NULL)) {
		App->Say("Could not write in to file");
		return 0;
	}

	if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+ pbih->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL))) {
		App->Say("Could not write in to file");
		return 0;
	}

	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL)) {
		App->Say("Could not write in to file");
		return 0;
	}

	if (!CloseHandle(hf)) {
		App->Say("Could not close file");
		return 0;
	}

	GlobalFree((HGLOBAL)lpBits);
	DeleteObject(hbmpTemp);
	DeleteDC(hdcTemp);

	return 1;
}

// *************************************************************************
// *						CheckPath Terry Bernie	   					   *
// *************************************************************************
void VM_Textures::Strip_JustFileName(char *pString, char *FileName)
{
	int Count = 0;
	int Mark = 0;
	bool Test = 0;

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
// *					CreateTextureInfo Terry Bernie	   		 	   	   *
// *************************************************************************
void VM_Textures::CreateTextureInfo(void)
{
	int Count = 0;

	while (Count < App->CL_Vm_Model->S_Texture[0]->UsedTextureCount)
	{
		App->CL_Vm_Model->S_TextureInfo[Count] = new GLTextureInfo_Type;
		App->CL_Vm_Model->S_TextureInfo[Count]->Tga = 0;
		App->CL_Vm_Model->S_TextureInfo[Count]->type = 0;
		App->CL_Vm_Model->S_TextureInfo[Count]->texID = 0;
		App->CL_Vm_Model->S_TextureInfo[Count]->ActorMaterialIndex = 0;
		App->CL_Vm_Model->S_TextureInfo[Count]->Bitmap = nullptr;

		App->CL_Vm_Model->S_TextureInfo[Count]->R = 0;
		App->CL_Vm_Model->S_TextureInfo[Count]->G = 0;
		App->CL_Vm_Model->S_TextureInfo[Count]->B = 0;

		strcpy(App->CL_Vm_Model->S_TextureInfo[Count]->MaterialName, "Unkown");

		App->CL_Vm_Model->S_TextureInfo[Count]->GEHasAlpha = 0;

		Count++;
	}
}

// *************************************************************************
// *								GetFormat					  	 	   *
// *************************************************************************
bool VM_Textures::GetFormat(int cformat)
{
	GEFormatString[0] = 0;

	switch (cformat)
	{
	case 0:
		strcpy(GEFormatString, "PIXELFORMAT_NO_DATA = 0");
		return 1;

	case 1:
		strcpy(GEFormatString, "PIXELFORMAT_8BIT");
		return 1;



	case 10:
		strcpy(GEFormatString, "PIXELFORMAT_24BIT_BGR");
		return 1;


	case 13:
		strcpy(GEFormatString, "PIXELFORMAT_32BIT_XRGB");
		return 1;

	case 17:
		strcpy(GEFormatString, "PIXELFORMAT_32BIT_ARGB");
		return 1;

	}

	strcpy(GEFormatString, "Cant Decode");
	return 1;
}

// *************************************************************************
// *							Jpg_To_Tga					  		 	   *
// *************************************************************************
bool VM_Textures::Jpg_To_Tga24(char* File)
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
bool VM_Textures::Jpg_To_png24(char* File)
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
bool VM_Textures::Bmp_To_Jpg(char* File)
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

