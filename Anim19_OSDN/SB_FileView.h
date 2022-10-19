/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_FileView
{
public:
	SB_FileView();
	~SB_FileView();

	void Start_FileView(void);
	void Init_FileView(void);

	void Redraw_FileView();
	void Reset_Class();

	void Change_Project_Name(void);
	void Change_Level_Name(void);
	void Change_Item_Name(HTREEITEM Folder, char *FolderName);

	void Mark_Altered_Folder(HTREEITEM Item);
	void Mark_Altered(HTREEITEM Item);
	void Mark_Clear(HTREEITEM Item);
	void Mark_Clear_Folder(HTREEITEM Item);

	void Set_FolderActive(HTREEITEM Folder);

	void DeleteItem();
	bool SelectItem(HTREEITEM TreeItem);

	char LevelName[255];

	// Delete All items and Reset file View [231121]
	void Delete_AllItems();

	bool FileView_Active;
	bool Level_But_Active;
	bool Stock_But_Active;

	bool FileView_Pined;

	HTREEITEM Add_Item(HTREEITEM Folder,char *SFileName, int Index, bool NewItem);

	HTREEITEM FV_Players_Folder;	// Players Folder FileFView
	HTREEITEM FV_Areas_Folder;		// Areas/Rooms Folder FileFView
	HTREEITEM FV_LevelFolder;
	HTREEITEM FV_Cameras_Folder;
	HTREEITEM FV_Objects_Folder;
	HTREEITEM FV_Messages_Folder;
	HTREEITEM FV_Sounds_Folder;
	HTREEITEM FV_Move_Folder;
	HTREEITEM FV_Teleporters_Folder;
	HTREEITEM FV_Collectables_Folder;

	HMENU hMenu;

protected:

	static LRESULT CALLBACK ListPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Init_Bmps_FileView();
	void AddRootFolder(void);
	void MoreFoldersD(void);
	void ExpandRoot(void);
	void Get_Selection(LPNMHDR lParam);
	void HideRightPanes(void);

	void Context_Menu(HWND hDlg);
	void Context_New(HWND hDlg);
	void Context_Delete(HWND hDlg);

	TV_INSERTSTRUCT tvinsert;

	HIMAGELIST hImageList;
	HBITMAP hBitMap;

	HTREEITEM Root;
	HTREEITEM GD_ProjectFolder;
	HTREEITEM GD_TriggerFolder;
	HTREEITEM GD_EntitiesFolder;
	HTREEITEM GD_Environment_Folder;
	HTREEITEM GD_Area_Change_Folder;
	HTREEITEM GD_Level_Change_Folder;
	HTREEITEM GD_Particles_Folder;

	int Context_Selection;

	char FileView_Folder[255];
	char FileView_File[255];
};

