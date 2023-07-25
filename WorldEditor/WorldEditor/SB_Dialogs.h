/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Dialogs
{
public:
	SB_Dialogs(void);
	~SB_Dialogs(void);

	void YesNo(char* Text, char* Text2);
	bool Start_ListData(int WhatList);
	void Start_Speed_Camera();
	bool Start_Dialog_DropGen();

	bool Canceled;

	char MessageString[100];
	char MessageString2[100];

	char btext[100];
	char Chr_DropText[MAX_PATH];
	int DropList_Data;

private:
	static LRESULT CALLBACK YesNo_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ListData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Speed_Camera_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dialog_DropGen_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void List_SceneData(HWND hDlg);
	void List_BoundingBox(HWND hDlg);
	void Read_ErrorLog(HWND hDlg);
	void UnCheck_All_SpeedMouseOption();
	void ListGroups(HWND List);
	void UpdateGroupDetails(HWND List);

	bool F_ListData_Dlg_Active;
	int mWhatList;

	bool Mouse_Normal;
	bool Mouse_Slow;
	bool Mouse_VerySlow;
	bool Mouse_Fast;

	CFusionDoc* m_pDoc;
};

