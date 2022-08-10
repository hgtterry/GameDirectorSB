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
	Chr_DropText[0] = 0;

	mFloat = 0;
	mInt = 0;

	mListType = Enums::ListBox_None;

	CheckNames = 0;

	DropList_Data = 0;

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

			HFONT Font2;
			Font2 = CreateFont( -20,0,0,0,FW_BOLD,0,0,0,0,OUT_TT_ONLY_PRECIS ,0,0,0, "Aerial Black");
			SendDlgItemMessage(hDlg,IDC_BANNER, WM_SETFONT, (WPARAM)Font2,MAKELPARAM(TRUE, 0));

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

	//DialogBox(App->hInst,(LPCTSTR)IDD_EDITFLOAT,App->Fdlg,(DLGPROC)Dialog_Int_Proc);
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

			HFONT Font2;
			Font2 = CreateFont( -20,0,0,0,FW_BOLD,0,0,0,0,OUT_TT_ONLY_PRECIS ,0,0,0, "Aerial Black");
		//	SendDlgItemMessage(hDlg,IDC_BANNER, WM_SETFONT, (WPARAM)Font2,MAKELPARAM(TRUE, 0));

		//	SendDlgItemMessage(hDlg,IDC_EDIT1, WM_SETFONT, (WPARAM)App->Font_CB15,MAKELPARAM(TRUE, 0));
			

		//	SetDlgItemText(hDlg,IDC_BANNER,(LPCTSTR)App->Cl_Dialogs->btext);

		//	SetDlgItemText(hDlg,IDC_EDIT1,(LPCTSTR)App->Cl_Dialogs->Chr_Int);
			
			return TRUE;
		}
		case WM_CTLCOLORSTATIC:
		{
			
			/*if(GetDlgItem(hDlg,IDC_BANNER) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
			}*/
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
			//	GetDlgItemText(hDlg,IDC_EDIT1,(LPTSTR)buff,256);
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
bool GD19_Dialogs::Dialog_Text(int Usage)
{
	CheckNames = Usage;

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

					/*if (App->Cl_Dialogs->CheckForSpaces == 1)
					{
						App->Cl_Utilities->TestForBadCharactors(buff);
						strcpy(buff,App->Cl_Utilities->Return_Chr);
					}*/

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
						int test = App->Cl_LookUps->Check_Objects_CheckNames(buff);
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

			HFONT Font2;
			Font2 = CreateFont( -20,0,0,0,FW_BOLD,0,0,0,0,OUT_TT_ONLY_PRECIS ,0,0,0, "Aerial Black");

			SendDlgItemMessage(hDlg,IDC_TITLENAME, WM_SETFONT, (WPARAM)Font2,MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg,IDC_CHECKNO, WM_SETFONT, (WPARAM)App->Font_CB15,MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg,IDC_CHECKYES, WM_SETFONT, (WPARAM)App->Font_CB15,MAKELPARAM(TRUE, 0));

		//	SetDlgItemText(hDlg,IDC_TITLENAME,(LPCTSTR)App->Cl_Dialogs->btext);
			

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
// *	  			  Dialog_DropGen Terry Bernie						   *
// *************************************************************************
bool GD19_Dialogs::Dialog_DropGen()
{
	//DialogBox(App->hInst,(LPCTSTR)IDD_DROPGEN,App->Fdlg,(DLGPROC)Dialog_DropGen_Proc);
	return 1;
}
// *************************************************************************
// *			Dialog_DropGen2_Proc Terry	Bernie						   *
// *************************************************************************
LRESULT CALLBACK GD19_Dialogs::Dialog_DropGen_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
				
	switch (message)
	{
	case WM_INITDIALOG:
		{	
		
			App->SetTitleBar(hDlg);

			/*SendDlgItemMessage(hDlg,IDC_TITLE, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg,IDC_CBGEN, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

			SetDlgItemText(hDlg,IDC_TITLE,(LPCTSTR)App->Cl_Dialogs->btext);*/
			
		//	HWND temp = GetDlgItem(hDlg,IDC_CBGEN);

			if(App->Cl_Dialogs->DropList_Data == Enums::DropDialog_TrigMoveObject)
			{
				//App->Cl_Dialogs->ListObjects(temp);
				return TRUE;
			}

			if(App->Cl_Dialogs->DropList_Data == Enums::DropDialog_TrigMoveAxis)
			{
				//App->Cl_Dialogs->ListAxis(temp);
				return TRUE;
			}

			if (App->Cl_Dialogs->DropList_Data == Enums::DropDialog_Locations)
			{
				//App->Cl_Dialogs->List_Locations(temp);
				return TRUE;
			}
			
	
			return TRUE;
		}
		case WM_CTLCOLORSTATIC:
		{
			
			//if(GetDlgItem(hDlg,IDC_TITLE) == (HWND)lParam)
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
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK) 
			{
				char buff[256];
				//GetDlgItemText(hDlg,IDC_CBGEN,(LPTSTR)buff,256);
				strcpy(App->Cl_Dialogs->Chr_DropText,buff);

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

//	DialogBox(App->hInst,(LPCTSTR)IDD_GENLIST2,App->Fdlg,(DLGPROC)Gen_ListBox_Proc);
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
			//SendDlgItemMessage(hDlg,IDC_LIST1, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

		//	HWND List = GetDlgItem(hDlg,IDC_LIST1);

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
// *	  					List_Messages_Stock Terry Bernie			   *
// *************************************************************************
void GD19_Dialogs::List_Messages_Stock(HWND List)
{
	SendMessage(List,LB_RESETCONTENT, 0,0);

	int Count = 0;
	while (Count < App->Cl_Panels_Com->Panel_Count)
	{
		SendMessage(List,LB_ADDSTRING, 0, (LPARAM) (LPCTSTR)App->Cl_Panels_Com->Get_Panel_Name(Count));
		Count++;
	}
}

// *************************************************************************
// *	  					List_Sounds_Stock Terry Bernie				   *
// *************************************************************************
void GD19_Dialogs::List_Sounds_Stock(HWND List)
{
	SendMessage(List,LB_RESETCONTENT, 0,0);

	int Count = 0;
	while (Count < App->Cl_Scene_Data->Stock_Sound_Count)
	{
		SendMessage(List,LB_ADDSTRING, 0, (LPARAM) (LPCTSTR)App->Cl_Scene_Data->St_Sounds[Count]->Name);
		Count++;
	}
}

// *************************************************************************
// *					ListObjects Terry Bernie				 		   *
// *************************************************************************
void GD19_Dialogs::ListObjects(HWND DropHwnd)
{
	int Count = 0;
	int Total = App->Cl_Scene_Data->ObjectCount;

	while (Count < Total)
	{
		{
			if (App->Cl_Scene_Data->Cl_Object[Count]->Type == Enums::Bullet_Type_Static)
			{
				if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Static)
				{
					SendMessage(DropHwnd, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->Cl_Scene_Data->Cl_Object[Count]->Name);
				}
			}
		}

		Count++;
	}

	SendMessage(DropHwnd, CB_SETCURSEL ,0,0);
}

// *************************************************************************
// *					List_Locations Terry Bernie				 		   *
// *************************************************************************
void GD19_Dialogs::List_Locations(HWND DropHwnd)
{
	int Count = 0;
	while (Count < App->Cl_Scene_Data->Player_Location_Count)
	{
		if (App->Cl_Scene_Data->S_Player_Locations[Count]->Deleted == 0)
		{
			SendMessage(DropHwnd, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->Cl_Scene_Data->S_Player_Locations[Count]->Name);
		}
		Count++;
	}

	SendMessage(DropHwnd, CB_SETCURSEL, 0, 0);
}

// *************************************************************************
// *					ListAxis Terry Bernie					 		   *
// *************************************************************************
void GD19_Dialogs::ListAxis(HWND DropHwnd)
{
	int Count = 0;
	bool Any = 0;
	
	SendMessage(DropHwnd, CB_ADDSTRING, 0,(LPARAM)"X");
	SendMessage(DropHwnd, CB_ADDSTRING, 0,(LPARAM)"Y");
	SendMessage(DropHwnd, CB_ADDSTRING, 0,(LPARAM)"Z");
		
	SendMessage(DropHwnd, CB_SETCURSEL ,0,0);
}

// *************************************************************************
// *	  					  GameMode_StartPosition_Dlg()				   *
// *************************************************************************
bool GD19_Dialogs::GameMode_StartPosition_Dlg()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_GMSTART, App->Fdlg, (DLGPROC)GameMode_StartPosition_Dlg_Proc);
	return 1;
}
// *************************************************************************
// *					Dialog_GameModeStart_Dlg_Proc	  				   *
// *************************************************************************
LRESULT CALLBACK GD19_Dialogs::GameMode_StartPosition_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->Cl_Dialogs->Canceled = 0;
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_STARTCUR && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_STARTLEVEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_QUITGM && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}
	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_STARTCUR)
		{
			App->Cl_Dialogs->Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return 1;
		}

		if (LOWORD(wParam) == IDC_STARTLEVEL)
		{
			App->Cl_Bullet->Reset_Physics();
			App->Cl_Dialogs->Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			App->Cl_Dialogs->Canceled = 1;
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_QUITGM)
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
// *	  					 YesNo Terry Bernie							   *
// *************************************************************************
void GD19_Dialogs::YesNo(char *Text, char *Text2)
{
	App->Cl_Dialogs->Canceled = 0;
	strcpy(MessageString, Text);
	strcpy(MessageString2, Text2);

	DialogBox(App->hInst, (LPCTSTR)IDD_YESNO, App->Fdlg, (DLGPROC)YesNo_Proc);
}
// *************************************************************************
// *					YesNo_Proc_Proc Terry Bernie	  				   *
// *************************************************************************
LRESULT CALLBACK GD19_Dialogs::YesNo_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->SetTitleBar(hDlg);

		SendDlgItemMessage(hDlg, IDC_BANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTEXT, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_BANNER, App->Cl_Dialogs->MessageString);
		SetDlgItemText(hDlg, IDC_STTEXT, App->Cl_Dialogs->MessageString2);
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

