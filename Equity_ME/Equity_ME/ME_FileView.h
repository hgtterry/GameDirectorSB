#pragma once
class ME_FileView
{
public:
	ME_FileView();
	~ME_FileView();

	void Reset_Class(void);

	void Start_FileView(void);
	void Init_FileView(void);
	void ExpandRoot(void);
	void Get_Selection(LPNMHDR lParam);
	void SelectItem(HTREEITEM TreeItem);
	void Delete_AllItems();

	HTREEITEM Add_Group(char *SFileName, int Index);

	bool FileView_Active;

protected:

	static LRESULT CALLBACK ListPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void AddRootFolder(void);
	void MoreFoldersD(void); // last folder level
	
	char FileView_Folder[256];
	char FileView_File[256];

	TV_INSERTSTRUCT tvinsert;

	HTREEITEM Root;
	HTREEITEM GD_ProjectFolder;

	HTREEITEM GD_ModelFolder;
	HTREEITEM GD_GroupsFolder;
};



