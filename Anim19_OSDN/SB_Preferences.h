/*
Copyright (c) 2021 EquitySB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Preferences
{
public:
	SB_Preferences();
	~SB_Preferences();

	void Set_Defaults();
	bool Write_Preferences();
	bool Read_Preferences();

	bool Start_Preferences();

	bool QL_Use_TestFile_Flag;
	char QL_User_File[MAX_PATH];

protected:

	static LRESULT CALLBACK Preferences_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK QuickLoad_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void AddRootFolder(void);

	bool Start_QuickLoad_Dlg();

	HWND Main_Window_Hwnd;
	HWND FileView_Hwnd;

	HTREEITEM Root;
	HTREEITEM FV_File;

	TV_INSERTSTRUCT tvinsert;

	FILE *WriteScene;
};


