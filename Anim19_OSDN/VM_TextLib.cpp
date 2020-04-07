/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "resource.h"
#include "GD19_App.h"
#include "VM_TextLib.h"

VM_TextLib::VM_TextLib()
{
	Entry = nullptr;
	pData = nullptr;
}

VM_TextLib::~VM_TextLib()
{
	
}


// *************************************************************************
// *							Start_TexturePack				  		   *
// *************************************************************************
void VM_TextLib::Start_TexturePack()
{
	int test = Txt_OpenFile("Texture Libary   *.txl\0*.txl\0", "Texure Editor", NULL);// S_Prefs[0]->TXLFolder);
	if (test == 0)
	{

		return;
	}

	DialogBox(App->hInst, (LPCTSTR)IDD_TEXTUREPACKER, App->Fdlg, (DLGPROC)TextureLib_Proc);
}

// *************************************************************************
// *					TextureLib_Proc  06/06/08   					   *
// *************************************************************************
LRESULT CALLBACK VM_TextLib::TextureLib_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->CL_Vm_TextLib->Entry = new BitmapEntry;

		SetWindowLong(GetDlgItem(hDlg, IDC_PREVIEW), GWL_WNDPROC, (LONG)TextureLibPreviewWnd);
		char buf1[200];
		HFONT				Font;
		HFONT				Font1;
		HFONT				Font2;
		HFONT				Font3;


		App->CL_Vm_TextLib->LoadFile(hDlg);

		/*strcpy(buf1, szTitle);
		strcat(buf1, "        ");
		strcat(buf1, C_TetureLib->pData->TXLFileName);
		SetWindowText(hDlg, buf1);*/

		Font = CreateFont(-24, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Arial Black");
		Font1 = CreateFont(-20, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Arial Black");
		Font2 = CreateFont(-12, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
		Font3 = CreateFont(-10, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier");
		SendDlgItemMessage(hDlg, IDC_TEXTURE, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ALPHA, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_GEINFO, WM_SETFONT, (WPARAM)Font1, MAKELPARAM(TRUE, 0));
		//	SendDlgItemMessage(hDlg,IDC_CTRLKEY, WM_SETFONT, (WPARAM)Font2, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TEXTURELIST, WM_SETFONT, (WPARAM)Font2, MAKELPARAM(TRUE, 0));

	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	return TRUE;

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{

			if (App->CL_Vm_TextLib->pData->Dirty)
			{
				int	Result;

				Result = MessageBox(NULL,
					"Do you want to save changes before quitting?",
					"Texture Packer",
					MB_YESNOCANCEL);

				if (Result == IDCANCEL)
					return 0;

				if (Result == IDYES)
				{
					if (App->CL_Vm_TextLib->pData->FileNameIsValid)
						App->CL_Vm_TextLib->Save(App->CL_Vm_TextLib->pData->TXLFileName);
					else
						App->CL_Vm_TextLib->Save(NULL);
				}
			}

			App->CL_Vm_TextLib->CleanUp();
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		//-------------------Click in Texture List Box ----------------
		if (LOWORD(wParam) == IDC_TEXTURELIST)
		{
			App->CL_Vm_TextLib->SelectBitmap();

			return TRUE;
		}
		//--------------------------------- Add -----------------------
		if (LOWORD(wParam) == IDC_ADD)
		{
			/*int test = C_File->OpenFileCom("Texture Files ( *.bmp *.tga )\0*.bmp;*.tga\0*.tga\0*.tga\0*.bmp\0*.bmp\0", "Add Texture", "Bitmap Files");
			if (test == 0)
			{
				return 1;
			}*/

			App->CL_Vm_TextLib->AddTexture(NULL, App->CL_Vm_TextLib->Txt_FileName);
			App->CL_Vm_TextLib->pData->Dirty = 1; // it as changed reqest save
			return TRUE;
		}
		//--------------------------------- Save ----------------------
		if (LOWORD(wParam) == IDC_SAVE)
		{

			App->CL_Vm_TextLib->Save(App->CL_Vm_TextLib->pData->TXLFileName);
			return TRUE;
		}
		//--------------------------------- Rename ----------------------
		if (LOWORD(wParam) == IDC_RENAME)
		{

			//DialogBox(hInst, (LPCTSTR)IDD_RENAME, Fdlg, (DLGPROC)RenameProc);
			//App->CL_Vm_TextLib->pData->Dirty = 1;  // it as changed reqest save
			return TRUE;
		}
		//--------------------------------- Save AS --------------------
		if (LOWORD(wParam) == IDC_SAVEAS)
		{

			App->CL_Vm_TextLib->Save(NULL);
			return TRUE;
		}

		//--------------------------------- IDC_LOAD --------------------
		/*	if (LOWORD(wParam) == IDC_LOAD)
		{

		C_TetureLib->TPack_ExtractSelected();

		strcpy(FileName,C_TetureLib->L_FileName);

		if (stricmp(C_TetureLib->L_FileName+strlen(C_TetureLib->L_FileName)-4,".bmp") == 0)
		{

		int textureID=S_TextureInfo[PictureIndex]->ActorMaterialIndex;
		S_TextureInfo[PictureIndex]->Tga=0;
		NEWLoadTexture(g_Texture,C_TetureLib->L_FileName,textureID,PictureIndex);
		Test();
		At->SingleTextureInfo(PictureIndex);
		C_Display->TextureNames();
		}
		if (stricmp(C_TetureLib->L_FileName+strlen(C_TetureLib->L_FileName)-4,".tga") == 0)
		{


		C_File->LoadTGA(C_TetureLib->L_FileName);
		C_Textures->ReloadTextures(g_Texture);
		At->SingleTextureInfo(PictureIndex);
		C_Display->TextureNames();
		}

		DeleteFile(C_TetureLib->L_FileName);

		return TRUE;
		}*/

		//--------------------------------- Save AS --------------------
		if (LOWORD(wParam) == IDC_EXPORTSELECTED)
		{

			App->CL_Vm_TextLib->TPack_ExtractSelected();
			return TRUE;
		}

		//--------------------------------- Export All -----------------
		if (LOWORD(wParam) == IDC_EXPORTALL)
		{
			/*char File[256];

			_getcwd(App->CL_Vm_TextLib->LastPath, 256);
			_splitpath(App->CL_Vm_TextLib->pData->TXLFileName, NULL, NULL, File, NULL);
			strcat(File, "_Textures");

			strcpy(S_File[0]->NewSubFolderName, File);

			strcpy(S_File[0]->SaveMessage, "Select Folder To Place Decompiled Textures");

			int Test = GetSaveFolder();
			if (Test == 0)
			{
				return 0;
			}

			App->CL_Vm_TextLib->TPack_ExtractAll();*/

			return TRUE;
		}

	}

	case WM_CTLCOLORSTATIC:
	{

		/*if (GetDlgItem(hDlg, IDC_ALPHA) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			hBrushStatic = CreateSolidBrush(RGB(200, 200, 0));
			return (UINT)hBrushStatic;
		}
		if (GetDlgItem(hDlg, IDC_TEXTURE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			hBrushStatic = CreateSolidBrush(RGB(200, 200, 0));
			return (UINT)hBrushStatic;
		}*/

		break;
	}
	break;
	}
	return FALSE;
}

// *************************************************************************
// *					TextureLibPreviewWnd							   *
// *************************************************************************

bool CALLBACK VM_TextLib::TextureLibPreviewWnd(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	if (msg == WM_PAINT)
	{

		PAINTSTRUCT	ps;
		HDC			hDC;
		RECT		Rect;

		hDC = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &Rect);
		Rect.left--;
		Rect.bottom--;
		FillRect(hDC, &Rect, (HBRUSH)(COLOR_WINDOW + 1));

		if (App->CL_Vm_TextLib->Entry->Bitmap != NULL)
		{
			RECT	Source;
			RECT	Dest;
			HDC		hDC;

			Source.left = 0;
			Source.top = 0;
			Source.bottom = geBitmap_Height(App->CL_Vm_TextLib->Entry->Bitmap);
			Source.right = geBitmap_Width(App->CL_Vm_TextLib->Entry->Bitmap);

			Dest = Rect;

			hDC = GetDC(hwnd);
			SetStretchBltMode(hDC, HALFTONE);

			App->CL_Vm_TextLib->Render2d_Blit(hDC,
				App->CL_Vm_TextLib->Entry->WinBitmap,
				App->CL_Vm_TextLib->Entry->WinABitmap,
				&Source,
				&Dest);

			ReleaseDC(hwnd, hDC);
		}
		EndPaint(hwnd, &ps);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

// *************************************************************************
// *							WriteTGA						  		   *
// *************************************************************************
int VM_TextLib::WriteTGA(const char * pszFile, geBitmap *pBitmap)
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

	uint8 *         pPixelData;
	uint8 *			pPixelDataA;

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

	tgah.Width = (uint16)BitmapInfo.Width;
	tgah.Height = (uint16)BitmapInfo.Height;

	tgah.PixelDepth = 32;
	tgah.ImageDescriptor = 8; //00001000 - not flipped, 8 alpha bits


	pPixelData = (uint8*)geBitmap_GetBits(pLock);

	pPixelDataA = (uint8*)geBitmap_GetBits(pLockA);

	// Write the tga header
	if (!WriteFile(hFile, (LPVOID)&tgah, sizeof(TGAHEADER), (LPDWORD)&nBytesWritten, (NULL)))
	{
		nErrorCode = TPACKERROR_WRITE;
		goto ExitWriteBitmap;
	}

	// write pixels
	pPixelData += 3 * tgah.Width*(tgah.Height - 1);
	pPixelDataA += tgah.Width*(tgah.Height - 1);
	for (i = 0; i < tgah.Height; i++)
	{
		for (j = 0; j < tgah.Width; j++)
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
// *							FindBitmap		 				  		   *
// *************************************************************************
bool VM_TextLib::Render2d_Blit(HDC hDC, HBITMAP Bmp, HBITMAP Alpha, const RECT *SourceRect, const RECT *DestRect)
{
	HDC		MemDC;
	int		SourceWidth;
	int		SourceHeight;
	int		DestWidth;
	int		DestHeight;

	MemDC = CreateCompatibleDC(hDC);
	if (MemDC == NULL)
		return FALSE;

	SelectObject(MemDC, Bmp);

	SourceWidth = SourceRect->right - SourceRect->left;
	SourceHeight = SourceRect->bottom - SourceRect->top;
	DestWidth = DestRect->right - DestRect->left;
	DestHeight = DestRect->bottom - DestRect->top;
	SetStretchBltMode(hDC, COLORONCOLOR);
	StretchBlt(hDC,
		DestRect->left,
		DestRect->top,
		DestHeight,
		DestHeight,
		MemDC,
		SourceRect->left,
		SourceRect->top,
		SourceWidth,
		SourceHeight,
		SRCCOPY);
	if (Alpha)
	{
		SelectObject(MemDC, Alpha);
		SetStretchBltMode(hDC, COLORONCOLOR);
		StretchBlt(hDC,
			DestRect->left + DestHeight + 2,
			DestRect->top,
			DestHeight,
			DestHeight,
			MemDC,
			SourceRect->left,
			SourceRect->top,
			SourceWidth,
			SourceHeight,
			SRCCOPY);
	}

	DeleteDC(MemDC);

	return TRUE;
}

// *************************************************************************
// *							TPack_ExtractAll				  		   *
// *************************************************************************
int VM_TextLib::WriteBMP8(const char * pszFile, geBitmap *pBitmap)
{
	geBitmap *       pLock = NULL;
	gePixelFormat    Format;
	geBitmap_Info    BitmapInfo;
	int              nErrorCode = TPACKERROR_UNKNOWN;      // Return code
	BITMAPFILEHEADER BmpHeader;                            // bitmap file-header 
	MY_BITMAPINFO    BmInfo;
	uint32           nBytesPerPixel;
	void *           pPixelData;
	uint8 *          pOut = NULL;
	uint8 *          pTmp = NULL;
	int              nNewStride = 0;
	int              nOldStride = 0;
	int              i;
	HANDLE           hFile = NULL;
	DWORD            nBytesWritten;
	uint8 *pNew;
	uint8 *pOld;
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

		BmInfo.bmiColors[i].rgbRed = (uint8)r;
		BmInfo.bmiColors[i].rgbGreen = (uint8)g;
		BmInfo.bmiColors[i].rgbBlue = (uint8)b;
		BmInfo.bmiColors[i].rgbReserved = (uint8)0;
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

	// Bitmap scanlines are padded to the nearest dword. If the pixel data from pBitmap
	// is not a the correct width, we need to fix it.
	// NOTE: The best solution is to write each scanline, That way we don't
	//       have to allocate a new pixel buffer.
	if (nNewStride == nOldStride)
	{
		pTmp = (uint8 *)pPixelData;
	}

	// Allocate new pixel buffer.
	else
	{
		pTmp = (uint8 *)geRam_Allocate(nNewStride * BitmapInfo.Height);
		if (pTmp == (uint8 *)0)
		{
			// Memory allocation error
			nErrorCode = TPACKERROR_MEMORYALLOCATION;
			goto ExitWriteBitmap;
		}


		pNew = (uint8 *)pTmp;
		pOld = (uint8 *)pPixelData;

		// Copy old to new
		for (y = 0; y < BitmapInfo.Height; y++)
		{
			memcpy(pNew, pOld, nOldStride);

			// Next row
			pOld += nOldStride;
			pNew += nNewStride;
		}
	}

	pOut = (uint8 *)geRam_Allocate(nNewStride * BitmapInfo.Height);
	if (pOut == (uint8 *)0)
	{
		// Memory allocation error
		nErrorCode = TPACKERROR_MEMORYALLOCATION;
		goto ExitWriteBitmap;
	}

	pNew = (uint8 *)pOut;
	pOld = (uint8 *)(pTmp + (nNewStride * (BitmapInfo.Height - 1)));

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

////   TXL LIBRARY STUFF
// *************************************************************************
// *						LoadFile  06/06/08 					  		   *
// *************************************************************************
bool VM_TextLib::LoadFile(HWND ChDlg)
{
	geVFile *			VFS = NULL;
	geVFile_Finder *	Finder = NULL;
	geVFile_Finder *	FinderCount = NULL;

	pData = new TPack_WindowData;
	pData->hwnd = ChDlg;
	pData->BitmapCount = 0;

	int TextureCount = 0;


	//App->Say(Txt_FileName);
	//App->Say(Txt_Path_FileName);
	VFS = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_VIRTUAL, Txt_Path_FileName, NULL, GE_VFILE_OPEN_READONLY | GE_VFILE_OPEN_DIRECTORY);
	if (!VFS)
	{
		NonFatalError("Could not open file %s", Txt_Path_FileName);
		return 0;
	}

	FinderCount = geVFile_CreateFinder(VFS, "*.*");
	if (!FinderCount)
	{
		NonFatalError("Could not load textures from 1 %s", Txt_Path_FileName);
		geVFile_Close(VFS);
		return 0;
	}

	while (geVFile_FinderGetNextFile(FinderCount) != GE_FALSE)
	{

		TextureCount++;

	}

	Finder = geVFile_CreateFinder(VFS, "*.*");
	if (!Finder)
	{
		NonFatalError("Could not load textures from 2 %s", Txt_Path_FileName);
		geVFile_Close(VFS);
		return 0;
	}


	while (geVFile_FinderGetNextFile(Finder) != GE_FALSE)
	{
		geVFile_Properties	Properties;

		geVFile_FinderGetProperties(Finder, &Properties);
		if (!AddTexture(VFS, Properties.Name))
		{
			geVFile_Close(VFS);
			return 0;
		}

	}
	strcpy(pData->TXLFileName, Txt_FileName);
	pData->FileNameIsValid = TRUE;
	pData->Dirty = FALSE;
	geVFile_Close(VFS);

	SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_SETCURSEL, (WPARAM)0, (LPARAM)0);

	return 1;
}


// *************************************************************************
// *						NonFatalError   					  		   *
// *************************************************************************
bool VM_TextLib::NonFatalError(const char *Msg, ...)
{
	char Buffer[1024];
	va_list argptr;

	va_start(argptr, Msg);
	vsprintf(Buffer, Msg, argptr);
	va_end(argptr);

	MessageBox(NULL, Buffer, "Error", MB_ICONEXCLAMATION | MB_OK);
	return 1;
}

// *************************************************************************
// *						AddTexture  06/06/08 				  		   *
// *************************************************************************
bool VM_TextLib::AddTexture(geVFile *BaseFile, const char *Path)
{
	geBitmap_Info	PInfo;
	geBitmap_Info	SInfo;
	geBitmap *		Bitmap;

	geVFile *		File;
	char			FileName[_MAX_FNAME];
	char *			Name;

	Bitmap = NULL;
	File = NULL;

	_splitpath(Path, NULL, NULL, FileName, NULL);
	Name = _strdup(FileName);
	if (!Name)
	{
		NonFatalError("Memory allocation error processing %s", Path);
		return FALSE;
	}

	if (BaseFile)
		File = geVFile_Open(BaseFile, Path, GE_VFILE_OPEN_READONLY);
	else
		File = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS, Path, NULL, GE_VFILE_OPEN_READONLY);

	if (!File)
	{
		NonFatalError("Could not open %s", Path);
		return TRUE;
	}

	Bitmap = geBitmap_CreateFromFile(File);
	geVFile_Close(File);
	if (!Bitmap)
	{
		NonFatalError("%s is not a valid bitmap", Path);
		return TRUE;
	}
	geBitmap_GetInfo(Bitmap, &PInfo, &SInfo);
	//	if	(PInfo.Format != GE_PIXELFORMAT_8BIT)
	//	{
	//		NonFatalError("%s is not an 8bit bitmap", Path);
	//		goto fail;
	//	}
	//	NewBitmapList = geRam_Realloc(pData->Bitmaps, sizeof(*NewBitmapList) * (pData->BitmapCount + 1));
	NewBitmapList[pData->BitmapCount] = new BitmapEntry;
	if (!NewBitmapList)
	{
		NonFatalError("Memory allocation error processing %s", Path);
		return TRUE;
	}

	NewBitmapList[pData->BitmapCount]->Name = Name;
	NewBitmapList[pData->BitmapCount]->Bitmap = Bitmap;
	NewBitmapList[pData->BitmapCount]->WinBitmap = NULL;
	NewBitmapList[pData->BitmapCount]->WinABitmap = NULL;
	NewBitmapList[pData->BitmapCount]->Flags = 0;
	pData->BitmapCount++;

	SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)Name);

	return TRUE;

}


