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

#include "StdAfx.h"
#include "AB_App.h"
#include "resource.h"
#include "SB_Dialogs.h"

SB_Dialogs::SB_Dialogs(void)
{
	MessageString[0] = 0;
	MessageString2[0] = 0;

	F_ListData_Dlg_Active = 0;

	Canceled = 0;

	m_pDoc = nullptr;
}

SB_Dialogs::~SB_Dialogs(void)
{
}

// *************************************************************************
// *	  			YesNo:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_Dialogs::YesNo(char* Text, char* Text2)
{
	Canceled = 0;
	MessageString[0] = 0;
	MessageString2[0] = 0;

	strcpy(MessageString, Text);
	strcpy(MessageString2, Text2);

	DialogBox(App->hInst, (LPCTSTR)IDD_SB_YESNO, App->MainHwnd, (DLGPROC)YesNo_Proc);
}

// *************************************************************************
// *		  YesNo_Proc_Proc:- Terry and Hazel Flanigan 2023	  		   *
// *************************************************************************
LRESULT CALLBACK SB_Dialogs::YesNo_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		//App->SetTitleBar(hDlg);

		SendDlgItemMessage(hDlg, IDC_BANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTEXT, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_BANNER, App->CLSB_Dialogs->MessageString);
		SetDlgItemText(hDlg, IDC_STTEXT, App->CLSB_Dialogs->MessageString2);
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_BANNER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		if (GetDlgItem(hDlg, IDC_STTEXT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		return FALSE;
	}
	case WM_NOTIFY:
	{
		/*LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDCANCEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	case WM_COMMAND:

		if (LOWORD(wParam) == IDOK)
		{
			App->CLSB_Dialogs->Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->CLSB_Dialogs->Canceled = 1;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;

	}
	return FALSE;
}

// *************************************************************************
// *	  		Start_ListData:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Dialogs::Start_ListData()
{
	if (F_ListData_Dlg_Active == 1)
	{
		return 1;
	}


	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	DialogBox(App->hInst, (LPCTSTR)IDD_SCENEDATA, App->MainHwnd, (DLGPROC)ListData_Proc);

	return 1;
}
// *************************************************************************
// *			ListData_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK SB_Dialogs::ListData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		App->CLSB_Dialogs->List_SceneData(hDlg);

		App->CLSB_Dialogs->F_ListData_Dlg_Active = 1;

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			App->CLSB_Dialogs->F_ListData_Dlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->CLSB_Dialogs->F_ListData_Dlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *	  	List_SceneData:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_Dialogs::List_SceneData(HWND hDlg)
{

	char buf[255];

	sprintf(buf, "%s", "3DT File--------------------------------");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s", "File = ", App->CL_World->mCurrent_3DT_File);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s", "Path = ", App->CL_World->mCurrent_3DT_Path);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s", "Path and File = ", App->CL_World->mCurrent_3DT_PathAndFile);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	//--------------------------------
	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	// ----------------------------------------- TXL_FilePath
	sprintf(buf, "%s", "TXL File --------------------------------");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "File = %s", App->CL_World->mCurrent_TXL_FileName);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "Path and File = %s", App->CL_World->mCurrent_TXL_FilePath);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);


	sprintf(buf, "%s%i", "Brush Count = ", App->CL_World->Get_Brush_Count());
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	int Stack_Memory = App->Get_Stack();
	sprintf(buf, "%s%i", "Stack Bytes= ", Stack_Memory);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	float megs = ((float)Stack_Memory / 1024) / 1024;
	sprintf(buf, "%s%f", "Stack megs= ", megs);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	float used = ((float)(2097152 - Stack_Memory) / 1024);
	sprintf(buf, "%s%f", "Stack Used K= ", used);

	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
}

// *************************************************************************
// *	  	List_BoundingBox:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Dialogs::List_BoundingBox(HWND hDlg)
{

	char buf[255];

	sprintf(buf, "%s", "3DT File--------------------------------");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s", "File = ", App->CL_World->mCurrent_3DT_File);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s", "Path = ", App->CL_World->mCurrent_3DT_Path);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s", "Path and File = ", App->CL_World->mCurrent_3DT_PathAndFile);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	//--------------------------------
	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	// ----------------------------------------- TXL_FilePath
	sprintf(buf, "%s", "TXL File --------------------------------");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "File = %s", App->CL_World->mCurrent_TXL_FileName);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "Path and File = %s", App->CL_World->mCurrent_TXL_FilePath);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);


	sprintf(buf, "%s%i", "Brush Count = ", App->CL_World->Get_Brush_Count());
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	int Stack_Memory = App->Get_Stack();
	sprintf(buf, "%s%i", "Stack Bytes= ", Stack_Memory);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	float megs = ((float)Stack_Memory / 1024) / 1024;
	sprintf(buf, "%s%f", "Stack megs= ", megs);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	float used = ((float)(2097152 - Stack_Memory) / 1024);
	sprintf(buf, "%s%f", "Stack Used K= ", used);

	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

}
