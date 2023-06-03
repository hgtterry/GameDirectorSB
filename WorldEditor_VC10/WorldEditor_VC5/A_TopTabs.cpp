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

A_TopTabs::A_TopTabs(void)
{
	Top_Tabs_Hwnd = NULL;
	Brush_Modify_Panel_Hwnd = NULL;
	File_Panel_Hwnd = NULL;

	Textured_Flag = 0;
	Wired_Flag = 0;

	Header_File_Flag = 0;
	Header_BrushModify_Flag = 0;

	Brush_Select_Flag = 0;
	Brush_MoveRotate_Flag = 0;
	Brush_Scale_Flag = 0;
	Brush_Shear_Flag = 0;
}

A_TopTabs::~A_TopTabs(void)
{
}

// *************************************************************************
// *	  		Start_Top_Tabs:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool A_TopTabs::Start_Top_Tabs()
{
	Top_Tabs_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TOPTABS, App->MainHwnd, (DLGPROC)Top_Tabs_Proc);

	Start_BrushModify_Panel();
	Start_File_Tab();

	// Select File Tab
	Reset_Tabs_Buttons();
	Header_File_Flag = 1;
	RedrawWindow(Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	ShowWindow(App->CL_TopTabs->File_Panel_Hwnd, SW_SHOW);
	
	return 1;
}