// *************************************************************************
// *						SelectBitmap  06/06/08 				  		   *
// *************************************************************************
bool VM_TextLib::SelectBitmap()
{

	int		Index;

	int location = 0;

	Index = SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	if (Index == LB_ERR)
	{
		//	Entry = NULL;
	}
	else
	{
		SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_GETTEXT, (WPARAM)Index, (LPARAM)&TextureName[0]);
		
		location = FindBitmap(pData, TextureName);

		//	assert(Entry);
		if (!NewBitmapList[location]->WinBitmap)
		{
			HWND	PreviewWnd;
			HBITMAP	hbm;
			HBITMAP	ahbm;
			HDC		hDC;

			PreviewWnd = GetDlgItem(pData->hwnd, IDC_PREVIEW);
			hDC = GetDC(PreviewWnd);
			hbm = CreateHBitmapFromgeBitmap(NewBitmapList[location]->Bitmap, hDC);
			NewBitmapList[location]->WinBitmap = hbm;

			if (geBitmap_HasAlpha(NewBitmapList[location]->Bitmap))
			{
				ahbm = CreateHBitmapFromgeBitmap(geBitmap_GetAlpha(NewBitmapList[location]->Bitmap), hDC);
				NewBitmapList[location]->WinABitmap = ahbm;
			}
			ReleaseDC(PreviewWnd, hDC);
		}

		if (!NewBitmapList[location]->WinBitmap)
		{
			NonFatalError("Memory allocation error creating bitmap");
			return 0;
		}
	}

	InvalidateRect(GetDlgItem(pData->hwnd, IDC_PREVIEW), NULL, TRUE);

	Entry = NewBitmapList[location];
	UpDateGeList(location);

	return 0;
}


