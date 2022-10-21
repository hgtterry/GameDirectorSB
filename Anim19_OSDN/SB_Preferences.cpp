/*
Copyright (c) 2021 EquitySB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

:- Terry and Hazel Flanigan 2022

*/

#include "stdafx.h"
#include "resource.h"
#include "GD19_App.h"
#include "SB_Preferences.h"

SB_Preferences::SB_Preferences()
{
	Main_Window_Hwnd = nullptr;
	FileView_Hwnd = nullptr;


	strcpy(Pref_Txl_Path_FileName, "Not_Set");

	strcpy(Pref_WE_JustFileName, "Not_Set");
	strcpy(Pref_WE_Path_FileName, "Not_Set");

	strcpy(Pref_Ogre_JustFileName, "Not_Set");
	strcpy(Pref_Ogre_Path, "Not_Set");
}

SB_Preferences::~SB_Preferences()
{
}

// *************************************************************************
// *						Write_Preferences Terry Flanigan 			   *
// *************************************************************************
bool SB_Preferences::Write_Preferences()
{
	WriteScene = NULL;

	char Preferences_Path[1024];

	strcpy(Preferences_Path, App->EquityDirecory_FullPath);;
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Preferences.ini");

	WriteScene = fopen(Preferences_Path, "wt");
	if (!WriteScene)
	{
		App->Say("Cant Create Save File");
		return 0;
	}

	fprintf(WriteScene, "%s\n", "[WE_Fast_Load]");
	fprintf(WriteScene, "%s%s\n", "Pref_WE_JustFileName=", Pref_WE_JustFileName);
	fprintf(WriteScene, "%s%s\n", "Pref_WE_Path_FileName=", Pref_WE_Path_FileName);
	fprintf(WriteScene, "%s%s\n", "Pref_Txl_Path_FileName=", Pref_Txl_Path_FileName);

	fprintf(WriteScene, "%s%s\n", "Pref_Ogre_JustFileName=", Pref_Ogre_JustFileName);
	fprintf(WriteScene, "%s%s\n", "Pref_Ogre_Path_FileName=", Pref_Ogre_Path);

	fprintf(WriteScene, "%s\n", " ");
	fclose(WriteScene);

	Read_Preferences();
	return 1;
}

// *************************************************************************
// *						Read_Preferences Terry Flanigan 			   *
// *************************************************************************
bool SB_Preferences::Read_Preferences()
{
	char chr_Tag1[1024];
	char chr_Tag2[1024];

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	char Preferences_Path[1024];

	strcpy(Preferences_Path, App->EquityDirecory_FullPath);
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Preferences.ini");

	App->Cl_Ini->SetPathName(Preferences_Path);

	App->Cl_Ini->GetString("WE_Fast_Load", "Pref_WE_JustFileName", chr_Tag1, 1024);
	strcpy(Pref_WE_JustFileName, chr_Tag1);

	App->Cl_Ini->GetString("WE_Fast_Load", "Pref_WE_Path_FileName", chr_Tag1, 1024);
	strcpy(Pref_WE_Path_FileName, chr_Tag1);

	App->Cl_Ini->GetString("WE_Fast_Load", "Pref_Txl_Path_FileName", chr_Tag2, 1024);
	strcpy(Pref_Txl_Path_FileName, chr_Tag2);

	App->Cl_Ini->GetString("WE_Fast_Load", "Pref_Ogre_JustFileName", chr_Tag2, 1024);
	strcpy(Pref_Ogre_JustFileName, chr_Tag2);

	App->Cl_Ini->GetString("WE_Fast_Load", "Pref_Ogre_Path_FileName", chr_Tag2, 1024);
	strcpy(Pref_Ogre_Path, chr_Tag2);

	//App->Say(chr_Tag1);

	return 1;
}

// *************************************************************************
// *	  	 Start_Preferences:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Preferences::Start_Preferences()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_PREFERENCES, App->Fdlg, (DLGPROC)Preferences_Proc);
	return 1;
}

// *************************************************************************
// *		  Preferences_Proc:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
LRESULT CALLBACK SB_Preferences::Preferences_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		/*App->SetTitleBar(hDlg);

		HFONT Font;
		Font = CreateFont(-20, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
		SendDlgItemMessage(hDlg, IDC_TITLENAME, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_EDITTEXT, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_TITLENAME, (LPCTSTR)App->Cl_Dialogs->btext);

		SetDlgItemText(hDlg, IDC_EDITTEXT, (LPCTSTR)App->Cl_Dialogs->Chr_Text);*/

		App->SBC_Prefs->Main_Window_Hwnd = hDlg;

		App->SBC_Prefs->FileView_Hwnd = GetDlgItem(hDlg, IDC_PREFTREE1);

		App->SBC_Prefs->AddRootFolder();

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_TITLENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
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

		/*if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
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
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
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
	}

	break;

	}
	return FALSE;
}

// *************************************************************************
// *		  AddRootFolder:- Terry and Hazel Flanigan 2022		 	 	   *
// *************************************************************************
void SB_Preferences::AddRootFolder(void)
{
	tvinsert.hParent = Root;			// top most level no need handle
	tvinsert.hInsertAfter = TVI_LAST; // work as root level
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "File";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_File = (HTREEITEM)SendDlgItemMessage(Main_Window_Hwnd, IDC_PREFTREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = FV_File;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Quick Load";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	SendDlgItemMessage(Main_Window_Hwnd, IDC_PREFTREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
}
