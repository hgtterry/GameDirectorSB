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

			HBITMAP hbmpTemp;

			hbmpTemp = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_DUMMY));

			App->CL_Model->Group[Index]->Base_Bitmap = hbmpTemp;
			App->CL_Model->Group[Index]->Bitmap_Loaded = -1;
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

// *************************************************************************
// *					CreateDummyTexture Terry Bernie   		 	 	   *
// *************************************************************************
bool ME_Textures::CreateDummyTexture(void)
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
		App->Say_Win("Compatible Faild");
		return 0;
	}

	if (!GetObject(hbmpTemp, sizeof(BITMAP), (LPSTR)&bmp))

	{
		App->Say_Win("Failed 3");
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
		App->Say_Win("writeBMP::Could not allocate memory");
		return 0;
	}

	if (!GetDIBits(hdcTemp, HBITMAP(hbmpTemp), 0, (WORD)pbih->biHeight, lpBits, pbmi,
		DIB_RGB_COLORS))
	{
		App->Say_Win("writeBMP::GetDIB error");
		return 0;
	}

	char buf[1024];
	strcpy(buf, App->CL_Model->Texture_FolderPath);
	strcat(buf, "Etemp.bmp");

	hf = CreateFile(buf, GENERIC_READ | GENERIC_WRITE, (DWORD)0,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
		(HANDLE)NULL);

	/*hf = CreateFile(App->ETemp_Folder, GENERIC_READ | GENERIC_WRITE, (DWORD)0,
	NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL,
	(HANDLE)NULL);*/

	if (hf == INVALID_HANDLE_VALUE)
	{
		App->Say_Win("Could not create file for writing");
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
		App->Say_Win("Could not write in to file");
		return 0;
	}

	if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
		+ pbih->biClrUsed * sizeof(RGBQUAD),
		(LPDWORD)&dwTmp, (NULL))) {
		App->Say_Win("Could not write in to file");
		return 0;
	}

	dwTotal = cb = pbih->biSizeImage;
	hp = lpBits;
	if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL)) {
		App->Say_Win("Could not write in to file");
		return 0;
	}

	if (!CloseHandle(hf)) {
		App->Say_Win("Could not close file");
		return 0;
	}

	GlobalFree((HGLOBAL)lpBits);
	DeleteObject(hbmpTemp);
	DeleteDC(hdcTemp);

	return 1;
}
