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

#if !defined(AFX_A_DIALOGS_H__373548E3_01B1_47FB_8C16_BF24D6C48B3A__INCLUDED_)
#define AFX_A_DIALOGS_H__373548E3_01B1_47FB_8C16_BF24D6C48B3A__INCLUDED_

class A_Dialogs  
{
public:
	A_Dialogs();
	virtual ~A_Dialogs();

	bool Show_About_Dlg();
	void Message(char* pString, char* pString2);
	void Start_Properties();
	bool Show_ListData();
	void List_SceneData(HWND hDlg);
	void Start_FrontPanel();
	char Message_Text_Header[MAX_PATH];
	char Message_Text_Message[MAX_PATH];

	bool F_WireFrame;
	bool F_Textured;

	bool F_ListData_Dlg_Active;

protected:

	static LRESULT CALLBACK Message_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ListData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK FrontPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK About_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);



	void A_Dialogs::Get_Current_Document();

	char Current_Txl_File[MAX_PATH];

	CFusionDoc			*m_pDoc;
};

#endif // !defined(AFX_A_DIALOGS_H__373548E3_01B1_47FB_8C16_BF24D6C48B3A__INCLUDED_)
