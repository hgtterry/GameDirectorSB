#include "stdafx.h"
#include "ME_App.h"
#include "resource.h"
#include "ME_Dialogs.h"


ME_Dialogs::ME_Dialogs()
{
}


ME_Dialogs::~ME_Dialogs()
{
}

// *************************************************************************
// *	  				Show_GroupData Terry Flanigan					   *
// *************************************************************************
bool ME_Dialogs::Show_GroupData()
{
	/*if (Active_Dlg_Float == 1)
	{
		return 1;
	}

	Active_Dlg_Float = 1;*/

	DialogBox(App->hInst, (LPCTSTR)IDD_GROUPDATA, App->Fdlg, (DLGPROC)GroupData_Proc);

	return 1;
}
// *************************************************************************
// *        		GroupData_Proc  Terry	Bernie						   *
// *************************************************************************
LRESULT CALLBACK ME_Dialogs::GroupData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		char buf[255];
		int Index = App->CL_Groups->Selected_Group;

		sprintf(buf, "%s", "Group Info");
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s", "    ");
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		//----------------------- 
		sprintf(buf, "%s%s", "Group Name = ", App->CL_Model->Group[Index]->GroupName);
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s%i", "Vertices = ", App->CL_Model->Group[Index]->GroupVertCount);
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s%i", "Faces = ", App->CL_Model->Group[Index]->GroupFaceCount);
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s", "    ");
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s%s", "Texture Name = ", App->CL_Model->Group[Index]->Text_FileName);
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s%s", "Texture Path = ", App->CL_Model->Group[Index]->Texture_PathFileName);
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

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
