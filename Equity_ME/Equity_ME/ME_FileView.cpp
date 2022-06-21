#include "stdafx.h"
#include "ME_App.h"
#include "resource.h"
#include "ME_FileView.h"


ME_FileView::ME_FileView()
{
}


ME_FileView::~ME_FileView()
{
}

// *************************************************************************
//							Start_FileView Terry Flanigan					*
// *************************************************************************
void ME_FileView::Start_FileView(void)
{
	App->ListPanel = CreateDialog(App->hInst, (LPCTSTR)IDD_LIST, App->MainHwnd, (DLGPROC)ListPanel_Proc);
}

// *************************************************************************
// *					ListPanel_Proc_Proc Terry Flanigan				   *
// *************************************************************************
LRESULT CALLBACK ME_FileView::ListPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG:
	{
		//App->SBC_FileView->FileView_Active = 1;
		ShowWindow(hDlg, 1);

		//SendDlgItemMessage(hDlg, IDC_TREE1, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		//CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_CHECKED);
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		//return (LONG)App->DialogBackGround;
	}

	case WM_SIZE:
	{
		//App->Cl_Panels->Resize_FileView();
	}break;

	case WM_NOTIFY:
	{
		/*LPNMHDR nmhdr = (LPNMHDR)lParam;
		if (nmhdr->idFrom == IDC_TREE1)
		{
			switch (nmhdr->code)
			{

			case TVN_SELCHANGED:
			{
				App->SBC_FileView->Get_Selection((LPNMHDR)lParam);
			}
			}
		}*/

		/*LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_ENVIONMENT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_LEVELS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_FileView->Level_But_Active);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_STOCK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_FileView->Stock_But_Active);
			return CDRF_DODEFAULT;
		}*/

		return 1;
	}
	case WM_COMMAND:
	{
		//if (LOWORD(wParam) == IDC_LEVELS)
		//{
		//	App->SBC_FileView->Level_But_Active = 1;
		//	App->SBC_FileView->Stock_But_Active = 0;
		//	App->RedrawWindow_Dlg(hDlg);

		//	ShowWindow(GetDlgItem(App->ListPanel, IDC_TREE1), 1);

		//	//App->GDCL_FileView->HideRightPanes();
		//	//ShowWindow(App->GD_Properties_Hwnd, 1);*/

		//	return TRUE;
		//}

		break;
	}

	case WM_CLOSE:
	{
		//App->SBC_FileView->FileView_Active = 0;
		ShowWindow(App->ListPanel, 0);

		//HMENU mMenu = GetMenu(App->MainHwnd);
		//CheckMenuItem(mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_UNCHECKED);

		break;
	}

	break;
	}
	return FALSE;
}
