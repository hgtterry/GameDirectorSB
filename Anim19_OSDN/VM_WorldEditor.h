#pragma once

typedef struct Char_type2 { char Name[256]; }Char_type2;

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
	bool Start_WE_import();

	bool LoadTextures_TXL();

	bool Txt_OpenFile(char* Extension, char* Title, char* StartDirectory);

	char Txt_FileName[255];
	char Txt_Path_FileName[1024];

	char WE_FileName[255];
	char WE_Path_FileName[1024];

protected:

	static LRESULT CALLBACK WE_import_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool AddTexture(geVFile *BaseFile, const char *Path,int  GroupIndex);

	bool NonFatalError(const char *Msg, ...);

	int Check_for_Textures(geVFile *BaseFile);
	bool Check_in_Txl(char *FileName);

	HBITMAP CreateHBitmapFromgeBitmap(geBitmap *Bitmap, HDC hdc);

	TPack_WindowData2 *p_Data2;
	BitmapEntry2 *	NewBitmapList2[200];
	BitmapEntry2 *   Entry;

	std::vector<Char_type2> BitMap_Names;

	int NameCount;
	OPENFILENAME ofn;
};
