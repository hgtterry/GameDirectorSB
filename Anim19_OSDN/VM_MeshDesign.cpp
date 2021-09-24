#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "VM_MeshDesign.h"


VM_MeshDesign::VM_MeshDesign()
{
}


VM_MeshDesign::~VM_MeshDesign()
{
}

// *************************************************************************
// *				StartMeshDesign  Terry	Bernie						   *
// *************************************************************************
bool VM_MeshDesign::StartMeshDesign()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_MESHDESIGN, App->Fdlg, (DLGPROC)MeshDesign_Proc);
	return 1;
}

// *************************************************************************
// *						MeshDesign_Proc Terry Bernie				   *
// *************************************************************************
LRESULT CALLBACK VM_MeshDesign::MeshDesign_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		//App->Cl_Mesh_Viewer->MainDlgHwnd = hDlg;

		//SendDlgItemMessage(hDlg, IDC_LISTFILES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDC_OBJECTNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDC_STNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDC_STSHAPE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDC_STTYPE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDC_CB_FOLDERS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDC_STFOLDER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDC_SELECTEDNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));


		//App->Cl_Mesh_Viewer->ListHwnd = GetDlgItem(hDlg, IDC_LISTFILES);

		//HWND Ogre_Hwnd = GetDlgItem(hDlg, IDC_OGREWIN);
		//App->Cl_Mesh_Viewer->MeshView_Hwnd = GetDlgItem(hDlg, IDC_OGREWIN);
		//App->Cl_Mesh_Viewer->Set_OgreWindow();

		////App->Cl19_Ogre->textArea->hide();

		//Ogre::Root::getSingletonPtr()->renderOneFrame();
		//Ogre::Root::getSingletonPtr()->renderOneFrame();

		//HWND CB_hWnd = GetDlgItem(hDlg, IDC_CB_FOLDERS);
		//App->Cl_Mesh_Viewer->Get_Media_Folders_Actors(CB_hWnd); // Populate Combo


		//App->Cl_Mesh_Viewer->SelectStartFolder();

		//App->Cl_Mesh_Viewer->SelectStatic = 0;
		//App->Cl_Mesh_Viewer->SelectDynamic = 0;
		//App->Cl_Mesh_Viewer->SelectTriMesh = 0;

		//App->Cl_Mesh_Viewer->Enable_ShapeButtons(0);
		//App->Cl_Mesh_Viewer->Enable_TypeButtons(0);

		//App->Cl_Mesh_Viewer->Physics_Type = Enums::Bullet_Type_None;

		/*char ConNum[256];
		char ATest[256];

		App->Cl19_Ogre->OgreListener->GD_MeshViewer_Running = 1;*/


		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STNAME) == (HWND)lParam)
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
	case WM_HSCROLL:
	{


		return 1;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDC_CONE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Mesh_Viewer->Selected_Shape_Cone);
			return CDRF_DODEFAULT;
		}

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
		}*/

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