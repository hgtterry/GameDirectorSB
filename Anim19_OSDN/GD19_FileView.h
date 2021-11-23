/*
Copyright (c) GameDirector 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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
class GD19_FileView
{
public:
	GD19_FileView();
	~GD19_FileView();

	void ChangeItem_Name_Stock(HTREEITEM Folder, char* FolderName);
	void ChangeItem_Name(HTREEITEM Folder, char* New_Name);

	void DeleteItem();

	void Select_Item(int Index);
	bool SelectItem(HTREEITEM TreeItem);
	void HideRightPanes(void);

	HTREEITEM Add_Room_Object(char* SFileName, int Index);
	HTREEITEM Add_MiscFile(char *SFileName, int Index);
	HTREEITEM Add_Sound_Entity(char *SFileName, int Index);
	HTREEITEM Add_Message_Entity(char *SFileName, int Index);
	HTREEITEM Add_Move_Entity(char *SFileName, int Index);
	HTREEITEM Add_Collectable(char* SFileName, int Index);
	HTREEITEM Add_Teleport(char* SFileName, int Index);

	HTREEITEM Add_PlayerFile(char *SFileName, int Index);
	
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

	HIMAGELIST hImageList;
	HBITMAP hBitMap;
	TV_INSERTSTRUCT tvinsert;

	char LevelName[255];
	char FileView_Folder[255];
	char FileView_File[255];

	bool FileView_Active;
	bool Level_But_Active;
	bool Stock_But_Active;
};

