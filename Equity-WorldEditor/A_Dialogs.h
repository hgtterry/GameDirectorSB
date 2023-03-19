// A_Dialogs.h: interface for the A_Dialogs class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_A_DIALOGS_H__373548E3_01B1_47FB_8C16_BF24D6C48B3A__INCLUDED_)
#define AFX_A_DIALOGS_H__373548E3_01B1_47FB_8C16_BF24D6C48B3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class A_Dialogs  
{
public:
	A_Dialogs();
	virtual ~A_Dialogs();

	bool Show_ListData();
	void List_SceneData(HWND hDlg);

	void Start_FrontPanel();

	bool F_WireFrame;
	bool F_Textured;

protected:

	static LRESULT CALLBACK ListData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK FrontPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif // !defined(AFX_A_DIALOGS_H__373548E3_01B1_47FB_8C16_BF24D6C48B3A__INCLUDED_)
