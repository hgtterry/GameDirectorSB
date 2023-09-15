#pragma once

/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

class SB_FileView
{
public:
	SB_FileView(void);
	~SB_FileView(void);

	void Start_FileView(void);
	void Init_FileView(void);
	HTREEITEM Add_Item(HTREEITEM Folder, char* SFileName, int Index, bool NewItem);
	void Set_FolderActive(HTREEITEM Folder);
	void SelectItem(HTREEITEM TreeItem);
	void ExpandRoot(void);
	void Mark_Altered(HTREEITEM Item);

	HTREEITEM FV_Players_Folder;	// Players Folder FileFView
	HTREEITEM FV_Objects_Folder;
	HTREEITEM FV_EntitiesFolder;
	HTREEITEM FV_Evirons_Folder;

private:

	static LRESULT CALLBACK ListPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void AddRootFolder(void);
	void MoreFoldersD(void);
	void Get_Selection(LPNMHDR lParam);

	char FileView_Folder[255];
	char FileView_File[255];

	TV_INSERTSTRUCT tvinsert;

	HTREEITEM Root;
	HTREEITEM GD_ProjectFolder;
	HTREEITEM FV_Areas_Folder;		// Areas/Rooms Folder FileFView
	HTREEITEM FV_LevelFolder;
	HTREEITEM FV_Cameras_Folder;
	

	HIMAGELIST hImageList;
	HBITMAP hBitMap;

};

