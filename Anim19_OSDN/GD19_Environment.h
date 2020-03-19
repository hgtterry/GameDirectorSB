#pragma once
class GD19_Environment
{
public:
	GD19_Environment(void);
	~GD19_Environment(void);

	void Start_Environment(void);
	void Load_Environment(void);
	bool EnableFog(bool SetFog);

protected:

	static LRESULT CALLBACK Environment_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK BackDrop_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Init_FileView(void);

	void Create_GeneralListBackDrop(HWND hDlg);
	void Create_GeneralList(HWND hDlg);
	void GetListControls(void);
	void AddOptions(void);
	void ListView_Selection(LPNMHDR lParam);

	bool Props_OnClick(LPARAM lParam);

	HWND OptionsDlgHwnd;
	HWND BackDrop_hWnd;
	HWND General_hLV;
	HWND mTreeCon;
	HWND mPropsCon;
	HWND Environment_hWnd;

	int SelectedProperties;

	char FileView_Folder[64];
	char FileView_File[64];
	char btext[255];
	char TextInt[256];

	bool Environment_Dlg_Active;

	TV_INSERTSTRUCT tvinsert;

	HTREEITEM mParent;
	HTREEITEM mRoot1;

	HIMAGELIST mImageList;
	HBITMAP hBitMap;

protected:

	void Update_CreateFogListView(void);
	void Update_CreateMainLightListView(void);
	void Update_CreateSoundListView(void);
	void Update_CreateSkyListView(void);

	void SetSky(bool Enable);
};

