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

//#define WINVER 0x0500
//
//#pragma comment(linker,"\"/manifestdependency:type='win32' \
//name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
//processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"") 

#include "StdAfx.h"
#include "AB_App.h"
#include "A_TopTabs.h"
#include "resource.h"

#include "FUSIONDoc.h"
#include "FUSIONView.h"

#include "Windows.h"
#include "wingdi.h"

SB_TopTabs::SB_TopTabs(void)
{
	Top_Tabs_Hwnd = nullptr;
	Brush_Modify_Panel_Hwnd = nullptr;
	File_Panel_Hwnd = nullptr;
	Test_Panel_Hwnd = nullptr;

	Quick_Command_Started = 0;

	Textured_Flag = 0;
	Wired_Flag = 0;

	Header_File_Flag = 0;
	Header_BrushModify_Flag = 0;
	Header_Test_Flag = 0;
	
	Brush_Select_Flag = 0;
	Brush_MoveRotate_Flag = 0;
	Brush_Scale_Flag = 0;
	Brush_Shear_Flag = 0;
}

SB_TopTabs::~SB_TopTabs(void)
{
}

// *************************************************************************
// *	  		Start_Headers_Tabs:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_TopTabs::Start_Headers_Tabs()
{
	if (Quick_Command_Started == 0)
	{
		Top_Tabs_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TOPTABS, App->MainHwnd, (DLGPROC)TB_Headers_Proc);

		Move_Window();

		Start_BrushModify_Panel();
		Start_File_Tab();
		Start_Test_Tab();

		Reset_Tabs_Buttons();
		Header_File_Flag = 1;
		RedrawWindow(Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		ShowWindow(File_Panel_Hwnd, SW_SHOW);

		Quick_Command_Started = 1;
	}
	
	return 1;
}

