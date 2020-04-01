#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "VM_TopBar.h"


VM_TopBar::VM_TopBar()
{
	TabsHwnd =	nullptr;
	TB_1 =		nullptr;
}


VM_TopBar::~VM_TopBar()
{
}

// *************************************************************************
// *	  					Start_TopBar  	Terry						   *
// *************************************************************************
bool VM_TopBar::Start_TopBar()
{
	DialogBox(App->hInst,(LPCTSTR)IDD_TOPBAR,App->Fdlg,(DLGPROC)TopBar_Proc);
	return 1;
}
// *************************************************************************
// *						TopBar_Proc Terry							   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::TopBar_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->CL_Vm_TopBar->TabsHwnd = CreateWindow(WC_TABCONTROL, "",
			WS_CHILD |
			WS_VISIBLE |
			ES_LEFT |
			TCS_MULTILINE |
			TCS_RAGGEDRIGHT,

			4, 4, 900, 200, hDlg, NULL, App->hInst, NULL);

		TabCtrl_SetItemSize(App->CL_Vm_TopBar->TabsHwnd, 54, 24);

		TC_ITEM item;
		ZeroMemory(&item, sizeof(item));
		item.mask = TCIF_TEXT;
		item.pszText = "Startup";
		TabCtrl_InsertItem(App->CL_Vm_TopBar->TabsHwnd, 0, &item);
		item.pszText = "Folders";
		TabCtrl_InsertItem(App->CL_Vm_TopBar->TabsHwnd, 1, &item);
		item.pszText = "Texture Files";
		TabCtrl_InsertItem(App->CL_Vm_TopBar->TabsHwnd, 2, &item);

		TabCtrl_SetCurFocus(App->CL_Vm_TopBar->TabsHwnd, 0);

		App->CL_Vm_TopBar->Start_TB1();
		

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{

		/*if(GetDlgItem(hDlg,IDC_BANNER) == (HWND)lParam)
		{
		SetBkColor((HDC) wParam, RGB(0, 255, 0));
		SetTextColor((HDC) wParam, RGB(0,0,255));
		SetBkMode((HDC) wParam, TRANSPARENT);
		return (UINT) App->AppBackground;
		}*/
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{

		LPNMHDR nmhdr = (LPNMHDR)lParam;
		switch (nmhdr->code)
		{
		case TCN_SELCHANGE:
		{
			int num = TabCtrl_GetCurSel(nmhdr->hwndFrom);
			switch (num)
			{
				//--------------------------------- Textures
			case 0:

				App->Say("1");
				/*ShowWindow(FoldersHWND, SW_HIDE);
				ShowWindow(TexturesHWND, SW_HIDE);
				ShowWindow(StartHWND, SW_SHOW);*/

				break;
				//--------------------------------- Bones
			case 1:

				App->Say("2");
				/*ShowWindow(StartHWND, SW_HIDE);
				ShowWindow(TexturesHWND, SW_HIDE);
				ShowWindow(FoldersHWND, SW_SHOW);*/

				break;
				//--------------------------------- Mesh
			case 2:

				App->Say("3");
				/*ShowWindow(FoldersHWND, SW_HIDE);
				ShowWindow(StartHWND, SW_HIDE);
				ShowWindow(TexturesHWND, SW_SHOW);*/
				break;


			}
		}

		}
		return 0;
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
// *						Start_TB1 Terry Berine						   *
// *************************************************************************
void VM_TopBar::Start_TB1(void)
{
	TB_1 = CreateDialog(App->hInst, (LPCTSTR)IDD_TB1, App->CL_Vm_TopBar->TabsHwnd, (DLGPROC)NULL);// App->Cl_ToolBar->TB1_Proc);
	//Init_Bmps();
	//TB_1_Active = 1;
}
