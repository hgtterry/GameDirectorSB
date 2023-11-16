/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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

#include "StdAfx.h"
#include "AB_App.h"
#include "resource.h"
#include "SB_Exporter.h"

SB_Exporter::SB_Exporter(void)
{
	Is_Canceled = 0;

	Selected_Index = 0;

	mJustName[0] = 0;
	mDirectory_Name[0] = 0;
	mFolder_Path[0] = 0;
}

SB_Exporter::~SB_Exporter(void)
{
}

// *************************************************************************
// *	  		Start_Export_Dlg:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Exporter::Start_Export_Dlg()
{
	App->CLSB_Exporter->Is_Canceled = 0;
	DialogBox(App->hInst, (LPCTSTR)IDD_SB_EXPORTOPTIONS, App->MainHwnd, (DLGPROC)Export_Dlg_Proc);
}
// *************************************************************************
// *        Export_Dlg_Proc:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
LRESULT CALLBACK SB_Exporter::Export_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_ST_BANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_FOLDER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_BROWSE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_NAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_CHANGE_NAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CK_SUBFOLDER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_SUBFOLDER_NAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_FOLDER_NAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_ST_FLD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_FN, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LST_FILEFORMATS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		App->CLSB_Exporter->Set_Dialog_Data(hDlg);
		
		HWND Temp = GetDlgItem(hDlg, IDC_CK_SUBFOLDER);
		SendMessage(Temp, BM_SETCHECK, BST_CHECKED, 0);
		App->CLSB_Export_Ogre3D->Add_Sub_Folder = 1;

		App->CLSB_Exporter->List_FIle_Formats(hDlg);

		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_ST_FOLDER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_ST_NAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_ST_SUBFOLDER_NAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_CK_SUBFOLDER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_BANNER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_FLD) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_FN) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
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

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;


		/*if (some_item->idFrom == IDC_BT_FOLDER_NAME && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_CHANGE_NAME && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_BROWSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
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
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_CK_SUBFOLDER)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_SUBFOLDER);
			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				EnableWindow(GetDlgItem(hDlg, IDC_ST_SUBFOLDER_NAME), 1);
				EnableWindow(GetDlgItem(hDlg, IDC_BT_FOLDER_NAME), 1);
				App->CLSB_Export_Ogre3D->Add_Sub_Folder = 1;
				return 1;
			}
			else
			{
				EnableWindow(GetDlgItem(hDlg, IDC_ST_SUBFOLDER_NAME), 0);
				EnableWindow(GetDlgItem(hDlg, IDC_BT_FOLDER_NAME), 0);
				App->CLSB_Export_Ogre3D->Add_Sub_Folder = 0;
				return 1;
			}

			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_CHANGE_NAME)
		{
			/*strcpy(App->CL_Dialogs->btext, "Change File Name");
			strcpy(App->CL_Dialogs->Chr_Text, App->CL_Model->JustName);

			App->CL_Dialogs->Dialog_Text();

			if (App->CL_Dialogs->Is_Canceled == 0)
			{
				strcpy(App->CLSB_Model->JustName, App->CL_Dialogs->Chr_Text);
			}

			SetDlgItemText(hDlg, IDC_ST_NAME, App->CL_Model->JustName);*/

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_FOLDER_NAME)
		{
			/*strcpy(App->CL_Dialogs->btext, "Change Folder Name");
			strcpy(App->CL_Dialogs->Chr_Text, App->CL_Export_Ogre3D->Directory_Name);

			App->CL_Dialogs->Dialog_Text();

			if (App->CL_Dialogs->Is_Canceled == 0)
			{
				strcpy(App->CLSB_Export_Ogre3D->Directory_Name, App->CL_Dialogs->Chr_Text);
			}

			SetDlgItemText(hDlg, IDC_ST_SUBFOLDER_NAME, App->CL_Export_Ogre3D->Directory_Name);*/

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_BROWSE)
		{
			strcpy(App->CLSB_FileIO->BrowserMessage, "Select Folder To Place Ogre Files");
			int Test = App->CLSB_FileIO->StartBrowser("");
			if (Test == 0) { return 1; }

			SetDlgItemText(hDlg, IDC_ST_FOLDER, App->CLSB_FileIO->szSelectedDir);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_LST_FILEFORMATS)
		{
			char buff[256];
			int Index = 0;
			Index = SendDlgItemMessage(hDlg, IDC_LST_FILEFORMATS, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			if (Index == -1)
			{
				return 1;
			}

			if (Index == 0)
			{
				strcpy(App->CLSB_Exporter->mDirectory_Name, App->CLSB_Exporter->mJustName);
				strcat(App->CLSB_Exporter->mDirectory_Name, "_Ogre");

				SetDlgItemText(hDlg, IDC_ST_SUBFOLDER_NAME, App->CLSB_Exporter->mDirectory_Name);
			}

			if (Index == 1)
			{
				strcpy(App->CLSB_Exporter->mDirectory_Name, App->CLSB_Exporter->mJustName);
				strcat(App->CLSB_Exporter->mDirectory_Name, "_Wavefront");

				SetDlgItemText(hDlg, IDC_ST_SUBFOLDER_NAME, App->CLSB_Exporter->mDirectory_Name);
			}

			App->CLSB_Exporter->Selected_Index = Index;


			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			
			if (App->CLSB_Exporter->Selected_Index == 0)
			{
				App->CLSB_Exporter->Ogre3D_Model();
			}

			if (App->CLSB_Exporter->Selected_Index == 1)
			{
				App->CLSB_Exporter->Object_Model();
			}

			App->CLSB_Exporter->Is_Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->CLSB_Exporter->Is_Canceled = 1;

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}

	}

	return FALSE;
}

