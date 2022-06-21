#pragma once
class ME_FileView
{
public:
	ME_FileView();
	~ME_FileView();

	void Start_FileView(void);
	void Init_FileView(void);

	bool FileView_Active;

protected:

	static LRESULT CALLBACK ListPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void AddRootFolder(void);

	TV_INSERTSTRUCT tvinsert;

	HTREEITEM Root;
	HTREEITEM GD_ProjectFolder;
};