// *************************************************************************
// *						FindBitmap  06/06/08 				  		   *
// *************************************************************************
int VM_TextLib::FindBitmap(TPack_WindowData *pData, const char *Name)
{
	int	i;

	for (i = 0; i < pData->BitmapCount; i++)
	{

		if (!strcmp(Name, NewBitmapList[i]->Name))
		{
			return i;
		}
	}

	return -1;
}



// *************************************************************************
// *				CreateHBitmapFromgeBitmap  06/06/08 		  		   *
// *************************************************************************
HBITMAP VM_TextLib::CreateHBitmapFromgeBitmap(geBitmap *Bitmap, HDC hdc)
{
	geBitmap * Lock;
	gePixelFormat Format;
	geBitmap_Info info;
	HBITMAP hbm = NULL;

	// <> choose format to be 8,16,or 24, whichever is closest to Bitmap
	Format = GE_PIXELFORMAT_24BIT_BGR;

	if (geBitmap_GetBits(Bitmap))
	{
		Lock = Bitmap;
	}
	else
	{
		if (!geBitmap_LockForRead(Bitmap, &Lock, 0, 0, Format, GE_FALSE, 0))
		{
			return NULL;
		}
	}

	geBitmap_GetInfo(Lock, &info, NULL);

	if (info.Format != Format)
		return NULL;

	{
		void * bits;
		BITMAPINFOHEADER bmih;
		int pelbytes;

		pelbytes = gePixelFormat_BytesPerPel(Format);
		bits = geBitmap_GetBits(Lock);

		bmih.biSize = sizeof(bmih);
		bmih.biHeight = -info.Height;
		bmih.biPlanes = 1;
		bmih.biBitCount = 24;
		bmih.biCompression = BI_RGB;
		bmih.biSizeImage = 0;
		bmih.biXPelsPerMeter = bmih.biYPelsPerMeter = 10000;
		bmih.biClrUsed = bmih.biClrImportant = 0;

		if ((info.Stride*pelbytes) == (((info.Stride*pelbytes) + 3)&(~3)))
		{
			bmih.biWidth = info.Stride;
			hbm = CreateDIBitmap(hdc, &bmih, CBM_INIT, bits, (BITMAPINFO *)&bmih, DIB_RGB_COLORS);
		}
		else
		{
			void * newbits;
			int Stride;

			bmih.biWidth = info.Width;
			Stride = (((info.Width*pelbytes) + 3)&(~3));
			newbits = geRam_Allocate(Stride * info.Height);
			if (newbits)
			{
				char *newptr, *oldptr;
				int y;

				newptr = (char *)newbits;
				oldptr = (char *)bits;
				for (y = 0; y < info.Height; y++)
				{
					memcpy(newptr, oldptr, (info.Width)*pelbytes);
					oldptr += info.Stride*pelbytes;
					newptr += Stride;
				}
				hbm = CreateDIBitmap(hdc, &bmih, CBM_INIT, newbits, (BITMAPINFO *)&bmih, DIB_RGB_COLORS);
				geRam_Free(newbits);
			}
		}
	}

	if (Lock != Bitmap)
	{
		geBitmap_UnLock(Lock);
	}

	return hbm;
}


