/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "EB_Options.h"


EB_Options::EB_Options()
{
	Main_Window_Hwnd =	nullptr;
	FileView_Hwnd =		nullptr;
}


EB_Options::~EB_Options()
{
}

// *************************************************************************
// *	  				 Start_Options_Dialog	Terry Bernie			   *
// *************************************************************************
bool EB_Options::Start_Options_Dialog()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_EQUITYOPTIONS, App->SBC_Equity->MainWindow_Hwnd, (DLGPROC)Options_Proc);

	return 1;
}

// *************************************************************************
// *					Options_Proc	Terry Bernie  					   *
// *************************************************************************
LRESULT CALLBACK EB_Options::Options_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		App->EBC_Options->Main_Window_Hwnd = hDlg;
		App->EBC_Options->FileView_Hwnd = GetDlgItem(hDlg, IDC_OPTIONSTREE1);

		App->EBC_Options->AddRootFolder();

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_TITLENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
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
		if (nmhdr->idFrom == IDC_OPTIONSTREE1)
		{
			switch (nmhdr->code)
			{

			case TVN_SELCHANGED:
			{
				App->EBC_Options->Get_Selection((LPNMHDR)lParam);
			}
			}
		}

		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
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

	case WM_COMMAND:
	{
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
	}

	break;

	}
	return FALSE;
}

// *************************************************************************
// *			AddRootFolder Terry Bernie			 				 	   *
// *************************************************************************
void EB_Options::AddRootFolder(void)
{
	tvinsert.hParent = Root;			// top most level no need handle
	tvinsert.hInsertAfter = TVI_LAST; // work as root level
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "File";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_File = (HTREEITEM)SendDlgItemMessage(Main_Window_Hwnd, IDC_OPTIONSTREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = FV_File;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Quick Load";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	SendDlgItemMessage(Main_Window_Hwnd, IDC_OPTIONSTREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
}

// *************************************************************************
// *					Get_Selection Terry Bernie					 	   *
// *************************************************************************
void EB_Options::Get_Selection(LPNMHDR lParam)
{

	strcpy(FileView_Folder, "");
	strcpy(FileView_File, "");

	int Index = 0;
	HWND Temp = GetDlgItem(Main_Window_Hwnd, IDC_OPTIONSTREE1);
	HTREEITEM i = TreeView_GetSelection(Temp);

	TVITEM item;
	item.hItem = i;
	item.pszText = FileView_Folder;
	item.cchTextMax = sizeof(FileView_Folder);
	item.mask = TVIF_TEXT | TVIF_PARAM;
	TreeView_GetItem(((LPNMHDR)lParam)->hwndFrom, &item);
	Index = item.lParam;

	HTREEITEM p = TreeView_GetParent(Temp, i);

	TVITEM item1;
	item1.hItem = p;
	item1.pszText = FileView_File;
	item1.cchTextMax = sizeof(FileView_File);
	item1.mask = TVIF_TEXT;
	TreeView_GetItem(((LPNMHDR)lParam)->hwndFrom, &item1);

	//--------------------------------------------------------------------------

	if (!strcmp(FileView_Folder, "Quick Load")) // Folder
	{
		Start_QuickLoad_Dialog();
		return;
	}

	if (!strcmp(FileView_File, "Quick Load"))
	{
		//App->Say("File");
		return;
	}

	return;
}

// *************************************************************************
// *	  				 Start_QuickLoad_Dialog	Terry Bernie			   *
// *************************************************************************
bool EB_Options::Start_QuickLoad_Dialog()
{
	CreateDialog(App->hInst, (LPCTSTR)IDD_EQLOPTIONS, App->EBC_Options->Main_Window_Hwnd, (DLGPROC)QuickLoad_Proc);

	return 1;
}

// *************************************************************************
// *					QuickLoad_Proc	Terry Bernie  					   *
// *************************************************************************
LRESULT CALLBACK EB_Options::QuickLoad_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_STTAGQLF, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STQLBOX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		return TRUE;
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{

		if (GetDlgItem(hDlg, IDC_STTAGQLF) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STQLBOX) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}


		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
	
		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
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

	case WM_COMMAND:
	{
		/*if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}*/
	}

	break;

	}
	return FALSE;
}

