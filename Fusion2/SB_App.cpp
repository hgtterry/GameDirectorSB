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

	//	pDoc = CMainFrame::GetCurrentDoc();

	//	pDoc = CFusionDoc::App;
}

SB_App::~SB_App()
{

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
//	HWND hwnd = GetDlgItem(IDD_TABDIALOG,0);
	//EqutyTab_Hwnd = 
	CreateDialog(NULL,(LPCTSTR)IDD_EQUITYTAB,NULL,(DLGPROC)EquityTab_Proc);
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
				App->EqutyTab_Hwnd = hDlg;

				char buf[255];
				_itoa(App->NumSelEntities,buf,10);
		
				SetDlgItemText(hDlg,IDC_STSELECT,(LPCTSTR)buf);
				return TRUE;
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

	Say("init");
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