// *************************************************************************
// *			TB_Headers_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs::TB_Headers_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BT_TB_MODIFY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TB_FILE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TB_TEST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BT_TB_TEXTURED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TB_WIRED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BT_TB_SELECTALL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TB_DESELECTALL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

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

		if (some_item->idFrom == IDC_BT_TB_TEXTURED && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_TopTabs->Textured_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_TB_WIRED && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_TopTabs->Wired_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_TB_SELECTALL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_TB_DESELECTALL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		// -------------------------------
		if (some_item->idFrom == IDC_BT_TB_MODIFY && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CLSB_TopTabs->Header_BrushModify_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_TB_FILE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CLSB_TopTabs->Header_File_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_TB_TEST && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CLSB_TopTabs->Header_Test_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		{
			// ---------------- Headers
			if (LOWORD(wParam) == IDC_BT_TB_TEST)
			{
				App->CLSB_TopTabs->Reset_Tabs_Buttons();
				App->CLSB_TopTabs->Header_Test_Flag = 1;
				RedrawWindow(App->CLSB_TopTabs->Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				ShowWindow(App->CLSB_TopTabs->Test_Panel_Hwnd, SW_SHOW);

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BT_TB_FILE)
			{
				App->CLSB_TopTabs->Reset_Tabs_Buttons();
				App->CLSB_TopTabs->Header_File_Flag = 1;
				RedrawWindow(App->CLSB_TopTabs->Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				
				ShowWindow(App->CLSB_TopTabs->File_Panel_Hwnd, SW_SHOW);
				
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BT_TB_MODIFY)
			{
				App->CLSB_TopTabs->Reset_Tabs_Buttons();
				App->CLSB_TopTabs->Header_BrushModify_Flag = 1;
				RedrawWindow(App->CLSB_TopTabs->Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				ShowWindow(App->CLSB_TopTabs->Brush_Modify_Panel_Hwnd, SW_SHOW);

				return TRUE;
			}
			
			// --------------------
			if (LOWORD(wParam) == IDC_BT_TB_TEXTURED)
			{
				App->CLSB_TopTabs->Reset_Render_Buttons();
				
				App->CLSB_TopTabs->Textured_Flag = 1;
				App->CL_Render_App->Render3D_Mode(ID_VIEW_TEXTUREVIEW);

				RedrawWindow(App->CLSB_TopTabs->Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BT_TB_WIRED)
			{
				App->CLSB_TopTabs->Reset_Render_Buttons();

				App->CLSB_TopTabs->Wired_Flag = 1;
				App->CL_Render_App->Render3D_Mode(ID_VIEW_3DWIREFRAME);

				RedrawWindow(App->CLSB_TopTabs->Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BT_TB_SELECTALL)
			{
				CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

				pDoc->SelectAll() ;
				pDoc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;

				App->CL_TabsGroups_Dlg->Update_Dlg_SelectedBrushesCount();

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BT_TB_DESELECTALL)
			{
				CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

				pDoc->ResetAllSelections();
				pDoc->UpdateSelected();
				pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);

				App->CL_TabsGroups_Dlg->Update_Dlg_SelectedBrushesCount();

				return TRUE;
			}

			if (LOWORD(wParam) == IDOK)
			{
				App->CLSB_TopTabs->Quick_Command_Started = 0;
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			if (LOWORD(wParam) == IDCANCEL)
			{
				App->CLSB_TopTabs->Quick_Command_Started = 0;
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			break;
		}

	}

	return FALSE;
}

// *************************************************************************
// *	  	Reset_Tabs_Buttons:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_TopTabs::Reset_Tabs_Buttons()
{
	Header_File_Flag = 0;
	Header_BrushModify_Flag = 0;
	Header_Test_Flag = 0;

	ShowWindow(Brush_Modify_Panel_Hwnd, SW_HIDE);
	ShowWindow(File_Panel_Hwnd, SW_HIDE);
	ShowWindow(Test_Panel_Hwnd, SW_HIDE);

	RedrawWindow(Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *	  	Reset_Render_Buttons:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_TopTabs::Reset_Render_Buttons()
{
	Textured_Flag = 0;
	Wired_Flag = 0;

	RedrawWindow(Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

}

// *************************************************************************
// *	  	Start_BrushModify_Panel:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_TopTabs::Start_BrushModify_Panel()
{
	Brush_Modify_Panel_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TB_PROPERTIES,Top_Tabs_Hwnd, (DLGPROC)BrushModify_Panel_Proc);
	return 1;
}

// *************************************************************************
// *		BrushModify_Panel_Proc:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs::BrushModify_Panel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BTSCALE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTTBSELECT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTTBMOVEROTATE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTTBSHEAR, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
		{
			return (LONG)App->Brush_White;
		}

	case WM_DRAWITEM:
		{

			LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT)lParam;

			if (lpDIS->CtlID == IDC_BTTBSELECT)
			{
				App->Custom_Button_Toggle_MFC(lpDIS,hDlg,App->CLSB_TopTabs->Brush_Select_Flag);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BTTBMOVEROTATE)
			{
				App->Custom_Button_Toggle_MFC(lpDIS,hDlg,App->CLSB_TopTabs->Brush_MoveRotate_Flag);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BTSCALE)
			{
				App->Custom_Button_Toggle_MFC(lpDIS,hDlg,App->CLSB_TopTabs->Brush_Scale_Flag);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BTTBSHEAR)
			{
				App->Custom_Button_Toggle_MFC(lpDIS,hDlg,App->CLSB_TopTabs->Brush_Shear_Flag);
				return TRUE;
			}

			return TRUE;
		}

	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDC_BTTBMOVEROTATE)
			{
				App->CLSB_TopTabs->Reset_Brush_Buttons();
				App->CLSB_TopTabs->Brush_MoveRotate_Flag = 1;

				RedrawWindow(App->CLSB_TopTabs->Brush_Modify_Panel_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->CLSB_TopTabs->Select_MoveRotate();
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BTTBSHEAR)
			{
				App->CLSB_TopTabs->Reset_Brush_Buttons();
				App->CLSB_TopTabs->Brush_Shear_Flag = 1;

				RedrawWindow(App->CLSB_TopTabs->Brush_Modify_Panel_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->CLSB_TopTabs->Select_Shear();
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BTSCALE)
			{
				App->CLSB_TopTabs->Reset_Brush_Buttons();
				App->CLSB_TopTabs->Brush_Scale_Flag = 1;

				RedrawWindow(App->CLSB_TopTabs->Brush_Modify_Panel_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->CLSB_TopTabs->Select_Scale();
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BTTBSELECT)
			{
				App->CLSB_TopTabs->Reset_Brush_Buttons();
				App->CLSB_TopTabs->Brush_Select_Flag = 1;

				RedrawWindow(App->CLSB_TopTabs->Brush_Modify_Panel_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->CLSB_TopTabs->Select_Mode();
				return TRUE;
			}

			break;
		}

	}

	return FALSE;
}

// *************************************************************************
// *	  	Reset_Brush_Buttons:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_TopTabs::Reset_Brush_Buttons()
{
	Brush_Select_Flag = 0;
	Brush_MoveRotate_Flag = 0;
	Brush_Scale_Flag = 0;
	Brush_Shear_Flag = 0;

	RedrawWindow(Brush_Modify_Panel_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *	  		Start_File_Tab:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_TopTabs::Start_File_Tab()
{
	File_Panel_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TB_FILES, Top_Tabs_Hwnd, (DLGPROC)Top_File_Proc);

	return 1;
}

// *************************************************************************
// *			Top_File_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs::Top_File_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BT_TBF_QUICKLOAD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
		{
			return (LONG)App->Brush_White;
		}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_TBF_QUICKLOAD && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDC_BT_TBF_QUICKLOAD)
			{

				char Txlpath[MAX_PATH];
				char path[MAX_PATH];

				strcpy(path,App->WorldEditor_Directory);
				strcat(path,"Levels\\Test.3dt");

				strcpy(Txlpath,App->WorldEditor_Directory);
				strcat(Txlpath,"Levels\\Equity.txl");

				strcpy(App->CL_File->PathFileName_3dt,path);

				App->CL_File->Open_3dt_File(0);

				App->CL_World->Set_Paths();

				App->CL_World->Reset_Editor();

				App->CL_TabsGroups_Dlg->Fill_ListBox();

				App->CL_World->Level_SetTxlPath(Txlpath);

				App->Say(path);
				return TRUE;
			}

			break;
		}

	}

	return FALSE;
}

// *************************************************************************
// *	  		Start_Test_Tab:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_TopTabs::Start_Test_Tab()
{
	Test_Panel_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TB_TEST, Top_Tabs_Hwnd, (DLGPROC)Top_Test_Proc);

	return 1;
}

// *************************************************************************
// *			Top_TestProc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs::Top_Test_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BT_TB_BUILDPREVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_PREVIEWSELECTED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BT_TB_WORLDINFO, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TB_NEWVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STARTEQUITY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_White;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_TB_BUILDPREVIEW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_PREVIEWSELECTED && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_TB_NEWVIEW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_TB_WORLDINFO && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_STARTEQUITY && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_STARTEQUITY)
		{
			App->CLSB_Equity->Start_Equity_Dialog(0);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_TB_NEWVIEW)
		{
			App->CL_Main_View->Start_Main_View_Dlg();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_TB_WORLDINFO)
		{
			App->CL_Dialogs->Show_ListData();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_TB_BUILDPREVIEW)
		{

			CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

			pDoc->SelectAll();
			pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);

			App->CL_Export_World->Export_World_GD3D(1);

			pDoc->ResetAllSelections();
			pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);


			App->CLSB_Equity->Start_Equity_Dialog(1);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_PREVIEWSELECTED)
		{

			CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

			int NumSelBrushes = SelBrushList_GetSize(pDoc->pSelBrushes);

			if (NumSelBrushes == 0)
			{
				App->Say("No Brushes Selected");
				return TRUE;
			}


			App->CL_Export_World->Export_World_GD3D(1);
			App->CLSB_Equity->Start_Equity_Dialog(1);

			App->CLSB_Camera->Set_Camera_Mode(Enums::CamModel);
		
			return TRUE;
		}

		break;
	}

	}

	return FALSE;
}