// *************************************************************************
// *					UpDateGeList  06/06/08 					  		   *
// *************************************************************************
bool VM_TextLib::UpDateGeList(int Location)
{
	int B = 0;
	geBitmap_Info	MPInfo;
	geBitmap_Info	MSInfo;

	char buff[256];
	strcpy(buff, "no info");
	SendDlgItemMessage(pData->hwnd, IDC_GEINFO, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

	sprintf(buff, "%s %s", "Texture Name :-", NewBitmapList[Location]->Name);
	SendDlgItemMessage(pData->hwnd, IDC_GEINFO, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);

	sprintf(buff, "%s %i", "Index :-", Location);
	SendDlgItemMessage(pData->hwnd, IDC_GEINFO, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);

	sprintf(buff, "%s %s", "Bitmap :-", "Valid");
	SendDlgItemMessage(pData->hwnd, IDC_GEINFO, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);

	sprintf(buff, "%s %d", "Width :-", geBitmap_Width(NewBitmapList[Location]->Bitmap));
	SendDlgItemMessage(pData->hwnd, IDC_GEINFO, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);

	sprintf(buff, "%s %d", "Height :-", geBitmap_Height(NewBitmapList[Location]->Bitmap));
	SendDlgItemMessage(pData->hwnd, IDC_GEINFO, LB_ADDSTRING, (WPARAM)0, (LPARAM)buff);


	geBitmap_GetInfo(NewBitmapList[Location]->Bitmap, &MPInfo, &MSInfo);
	
	return 1;
}

// *************************************************************************
// *					ExtractSelected  21/06/08 						   *
// *************************************************************************
bool VM_TextLib::TPack_ExtractSelected()
{
	HWND            hLB = 0;// GetDlgItem(pData->hwnd, IDC_TEXTURELIST);
	int             nSel;
	//	BitmapEntry *	pEntry;
	char            szName[256];
	char            szFile[256];
	char            szPath[256];
	int             nErrorCode;

	//----------------------------------------------
	// Get current selected list box entry.
	// Get the  geBitmap.
	// Write 8-bit BMP file.
	//----------------------------------------------

	// Ouput to the current directory
	GetCurrentDirectory(MAX_PATH, szPath);

	nSel = SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	if (nSel == LB_ERR)
	{
		//	Entry = NULL;
	}
	SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_GETTEXT, (WPARAM)nSel, (LPARAM)&szName[0]);


	//	App->CL_Vm_TextLib->pEntry = FindBitmap(pData, szName);
	//	if (pEntry)
	{
		// Create an output file name
		strcpy(szFile, szPath);
		strcat(szFile, "\\");
		strcat(szFile, NewBitmapList[nSel]->Name);

		if (geBitmap_HasAlpha(NewBitmapList[nSel]->Bitmap))
		{
			char Buf1[200];
			strcpy(Buf1, NewBitmapList[nSel]->Name);
			strcat(Buf1, ".tga");

			int Test = SaveSelectedFile("Tga File   *.tga\0*.tga\0", Buf1);
			if (Test == 0)
			{
				return 0;
			}

			int Check = CheckExtention(SaveFile);
			if (Check == 0)
			{
				strcat(SaveFile, ".tga");
			}
			strcpy(L_FileName, SaveFile);
		}
		else
		{
			char Buf1[200];
			strcpy(Buf1, NewBitmapList[nSel]->Name);
			strcat(Buf1, ".bmp");
			int Test = SaveSelectedFile("Bitmap File   *.bmp\0*.bmp\0", Buf1);
			if (Test == 0)
			{
				return 0;
			}

			int Check = CheckExtention(SaveFile);
			if (Check == 0)
			{
				strcat(SaveFile, ".bmp");
			}
			strcpy(L_FileName, SaveFile);
		}

		if (geBitmap_HasAlpha(NewBitmapList[nSel]->Bitmap))
			nErrorCode = WriteTGA(SaveFile, NewBitmapList[nSel]->Bitmap);
		else
			nErrorCode = WriteBMP8(SaveFile, NewBitmapList[nSel]->Bitmap);
		// end change

		if (nErrorCode != TPACKERROR_OK)
		{
			// Error writing this bitmap
			switch (nErrorCode)
			{
			case TPACKERROR_CREATEFILE:
				NonFatalError("Unable to create output file %s", SaveFile);
				break;
			case TPACKERROR_WRITE:
				NonFatalError("I/O error writing %s", szFile);
				break;
			case TPACKERROR_MEMORYALLOCATION:
				NonFatalError("Memory allocation error writing %s", SaveFile);
				break;
			case TPACKERROR_UNKNOWN:
			default:
				NonFatalError("UInknown error writing %s", SaveFile);
			}
		}

	}
	return 1;
}


