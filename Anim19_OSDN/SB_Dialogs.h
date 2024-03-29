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
class SB_Dialogs
{
public:
	SB_Dialogs();
	~SB_Dialogs();

	void Front_Screen();

	bool Dialog_Text();
	void YesNo(char *Text, char *Text2,bool YesNo);
	bool Dialog_DropGen();

	bool Dialog_Counter();
	bool UpDate_Counter_Dialog(HWND hDlg);
	bool Set_Counter_Dialog(HWND hDlg, bool Disable);
	bool GameMode_StartPosition_Dlg();

	bool Start_Message_Settings_DLG();
	bool Start_Copy_Dlg(int Usage, bool CheckForSpaces, bool Use_Camera);
	
	bool DoFPS;
	bool Saved_DoFPS;

	char Chr_DropText[MAX_PATH];
	int DropList_Data;

	bool Canceled;
	bool YesNo_Flag;

	char btext[MAX_PATH];
	char Chr_Text[MAX_PATH];

	char MessageString[MAX_PATH];
	char MessageString2[MAX_PATH];

protected:

	static LRESULT CALLBACK Dialog_Text_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK YesNo_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dialog_DropGen_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Front_Screen_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dialog_Counter_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK GameMode_StartPosition_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Message_Settings_DLG_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Copy_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void ListObjects(HWND List);
	void List_Locations(HWND List);
	void List_Axis(HWND List);
	void List_Counters(HWND List);
	void List_Display(HWND List);
	void List_Maths(HWND List);
	void List_Particles(HWND List);
};