// *************************************************************************
// *			Top_Tabs_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_TopTabs::Top_Tabs_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BT_TB_MODIFY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TB_FILE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TB_TEXTURED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TB_WIRED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BT_TB_SELECTALL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TB_DESELECTALL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TB_BUILDPREVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BT_TB_WORLDINFO, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TB_NEWVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

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

	case WM_DRAWITEM:
		{

			LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT)lParam;

			if (lpDIS->CtlID == IDC_BT_TB_TEXTURED)
			{
				App->Custom_Button_Toggle_MFC(lpDIS,hDlg,App->CL_TopTabs->Textured_Flag);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BT_TB_WIRED)
			{
				App->Custom_Button_Toggle_MFC(lpDIS,hDlg,App->CL_TopTabs->Wired_Flag);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BT_TB_NEWVIEW)
			{
				App->Custom_Button_Normal_MFC(lpDIS,hDlg);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BT_TB_SELECTALL)
			{
				App->Custom_Button_Normal_MFC(lpDIS,hDlg);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BT_TB_DESELECTALL)
			{
				App->Custom_Button_Normal_MFC(lpDIS,hDlg);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BT_TB_BUILDPREVIEW)
			{
				App->Custom_Button_Normal_MFC(lpDIS,hDlg);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BT_TB_WORLDINFO)
			{
				App->Custom_Button_Normal_MFC(lpDIS,hDlg);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BT_TB_FILE)
			{
				App->Custom_Button_Toggle_Tabs_MFC(lpDIS,hDlg,App->CL_TopTabs->Header_File_Flag);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BT_TB_MODIFY)
			{
				App->Custom_Button_Toggle_Tabs_MFC(lpDIS,hDlg,App->CL_TopTabs->Header_BrushModify_Flag);
				return TRUE;
			}


			return TRUE;
		}

	case WM_COMMAND:
		{
			// ---------------- Tabs
			if (LOWORD(wParam) == IDC_STARTOGRE)
			{
				App->CL_Ogre_Dialog->Start_Ogre_Dialog();

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BT_TB_NEWVIEW)
			{
				App->CL_Main_View->Start_Main_View_Dlg();
				return TRUE;
			}
			
			if (LOWORD(wParam) == IDC_BT_TB_FILE)
			{
				App->CL_TopTabs->Reset_Tabs_Buttons();
				App->CL_TopTabs->Header_File_Flag = 1;
				RedrawWindow(App->CL_TopTabs->Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				
				ShowWindow(App->CL_TopTabs->File_Panel_Hwnd, SW_SHOW);
				
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BT_TB_MODIFY)
			{
				App->CL_TopTabs->Reset_Tabs_Buttons();
				App->CL_TopTabs->Header_BrushModify_Flag = 1;
				RedrawWindow(App->CL_TopTabs->Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				ShowWindow(App->CL_TopTabs->Brush_Modify_Panel_Hwnd, SW_SHOW);

				return TRUE;
			}
			
			// --------------------
			if (LOWORD(wParam) == IDC_BT_TB_TEXTURED)
			{
				App->CL_TopTabs->Reset_Render_Buttons();
				
				App->CL_TopTabs->Textured_Flag = 1;
				App->CL_Render_App->Render3D_Mode(ID_VIEW_TEXTUREVIEW);

				RedrawWindow(App->CL_TopTabs->Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BT_TB_WIRED)
			{
				App->CL_TopTabs->Reset_Render_Buttons();

				App->CL_TopTabs->Wired_Flag = 1;
				App->CL_Render_App->Render3D_Mode(ID_VIEW_3DWIREFRAME);

				RedrawWindow(App->CL_TopTabs->Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				return TRUE;
			}

			// ----------------------------------------------
			if (LOWORD(wParam) == IDC_BT_TB_WORLDINFO)
			{
				App->CL_Dialogs->Show_ListData();
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BT_TB_DESELECTALL)
			{
				CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

				pDoc->ResetAllSelections() ;
				pDoc->UpdateSelected();
				pDoc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BT_TB_SELECTALL)
			{
				CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

				pDoc->SelectAll() ;
				pDoc->UpdateAllViews( UAV_ALL3DVIEWS, NULL ) ;

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BT_TB_BUILDPREVIEW)
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

					pDoc->SelectAll();
					pDoc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );


					char Path[MAX_PATH];
					strcpy(Path,App->WorldEditor_Directory);
					strcat(Path,"World_Viewer.exe");

					App->CL_Export_World->Export_World_GD3D(1);
					ShellExecute(App->MainHwnd, "open", Path, "WorldEditor",App->WorldEditor_Directory, SW_SHOW);

					pDoc->ResetAllSelections();
					pDoc->UpdateAllViews( UAV_ALL3DVIEWS, NULL );
				}

				return TRUE;
			}



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
// *	  	Reset_Tabs_Buttons:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_TopTabs::Reset_Tabs_Buttons()
{
	Header_File_Flag = 0;
	Header_BrushModify_Flag = 0;

	ShowWindow(Brush_Modify_Panel_Hwnd, SW_HIDE);
	ShowWindow(File_Panel_Hwnd, SW_HIDE);

	RedrawWindow(App->CL_TopTabs->Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *	  	Reset_Render_Buttons:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TopTabs::Reset_Render_Buttons()
{
	App->CL_TopTabs->Textured_Flag = 0;
	App->CL_TopTabs->Wired_Flag = 0;

	RedrawWindow(App->CL_TopTabs->Top_Tabs_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

}

// *************************************************************************
// *	  	Start_BrushModify_Panel:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool A_TopTabs::Start_BrushModify_Panel()
{
	Brush_Modify_Panel_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TB_PROPERTIES,Top_Tabs_Hwnd, (DLGPROC)BrushModify_Panel_Proc);
	return 1;
}

// *************************************************************************
// *		BrushModify_Panel_Proc:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
LRESULT CALLBACK A_TopTabs::BrushModify_Panel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
				App->Custom_Button_Toggle_MFC(lpDIS,hDlg,App->CL_TopTabs->Brush_Select_Flag);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BTTBMOVEROTATE)
			{
				App->Custom_Button_Toggle_MFC(lpDIS,hDlg,App->CL_TopTabs->Brush_MoveRotate_Flag);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BTSCALE)
			{
				App->Custom_Button_Toggle_MFC(lpDIS,hDlg,App->CL_TopTabs->Brush_Scale_Flag);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BTTBSHEAR)
			{
				App->Custom_Button_Toggle_MFC(lpDIS,hDlg,App->CL_TopTabs->Brush_Shear_Flag);
				return TRUE;
			}

			return TRUE;
		}

	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDC_BTTBMOVEROTATE)
			{
				App->CL_TopTabs->Reset_Brush_Buttons();
				App->CL_TopTabs->Brush_MoveRotate_Flag = 1;

				RedrawWindow(App->CL_TopTabs->Brush_Modify_Panel_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->CL_TopTabs->Select_MoveRotate();
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BTTBSHEAR)
			{
				App->CL_TopTabs->Reset_Brush_Buttons();
				App->CL_TopTabs->Brush_Shear_Flag = 1;

				RedrawWindow(App->CL_TopTabs->Brush_Modify_Panel_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->CL_TopTabs->Select_Shear();
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BTSCALE)
			{
				App->CL_TopTabs->Reset_Brush_Buttons();
				App->CL_TopTabs->Brush_Scale_Flag = 1;

				RedrawWindow(App->CL_TopTabs->Brush_Modify_Panel_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->CL_TopTabs->Select_Scale();
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_BTTBSELECT)
			{
				App->CL_TopTabs->Reset_Brush_Buttons();
				App->CL_TopTabs->Brush_Select_Flag = 1;

				RedrawWindow(App->CL_TopTabs->Brush_Modify_Panel_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->CL_TopTabs->Select_Mode();
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
void A_TopTabs::Reset_Brush_Buttons()
{
	Brush_Select_Flag = 0;
	Brush_MoveRotate_Flag = 0;
	Brush_Scale_Flag = 0;
	Brush_Shear_Flag = 0;

	RedrawWindow(App->CL_TopTabs->Brush_Modify_Panel_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *	  		Start_File_Tab:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool A_TopTabs::Start_File_Tab()
{
	File_Panel_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TB_FILES, Top_Tabs_Hwnd, (DLGPROC)Top_File_Proc);

	return 1;
}

// *************************************************************************
// *			Top_File_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_TopTabs::Top_File_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

	case WM_DRAWITEM:
		{

			LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT)lParam;

			if (lpDIS->CtlID == IDC_BT_TBF_QUICKLOAD)
			{
				App->Custom_Button_Normal_MFC(lpDIS,hDlg);
				return TRUE;
			}

			return TRUE;
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

				//AfxGetApp()->OpenDocumentFile(path);

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
// *		 	Select_Mode:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_TopTabs::Select_Mode()
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
void A_TopTabs::Select_MoveRotate()
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
void A_TopTabs::Select_Scale()
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
void A_TopTabs::Select_Shear()
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