// *************************************************************************
// *				SaveSelectedFile  09/04/04   						   *
// *************************************************************************
bool VM_TextLib::SaveSelectedFile(char* Extension, char* TszFile)
{
	OPENFILENAME ofn;
	char LszFile[260];
	LszFile[0] = 0;
	strcpy(LszFile, TszFile);


	//	strcpy(szFile,FileNameFullACP); // Copy OpenFile Name 
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = LszFile;
	ofn.nMaxFile = sizeof(LszFile);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = SaveFile;
	ofn.nMaxFileTitle = sizeof(SaveFile);;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrTitle = "Save Texture";

	ofn.Flags =
		OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT;
	if (GetSaveFileName(&ofn) == TRUE)
	{
		strcpy(SaveFile, LszFile);
		return 1;
	}

	return 0;
}


// *************************************************************************
// *					CheckExtention  09/04/04   					 	   *
// *************************************************************************
bool VM_TextLib::CheckExtention(char *FileName)
{
	int ch = '.';
	char *IsIt;
	IsIt = strchr(FileName, ch);
	if (IsIt == NULL) // if no extension . extension return 0
	{
		return 0;
	}
	return 1; // file name has an extension return 1;
}


// *************************************************************************
// *						TPack_ExtractAll  06/06/08 			  		   *
// *************************************************************************
bool VM_TextLib::TPack_ExtractAll()
{
	//HWND            hLB = GetDlgItem(pData->hwnd, IDC_TEXTURELIST);
	//int             nCount;
	//int             i;
	////	BitmapEntry *	pEntry;
	//char            szName[256];
	//char            szFile[256];
	//char            szPath[256];
	//int             nErrorCode;

	//_chdir(S_File[0]->NewPath);
	//strcpy(szPath, S_File[0]->NewPath);
	//_mkdir(S_File[0]->NewSubFolderName);
	//strcat(szPath, "//");
	//strcat(szPath, S_File[0]->NewSubFolderName);

	//nCount = SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_GETCOUNT, (WPARAM)0, (LPARAM)0);

	//for (i = 0; i < nCount; i++)
	//{
	//	if (SendMessage(pData->hwnd, LB_GETTEXT, i, (LPARAM)(LPCTSTR)szName) != LB_ERR) // Get text
	//	{

	//		if (NewBitmapList[i])
	//		{
	//			strcpy(szFile, szPath);
	//			strcat(szFile, "\\");
	//			strcat(szFile, NewBitmapList[i]->Name);

	//			if (geBitmap_HasAlpha(NewBitmapList[i]->Bitmap))
	//				strcat(szFile, ".tga");
	//			else
	//				strcat(szFile, ".bmp");


	//			if (geBitmap_HasAlpha(NewBitmapList[i]->Bitmap))
	//				nErrorCode = WriteTGA(szFile, NewBitmapList[i]->Bitmap);
	//			else
	//				nErrorCode = WriteBMP8(szFile, NewBitmapList[i]->Bitmap);


	//			if (nErrorCode != TPACKERROR_OK)
	//			{
	//				// Error writing this bitmap
	//				switch (nErrorCode)
	//				{
	//				case TPACKERROR_CREATEFILE:
	//					NonFatalError("Unable to create output file %s", szFile);
	//					break;
	//				case TPACKERROR_WRITE:
	//					NonFatalError("I/O error writing %s", szFile);
	//					break;
	//				case TPACKERROR_MEMORYALLOCATION:
	//					NonFatalError("Memory allocation error writing %s", szFile);
	//					break;
	//				case TPACKERROR_UNKNOWN:
	//				default:
	//					NonFatalError("UInknown error writing %s", szFile);
	//				}

	//				break;
	//			}
	//		}
	//	}
	//}

	return 1;
}

