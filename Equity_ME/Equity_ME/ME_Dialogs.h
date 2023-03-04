/*
Copyright (c) 2022 Equity_ME Model Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
class ME_Dialogs
{
public:
	ME_Dialogs();
	~ME_Dialogs();

	bool Show_ListData();
	void Start_Speed_Camera();
	void Message(char *pString);
	void YesNo(char *Text, char *Text2);
	void Dialog_Text();

	int What_List;

	bool Canceled;
	bool Is_Canceled;

	char MessageString[100];
	char MessageString2[100];

	char btext[MAX_PATH];
	char Chr_Text[MAX_PATH];

protected:

	static LRESULT CALLBACK GroupData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Speed_Camera_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Message_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK YesNo_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dialog_Text_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void List_GroupData(HWND hDlg);
	void List_App_Data(HWND hDlg);

	void UnCheck_All_SpeedMouseOption();

	bool Mouse_Normal;
	bool Mouse_Slow;
	bool Mouse_VerySlow;
	bool Mouse_Fast;

	char Message_Text[MAX_PATH];
};

