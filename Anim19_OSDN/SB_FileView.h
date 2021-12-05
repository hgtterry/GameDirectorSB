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

	void Change_Level_Name(void);
	void Change_Item_Name(HTREEITEM Folder, char *FolderName);

	void DeleteItem();
	void Select_Item(int Index);
	bool SelectItem(HTREEITEM TreeItem);

	char LevelName[255];

	// Delete All items and Reset file View [231121]
	void Delete_AllItems();

	bool FileView_Active;
	bool Level_But_Active;
	bool Stock_But_Active;

	HTREEITEM Add_PlayerFile(char *SFileName, int Index);
	HTREEITEM Add_Camera(char *SFileName, int Index);
	HTREEITEM Add_Area(char *SFileName, int Index);

protected:

	static LRESULT CALLBACK ListPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void AddRootFolder(void);
	void MoreFoldersD(void);
	void ExpandRoot(void);
	void Get_Selection(LPNMHDR lParam);
	void HideRightPanes(void);

	TV_INSERTSTRUCT tvinsert;

	HIMAGELIST hImageList;
	HBITMAP hBitMap;

	HTREEITEM Root;
	HTREEITEM GD_ProjectFolder;
	HTREEITEM GD_ObjectsFolder;
	HTREEITEM GD_LevelFolder;
	HTREEITEM GD_CameraFolder;
	HTREEITEM GD_TriggerFolder;
	HTREEITEM GD_EntitiesFolder;
	HTREEITEM GD_Entities_Sound_Folder;
	HTREEITEM GD_Entities_Message_Folder;
	HTREEITEM GD_Entities_Move_Folder;
	HTREEITEM GD_Collectables_Folder;
	HTREEITEM GD_Teleporters_Folder;
	HTREEITEM GD_Environment_Folder;
	HTREEITEM GD_Area_Change_Folder;
	HTREEITEM GD_Level_Change_Folder;
	HTREEITEM GD_Particles_Folder;

	HTREEITEM GD_Player;
	HTREEITEM GD_Rooms;

	char FileView_Folder[255];
	char FileView_File[255];
};