// *************************************************************************
// *						Save/SaveAs  13/06/08 				  		   *
// *************************************************************************
bool VM_TextLib::Save(const char *Path)
{
	char		FileName[_MAX_PATH];
	geVFile *	VFS;
	int			i;

	if (!Path)
	{
		OPENFILENAME ofn;	// Windows open filename structure...
		char Filter[_MAX_PATH];
		char	Dir[_MAX_PATH];

		FileName[0] = '\0';

		GetCurrentDirectory(sizeof(Dir), Dir);

		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = pData->hwnd;
		ofn.hInstance = pData->Instance;
		{
			char *c;

			// build actor file filter string
			strcpy(Filter, "Texture Libraries (*.txl)");
			c = &Filter[strlen(Filter)] + 1;
			// c points one beyond end of string
			strcpy(c, "*.txl");
			c = &c[strlen(c)] + 1;
			*c = '\0';	// 2nd terminating nul character
		}
		ofn.lpstrFilter = Filter;
		ofn.lpstrCustomFilter = NULL;
		ofn.nMaxCustFilter = 0;
		ofn.nFilterIndex = 1;
		ofn.lpstrFile = FileName;
		ofn.nMaxFile = sizeof(FileName);
		ofn.lpstrFileTitle = FileName;
		ofn.nMaxFileTitle = sizeof(FileName);
		ofn.lpstrInitialDir = Dir;
		ofn.lpstrTitle = NULL;
		ofn.Flags = OFN_HIDEREADONLY;
		ofn.nFileOffset = 0;
		ofn.nFileExtension = 0;
		ofn.lpstrDefExt = "txl";
		ofn.lCustData = 0;
		ofn.lpfnHook = NULL;
		ofn.lpTemplateName = NULL;

		if (!GetSaveFileName(&ofn))
			return 0;

		Path = FileName;
	}

	_unlink(Path);
	VFS = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_VIRTUAL, Path, NULL, GE_VFILE_OPEN_CREATE | GE_VFILE_OPEN_DIRECTORY);
	if (!VFS)
	{
		NonFatalError("Could not open file %s", Path);
		return 0;
	}

	for (i = 0; i < pData->BitmapCount; i++)
	{
		geVFile *	File;
		geBoolean	WriteResult;



		File = geVFile_Open(VFS, NewBitmapList[i]->Name, GE_VFILE_OPEN_CREATE);
		if (!File)
		{
			NonFatalError("Could not save bitmap %s", NewBitmapList[i]->Name);
			geVFile_Close(VFS);
			return 0;
		}
		WriteResult = geBitmap_WriteToFile(NewBitmapList[i]->Bitmap, File);
		geVFile_Close(File);
		if (WriteResult == GE_FALSE)
		{
			NonFatalError("Could not save bitmap %s", NewBitmapList[i]->Name);
			geVFile_Close(VFS);
			return 0;
		}
	}

	strcpy(pData->TXLFileName, Path);
	pData->FileNameIsValid = TRUE;

	if (geVFile_Close(VFS) == GE_FALSE)
		NonFatalError("I/O error writing %s", Path);
	else
		pData->Dirty = FALSE;
	return 1;
}