// *************************************************************************
// *		 	Select_Mode:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_TopTabs::Select_Mode()
{
	/*AfxGetApp()->OpenDocumentFile("C:\\Users\\Acer\\Desktop\\SB_GD\\Bin\\Tools\\Levels\\StartRoom.3dt");
	App->CL_World->Set_Paths();*/

	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	m_pDoc->mCurrentTool = CURTOOL_NONE;
	m_pDoc->mModeTool = ID_GENERALSELECT;
	m_pDoc->ConfigureCurrentTool();

}

// *************************************************************************
// *	  	Select_MoveRotate:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_TopTabs::Select_MoveRotate()
{
	CFusionView			*pView;

	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	POSITION pos;
	pos = m_pDoc->GetFirstViewPosition();
	pView = (CFusionView*)m_pDoc->GetNextView(pos) ;

	int mode = pView->GetModeTool();

	if(mode == ID_TOOLS_TEMPLATE)
	{
		pView->SetTool( ID_TOOLS_BRUSH_MOVEROTATEBRUSH );
		m_pDoc->ConfigureCurrentTool();
	} 
	else 
	{
		if(pView->GetTool()==ID_TOOLS_BRUSH_MOVEROTATEBRUSH)
		{
			pView->SetTool(CURTOOL_NONE);
			pView->SetAdjustMode (ADJUST_MODE_FACE);
		} 
		else 
		{
			pView->SetTool(ID_TOOLS_BRUSH_MOVEROTATEBRUSH);
		}

		m_pDoc->ConfigureCurrentTool();
	}
}

