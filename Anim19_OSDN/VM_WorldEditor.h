#pragma once

typedef	struct	BitmapEntry2
{
	char *		Name;
	geBitmap *	Bitmap;
	HBITMAP		WinBitmap;
	HBITMAP		WinABitmap;
	unsigned	Flags;
	int			Dirty;
}	BitmapEntry2;

typedef struct	TPack_WindowData2
{
	HINSTANCE		Instance;
	HWND			hwnd;
	int				BitmapCount;
	BitmapEntry	*	Bitmaps;
	BitmapEntry *	SelectedEntry;
	BOOL			FileNameIsValid;
	char			TXLFileName[1024];
	BOOL			Dirty;
}	TPack_WindowData2;


class VM_WorldEditor
{
public:
	VM_WorldEditor();
	~VM_WorldEditor();

	void Adjust();;
	void Change_Textures();

	bool Txt_OpenFile(char* Extension, char* Title, char* StartDirectory);

	char Txt_FileName[255];
	char Txt_Path_FileName[1024];

protected:

	bool LoadFile();
	bool AddTexture(geVFile *BaseFile, const char *Path);

	bool NonFatalError(const char *Msg, ...);

	TPack_WindowData2 *p_Data2;
	BitmapEntry2 *	NewBitmapList2[200];
	BitmapEntry2 *   Entry;

	OPENFILENAME ofn;
};