// *************************************************************************
// *						CleanUp  06/06/08 					  		   *
// *************************************************************************
bool VM_TextLib::CleanUp()
{

	if (Entry) { delete Entry; Entry = NULL; }

	//if (pData ) { delete pData; pData = NULL; }
	return 1;
}

// *************************************************************************
// *						GetName  06/06/08 					  		   *
// *************************************************************************
bool VM_TextLib::GetName()
{

	int Index = 0;// SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
//	SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_GETTEXT, (WPARAM)Index, (LPARAM)&TextureName[0]);
	return 1;
}
// *************************************************************************
// *						ReName  06/06/08 					  		   *
// *************************************************************************
bool VM_TextLib::ReName(const char *NewName)
{

	int Index = 0;// SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	//SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_GETTEXT, (WPARAM)Index, (LPARAM)&TextureName[0]);
	int location = FindBitmap(pData, TextureName);

	strcpy(NewBitmapList[location]->Name, NewName);
	return 1;
}

// *************************************************************************
// *						UpDateList  13/06/08 					  	   *
// *************************************************************************
bool VM_TextLib::UpDateList(const char *NewName)
{

	int Index = SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

	int	i;

	for (i = 0; i < pData->BitmapCount; i++)
	{

		SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)NewBitmapList[i]->Name);

	}

	SendDlgItemMessage(pData->hwnd, IDC_TEXTURELIST, LB_SETCURSEL, (WPARAM)Index, (LPARAM)0);

	return 1;
}

// *************************************************************************
// *					Txt_OpenFile Terry Bernie						   *
// *************************************************************************
bool VM_TextLib::Txt_OpenFile(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(Txt_FileName, "");
	strcpy(Txt_Path_FileName, "");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Txt_Path_FileName;						// full path and file name
	ofn.nMaxFile = sizeof(Txt_Path_FileName);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Txt_FileName;						// Just File Name
	ofn.nMaxFileTitle = sizeof(Txt_FileName);;
	ofn.lpstrInitialDir = StartDirectory;
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return 1;
	}
	return 0;
}