// *************************************************************************
// *		 	Select_Scale:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_TopTabs::Select_Scale()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	int mode = m_pDoc->mModeTool;// pView->GetModeTool();

	if(mode == ID_TOOLS_TEMPLATE)
	{
		m_pDoc->mCurrentTool = ID_TOOLS_BRUSH_SCALEBRUSH;
		m_pDoc->ConfigureCurrentTool();
	} 
	else 
	{
		if(m_pDoc->mCurrentTool == ID_TOOLS_BRUSH_SCALEBRUSH)
		{
			m_pDoc->mCurrentTool = CURTOOL_NONE;
			m_pDoc->mAdjustMode = ADJUST_MODE_FACE;
		} 
		else 
		{
			m_pDoc->mCurrentTool = ID_TOOLS_BRUSH_SCALEBRUSH;
		}

		m_pDoc->ConfigureCurrentTool();
	}
}

// *************************************************************************
// *		 	Select_Shear:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_TopTabs::Select_Shear()
{
	CFusionView			*pView;

	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	POSITION pos;
	pos = m_pDoc->GetFirstViewPosition();
	pView = (CFusionView*)m_pDoc->GetNextView(pos) ;

	int mode = pView->GetModeTool();

	if(mode == ID_TOOLS_TEMPLATE)
	{
		pView->SetTool( ID_TOOLS_BRUSH_SHEARBRUSH);
		m_pDoc->ConfigureCurrentTool();
	} 
	else 
	{
		if(pView->GetTool() == ID_TOOLS_BRUSH_SHEARBRUSH)
		{
			pView->SetTool(CURTOOL_NONE);
			pView->SetAdjustMode (ADJUST_MODE_FACE);
		}
		else 
		{
			pView->SetTool(ID_TOOLS_BRUSH_SHEARBRUSH);
		}

		m_pDoc->ConfigureCurrentTool();
	}
}

// *************************************************************************
// *				Move_Window:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_TopTabs::Move_Window(void)
{

	RECT rect;
	GetWindowRect(App->MainHwnd, &rect);

	int widthX = rect.right - rect.left;
	int heightY = rect.bottom - rect.top;

	SetWindowPos(Top_Tabs_Hwnd, NULL, (rect.left+ (rect.right/2))-300, rect.top+100,
		0, 0, SWP_NOSIZE | SWP_NOZORDER);

}
