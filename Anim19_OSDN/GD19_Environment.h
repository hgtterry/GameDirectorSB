/*
Copyright (c) 2022 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
class GD19_Environment
{
public:
	GD19_Environment(void);
	~GD19_Environment(void);

	void Start_Environment(char* Category);
	bool EnableFog(bool SetFog);
	void SetSky(bool Enable);

	void Show_Environment_Dialog(bool show);
	void Enable_Environment_Dialog(bool show);

	void Test_Ambient();

	void Select_Category(char* FileView_Folder);

	bool Environment_Dlg_Active;

	HWND Environment_hWnd;

protected:

	static LRESULT CALLBACK Environment_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK BackDrop_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Create_GeneralListBackDrop(HWND hDlg);
	void Create_GeneralList(HWND hDlg);
	
	bool On_Click_Props(LPARAM lParam);

	HWND BackDrop_hWnd;
	HWND General_hLV;
	HWND mPropsCon;

	int SelectedProperties;

	char FileView_Folder[64];
	
	char btext[255];
	
	HTREEITEM mParent;
	HTREEITEM mRoot1;

	void Update_CreateFogListView(void);
	void Update_CreateMainLightListView(void);
	void Update_CreateSoundListView(void);
	void Update_CreateSkyListView(void);


	TV_INSERTSTRUCT tvinsert;
};

