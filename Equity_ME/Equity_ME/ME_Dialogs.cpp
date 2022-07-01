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
// *        		GroupData_Proc  Terry	Bernie						   *
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

		if (App->CL_Dialogs->What_List == Enums::Show_List_Model)
		{
			App->CL_Dialogs->List_ModelData(hDlg);
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
// *	  				List_ModelData Terry Flanigan					   *
// *************************************************************************
void ME_Dialogs::List_ModelData(HWND hDlg)
{

	char buf[255];
	
	sprintf(buf, "%s", "Model Info");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	//----------------------- 
	sprintf(buf, "%s%s", "Model Name = ", App->CL_Model->FileName);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	//----------------------- 
	sprintf(buf, "%s%s", "Model Path = ", App->CL_Model->Path_FileName);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%i", "Vertices = ", App->CL_Model->VerticeCount);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%i", "Faces = ", App->CL_Model->FaceCount);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s", "    ");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	sprintf(buf, "%s%i", "Groups = ", App->CL_Model->Get_Groupt_Count());
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
