// A_Dialogs.cpp: implementation of the A_Dialogs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AB_App.h"
#include "resource.h"
#include "A_Dialogs.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

A_Dialogs::A_Dialogs()
{

}

A_Dialogs::~A_Dialogs()
{

}

// *************************************************************************
// *	  				Show_ListData Terry Flanigan					   *
// *************************************************************************
bool A_Dialogs::Show_ListData()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_SCENEDATA, App->MainHwnd, (DLGPROC)GroupData_Proc);

	return 1;
}
// *************************************************************************
// *        		GroupData_Proc  Terry Flanigan						   *
// *************************************************************************
LRESULT CALLBACK A_Dialogs::GroupData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		App->CL_Dialogs->List_SceneData(hDlg);

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
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *	  				List_SceneData Terry Flanigan					   *
// *************************************************************************
void A_Dialogs::List_SceneData(HWND hDlg)
{
	
	char buf[255];

	sprintf(buf, "%s", "Scene Info");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s","Last Saved EBR Path = ",App->CL_FileIO->PathFileName);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s", "File = ", App->CL_Scene->Current_3DT_File);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s", "Current 3DT Path = ", App->CL_Scene->Current_3DT_Path);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	// ----------------------------------------- Just 3DT Path
	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "Just 3DT Path");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s",App->CL_Scene->Current_3DT_Just_Path);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);


//	sprintf(buf, "%s%i", "Faces = ", App->CL_Model->Group[Index]->GroupFaceCount);
//	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

//	sprintf(buf, "%s", "    ");
//	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

//	sprintf(buf, "%s%s", "Material Name = ", App->CL_Model->Group[Index]->MaterialName);
//	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

//	sprintf(buf, "%s%s", "Texture Name = ", App->CL_Model->Group[Index]->Text_FileName);
//	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

//	sprintf(buf, "%s%s", "Texture Name = ", App->CL_Model->Group[Index]->Equity_Text_FileName);
//	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

//	sprintf(buf, "%s%s", "Texture Path = ", App->CL_Model->Group[Index]->Texture_PathFileName);
//	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

//	sprintf(buf, "%s%i", "Bit Depth = ", App->CL_Model->Group[Index]->Depth);
//	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

//	sprintf(buf, "%s%i x %i", "Dimensions = ", App->CL_Model->Group[Index]->Width, App->CL_Model->Group[Index]->Height);
//	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

//	sprintf(buf, "%s", "    ");
//	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
}
