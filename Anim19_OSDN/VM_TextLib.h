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

#pragma once

#define	ENTRY_DELETED	0x00000001

// Error codes
#define TPACKERROR_OK                0    
#define TPACKERROR_UNKNOWN           (TPACKERROR_OK - 1)    
#define TPACKERROR_WRITE             (TPACKERROR_OK - 2)
#define TPACKERROR_MEMORYALLOCATION  (TPACKERROR_OK - 3)
#define TPACKERROR_CREATEFILE        (TPACKERROR_OK - 4)

typedef struct tagMY_BITMAPINFO
{
	BITMAPINFOHEADER bmiHeader; 
	RGBQUAD          bmiColors[256]; 
} MY_BITMAPINFO, *pMY_BITMAPINFO, **ppMY_BITMAPINFO; 

#define PAD32(i)     (((i)+31)/32*4)

typedef	struct	BitmapEntry
{
	char *		Name;
	geBitmap *	Bitmap;
	HBITMAP		WinBitmap;
	HBITMAP		WinABitmap;
	unsigned	Flags;
	int			Dirty;
}	BitmapEntry;
 
typedef struct	TPack_WindowData
{
	HINSTANCE		Instance;
	HWND			hwnd;
	int				BitmapCount;
	BitmapEntry	*	Bitmaps;
	BitmapEntry *	SelectedEntry;
	BOOL			FileNameIsValid;
	char			TXLFileName[1024];
	BOOL			Dirty;
}	TPack_WindowData;


class VM_TextLib
{
public:
	VM_TextLib();
	~VM_TextLib();

	void Start_TexturePack();

	int WriteTGA(const char * pszFile, geBitmap *pBitmap);

	bool Render2d_Blit(HDC hDC, HBITMAP Bmp,  HBITMAP Alpha, const RECT *SourceRect, const RECT *DestRect);

	int WriteBMP8(const char * pszFile, geBitmap *pBitmap);


	bool LoadFile(HWND ChDlg);
	bool NonFatalError(const char *Msg, ...);
	bool AddTexture(geVFile *BaseFile, const char *Path);
	bool SelectBitmap();
	int FindBitmap(TPack_WindowData *pData, const char *Name);
	HBITMAP CreateHBitmapFromgeBitmap (geBitmap *Bitmap, HDC hdc);
	bool UpDateGeList(int Location);

	bool TPack_ExtractSelected();
	bool SaveSelectedFile(char* Extension,char* TszFile);

	bool CheckExtention(char *FileName);
	bool TPack_ExtractAll();
	bool Save(const char *Path);
	bool CleanUp();
	bool GetName();
	bool ReName(const char *NewName);
	bool UpDateList(const char *NewName);



	TPack_WindowData *p_Data;
	BitmapEntry *	NewBitmapList[200];
	BitmapEntry *   Entry;

	char LastPath [256];
	char TextureName[256];
	char NewTextureName[256];
	int EditOrLoad;
	char L_FileName[256];
	char SaveFile[256];

	char Txt_FileName[255];
	char Txt_Path_FileName[1024];

protected:

	static LRESULT CALLBACK TextureLib_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static bool CALLBACK TextureLibPreviewWnd(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK RenameProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	
	bool Txt_OpenFile(char* Extension, char* Title, char* StartDirectory);

	OPENFILENAME ofn;

};

