// bbbb.cpp: implementation of the bbbb class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"       // main symbols
#include "bbbb.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bbbb::bbbb()
{
	Test();
}

bbbb::~bbbb()
{

}

bool bbbb::Test()
{
	MessageBox (NULL,"Can't replace the first key.", "Edit key", MB_ICONEXCLAMATION | MB_OK);
	return 1;
}

// *************************************************************************
// *	  				 Dialog_Text	Terry Bernie					   *
// *************************************************************************
bool bbbb::Dialog_Text()
{
	DialogBox(NULL,(LPCTSTR)IDD_PROP_TEXT,NULL,(DLGPROC)Dialog_Text_Proc);
	return 1;
}
// *************************************************************************
// *				Dialog_Text_Proc	Terry Bernie  					   *
// *************************************************************************
LRESULT CALLBACK bbbb::Dialog_Text_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{		
	switch (message)
	{
		case WM_INITDIALOG:
			{	

				return TRUE;
			}
	

		case WM_COMMAND:
			{
				if (LOWORD(wParam) == IDOK) 
				{
					EndDialog(hDlg, LOWORD(wParam));
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
