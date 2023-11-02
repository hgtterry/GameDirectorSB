/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "AB_App.h"
#include "SB_Mesh_Mgr.h"

SB_Mesh_Mgr::SB_Mesh_Mgr(void)
{
}

SB_Mesh_Mgr::~SB_Mesh_Mgr(void)
{
}

// *************************************************************************
// *	  		Start_Brush_Viewer:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Mesh_Mgr::Start_Brush_Viewer()
{
	App->Get_Current_Document();

	CreateDialog(App->hInst, (LPCTSTR)IDD_SB_BRUSH_VIEWER, App->Equity_Dlg_hWnd, (DLGPROC)Brush_Viewer_Proc);
	Debug
}

// *************************************************************************
// *			Brush_Viewer_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK SB_Mesh_Mgr::Brush_Viewer_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_LISTBRUSHES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_LISTDATA, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BTJUSTBRUSH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LISTBRUSHES, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		char buf[MAX_PATH];
		int Count = 0;
		while (Count < App->CLSB_Model->BrushCount)
		{
			SendDlgItemMessage(hDlg, IDC_LISTBRUSHES, LB_ADDSTRING, (WPARAM)0, (LPARAM)itoa(Count, buf, 10));
			Count++;
		}

		App->CLSB_Mesh_Mgr->UpdateBrushData(hDlg, 0);

		App->CLSB_Ogre->RenderListener->Render_Just_Brush = 0;

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

		if (some_item->idFrom == IDC_BTJUSTBRUSH && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_Ogre->RenderListener->Render_Just_Brush);
			return CDRF_DODEFAULT;
		}

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
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BT_LOOKAT)
		{
			App->CLSB_Model->Set_BondingBox_Selected_Brush(App->CLSB_Ogre->RenderListener->Selected_Brush_Index);
			App->CLSB_Ogre->mCamera->lookAt(Ogre::Vector3(App->CLSB_Model->Sel_Brush_Centre.x, App->CLSB_Model->Sel_Brush_Centre.y, App->CLSB_Model->Sel_Brush_Centre.z));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTJUSTBRUSH)
		{
			if (App->CLSB_Ogre->RenderListener->Render_Just_Brush == 1)
			{
				App->CLSB_Ogre->RenderListener->Render_Just_Brush = 0;
			}
			else
			{
				App->CLSB_Ogre->RenderListener->Render_Just_Brush = 1;
			}

			App->CLSB_Ogre->RenderFrame();

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_LISTBRUSHES)
		{
			char buff[256];
			int Index = 0;
			Index = SendDlgItemMessage(hDlg, IDC_LISTBRUSHES, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			if (Index == -1)
			{
				return 1;
			}

			App->CLSB_Ogre->RenderListener->Selected_Brush_Index = Index;
			App->CLSB_Ogre->RenderListener->Selected_Group_Index = App->CLSB_Model->B_Brush[Index]->Group_Index;

			SetDlgItemText(hDlg, IDC_STBRUSHINDEX, (LPCTSTR)itoa(Index, buff, 10));

			App->CLSB_Mesh_Mgr->UpdateBrushData(hDlg, Index);

			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			//App->CLSB_Dialogs->F_ListData_Dlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			//App->CLSB_Dialogs->F_ListData_Dlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}

	return FALSE;
}

// *************************************************************************
// *			UpdateBrushData:- Terry and Hazel Flanigan 2023		 	   *
// *************************************************************************
void SB_Mesh_Mgr::UpdateBrushData(HWND hDlg, int Index)
{
	SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

	char buf[MAX_PATH];

	sprintf(buf, "Group Index %i %s", App->CLSB_Model->B_Brush[Index]->Group_Index, App->CLSB_Model->B_Brush[Index]->Brush_Name);
	SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "Faces %i", App->CLSB_Model->B_Brush[Index]->Face_Count);
	SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "Vertices %i", App->CLSB_Model->B_Brush[Index]->Vertice_Count);
	SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	int Count = 0;

	while (Count < App->CLSB_Model->B_Brush[Index]->Face_Count)
	{
		sprintf(buf, "Text_ID %i", App->CLSB_Model->B_Brush[Index]->TextID_Data[Count].ID);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
		Count++;
	}

	App->CLSB_Model->Set_BondingBox_Selected_Brush(Index);
}
