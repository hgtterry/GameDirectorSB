// A_Dialogs.cpp: implementation of the A_Dialogs class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AB_App.h"
#include "resource.h"
#include "A_Dialogs.h"

#include "FUSIONView.h"
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
	DialogBox(App->hInst, (LPCTSTR)IDD_SCENEDATA, App->MainHwnd, (DLGPROC)ListData_Proc);

	return 1;
}
// *************************************************************************
// *        		ListData_Proc  Terry Flanigan						   *
// *************************************************************************
LRESULT CALLBACK A_Dialogs::ListData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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


	// ----------------------------------------- TXL_FilePath
	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "TXL File --------------------------------");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "File Name And Path:- %s",App->CL_Scene->Current_TXL_FilePath);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "Just File Name:- %s",App->CL_Scene->Current_TXL_FileName);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

}

// *************************************************************************
// *	  				Start_FrontPanel Terry Flanigan					   *
// *************************************************************************
void A_Dialogs::Start_FrontPanel()
{
	CreateDialog(App->hInst, (LPCTSTR)IDD_EQ_FRONTPANEL, App->MainHwnd, (DLGPROC)FrontPanel_Proc);
}

// *************************************************************************
// *        		FrontPanel_Proc  Terry Flanigan						   *
// *************************************************************************
LRESULT CALLBACK A_Dialogs::FrontPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		//SendDlgItemMessage(hDlg, IDC_BTSETVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
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
		{
			// Textured
			if (LOWORD(wParam) == IDC_BTSETVIEW)
			{
				App->CL_Render_App->Render3D_Mode(ID_VIEW_TEXTUREVIEW);
				return TRUE;
			}

			// Wired Framed
			if (LOWORD(wParam) == IDC_BTSELECTALL)
			{
				CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

				pDoc->SelectAll() ;
				pDoc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BTDESELECTALL)
			{
				CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

				pDoc->ResetAllSelections() ;
				pDoc->UpdateSelected();
				pDoc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BTWIRE)
			{
				App->CL_Render_App->Render3D_Mode(ID_VIEW_3DWIREFRAME);
				return TRUE;
			}

			// -----------------------------------------------------------------
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
	}
	return FALSE;
}
