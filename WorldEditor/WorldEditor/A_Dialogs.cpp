/*
Copyright (c) 2023 Equity_ME World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "resource.h"
#include "A_Dialogs.h"

#include "FUSIONView.h"
#include "FUSIONDoc.h"


A_Dialogs::A_Dialogs()
{
	F_Textured = 0;
	F_WireFrame = 1;
	
	Message_Text_Header[0] = 0;
	Message_Text_Message[0] = 0;
	Current_Txl_File[0] = 0;

	CenterOfSelection.X = 0;
	CenterOfSelection.Y = 0;
	CenterOfSelection.Z = 0;

}

A_Dialogs::~A_Dialogs()
{

}

// *************************************************************************
// *	  	Get_Current_Document:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_Dialogs::Get_Current_Document()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();
}

// *************************************************************************
// *	  		Message:- Terry and Hazel Flanigan 2023					   *
// *************************************************************************
void A_Dialogs::Message(char* pString, char* pString2)
{
	strcpy(Message_Text_Header, pString);
	strcpy(Message_Text_Message, pString2);

	if (App->CLSB_Equity->EquitySB_Dialog_Visible == 0)
	{
		DialogBox(App->hInst, (LPCTSTR)IDD_MESSAGE, App->MainHwnd, (DLGPROC)Message_Proc);
	}
	else
	{
		DialogBox(App->hInst, (LPCTSTR)IDD_MESSAGE, App->Equity_Dlg_hWnd, (DLGPROC)Message_Proc);
	}
}
// *************************************************************************
// *        	Message_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_Dialogs::Message_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_BANNER, WM_SETFONT, (WPARAM)App->Font_Banner, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTEXT, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STMESSAGE, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_STTEXT, App->CL_Dialogs->Message_Text_Header);
		SetDlgItemText(hDlg, IDC_STMESSAGE, App->CL_Dialogs->Message_Text_Message);

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_BANNER) == (HWND)lParam)
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
		}

		if (GetDlgItem(hDlg, IDC_STMESSAGE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
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
// *	  		Start_Properties:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_Dialogs::Start_Properties()
{
	App->Get_Current_Document();

	Current_Txl_File[0] = 0;

	DialogBox(App->hInst, (LPCTSTR)IDD_LEVELOPTIONS_GD, App->MainHwnd, (DLGPROC)Properties_Proc);

}
// *************************************************************************
// *        	Properties_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_Dialogs::Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_STTXL, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EDITTXL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BROWSETXL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		
		SetDlgItemText(hDlg, IDC_EDITTXL, Level_GetWadPath(App->CLSB_Doc->pLevel));

		strcpy(App->CL_Dialogs->Current_Txl_File,Level_GetWadPath(App->CLSB_Doc->pLevel));

		return TRUE;

	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STTXL) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
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

		if (some_item->idFrom == IDC_BROWSETXL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BROWSETXL)
		{
			int test = App->CLSB_FileIO->Open_File_Model(App->MainHwnd,"Texture Libary   *.txl\0*.txl\0", "Texure Editor", NULL);
			if (test == 0)
			{
				return 1;
			}

			SetDlgItemText(hDlg, IDC_EDITTXL,App->CLSB_FileIO->PathFileName);

			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			char buff[MAX_PATH];
			GetDlgItemText(hDlg,IDC_EDITTXL,buff,MAX_PATH);


			//int Result = 0;
			//Result = strcmp(buff, App->CL_Dialogs->Current_Txl_File);
			//if (Result == 0)
			//{
			//	//App->Say("The Same");
			//}
			//else
			{
				Level_SetWadPath(App->CLSB_Doc->pLevel,buff);

				App->CL_World->Set_Current_TxlPath();

				App->m_pDoc->UpdateAfterWadChange();

			}

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
// *	  	Start_FrontPanel:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_Dialogs::Start_FrontPanel()
{
	CreateDialog(App->hInst, (LPCTSTR)IDD_EQ_FRONTPANEL, App->MainHwnd, (DLGPROC)FrontPanel_Proc);
}

// *************************************************************************
// *        FrontPanel_Proc:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
LRESULT CALLBACK A_Dialogs::FrontPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BTSETVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTSELECTALL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTDESELECTALL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTWIRE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTTESTDLG, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTBUILDVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

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
			if (LOWORD(wParam) == IDC_BTWORLDINFO)
			{
				App->CLSB_Dialogs->Start_ListData(0);
				return TRUE;
			}


			if (LOWORD(wParam) == IDC_BTBUILDVIEW)
			{

				bool test = App->IsProcessRunning("World_Viewer.exe");
				if (test == 1)
				{
					//App->Say("Running");
				}
				else
				{
					//App->Say("Not Running");


					CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

					App->CLSB_Doc->SelectAll();
					App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );



					char Path[MAX_PATH];
					strcpy(Path,App->WorldEditor_Directory);
					strcat(Path,"World_Viewer.exe");

					App->CLSB_Export_World->Export_World_GD3D(1);
					ShellExecute(App->MainHwnd, "open", Path, "WorldEditor",App->WorldEditor_Directory, SW_SHOW);

					App->CLSB_Doc->ResetAllSelections();
					App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );

				}

				
				return TRUE;
			}
			
			if (LOWORD(wParam) == IDC_BTTESTDLG)
			{
				CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

				/*pDoc->
				CFusionApp::OnOpenRecentFile(1);*/
				//CWinApp::OnOpenRecentFile (1);

				
				//App->CL_TextureDialog->Start_TextureDialog();

				/*char buf[MAX_PATH];
				GetMenuStringA(App->hMenu, ID_FILE_MRU_FILE2, buf, MAX_PATH, 1);

				App->Say(buf);*/



				return TRUE;
			}

			// Wired Framed
			if (LOWORD(wParam) == IDC_BTSELECTALL)
			{
				App->CLSB_Doc->SelectAll() ;
				App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BTDESELECTALL)
			{
				App->CLSB_Doc->ResetAllSelections() ;
				App->CLSB_Doc->UpdateSelected();
				App->CLSB_Doc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BTWIRE)
			{
				App->CL_Render_App->Render3D_Mode(ID_VIEW_3DWIREFRAME);

				App->CL_Dialogs->F_WireFrame = 1;
				App->CL_Dialogs->F_Textured = 0;

				InvalidateRect(hDlg, NULL, false);
				return TRUE;
			}

			// Textured
			if (LOWORD(wParam) == IDC_BTSETVIEW)
			{
				App->CL_Render_App->Render3D_Mode(ID_VIEW_TEXTUREVIEW);

				App->CL_Dialogs->F_WireFrame = 0;
				App->CL_Dialogs->F_Textured = 1;

				InvalidateRect(hDlg, NULL, false);
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

// *************************************************************************
// *	  		Show_About_Dlg:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool A_Dialogs::Show_About_Dlg()
{

	DialogBox(App->hInst, (LPCTSTR)IDD_ABOUTBOX, App->MainHwnd, (DLGPROC)About_Dlg_Proc);

	return 1;
}

// *************************************************************************
// *        	About_Dlg_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_Dialogs::About_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
		{
			SendDlgItemMessage(hDlg, IDC_STHELP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

			char buf[2024];
			strcpy(buf,"\r\nGenesis3D Equity_WE version 1.26 Alpha\r\n\r\nThis version of the World Editor is heavly modified version\r\n of RFpro and World Editor.\r\n\r\nFor additional information on Genesis3D, visit:\r\nhttps://www.realityfactory.info/cms/\r\n\r\nThanks");
			SetDlgItemText(hDlg, IDC_STHELP,buf);

			
			return TRUE;

		}
	case WM_CTLCOLORSTATIC:
		{
			if (GetDlgItem(hDlg, IDC_STHELP) == (HWND)lParam)
			{
				SetBkColor((HDC)wParam, RGB(0, 255, 0));
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

			break;
		}
	}

	return FALSE;
}

// *************************************************************************
// *	  	Start_Move_Brush_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool A_Dialogs::Start_Move_Brush_Dlg()
{

	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	CenterOfSelection = m_pDoc->SelectedGeoCenter;

	DialogBox(App->hInst, (LPCTSTR)IDD_SB_MOVEBRUSH, App->MainHwnd, (DLGPROC)Move_Brush_Proc);

	return 1;
}

// *************************************************************************
// *        	Move_Brush_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_Dialogs::Move_Brush_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
		{
			SendDlgItemMessage(hDlg, IDC_STBRUSH, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg, IDC_STPOSITION, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));

			SendDlgItemMessage(hDlg, IDC_STCAMX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg, IDC_EDCAMX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

			SendDlgItemMessage(hDlg, IDC_STCAMY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg, IDC_EDCAMY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

			SendDlgItemMessage(hDlg, IDC_STCAMZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg, IDC_EDCAMZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

			SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

			SendDlgItemMessage(hDlg, IDC_BTRESETPOSITION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

			char buf[255];

			sprintf(buf, "%f", App->CL_Dialogs->CenterOfSelection.X);
			SetDlgItemText(hDlg, IDC_EDCAMX,buf);

			sprintf(buf, "%f", App->CL_Dialogs->CenterOfSelection.Y);
			SetDlgItemText(hDlg, IDC_EDCAMY,buf);

			sprintf(buf, "%f", App->CL_Dialogs->CenterOfSelection.Z);
			SetDlgItemText(hDlg, IDC_EDCAMZ,buf);

			return TRUE;

		}
	case WM_CTLCOLORSTATIC:
		{

			if (GetDlgItem(hDlg, IDC_STBRUSH) == (HWND)lParam)
			{
				SetBkColor((HDC)wParam, RGB(0, 255, 0));
				SetTextColor((HDC)wParam, RGB(0, 0, 0));
				SetBkMode((HDC)wParam, TRANSPARENT);
				return (UINT)App->AppBackground;
			}
			if (GetDlgItem(hDlg, IDC_STPOSITION) == (HWND)lParam)
			{
				SetBkColor((HDC)wParam, RGB(0, 255, 0));
				SetTextColor((HDC)wParam, RGB(0, 0, 0));
				SetBkMode((HDC)wParam, TRANSPARENT);
				return (UINT)App->AppBackground;
			}

			if (GetDlgItem(hDlg, IDC_STCAMX) == (HWND)lParam)
			{
				SetBkColor((HDC)wParam, RGB(0, 255, 0));
				SetTextColor((HDC)wParam, RGB(0, 0, 0));
				SetBkMode((HDC)wParam, TRANSPARENT);
				return (UINT)App->AppBackground;
			}
			if (GetDlgItem(hDlg, IDC_STCAMY) == (HWND)lParam)
			{
				SetBkColor((HDC)wParam, RGB(0, 255, 0));
				SetTextColor((HDC)wParam, RGB(0, 0, 0));
				SetBkMode((HDC)wParam, TRANSPARENT);
				return (UINT)App->AppBackground;
			}

			if (GetDlgItem(hDlg, IDC_STCAMZ) == (HWND)lParam)
			{
				SetBkColor((HDC)wParam, RGB(0, 255, 0));
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

		if (some_item->idFrom == IDC_BTRESETPOSITION && some_item->code == NM_CUSTOMDRAW)
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
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDC_BTRESETPOSITION)
			{

				App->CL_Dialogs->CenterOfSelection.X = 0; 
				App->CL_Dialogs->CenterOfSelection.Y = 0;
				App->CL_Dialogs->CenterOfSelection.Z = 0;

				char buf[100];

				sprintf(buf, "%f", App->CL_Dialogs->CenterOfSelection.X);
				SetDlgItemText(hDlg, IDC_EDCAMX,buf);

				sprintf(buf, "%f", App->CL_Dialogs->CenterOfSelection.Y);
				SetDlgItemText(hDlg, IDC_EDCAMY,buf);

				sprintf(buf, "%f", App->CL_Dialogs->CenterOfSelection.Z);
				SetDlgItemText(hDlg, IDC_EDCAMZ,buf);

				geVec3d_Subtract(&App->CL_Dialogs->CenterOfSelection, &App->CL_Dialogs->m_pDoc->SelectedGeoCenter, &App->CL_Dialogs->CenterOfSelection);
				if (App->CL_Dialogs->m_pDoc->mModeTool == ID_TOOLS_TEMPLATE)
				{
					App->CL_Dialogs->m_pDoc->MoveTemplateBrush(&App->CL_Dialogs->CenterOfSelection);
				}
				else
				{
					App->CL_Dialogs->m_pDoc->MoveSelectedBrushList(App->CL_Dialogs->m_pDoc->pSelBrushes, &App->CL_Dialogs->CenterOfSelection);
				}

				App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);

				return TRUE;
			}

			if (LOWORD(wParam) == IDOK)
			{

				char buff[MAX_PATH];
				GetDlgItemText(hDlg,IDC_EDCAMX,(LPTSTR)buff,MAX_PATH);
				App->CL_Dialogs->CenterOfSelection.X = (float)atof(buff);

				GetDlgItemText(hDlg,IDC_EDCAMY,(LPTSTR)buff,MAX_PATH);
				App->CL_Dialogs->CenterOfSelection.Y = (float)atof(buff);

				GetDlgItemText(hDlg,IDC_EDCAMZ,(LPTSTR)buff,MAX_PATH);
				App->CL_Dialogs->CenterOfSelection.Z = (float)atof(buff);

				geVec3d_Subtract(&App->CL_Dialogs->CenterOfSelection, &App->CL_Dialogs->m_pDoc->SelectedGeoCenter, &App->CL_Dialogs->CenterOfSelection);
				if (App->CL_Dialogs->m_pDoc->mModeTool == ID_TOOLS_TEMPLATE)
				{
					App->CL_Dialogs->m_pDoc->MoveTemplateBrush(&App->CL_Dialogs->CenterOfSelection);
				}
				else
				{
					App->CL_Dialogs->m_pDoc->MoveSelectedBrushList(App->CL_Dialogs->m_pDoc->pSelBrushes, &App->CL_Dialogs->CenterOfSelection);
				}

				App->CLSB_Doc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);

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
