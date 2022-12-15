#include "StdAfx.h"
#include "GD19_App.h"
#include "resource.h"
#include "GD19_DIALOGS.h"


GD19_Dialogs::GD19_Dialogs(void)
{
	Object_Index = 0;
	Canceled = 0;
	TrueFlase = 0;

	Active_Dlg_Float = 0;
	Active_Dlg_Int = 0;

	Location_Dlg_Active = 0;

	btext[0] = 0;
	Chr_Float[0] = 0;

	mFloat = 0;
	mInt = 0;

	mListType = Enums::ListBox_None;

	CheckNames = 0;
	CheckSpaces = 0;

	Mouse_Normal2 = 1;
	Mouse_Slow2 = 0;
	Mouse_VerySlow2 = 0;
	Mouse_Fast2 = 0;

	ListBox_Index = 0;

	LocationDlg_hWnd = nullptr;

}


GD19_Dialogs::~GD19_Dialogs(void)
{
}

// *************************************************************************
// *	  		Dialog_Float()  	Terry	Bernie						   *
// *************************************************************************
bool GD19_Dialogs::Dialog_Float()
{
	if (Active_Dlg_Float== 1)
	{
		return 1;
	}

	Active_Dlg_Float = 1;

	DialogBox(App->hInst,(LPCTSTR)IDD_EDITFLOAT,App->Fdlg,(DLGPROC)Dialog_Float_Proc);

	return 1;
}
// *************************************************************************
// *        	Dialog_Float_Proc  Terry	Bernie						   *
// *************************************************************************
LRESULT CALLBACK GD19_Dialogs::Dialog_Float_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
				
	switch (message)
	{
	case WM_INITDIALOG:
		{	
			App->SetTitleBar(hDlg);

			SendDlgItemMessage(hDlg,IDC_BANNER, WM_SETFONT, (WPARAM)App->Font_Arial20,MAKELPARAM(TRUE, 0));

			SendDlgItemMessage(hDlg,IDC_EDIT1, WM_SETFONT, (WPARAM)App->Font_CB15,MAKELPARAM(TRUE, 0));
			

			SetDlgItemText(hDlg,IDC_BANNER,(LPCTSTR)App->Cl_Dialogs->btext);

			SetDlgItemText(hDlg,IDC_EDIT1,(LPCTSTR)App->Cl_Dialogs->Chr_Float);
			
			return TRUE;
		}
		case WM_CTLCOLORSTATIC:
		{
			
			if(GetDlgItem(hDlg,IDC_BANNER) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
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
			if (LOWORD(wParam) == IDOK) 
			{
				char buff[256];
				int result=0;
				GetDlgItemText(hDlg,IDC_EDIT1,(LPTSTR)buff,256);
				strcpy(App->Cl_Dialogs->Chr_Float,buff);
				App->Cl_Dialogs->mFloat = (float)atof(buff);

				App->Cl_Dialogs->Canceled = 0;
				App->Cl_Dialogs->Active_Dlg_Float = 0;
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			if (LOWORD(wParam)== IDCANCEL) 
			{
				App->Cl_Dialogs->Canceled = 1;
				App->Cl_Dialogs->Active_Dlg_Float = 0;
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			break;
	}
    return FALSE;
}

// *************************************************************************
// *	  		Dialog_Int()  	Terry	Bernie							   *
// *************************************************************************
bool GD19_Dialogs::Dialog_Int()
{
	if (Active_Dlg_Int == 1)
	{
		return 1;
	}

	Active_Dlg_Int = 1;

	DialogBox(App->hInst,(LPCTSTR)IDD_EDITFLOAT,App->Fdlg,(DLGPROC)Dialog_Int_Proc);
	return 1;
}
// *************************************************************************
// *        	Dialog_Int_Proc  Terry	Bernie							   *
// *************************************************************************
LRESULT CALLBACK GD19_Dialogs::Dialog_Int_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
				
	switch (message)
	{
	case WM_INITDIALOG:
		{	
			App->SetTitleBar(hDlg);

			SendDlgItemMessage(hDlg, IDC_BANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

			SendDlgItemMessage(hDlg, IDC_EDIT1, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			

			SetDlgItemText(hDlg,IDC_BANNER,(LPCTSTR)App->Cl_Dialogs->btext);

			SetDlgItemText(hDlg,IDC_EDIT1,(LPCTSTR)App->Cl_Dialogs->Chr_Int);
			
			return TRUE;
		}
		case WM_CTLCOLORSTATIC:
		{
			
			if(GetDlgItem(hDlg,IDC_BANNER) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
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
			if (LOWORD(wParam) == IDOK) 
			{
				char buff[256];
				int result=0;
				GetDlgItemText(hDlg,IDC_EDIT1,(LPTSTR)buff,256);
				strcpy(App->Cl_Dialogs->Chr_Int,buff);
				App->Cl_Dialogs->mInt = atoi(buff);

				App->Cl_Dialogs->Canceled = 0;
				App->Cl_Dialogs->Active_Dlg_Int = 0;
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			if (LOWORD(wParam)== IDCANCEL) 
			{
				App->Cl_Dialogs->Canceled = 1;
				App->Cl_Dialogs->Active_Dlg_Int = 0;
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			break;
	}
    return FALSE;
}

// *************************************************************************
// *	  				 Dialog_Text	Terry Bernie					   *
// *************************************************************************
bool GD19_Dialogs::Dialog_Text(int Usage, bool CheckForSpaces)
{
	App->Cl_Dialogs->CheckNames = Usage;
	App->Cl_Dialogs->CheckSpaces = CheckForSpaces;

	DialogBox(App->hInst,(LPCTSTR)IDD_PROP_TEXT,App->Fdlg,(DLGPROC)Dialog_Text_Proc);
	return 1;
}
// *************************************************************************
// *				Dialog_Text_Proc	Terry Bernie  					   *
// *************************************************************************
LRESULT CALLBACK GD19_Dialogs::Dialog_Text_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{		
	switch (message)
	{
		case WM_INITDIALOG:
			{	

			App->SetTitleBar(hDlg);

			HFONT Font;
			Font = CreateFont( -20,0,0,0,FW_BOLD,0,0,0,0,OUT_TT_ONLY_PRECIS ,0,0,0, "Courier Black");
			SendDlgItemMessage(hDlg,IDC_TITLENAME, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

			SendDlgItemMessage(hDlg, IDC_EDITTEXT, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));

			SetDlgItemText(hDlg,IDC_TITLENAME,(LPCTSTR)App->Cl_Dialogs->btext);

			SetDlgItemText(hDlg,IDC_EDITTEXT,(LPCTSTR)App->Cl_Dialogs->Chr_Text);
			
				return TRUE;
			}
		case WM_CTLCOLORSTATIC:
		{
			if(GetDlgItem(hDlg,IDC_TITLENAME) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
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
					GetDlgItemText(hDlg,IDC_EDITTEXT,(LPTSTR)buff,255);

					// Checks for Spaces
					if (App->Cl_Dialogs->CheckSpaces == 1)
					{
						App->Cl_Utilities->TestForBadCharactors(buff);
						strcpy(buff,App->Cl_Utilities->Return_Chr);
					}

					// Checks name duplication Locations
					if (App->Cl_Dialogs->CheckNames == Enums::Check_Names_Locatoins)
					{
						int test = App->Cl_LookUps->Player_Location_CheckNames(buff);
						if (test == 1)
						{
							App->Say("Name Already Exsits");
							return 1;
						}
					}

					// Checks name duplication Objects
					if (App->Cl_Dialogs->CheckNames == Enums::Check_Names_Objects)
					{
						int test = App->SBC_LookUps->CheckNames_Objects(buff);
						if (test == 1)
						{
							App->Say("Name Already Exsits");
							return 1;
						}
					}

					strcpy(App->Cl_Dialogs->Chr_Text,buff);

					App->Cl_Dialogs->Canceled = 0;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
				}

				if (LOWORD(wParam)== IDCANCEL) 
				{
					App->Cl_Dialogs->Canceled = 1;
					EndDialog(hDlg, LOWORD(wParam));
					return TRUE;
				}
			}

			break;

	}
    return FALSE;
}

// *************************************************************************
// *	  					 TrueFlase Terry Bernie						   *
// *************************************************************************
bool GD19_Dialogs::Dialog_TrueFlase(HWND Parent)
{
	DialogBox(App->hInst,(LPCTSTR)IDD_GD_TRUEFALSE,Parent,(DLGPROC)Dialog_TrueFlase_Proc);
	return 1;
}
// *************************************************************************
// *						Dialog_TrueFlase_Proc	  					   *
// *************************************************************************
LRESULT CALLBACK GD19_Dialogs::Dialog_TrueFlase_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{		
	switch (message)
	{
		case WM_INITDIALOG:
			{	

			App->SetTitleBar(hDlg);

			SendDlgItemMessage(hDlg,IDC_TITLENAME, WM_SETFONT, (WPARAM)App->Font_Arial20,MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg,IDC_CHECKNO, WM_SETFONT, (WPARAM)App->Font_CB15,MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg,IDC_CHECKYES, WM_SETFONT, (WPARAM)App->Font_CB15,MAKELPARAM(TRUE, 0));

			SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

			SetDlgItemText(hDlg,IDC_TITLENAME,(LPCTSTR)App->Cl_Dialogs->btext);
			

			if (App->Cl_Dialogs->TrueFlase == 1)
			{
				HWND temp = GetDlgItem(hDlg,IDC_CHECKYES);
				SendMessage(temp,BM_SETCHECK,1,0);
				temp = GetDlgItem(hDlg,IDC_CHECKNO);
				SendMessage(temp,BM_SETCHECK,0,0);
			}
			else
			{
				HWND temp = GetDlgItem(hDlg,IDC_CHECKYES);
				SendMessage(temp,BM_SETCHECK,0,0);
				temp = GetDlgItem(hDlg,IDC_CHECKNO);
				SendMessage(temp,BM_SETCHECK,1,0);
			}
				return TRUE;
			}
		case WM_CTLCOLORSTATIC:
		{
			if(GetDlgItem(hDlg,IDC_TITLENAME) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
			}
			if(GetDlgItem(hDlg,IDC_CHECKYES) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
			}
			if(GetDlgItem(hDlg,IDC_CHECKNO) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
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
			if (LOWORD(wParam) == IDC_CHECKYES)
			{
				HWND temp = GetDlgItem(hDlg,IDC_CHECKYES);
				SendMessage(temp,BM_SETCHECK,1,0);
				temp = GetDlgItem(hDlg,IDC_CHECKNO);
				SendMessage(temp,BM_SETCHECK,0,0);	
				App->Cl_Dialogs->TrueFlase = 1;
			}

			if (LOWORD(wParam) == IDC_CHECKNO)
			{
				HWND temp = GetDlgItem(hDlg,IDC_CHECKNO);
				SendMessage(temp,BM_SETCHECK,1,0);
				temp = GetDlgItem(hDlg,IDC_CHECKYES);
				SendMessage(temp,BM_SETCHECK,0,0);	
				App->Cl_Dialogs->TrueFlase = 0;
			}
				
			if (LOWORD(wParam) == IDOK) 
			{
				App->Cl_Dialogs->Canceled = 0;
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			if (LOWORD(wParam)== IDCANCEL) 
			{
				App->Cl_Dialogs->Canceled = 1;
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			break;

	}
    return FALSE;
}


// *************************************************************************
// *	  					Start_Gen_ListBox Terry Bernie				   *
// *************************************************************************
void GD19_Dialogs::Start_Gen_ListBox(int ListType)
{
	mListType = ListType;

	DialogBox(App->hInst,(LPCTSTR)IDD_LISTDATA,App->Fdlg,(DLGPROC)Gen_ListBox_Proc);
}

// *************************************************************************
// *					Gen_ListBox_Proc Terry Bernie 					   *
// *************************************************************************
LRESULT CALLBACK GD19_Dialogs::Gen_ListBox_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG:
		{
			HFONT Font;
			Font = CreateFont( -15,0,0,0, 0,0,0,0,0,OUT_TT_ONLY_PRECIS ,0,0,0, "Aerial Black");
			SendDlgItemMessage(hDlg, IDC_LISTGROUP, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

			HWND List = GetDlgItem(hDlg, IDC_LISTGROUP);

			if(App->Cl_Dialogs->mListType == Enums::ListBox_Stock_Messages)
			{
				//App->Cl_Dialogs->List_Messages_Stock(List);
			}

			if(App->Cl_Dialogs->mListType == Enums::ListBox_Stock_Sounds)
			{
				//App->Cl_Dialogs->List_Sounds_Stock(List);
			}

			if(App->Cl_Dialogs->mListType == Enums::ListBox_Resource_Paths)
			{
				//App->Cl_Resources->Start_List_Folders(List,"",1);
			}

			if(App->Cl_Dialogs->mListType == Enums::ListBox_Resource_MeshMaterials)
			{
				//App->Cl_Resources->List_MeshMaterials(List);
			}

			if (App->Cl_Dialogs->mListType == Enums::ListBox_Resource_Folder)
			{
				App->Cl_Dialogs->Contents_Resource_Folder(List);
			}

			return TRUE;
		}

	case WM_CTLCOLORDLG:
		{
			return (LONG)App->AppBackground;
		}

		break;
	case WM_CTLCOLORSTATIC:
		{
			
			return FALSE;
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
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			break;
		}
	}
	return FALSE;
}

// *************************************************************************
// *	  				Contents_Resource_Folder Terry Bernie			   *
// *************************************************************************
void GD19_Dialogs::Contents_Resource_Folder(HWND List)
{
	SendMessage(List, LB_RESETCONTENT, 0, 0);
	char Path[MAX_PATH];
	strcpy(Path, App->SBC_Project->m_Main_Assets_Path);
	strcat(Path, "*.*");

	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(Path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {

			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) 
			{
				SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)fd.cFileName);
			}

		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
}

// *************************************************************************
// *	  					List_Messages_Stock Terry Bernie			   *
// *************************************************************************
void GD19_Dialogs::List_Messages_Stock(HWND List)
{
	SendMessage(List,LB_RESETCONTENT, 0,0);

	/*int Count = 0;
	while (Count < App->Cl_Panels_Com->Panel_Count)
	{
		SendMessage(List,LB_ADDSTRING, 0, (LPARAM) (LPCTSTR)App->Cl_Panels_Com->Get_Panel_Name(Count));
		Count++;
	}*/
}

// *************************************************************************
// *	  					List_Sounds_Stock Terry Bernie				   *
// *************************************************************************
void GD19_Dialogs::List_Sounds_Stock(HWND List)
{
	SendMessage(List,LB_RESETCONTENT, 0,0);

	//int Count = 0;
//	while (Count < App->Cl_Scene_Data->Stock_Sound_Count)
	{
//		SendMessage(List,LB_ADDSTRING, 0, (LPARAM) (LPCTSTR)App->Cl_Scene_Data->St_Sounds[Count]->Name);
		//Count++;
	}
}


// *************************************************************************
// *	  				Message Terry Bernie							   *
// *************************************************************************
void GD19_Dialogs::Message(char *pString)
{
	strcpy(Message_Text, pString);
	DialogBox(App->hInst, (LPCTSTR)IDD_MESSAGE, App->Fdlg, (DLGPROC)Message_Proc);
}
// *************************************************************************
// *        			Message_Proc  Terry	Bernie						   *
// *************************************************************************
LRESULT CALLBACK GD19_Dialogs::Message_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->SetTitleBar(hDlg);

		HFONT Font;
		Font = CreateFont(-20, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
		SendDlgItemMessage(hDlg, IDC_STTEXT, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BANNER, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_STTEXT, App->Cl_Dialogs->Message_Text);

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
			App->Cl_Dialogs->Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->Cl_Dialogs->Canceled = 1;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}





