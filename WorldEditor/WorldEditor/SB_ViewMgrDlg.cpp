#include "stdafx.h"
#include "SB_ViewMgrDlg.h"

#include "FUSIONView.h"
#include "FUSIONDoc.h"
#include "ChildFrm.h"

SB_ViewMgrDlg::SB_ViewMgrDlg(void)
{
}

SB_ViewMgrDlg::~SB_ViewMgrDlg(void)
{
}


// *************************************************************************
// *	  	Start_View_MgrDlg:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_ViewMgrDlg::Start_View_MgrDlg()
{
	CreateDialog(App->hInst, (LPCTSTR)IDD_SB_VIEWMANAGER, App->MainHwnd, (DLGPROC)View_MgrDlg_Proc);
}

// *************************************************************************
// *		  View_MgrDlg_Proc:- Terry and Hazel Flanigan 2023	  		   *
// *************************************************************************
LRESULT CALLBACK SB_ViewMgrDlg::View_MgrDlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		
		SendDlgItemMessage(hDlg, IDC_BT_UPPERLEFT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_UPPERRIGHT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_LOWERLEFT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_LOWERRIGHT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_RESTORE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BT_PREVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_BANNER) == (HWND)lParam)
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
		}*/

		return FALSE;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_UPPERLEFT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_UPPERRIGHT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_LOWERLEFT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_LOWERRIGHT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_RESTORE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_PREVIEW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BT_UPPERLEFT)
		{
			App->CLSB_ViewMgrDlg->MaximizeUpperLeftPane();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_UPPERRIGHT)
		{
			App->CLSB_ViewMgrDlg->MaximizeUpperRightPane();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_LOWERLEFT)
		{
			App->CLSB_ViewMgrDlg->MaximizeLowerLeftPane();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_LOWERRIGHT)
		{
			App->CLSB_ViewMgrDlg->MaximizeLowerRightPane();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_RESTORE)
		{
			App->CLSB_ViewMgrDlg->RestoreAllPanes();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_PREVIEW)
		{
			App->CLSB_Equity->Do_Preview_All();
			return TRUE;
		}
		
		if (LOWORD(wParam) == IDOK)
		{
			//App->CLSB_Dialogs->Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			//App->CLSB_Dialogs->Canceled = 1;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;

	}
	return FALSE;
}

// *************************************************************************
// *		MaximizeUpperLeftPane:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_ViewMgrDlg::MaximizeUpperLeftPane()
{
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMainFrame)
	{
		CChildFrame* pChildFrame = NULL;

		pChildFrame = (CChildFrame*)pMainFrame->MDIGetActive();
		if (pChildFrame)
		{
			ASSERT(pChildFrame->IsKindOf(RUNTIME_CLASS(CChildFrame)));

			pChildFrame->MaximizeUpperLeftPane();
		}
	}
}

// *************************************************************************
// *		MaximizeUpperRightPane:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_ViewMgrDlg::MaximizeUpperRightPane()
{
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMainFrame)
	{
		CChildFrame* pChildFrame = NULL;

		pChildFrame = (CChildFrame*)pMainFrame->MDIGetActive();
		if (pChildFrame)
		{
			ASSERT(pChildFrame->IsKindOf(RUNTIME_CLASS(CChildFrame)));

			pChildFrame->MaximizeUpperRightPane();
		}
	}
}

// *************************************************************************
// *		MaximizeLowerLeftPane:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_ViewMgrDlg::MaximizeLowerLeftPane()
{
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMainFrame)
	{
		CChildFrame* pChildFrame = NULL;

		pChildFrame = (CChildFrame*)pMainFrame->MDIGetActive();
		if (pChildFrame)
		{
			ASSERT(pChildFrame->IsKindOf(RUNTIME_CLASS(CChildFrame)));

			pChildFrame->MaximizeLowerLeftPane();
		}
	}
}

// *************************************************************************
// *		MaximizeLowerRightPane:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_ViewMgrDlg::MaximizeLowerRightPane()
{

	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMainFrame)
	{
		CChildFrame* pChildFrame = NULL;

		pChildFrame = (CChildFrame*)pMainFrame->MDIGetActive();
		if (pChildFrame)
		{
			ASSERT(pChildFrame->IsKindOf(RUNTIME_CLASS(CChildFrame)));

			pChildFrame->MaximizeLowerRightPane();
		}
	}

}

// *************************************************************************
// *			RestoreAllPanes:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_ViewMgrDlg::RestoreAllPanes()
{
	CMainFrame* pMainFrame = NULL;
	pMainFrame = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (pMainFrame)
	{
		CChildFrame* pChildFrame = NULL;

		pChildFrame = (CChildFrame*)pMainFrame->MDIGetActive();
		if (pChildFrame)
		{
			ASSERT(pChildFrame->IsKindOf(RUNTIME_CLASS(CChildFrame)));

			pChildFrame->RestoreAllPanes();
		}
	}
}
