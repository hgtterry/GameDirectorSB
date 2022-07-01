#include "stdafx.h"
#include "ME_App.h"
#include "resource.h"
#include "ME_Dialogs.h"


ME_Dialogs::ME_Dialogs()
{
	What_List = Enums::Show_List_None;
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
		//SendDlgItemMessage(hDlg, IDC_STBANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		//SendDlgItemMessage(hDlg, IDC_CKNORMAL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDC_CKSLOW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDC_CKVERYSLOW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CKFAST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		//App->SBC_TopTabs->MouseOption_DlgHwnd = hDlg;

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

		/*if (some_item->idFrom == IDC_CKNORMAL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dialogs->Mouse_Normal2);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CKSLOW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dialogs->Mouse_Slow2);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CKVERYSLOW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dialogs->Mouse_VerySlow2);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CKFAST && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dialogs->Mouse_Fast2);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		/*if (LOWORD(wParam) == IDC_CKNORMAL)
		{
			if (App->Cl19_Ogre->OgreListener->Equity_Running == 1)
			{
				App->EBC_Listener->mMoveSensitivity = 50;
				App->EBC_Listener->mMoveSensitivityMouse = 50;
			}
			else
			{
				App->Cl19_Ogre->OgreListener->mMoveSensitivity = 50;
				App->Cl19_Ogre->OgreListener->mMoveSensitivityMouse = 50;
			}

			App->SBC_TopTabs->UnCheck_All_MouseOption(hDlg);
			App->Cl_Dialogs->Mouse_Normal2 = 1;

			InvalidateRect(hDlg, NULL, false);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CKSLOW)
		{
			if (App->Cl19_Ogre->OgreListener->Equity_Running == 1)
			{
				App->EBC_Listener->mMoveSensitivity = 5;
				App->EBC_Listener->mMoveSensitivityMouse = 5;
			}
			else
			{
				App->Cl19_Ogre->OgreListener->mMoveSensitivity = 5;
				App->Cl19_Ogre->OgreListener->mMoveSensitivityMouse = 5;
			}

			App->SBC_TopTabs->UnCheck_All_MouseOption(hDlg);
			App->Cl_Dialogs->Mouse_Slow2 = 1;

			InvalidateRect(hDlg, NULL, false);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CKVERYSLOW)
		{
			if (App->Cl19_Ogre->OgreListener->Equity_Running == 1)
			{
				App->EBC_Listener->mMoveSensitivity = 1;
				App->EBC_Listener->mMoveSensitivityMouse = 1;
			}
			else
			{
				App->Cl19_Ogre->OgreListener->mMoveSensitivity = 1;
				App->Cl19_Ogre->OgreListener->mMoveSensitivityMouse = 1;
			}

			App->SBC_TopTabs->UnCheck_All_MouseOption(hDlg);
			App->Cl_Dialogs->Mouse_VerySlow2 = 1;

			InvalidateRect(hDlg, NULL, false);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}*/

		if (LOWORD(wParam) == IDC_CKFAST)
		{
			
			App->CL_Ogre->Ogre_Listener->mMoveSensitivity = 250;
			App->CL_Ogre->Ogre_Listener->mMoveSensitivityMouse = 250;
			
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
