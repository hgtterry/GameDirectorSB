#pragma once
class GD19_Stock
{
public:
	GD19_Stock(void);
	~GD19_Stock(void);

	void Start_Stock_Dialog(void);

	void Update_Message_Properties(void);
	void Update_Sound_Properties(void);

	void Add_Panel(void);
	void Update_Panel_Properties(void);
	int Edit_Panel_Stock(LPARAM lParam);

	int Selected_Stock_Index;
	int Selected_Stock_Index2;
	int Selected_Stock_Type;
	int Selected_Panel_Index;

	void List_Stock_Dialog(int ListType);
	
	int ListIndex;
	int ListIndex_Old;
	int ItemToSelect;

	HWND Stock_Dialog_hWnd;
	HWND OptionsDlgHwnd;
	HWND Stock_Properties_hLV;

protected:

	static LRESULT CALLBACK List_Stock_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Stock_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void ListView_OnClickOptions(LPARAM lParam);
	int Edit_Message_Stock(LPARAM lParam);
	int Edit_Sound_Stock(LPARAM lParam);

	void Test_Sound(int Index);
	void List_Sounds_Stock(HWND List);
	void Select_Item(int Index);

	void Init_Stock_FileView(void);
	void AddOptions(void);
	void Stock_Create_Properties_hLV(void);

	HWND ItemList_Hwnd;

	char btext[255];

	int mListType;

	TV_INSERTSTRUCT tvinsert;
	HTREEITEM mParent;
	HTREEITEM mRoot1;

	HIMAGELIST mImageList;
	HBITMAP hBitMap;
};