// *************************************************************************
// *	  				Start_Projection Terry Bernie					   *
// *************************************************************************
void GD19_Dialogs::Start_Projection()
{
	if (Location_Dlg_Active == 1)
	{
		Location_Dlg_Active = 0;
		EndDialog(LocationDlg_hWnd, 0);
		return;
	}

	Location_Dlg_Active = 1;

	LocationDlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PROJECTION, App->Fdlg, (DLGPROC)Projection_Proc);
}
// *************************************************************************
// *					Projection_Proc Terry Bernie		 			   *
// *************************************************************************
LRESULT CALLBACK GD19_Dialogs::Projection_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->Cl_Dialogs->ListBox_Index = 0;
		SendDlgItemMessage(hDlg, IDC_STBANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		//App->Cl_World->Store_Location();

		SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CKMOVECAM, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		SendDlgItemMessage(hDlg, IDC_CKMOVECAM, BM_SETCHECK, 1, 0);

		int Count = 0;
		while (Count < App->Cl_Scene_Data->Player_Location_Count)
		{
			if (App->Cl_Scene_Data->S_Player_Locations[Count]->Deleted == 0)
			{
				SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)App->Cl_Scene_Data->S_Player_Locations[Count]->Name);
			}
			Count++;
		}

		SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);

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
		if (GetDlgItem(hDlg, IDC_CKMOVECAM) == (HWND)lParam)
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

		if (some_item->idFrom == IDC_BTSAVE_LOCATION_PLAYER && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTMOVE_PLAYER && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTEDITT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTDELETE && some_item->code == NM_CUSTOMDRAW)
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

		// Rename
		if (LOWORD(wParam) == IDC_BTEDITT)
		{
			int Index = App->Cl_Dialogs->ListBox_Index;
			if (Index == 0)
			{
				App->Say("Start Location can not be Edited");
				return 1;
			}

			char buff[255];
			SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_GETTEXT, (WPARAM)Index, (LPARAM)(LPCTSTR)buff);

			int Location_Index = App->Cl_LookUps->Player_Location_GetIndex_ByName(buff); // Get by Referance (Name)

			strcpy(App->Cl_Dialogs->btext, "Location Name");

			char numbuf[255];
			_itoa(App->Cl_Scene_Data->Player_Location_Count, numbuf, 10);

			strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Scene_Data->S_Player_Locations[Location_Index]->Name);

			App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Locatoins);

			if (App->Cl_Dialogs->Canceled == 1)
			{
				return TRUE;
			}


			strcpy(App->Cl_Scene_Data->S_Player_Locations[Location_Index]->Name, App->Cl_Dialogs->Chr_Text);

			SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
			int Count = 0;
			while (Count < App->Cl_Scene_Data->Player_Location_Count)
			{

				if (App->Cl_Scene_Data->S_Player_Locations[Count]->Deleted == 0)
				{
					SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)App->Cl_Scene_Data->S_Player_Locations[Count]->Name);
				}

				Count++;
			}

			SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_SETCURSEL, (WPARAM)Index, (LPARAM)(LPCTSTR)0);
			return TRUE;
		}

		// Delete Location
		if (LOWORD(wParam) == IDC_BTDELETE)
		{

			int Index = App->Cl_Dialogs->ListBox_Index;
			if (Index == 0)
			{
				App->Say("Start Location can not be deleted");
				return 1;
			}

			char buff[255];
			SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_GETTEXT, (WPARAM)Index, (LPARAM)(LPCTSTR)buff);

			int Location_Index = App->Cl_LookUps->Player_Location_GetIndex_ByName(buff); // Get by Referance (Name)

			char tag[255];
			strcpy(tag, "Delete Location  ");
			strcat(tag, App->Cl_Scene_Data->S_Player_Locations[Location_Index]->Name);

			App->Cl_Dialogs->YesNo(tag, "Are you sure");
			if (App->Cl_Dialogs->Canceled == 0)
			{
				App->Cl_Scene_Data->S_Player_Locations[Location_Index]->Deleted = 1;
				SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
				int Count = 0;
				while (Count < App->Cl_Scene_Data->Player_Location_Count)
				{
					if (App->Cl_Scene_Data->S_Player_Locations[Count]->Deleted == 0)
					{
						SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)App->Cl_Scene_Data->S_Player_Locations[Count]->Name);
					}

					Count++;
				}
			}

			//SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_BTMOVE_PLAYER)
		{
			int Index = App->Cl_Dialogs->ListBox_Index;
			char buff[255];
			SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_GETTEXT, (WPARAM)Index, (LPARAM)(LPCTSTR)buff);

			int Location_Index = App->Cl_LookUps->Player_Location_GetIndex_ByName(buff); // Get by Referance (Name)

			if (Location_Index > -1)
			{
				App->SBC_Player->Goto_Location(Location_Index);

				HWND temp = GetDlgItem(hDlg, IDC_CKMOVECAM);
				int test = SendMessage(temp, BM_GETCHECK, 0, 0);
				if (test == BST_CHECKED)
				{
					App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;
					Root::getSingletonPtr()->renderOneFrame();
					Root::getSingletonPtr()->renderOneFrame();
					App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;
				}
			}
			else
			{
				App->Say("Cant Find Location");
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTSAVE_LOCATION_PLAYER)
		{
			strcpy(App->Cl_Dialogs->btext, "Location Name");

			char buf[255];
			char numbuf[255];
			_itoa(App->Cl_Scene_Data->Player_Location_Count, numbuf, 10);

			strcpy(buf, "New_Location_");
			strcat(buf, numbuf);
			strcpy(App->Cl_Dialogs->Chr_Text, buf);

			App->Cl_Dialogs->Dialog_Text(1);

			if (App->Cl_Dialogs->Canceled == 1)
			{
				return TRUE;
			}

			strcpy(buf, App->Cl_Dialogs->Chr_Text);
			App->SBC_Player->Save_Location(buf);

			SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)buf);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_LSTLOCATIONS)
		{
			int Index = 0;

			Index = SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			if (Index == -1)
			{
				return 1;
			}

			App->Cl_Dialogs->ListBox_Index = Index;

			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->Cl_Dialogs->Location_Dlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

// *************************************************************************
// *	  				Dialog_OgreReloadMesh Terry Bernie				   *
// *************************************************************************
void GD19_Dialogs::Start_DataView()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_DATAVIEW, App->Fdlg, (DLGPROC)Start_DataView_Proc);
}
// *************************************************************************
// *				Dialog_OgreReloadMesh_Proc Terry Bernie	  			   *
// *************************************************************************
LRESULT CALLBACK GD19_Dialogs::Start_DataView_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_LISTDATA, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		char buf[255];

		sprintf(buf, "%s", "Model Info   ");
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s", "    ");
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		////----------------------- 
	
		sprintf(buf, "%s%s", "Level Directory   ", App->LevelDirectory);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s%s", "Level Name   ", App->Cl_Scene_Data->S_Scene[0]->LevelName);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s", "    ");
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);


		sprintf(buf, "%s%s", "Scene Version    ", App->Cl_Scene_Data->S_Scene[0]->SceneVersion);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s%i", "Scene Type    ", App->Cl_Scene_Data->S_Scene[0]->SceneType);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s%s", "Terrian ", App->Cl_Scene_Data->S_Scene[0]->TerrainFileName);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s", "    ");
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		sprintf(buf, "%s%i", "Collision_Objects    ", App->Cl_Bullet->dynamicsWorld->getNumCollisionObjects() - 1);
		SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		return TRUE;
	}
	/*case WM_CTLCOLORSTATIC:
	{
	
	}
	return FALSE;
	}*/

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDC_GROUPS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_ENVIRO && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_SOUND && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CAMARA && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_FOG && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_OPTIONS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}
		if (some_item->idFrom == IDC_BTLEVEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}
	case WM_COMMAND:

		/*if (LOWORD(wParam) == IDC_BT_USER_FOLDERS)
		{
			char buf[255];
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

			int Count = 0;
			while (Count < App->Cl_Ogre->UserFile_Count)
			{
				strcpy(buf, App->Cl_Ogre->User_File[Count].c_str());
				SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
				Count++;
			}
			return 1;
		}*/

		/*if (LOWORD(wParam) == IDC_BTLEVEL)
		{
			char buf[255];
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

			sprintf(buf, "%s%s", "GDSceneName    ", App->Cl_Scene_Data->S_Scene[0]->GDSceneName);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s%s", "Level Directory   ", App->LevelDirectory);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s%s", "Level Name   ", App->Cl_Scene_Data->S_Scene[0]->LevelName);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s", "    ");
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);


			sprintf(buf, "%s%s", "Scene Version    ", App->Cl_Scene_Data->S_Scene[0]->SceneVersion);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s%i", "Scene Type    ", App->Cl_Scene_Data->S_Scene[0]->SceneType);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s%s", "Terrian ", App->Cl_Scene_Data->S_Scene[0]->TerrainFileName);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s", "    ");
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			return 1;
		}*/

		/*if (LOWORD(wParam) == IDC_OPTIONS)
		{
			char buf[255];
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

			sprintf(buf, "%s %i", "Has Planes  ", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Planes);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s %i", "Has Objects  ", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Objects);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s %i", "Has Particles  ", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Particles);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s %i", "Has Weapons  ", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Weapons);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s %i", "Has Player  ", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Player);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s %i", "Has Debug  ", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Debug);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			return 1;
		}*/

		/*if (LOWORD(wParam) == IDC_FOG)
		{
			char buf[255];
			float w = 0;
			float x = 0;
			float y = 0;
			float z = 0;

			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

			sprintf(buf, "%s %i", "Visible  ", App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s %i", "Mode  ", App->Cl_Scene_Data->S_Scene[0]->Fog[0].Mode);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s %f %f %f", "Colour  ", App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.x, App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.y, App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.z);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s %f", "Density  ", App->Cl_Scene_Data->S_Scene[0]->Fog[0].Density);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s %f", "Start  ", App->Cl_Scene_Data->S_Scene[0]->Fog[0].Start);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s %f", "End  ", App->Cl_Scene_Data->S_Scene[0]->Fog[0].End);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
			return 1;
		}*/

		/*if (LOWORD(wParam) == IDC_CAMARA)
		{
			char buf[255];
			float w = 0;
			float x = 0;
			float y = 0;
			float z = 0;

			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

			sprintf(buf, "%s%f", "Camera Height  ", App->Cl_Scene_Data->S_Camera[0]->CameraHeight);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s", "    ");
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			x = App->Cl_Scene_Data->S_Camera[0]->PosX;
			y = App->Cl_Scene_Data->S_Camera[0]->PosY;
			z = App->Cl_Scene_Data->S_Camera[0]->PosZ;

			sprintf(buf, "%s", "Start Position");
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "(X) %f (Y) %f (Z) %f", x, y, z);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			w = App->Cl_Scene_Data->S_Camera[0]->RotW;
			x = App->Cl_Scene_Data->S_Camera[0]->RotX;
			y = App->Cl_Scene_Data->S_Camera[0]->RotY;
			z = App->Cl_Scene_Data->S_Camera[0]->RotZ;

			sprintf(buf, "(W) %f (X) %f (Y) %f (Z) %f", w, x, y, z);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s", "    ");
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s%f", "Walk Speed  ", App->Cl_Scene_Data->S_Camera[0]->WalkSpeed);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s%f", "Run Speed  ", App->Cl_Scene_Data->S_Camera[0]->RunSpeed);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			return 1;
		}*/

		/*if (LOWORD(wParam) == IDC_SOUND)
		{
			char buf[255];
			float a = 0;
			float b = 0;
			float c = 0;

			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

			if (App->Cl_SoundMgr->SoundFile_Count > 0)
			{
				int Count = 0;
				while (Count < App->Cl_SoundMgr->SoundFile_Count)
				{
					sprintf(buf, "%s%s", "Sound File  ", App->Cl_SoundMgr->Sound_File);
					SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)App->Cl_SoundMgr->Sound_File[Count].c_str());
					Count++;
				}
			}
			else
			{
				SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)"No Sound Files Loaded");
			}

			return 1;
		}*/

		/*if (LOWORD(wParam) == IDC_ENVIRO)
		{
			char buf[255];
			float a = 0;
			float b = 0;
			float c = 0;

			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

			a = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.x;
			b = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.y;
			c = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.z;

			sprintf(buf, "%s%f %f %f", "Ambient  ", a, b, c);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			a = App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.x;
			b = App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.y;
			c = App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.z;

			sprintf(buf, "%s%f %f %f", "Diffuse  ", a, b, c);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			a = App->Cl_Scene_Data->S_Scene[0]->SpecularColour.x;
			b = App->Cl_Scene_Data->S_Scene[0]->SpecularColour.y;
			c = App->Cl_Scene_Data->S_Scene[0]->SpecularColour.z;

			sprintf(buf, "%s%f %f %f", "Specular  ", a, b, c);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			return 1;
		}
		*/
		if (LOWORD(wParam) == IDC_OBJECTS)
		{
			char buf[255];
			float w = 0;
			float x = 0;
			float y = 0;
			float z = 0;

			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

			sprintf(buf, "%s%i", "Object Count    ", App->Cl_Scene_Data->ObjectCount);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s%i", "Next Object    ", App->Cl_Scene_Data->NewObjectID);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s", "    ");
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			int Index = 0;

			while (Index < App->Cl_Scene_Data->ObjectCount)
			{
				sprintf(buf, "%s", "    ");
				SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

				sprintf(buf, "%s%i", "Object_ID:-    ", App->Cl_Scene_Data->Cl_Object[Index]->Object_ID);
				SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

				sprintf(buf, "Usage %i", App->Cl_Scene_Data->Cl_Object[Index]->Usage);
				SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

				sprintf(buf, "%s%s", "Name:-    ", App->Cl_Scene_Data->Cl_Object[Index]->Name);
				SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

				sprintf(buf, "%s%s", "Mesh Name:-    ", App->Cl_Scene_Data->Cl_Object[Index]->MeshName);
				SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

				sprintf(buf, "%s%s", "Mesh Path:-    ", App->Cl_Scene_Data->Cl_Object[Index]->MeshName_FullPath);
				SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

				x = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.x;
				y = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.y;
				z = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.z;

				sprintf(buf, "Position (X) %f (Y) %f (Z) %f", x, y, z);
				SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

				x = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.x;
				y = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.y;
				z = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.z;

				sprintf(buf, "Rotation (X) %f (Y) %f (Z) %f", x, y, z);
				SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

				x = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.x;
				y = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.y;
				z = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.z;

				sprintf(buf, "Scale (X) %f (Y) %f (Z) %f", x, y, z);
				SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

				if (App->Cl_Scene_Data->Cl_Object[Index]->Usage == Enums::Usage_Move)
				{
					sprintf(buf, "%s%s", "Move_Object:-    ", App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->Object_Name);
					SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

					sprintf(buf, "%s%i", "Object_Index:-    ", App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->Object_Index);
					SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

					sprintf(buf, "%s%i", "Object_ID:-    ", App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->Object_ID);
					SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
				}

				sprintf(buf, "%s%i", "Has_Sound:-    ", App->Cl_Scene_Data->Cl_Object[Index]->HasSound);
				SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

				Index++;
			}

			sprintf(buf, "%s", "    ");
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			sprintf(buf, "%s%i", "Next_Object_ID:-    ", App->Cl_Scene_Data->Object_ID_Counter);
			SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

			return TRUE;
		}

		//if (LOWORD(wParam) == IDC_TEST)
		//{
		//	//SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		//	//char buf[256];
		//	//Ogre::Vector3 OgrePosition;
		//	//OgrePosition = App->Cl_Ogre->mCamera->getPosition();

		//	//float width = (float)App->Cl_Ogre->mCamera->getViewport()->getActualWidth(); // viewport width
		//	//float ty = (float)(OgrePosition.x / width);

		//	//Ray ray = App->Cl_Ogre->mCamera->getCameraToViewportRay(ty, 0);

		//	//sprintf(buf, "%s%f", "Camera Width = ", width);
		//	//SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		//	//sprintf(buf, "%s%f", "Cam X = ", OgrePosition.x);
		//	//SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		//	//sprintf(buf, "%s%f", "Cam to Viewport = ", ray.getOrigin().x);
		//	//SendDlgItemMessage(hDlg, IDC_LISTDATA, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

		//	return TRUE;
		//}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;

	}
	return FALSE;
}


