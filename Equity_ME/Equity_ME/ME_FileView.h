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
	void Change_Level_Name(void);
	void Set_FolderActive(HTREEITEM Folder);

	HTREEITEM Add_Group(char *SFileName, int Index);
	void Add_MotionFile(char *SFileName, int Index);

	HTREEITEM GD_GroupsFolder;
	HTREEITEM GD_AnimationFolder;

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
	

	HIMAGELIST hImageList;
};



