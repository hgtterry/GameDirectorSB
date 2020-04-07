// TTextureLib.h: interface for the TTextureLib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TTEXTURELIB_H__DB5984F2_BA86_412D_A409_C0EC519FBDC5__INCLUDED_)
#define AFX_TTEXTURELIB_H__DB5984F2_BA86_412D_A409_C0EC519FBDC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	char			TXLFileName[256];
	BOOL			Dirty;
}	TPack_WindowData;

#pragma pack(1)

//typedef struct TGAHEADER
//{
//	char	IDLength;
//	char	ColorMapType;
//	char	ImageType;
//	uint16	CMFirstEntry;
//	uint16	CMLength;
//	char	CMEntrySize;
//	uint16	Xorigin;
//	uint16	Yorigin;
//	uint16	Width;
//	uint16	Height;
//	char	PixelDepth;
//	char	ImageDescriptor;
//} TGAHEADER;

#pragma pack()


class VM_TextLib
{
public:
	VM_TextLib();
	virtual ~VM_TextLib();

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



	TPack_WindowData *pData;
	BitmapEntry *	NewBitmapList[200];
	BitmapEntry *   Entry;
	char LastPath [256];
	char TextureName[256];
	char NewTextureName[256];
	int EditOrLoad;
	char L_FileName[256];
	char SaveFile[256];

	char FileName[255];

};

#endif // !defined(AFX_TTEXTURELIB_H__DB5984F2_BA86_412D_A409_C0EC519FBDC5__INCLUDED_)
