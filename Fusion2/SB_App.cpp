// SB_App.cpp: implementation of the SB_App class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "fusion.h"
#include "SB_App.h"
#include "FUSIONDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SB_App::SB_App()
{
	NumSelEntities = 0;
	EqutyTab_Hwnd = NULL;
	
	AppBackground = 0;
	BlackBrush = 0;
	Brush_Blue = 0;
	Brush_White = 0;
	Brush_Green = 0;
	Brush_But_Normal = 0;
	Brush_But_Hover = 0;
	Brush_But_Pressed = 0;
	Brush_Red = 0;
	Brush_Tabs = 0;
	Brush_Tabs_UnSelected = 0;
	DialogBackGround = 0;

	Font_CB12 = 0;
	Font_CB15 = 0;
	Font_CB15_Bold = 0;
	Font_Arial20 = 0;
	Show_Dialog_Flag = 0;
}

SB_App::~SB_App()
{

}

// *************************************************************************
// *					SetBrushes_Fonts Terry Flanigan					   *
// *************************************************************************
void SB_App::SetBrushes_Fonts(void)
{
	AppBackground = CreateSolidBrush(RGB(213, 222, 242));
	DialogBackGround = CreateSolidBrush(RGB(208, 230, 252));

	BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	Brush_White = CreateSolidBrush(RGB(255, 255, 255));
	Brush_Red = CreateSolidBrush(RGB(252, 85, 63));
	Brush_Green = CreateSolidBrush(RGB(0, 255, 0));
	Brush_Blue = CreateSolidBrush(RGB(0, 180, 255));

	Brush_But_Normal = CreateSolidBrush(RGB(255, 255, 150));
	Brush_But_Hover = CreateSolidBrush(RGB(255, 255, 200));
	Brush_But_Pressed = CreateSolidBrush(RGB(240, 240, 190));
	Brush_Tabs = CreateSolidBrush(RGB(255, 255, 255));
	Brush_Tabs_UnSelected = CreateSolidBrush(RGB(190, 190, 190));

	Font_CB12 = CreateFont(-12, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
	Font_CB15 = CreateFont(-15, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
	Font_Arial20 = CreateFont(-20, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Arial");
	Font_CB15_Bold = CreateFont(-15, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
}

// *************************************************************************
// *									Say								   *
// *************************************************************************
void SB_App::Say(const char* Message)
{
	char text[1024];
	strcpy(text, Message);

	char num[255];
	_itoa(NumSelEntities,num,10);

	MessageBox (NULL,text,num, MB_ICONEXCLAMATION | MB_OK);
//	App->Cl_Dialogs->Message(text);
}

// *************************************************************************
// *	  				 Start_EquityTab Terry Flanigan					   *
// *************************************************************************
bool SB_App::Start_EquityTab()
{
	EqutyTab_Hwnd = NULL;

	EqutyTab_Hwnd = CreateDialog(NULL,(LPCTSTR)IDD_EQUITYTAB,NULL,(DLGPROC)EquityTab_Proc);
	return 1;
}
// *************************************************************************
// *				Dialog_Text_Proc  Terry Flanigan  					   *
// *************************************************************************
LRESULT CALLBACK SB_App::EquityTab_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{		
	switch (message)
	{
		case WM_INITDIALOG:
			{	
				SendDlgItemMessage(hDlg,IDC_STSELECT, WM_SETFONT, (WPARAM)App->Font_CB15,MAKELPARAM(TRUE, 0));

				App->EqutyTab_Hwnd = hDlg;

				char buf[255];
				_itoa(App->NumSelEntities,buf,10);
		
				SetDlgItemText(hDlg,IDC_STSELECT,(LPCTSTR)buf);
				return TRUE;
			}
		case WM_CTLCOLORSTATIC:
			{
				if (GetDlgItem(hDlg, IDC_STSELECT) == (HWND)lParam)
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
				return (LONG)App->Brush_Green;
			}

		case WM_COMMAND:
			{
				
				
				if (LOWORD(wParam) == IDC_BTUPDATE) 
				{
					App->UpdateTab_Dialog(hDlg);
					return TRUE;
				}
				
				if (LOWORD(wParam) == IDOK) 
				{
					//EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
				}

				if (LOWORD(wParam)== IDCANCEL) 
				{
					return TRUE;
				}
			}

			break;

	}
    return FALSE;
}

// *************************************************************************
// *	  					 Init Terry Flanigan						   *
// *************************************************************************
bool SB_App::Init()
{
	SetBrushes_Fonts();
	return 1;
}

// *************************************************************************
// *	  				UpdateTab_Dialog Terry Flanigan					   *
// *************************************************************************
bool SB_App::UpdateTab_Dialog(HWND hDlg)
{
	char buf[255];
	_itoa(NumSelEntities,buf,10);
	SetDlgItemText(hDlg,IDC_STSELECT,(LPCTSTR)buf);
	return 1;
}

// *************************************************************************
// *	  				Show_Dialog Terry Flanigan						   *
// *************************************************************************
bool SB_App::Show_Dialog(bool flag)
{
//	ShowWindow(EqutyTab_Hwnd,flag);
	return 1;
}