// *************************************************************************
// *			Set_Dialog_Data:- Terry and Hazel Flanigan 2023 		   *
// *************************************************************************
void SB_Exporter::Set_Dialog_Data(HWND m_hDlg)
{
	// Just Name
	char buf[MAX_PATH];
	strcpy(buf, App->CL_World->mCurrent_3DT_File);
	int Len = strlen(buf);
	buf[Len - 4] = 0;
	strcpy(App->CLSB_Exporter->mJustName, buf);
	SetDlgItemText(m_hDlg, IDC_ST_NAME, buf);

	// Folder Path
	strcpy(App->CLSB_Exporter->mFolder_Path, App->CLSB_FileIO->szSelectedDir);
	SetDlgItemText(m_hDlg, IDC_ST_FOLDER, App->CLSB_FileIO->szSelectedDir);

	// Directory Name
	strcpy(App->CLSB_Exporter->mDirectory_Name, App->CLSB_Exporter->mJustName);
	strcat(App->CLSB_Exporter->mDirectory_Name, "_Ogre");
	SetDlgItemText(m_hDlg, IDC_ST_SUBFOLDER_NAME, App->CLSB_Exporter->mDirectory_Name);

}

// *************************************************************************
// *			List_FIle_Formats:- Terry and Hazel Flanigan 2023 		   *
// *************************************************************************
void SB_Exporter::List_FIle_Formats(HWND m_hDlg)
{
	char buf[100];

	sprintf(buf,"%s", "Ogre3D .mesh");
	SendDlgItemMessage(m_hDlg, IDC_LST_FILEFORMATS, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "Wavefront Object .obj");
	SendDlgItemMessage(m_hDlg, IDC_LST_FILEFORMATS, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
}

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------
 
 
// *************************************************************************
// *			Ogre3D_Model:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Exporter::Ogre3D_Model(void)
{

	App->CLSB_Mesh_Mgr->WE_Build_Brush_List(0);
	App->CLSB_Mesh_Mgr->WE_Convert_All_Texture_Groups();

	App->CLSB_Export_Ogre3D->Export_AssimpToOgre();

	App->Say("Ogre3D Mesh file Created successfully");
}

// *************************************************************************
// *					Object_Model Terry Bernie						   *
// *************************************************************************
void SB_Exporter::Object_Model(void)
{
	App->CLSB_Mesh_Mgr->WE_Build_Brush_List(0);
	App->CLSB_Mesh_Mgr->WE_Convert_All_Texture_Groups();

	bool test = App->CLSB_Export_Object->Create_ObjectFile();

	if (test == 1)
	{
		App->Say("Wavefront Object file Created successfully");
	}
}
