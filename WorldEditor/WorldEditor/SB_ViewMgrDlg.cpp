#include "stdafx.h"
#include "SB_ViewMgrDlg.h"

#include "FUSIONView.h"
#include "FUSIONDoc.h"
#include "ChildFrm.h"

SB_ViewMgrDlg::SB_ViewMgrDlg(void)
{
	TopLeft_Flag = 0;
	TopRight_Flag = 0;
	BottomLeft_Flag = 0;
	BottomRight_Flag = 0;

	MgrDlg_hWnd = nullptr;
	View_MgrDlg_Active = 0;

	LinkViews_Flag = 1;

}

SB_ViewMgrDlg::~SB_ViewMgrDlg(void)
{
}


// *************************************************************************
// *	  	Start_View_MgrDlg:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_ViewMgrDlg::Start_View_MgrDlg()
{
	if (View_MgrDlg_Active == 0)
	{
		MgrDlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_VIEWMANAGER, App->MainHwnd, (DLGPROC)View_MgrDlg_Proc);
		View_MgrDlg_Active = 1;

		App->CLSB_TopTabs->Update_Dlg_Controls();
	}
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
		SendDlgItemMessage(hDlg, IDC_BT_LINKVIEWS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BT_SELECTED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_BT_PREVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_VIEWUPDATE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_EXPORT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		if (Prefs_GetLinkViewports(((CFusionApp*)AfxGetApp())->GetPreferencesNormal()))
		{
			App->CLSB_ViewMgrDlg->LinkViews_Flag = 1;
		}
		else
		{
			App->CLSB_ViewMgrDlg->LinkViews_Flag = 0;
		}

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_UPPERLEFT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_ViewMgrDlg->TopLeft_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_UPPERRIGHT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_ViewMgrDlg->TopRight_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_LOWERLEFT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_ViewMgrDlg->BottomLeft_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_LOWERRIGHT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_ViewMgrDlg->BottomRight_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_RESTORE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_LINKVIEWS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_ViewMgrDlg->LinkViews_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_PREVIEW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			bool test = IsWindowEnabled(GetDlgItem(hDlg, IDC_BT_PREVIEW));
			if (test == 0)
			{
				App->Custom_Button_Greyed(item);
			}
			else
			{
				App->Custom_Button_Normal(item);
			}

			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_SELECTED && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			bool test = IsWindowEnabled(GetDlgItem(hDlg, IDC_BT_SELECTED));
			if (test == 0)
			{
				App->Custom_Button_Greyed(item);
			}
			else
			{
				App->Custom_Button_Normal(item);
			}

			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_VIEWUPDATE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			bool test = IsWindowEnabled(GetDlgItem(hDlg, IDC_BT_VIEWUPDATE));
			if (test == 0)
			{
				App->Custom_Button_Greyed(item);
			}
			else
			{
				App->Custom_Button_Normal(item);
			}

			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_EXPORT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			bool test = IsWindowEnabled(GetDlgItem(hDlg, IDC_BT_EXPORT));
			if (test == 0)
			{
				App->Custom_Button_Greyed(item);
			}
			else
			{
				App->Custom_Button_Normal(item);
			}

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
			App->CLSB_ViewMgrDlg->Reset_Flags();
			App->CLSB_ViewMgrDlg->TopLeft_Flag = 1;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_UPPERRIGHT)
		{
			App->CLSB_ViewMgrDlg->MaximizeUpperRightPane();
			App->CLSB_ViewMgrDlg->Reset_Flags();
			App->CLSB_ViewMgrDlg->TopRight_Flag = 1;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_LOWERLEFT)
		{
			App->CLSB_ViewMgrDlg->MaximizeLowerLeftPane();
			App->CLSB_ViewMgrDlg->Reset_Flags();
			App->CLSB_ViewMgrDlg->BottomLeft_Flag = 1;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_LOWERRIGHT)
		{
			App->CLSB_ViewMgrDlg->MaximizeLowerRightPane();
			App->CLSB_ViewMgrDlg->Reset_Flags();
			App->CLSB_ViewMgrDlg->BottomRight_Flag = 1;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_RESTORE)
		{
			App->CLSB_ViewMgrDlg->RestoreAllPanes();
			App->CLSB_ViewMgrDlg->Reset_Flags();
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_LINKVIEWS)
		{
			if (App->CLSB_ViewMgrDlg->LinkViews_Flag == 1)
			{
				App->CLSB_ViewMgrDlg->LinkViews_Flag = 0;
				App->CLSB_Doc->OnLinkviewports();
			}
			else
			{
				App->CLSB_ViewMgrDlg->LinkViews_Flag = 1;
				App->CLSB_Doc->OnLinkviewports();
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_SELECTED)
		{
			App->CLSB_Equity->Do_Preview_Selected();
			return TRUE;
		}


		if (LOWORD(wParam) == IDC_BT_PREVIEW)
		{
			App->CLSB_Equity->Do_Preview_All();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_VIEWUPDATE)
		{
			App->CLSB_Scene->Update_Scene();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_EXPORT)
		{
			App->Enable_Dialogs(0);
			App->CLSB_Exporter->Start_Export_Dlg();

			if (App->CLSB_Exporter->Is_Canceled == 1)
			{
				App->Enable_Dialogs(1);
				App->Say("Canceled");
			}

			App->CLSB_Exporter->Do_Export();

			App->Enable_Dialogs(1);

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDOK)
		{
			App->CLSB_ViewMgrDlg->View_MgrDlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->CLSB_ViewMgrDlg->View_MgrDlg_Active = 0;
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

// *************************************************************************
// *		  	Reset_Flags:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_ViewMgrDlg::Reset_Flags()
{
	TopLeft_Flag = 0;
	TopRight_Flag = 0;
	BottomLeft_Flag = 0;
	BottomRight_Flag = 0;
}
