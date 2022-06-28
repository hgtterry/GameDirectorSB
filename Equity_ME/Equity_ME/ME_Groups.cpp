#include "stdafx.h"
#include "ME_App.h"
#include "resource.h"
#include "ME_Groups.h"


ME_Groups::ME_Groups()
{
	RightGroups_Hwnd = nullptr;

	Selected_Group = 0;
	RightGroups_Visable = 0;

	Sel_BaseBitmap = nullptr;
	BasePicWidth = 0;
	BasePicHeight = 0;
}


ME_Groups::~ME_Groups()
{
}

// *************************************************************************
// *					Reaet_Class Terry Flanigan						   *
// *************************************************************************
void ME_Groups::Reset_Class(void)
{
	Selected_Group = 0;
	Sel_BaseBitmap = nullptr;
	BasePicWidth = 0;
	BasePicHeight = 0;

	ShowWindow(GetDlgItem(RightGroups_Hwnd, IDC_BASETEXTURE2), 0);
	ShowWindow(GetDlgItem(RightGroups_Hwnd, IDC_BASETEXTURE2), 1);

	SetDlgItemText(RightGroups_Hwnd, IDC_RGGROUPNAME, "Group Name");
	SetDlgItemText(RightGroups_Hwnd, IDC_RGTEXTURENAME, "Texture Name");
}

// *************************************************************************
// *							Start_Groups				  		 	   *
// *************************************************************************
bool ME_Groups::Start_Groups()
{
	RightGroups_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_RIGHTGROUPS, App->MainHwnd, (DLGPROC)Groups_Proc);
	ShowWindow(RightGroups_Hwnd, 1);
	RightGroups_Visable = 1;
	return 1;
}

// *************************************************************************
// *						Groups_Proc Terry Bernie		  			   *
// *************************************************************************
LRESULT CALLBACK ME_Groups::Groups_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_RGGROUPNAME, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_RGTEXTURENAME, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BTCHANGETEXTURE, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTGROUPINFO, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));

		
		SetWindowLong(GetDlgItem(hDlg, IDC_BASETEXTURE2), GWL_WNDPROC, (LONG)ViewerBasePic);
	}

	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_RGGROUPNAME) == (HWND)lParam)
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_RGTEXTURENAME) == (HWND)lParam)
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_CLOSE:
	{
		ShowWindow(App->CL_Groups->RightGroups_Hwnd, 0);
		App->CL_Groups->RightGroups_Visable = 0;
		CheckMenuItem(App->mMenu, ID_WINDOWS_GROUPS, MF_BYCOMMAND | MF_UNCHECKED);
		break;
	}

	
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BTCHANGETEXTURE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTGROUPINFO && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BTCHANGETEXTURE)
		{
			if (App->CL_Model->Model_Loaded == 1)
			{
				App->CL_Panels->Enable_Panels(0);
				App->CL_Textures->ChangeTexture_Model();
				App->CL_Panels->Enable_Panels(1);
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTGROUPINFO)
		{
			if (App->CL_Model->Model_Loaded == 1)
			{
				App->CL_Panels->Enable_Panels(0);
				App->CL_Dialogs->Show_GroupData();
				App->CL_Panels->Enable_Panels(1);
			}
			return TRUE;
		}
	}

	}
	return FALSE;
}

// *************************************************************************
// *						ViewerBasePic Terry Flanigan	  			   *
// *************************************************************************
bool CALLBACK ME_Groups::ViewerBasePic(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_PAINT)
	{
		PAINTSTRUCT	ps;
		HDC			hDC;
		RECT		Rect;

		hDC = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &Rect);
		Rect.left--;
		Rect.bottom--;
		FillRect(hDC, &Rect, (HBRUSH)(RGB(0, 255, 0)));

		if (App->CL_Groups->Sel_BaseBitmap != NULL)
		{
			RECT	Source;
			RECT	Dest;
			HDC		hDC;

			Source.left = 0;
			Source.top = 0;
			Source.bottom = App->CL_Groups->BasePicHeight;
			Source.right = App->CL_Groups->BasePicWidth;

			Dest = Rect;

			hDC = GetDC(hwnd);
			SetStretchBltMode(hDC, HALFTONE);

			App->CL_Groups->RenderTexture_Blit(hDC, App->CL_Groups->Sel_BaseBitmap, &Source, &Dest);
			ReleaseDC(hwnd, hDC);
		}

		EndPaint(hwnd, &ps);
		return 0;
	}
	return 0;// DefWindowProc(hwnd, msg, wParam, lParam);
}

// *************************************************************************
// *					RenderTexture_Blit Terry Bernie		  		   *
// *************************************************************************
bool ME_Groups::RenderTexture_Blit(HDC hDC, HBITMAP Bmp, const RECT *SourceRect, const RECT *DestRect)
{
	HDC		MemDC;
	int		SourceWidth;
	int		SourceHeight;
	int		DestWidth;
	int		DestHeight;

	MemDC = CreateCompatibleDC(hDC);
	if (MemDC == NULL)
		return FALSE;

	if (Bmp)
	{
		SelectObject(MemDC, Bmp);

		SourceWidth = SourceRect->right - SourceRect->left;
		SourceHeight = SourceRect->bottom - SourceRect->top;
		DestWidth = DestRect->right - DestRect->left;
		DestHeight = DestRect->bottom - DestRect->top;
		SetStretchBltMode(hDC, COLORONCOLOR);
		StretchBlt(hDC,
			DestRect->left,
			DestRect->top,
			DestHeight,
			DestHeight,
			MemDC,
			SourceRect->left,
			SourceRect->top,
			SourceWidth,
			SourceHeight,
			SRCCOPY);
	}

	DeleteDC(MemDC);

	return TRUE;
}

// *************************************************************************
// *					Update_Groups  Terry Flanigan		  		 	   *
// *************************************************************************
bool ME_Groups::Update_Groups()
{
	int Index = Selected_Group;

	SetDlgItemText(RightGroups_Hwnd, IDC_RGGROUPNAME, App->CL_Model->Group[Index]->GroupName);
	SetDlgItemText(RightGroups_Hwnd, IDC_RGTEXTURENAME, App->CL_Model->Group[Index]->Text_FileName);

	RightGroups_Visable = 1;
	ShowWindow(RightGroups_Hwnd, 1);
	CheckMenuItem(App->mMenu, ID_WINDOWS_GROUPS, MF_BYCOMMAND | MF_CHECKED);

	Sel_BaseBitmap = App->CL_Model->Group[Index]->Base_Bitmap;

	BITMAP bm;
	GetObject(Sel_BaseBitmap, sizeof(bm), &bm);

	BasePicWidth = bm.bmWidth;
	BasePicHeight = bm.bmHeight;

	ShowWindow(GetDlgItem(RightGroups_Hwnd, IDC_BASETEXTURE2), 0);
	ShowWindow(GetDlgItem(RightGroups_Hwnd, IDC_BASETEXTURE2), 1);

	return 1;
}
