/*
Copyright (c) 2022 Equity_ME Model Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "resource.h"
#include "ME_Dialogs.h"


ME_Dialogs::ME_Dialogs()
{
	What_List = Enums::Show_List_None;

	Mouse_Normal = 1;
	Mouse_Slow = 0;
	Mouse_VerySlow = 0;
	Mouse_Fast = 0;

	Message_Text[0] = 0;

	Canceled = 0;
	Is_Canceled = 0;

	MessageString[0] = 0;
	MessageString2[0] = 0;

	btext[0] = 0;
	Chr_Text[0] = 0;
}


ME_Dialogs::~ME_Dialogs()
{
}

// *************************************************************************
// *	  				Show_ListData Terry Flanigan					   *
// *************************************************************************
bool ME_Dialogs::Show_ListData()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_GROUPDATA, App->Fdlg, (DLGPROC)GroupData_Proc);

	return 1;
}
// *************************************************************************
// *        		GroupData_Proc  Terry Flanigan						   *
// *************************************************************************
LRESULT CALLBACK ME_Dialogs::GroupData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		if (App->CL_Dialogs->What_List == Enums::Show_List_Group)
		{
			App->CL_Dialogs->List_GroupData(hDlg);
			return TRUE;
		}

		if (App->CL_Dialogs->What_List == Enums::Show_List_App)
		{
			App->CL_Dialogs->List_App_Data(hDlg);
			return TRUE;
		}

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
// *	  				List_GroupData Terry Flanigan					   *
// *************************************************************************
void ME_Dialogs::List_GroupData(HWND hDlg)
{
	
	char buf[255];
	int Index = App->CL_Groups->Selected_Group;

	sprintf(buf, "%s", "Group Info");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	//----------------------- 
	sprintf(buf, "%s%s", "Group Name = ", App->CL_Model->Group[Index]->GroupName);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%i", "Vertices = ", App->CL_Model->Group[Index]->GroupVertCount);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%i", "Faces = ", App->CL_Model->Group[Index]->GroupFaceCount);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s", "Material Name = ", App->CL_Model->Group[Index]->MaterialName);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s", "Texture Name = ", App->CL_Model->Group[Index]->Text_FileName);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s", "Texture Name = ", App->CL_Model->Group[Index]->Equity_Text_FileName);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%s", "Texture Path = ", App->CL_Model->Group[Index]->Texture_PathFileName);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%i", "Bit Depth = ", App->CL_Model->Group[Index]->Depth);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%i x %i", "Dimensions = ", App->CL_Model->Group[Index]->Width, App->CL_Model->Group[Index]->Height);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
}

// *************************************************************************
// *	  				List_App_Data Terry Flanigan					   *
// *************************************************************************
void ME_Dialogs::List_App_Data(HWND hDlg)
{

	char buf[255];

	sprintf(buf, "%s", "App Info");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	int Count = 0;
	while (Count < 20)
	{

		sprintf(buf, "%i %s%i",Count ,"Group Hwnd = ", App->CL_Model->Group[Count]);
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
		Count++;
	}

	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%i %s%i", Count, "BB Hwnd = ", App->CL_Model->S_BoundingBox[0]);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	App->CL_Ogre->Get_View_Height_Width();
	sprintf(buf, "%s %i", "With = ", App->CL_Ogre->Ogre_Listener->View_Width);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s %i", "Height = ", App->CL_Ogre->Ogre_Listener->View_Height);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	
}

// *************************************************************************
// *	  				Start_Speed_Camera Terry Flanigan				   *
// *************************************************************************
void ME_Dialogs::Start_Speed_Camera()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_MOUSESENSITIVITY,App->Fdlg, (DLGPROC)Speed_Camera_Proc);
}
// *************************************************************************
// *					Speed_Camera_Proc Terry Flanigan	  			   *
// *************************************************************************
LRESULT CALLBACK ME_Dialogs::Speed_Camera_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_STBANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_CKNORMAL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CKSLOW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CKVERYSLOW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CKFAST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STBANNER) == (HWND)lParam)
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

		if (some_item->idFrom == IDC_CKNORMAL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Dialogs->Mouse_Normal);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CKSLOW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Dialogs->Mouse_Slow);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CKVERYSLOW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Dialogs->Mouse_VerySlow);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CKFAST && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Dialogs->Mouse_Fast);
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

		if (LOWORD(wParam) == IDC_CKNORMAL)
		{
			
			App->CL_Ogre->Ogre_Listener->mMoveSensitivity = 50;
			App->CL_Ogre->Ogre_Listener->mMoveSensitivityMouse = 50;
			

			App->CL_Dialogs->UnCheck_All_SpeedMouseOption();
			App->CL_Dialogs->Mouse_Normal = 1;

			InvalidateRect(hDlg, NULL, false);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CKSLOW)
		{
			
			App->CL_Ogre->Ogre_Listener->mMoveSensitivity = 5;
			App->CL_Ogre->Ogre_Listener->mMoveSensitivityMouse = 5;
			
			App->CL_Dialogs->UnCheck_All_SpeedMouseOption();
			App->CL_Dialogs->Mouse_Slow = 1;

			InvalidateRect(hDlg, NULL, false);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CKVERYSLOW)
		{
			
			App->CL_Ogre->Ogre_Listener->mMoveSensitivity = 1;
			App->CL_Ogre->Ogre_Listener->mMoveSensitivityMouse = 1;
			

			App->CL_Dialogs->UnCheck_All_SpeedMouseOption();
			App->CL_Dialogs->Mouse_VerySlow = 1;

			InvalidateRect(hDlg, NULL, false);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CKFAST)
		{
			
			App->CL_Ogre->Ogre_Listener->mMoveSensitivity = 250;
			App->CL_Ogre->Ogre_Listener->mMoveSensitivityMouse = 250;
			
			App->CL_Dialogs->UnCheck_All_SpeedMouseOption();
			App->CL_Dialogs->Mouse_Fast = 1;

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
// *				UnCheck_All_SpeedMouseOption Terry Flanigan			   *
// *************************************************************************
void ME_Dialogs::UnCheck_All_SpeedMouseOption()
{
	Mouse_Normal = 0;
	Mouse_Slow = 0;
	Mouse_VerySlow = 0;
	Mouse_Fast = 0;
}

// *************************************************************************
// *	  				Message Terry Flanigan							   *
// *************************************************************************
void ME_Dialogs::Message(char *pString)
{
	strcpy(Message_Text, pString);
	DialogBox(App->hInst, (LPCTSTR)IDD_MESSAGE, App->Fdlg, (DLGPROC)Message_Proc);
}
// *************************************************************************
// *        			Message_Proc  Terry	Flanigan					   *
// *************************************************************************
LRESULT CALLBACK ME_Dialogs::Message_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		HFONT Font;
		Font = CreateFont(-20, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
		SendDlgItemMessage(hDlg, IDC_STTEXT, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BANNER, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_STTEXT, App->CL_Dialogs->Message_Text);

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
		return CDRF_DODEFAULT;
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
// *	  					 YesNo Terry Bernie							   *
// *************************************************************************
void ME_Dialogs::YesNo(char *Text, char *Text2)
{
	Canceled = 0;
	MessageString[0] = 0;
	MessageString2[0] = 0;

	strcpy(MessageString, Text);
	strcpy(MessageString2, Text2);

	DialogBox(App->hInst, (LPCTSTR)IDD_YESNO, App->Fdlg, (DLGPROC)YesNo_Proc);
}
// *************************************************************************
// *					YesNo_Proc_Proc Terry Bernie	  				   *
// *************************************************************************
LRESULT CALLBACK ME_Dialogs::YesNo_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		//App->SetTitleBar(hDlg);

		SendDlgItemMessage(hDlg, IDC_BANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTEXT, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_BANNER, App->CL_Dialogs->MessageString);
		SetDlgItemText(hDlg, IDC_STTEXT, App->CL_Dialogs->MessageString2);
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
		return FALSE;
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

		return CDRF_DODEFAULT;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	case WM_COMMAND:

		if (LOWORD(wParam) == IDOK)
		{
			App->CL_Dialogs->Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->CL_Dialogs->Canceled = 1;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;

	}
	return FALSE;
}

// *************************************************************************
// *	  			Dialog_Text:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void ME_Dialogs::Dialog_Text()
{
	Is_Canceled = 0;

	DialogBox(App->hInst, (LPCTSTR)IDD_PROP_TEXT, App->Fdlg, (DLGPROC)Dialog_Text_Proc);
}
// *************************************************************************
// *			Dialog_Text_Proc:- Terry and Hazel Flanigan 2022 		   *
// *************************************************************************
LRESULT CALLBACK ME_Dialogs::Dialog_Text_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		//App->SetTitleBar(hDlg);

		SendDlgItemMessage(hDlg, IDC_TITLENAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EDITTEXT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_TITLENAME, (LPCTSTR)App->CL_Dialogs->btext);
		SetDlgItemText(hDlg, IDC_EDITTEXT, (LPCTSTR)App->CL_Dialogs->Chr_Text);
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_TITLENAME) == (HWND)lParam)
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

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK)
		{
			char buff[255];
			GetDlgItemText(hDlg, IDC_EDITTEXT, (LPTSTR)buff, 255);

			strcpy(App->CL_Dialogs->Chr_Text, buff);

			App->CL_Dialogs->Is_Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->CL_Dialogs->Is_Canceled = 1;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}

	break;

	}
	return FALSE;
}
