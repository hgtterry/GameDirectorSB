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

typedef struct TGAHEADER
{
	char	IDLength;
	char	ColorMapType;
	char	ImageType;
	uint16	CMFirstEntry;
	uint16	CMLength;
	char	CMEntrySize;
	uint16	Xorigin;
	uint16	Yorigin;
	uint16	Width;
	uint16	Height;
	char	PixelDepth;
	char	ImageDescriptor;
} TGAHEADER;

#pragma pack()


class TTextureLib  
{
public:
	TTextureLib();
	virtual ~TTextureLib();

	int TTextureLib::WriteTGA(const char * pszFile, geBitmap *pBitmap);

	BOOL TTextureLib::Render2d_Blit(HDC hDC, HBITMAP Bmp,  HBITMAP Alpha, const RECT *SourceRect, const RECT *DestRect);

	int TTextureLib::WriteBMP8(const char * pszFile, geBitmap *pBitmap);


	BOOL TTextureLib::LoadFile(HWND ChDlg);
	BOOL TTextureLib::NonFatalError(const char *Msg, ...);
	BOOL TTextureLib::AddTexture(geVFile *BaseFile, const char *Path);
	BOOL TTextureLib::SelectBitmap();
	int TTextureLib::FindBitmap(TPack_WindowData *pData, const char *Name);
	HBITMAP TTextureLib::CreateHBitmapFromgeBitmap (geBitmap *Bitmap, HDC hdc);
	BOOL TTextureLib::UpDateGeList(int Location);

	BOOL TTextureLib::TPack_ExtractSelected();
	BOOL TTextureLib::SaveSelectedFile(char* Extension,char* TszFile);

	BOOL TTextureLib::CheckExtention(char *FileName);
	BOOL TTextureLib::TPack_ExtractAll();
	BOOL TTextureLib::Save(const char *Path);
	BOOL TTextureLib::CleanUp();
	BOOL TTextureLib::GetName();
	BOOL TTextureLib::ReName(const char *NewName);
	BOOL TTextureLib::UpDateList(const char *NewName);



	TPack_WindowData *pData;
	BitmapEntry *	NewBitmapList[200];
	BitmapEntry *   Entry;
	char LastPath [256];
	char TextureName[256];
	char NewTextureName[256];
	int EditOrLoad;
	char L_FileName[256];
	char SaveFile[256];

};

#endif // !defined(AFX_TTEXTURELIB_H__DB5984F2_BA86_412D_A409_C0EC519FBDC5__INCLUDED_)
