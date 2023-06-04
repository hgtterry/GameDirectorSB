#include "StdAfx.h"
#include "AB_App.h"
#include "resource.h"
#include "SB_Ogre_Dialog.h"

SB_Ogre_Dialog::SB_Ogre_Dialog(void)
{
	OgreView_3D_hWnd = NULL;
	TestHwnd = NULL;
}

SB_Ogre_Dialog::~SB_Ogre_Dialog(void)
{
}

// *************************************************************************
// *			Switch_3D_Window:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Ogre_Dialog::Switch_3D_Window()
{
	//App->CL_Ogre->InitOgre();
	//Ogre::Root::getSingletonPtr()->renderOneFrame();

	App->CL_Ogre->mWindow->resize(500, 500);
	int test = SetWindowLong(App->CL_Ogre->Ogre_Window_hWnd, GWL_WNDPROC, (LONG)App->CL_Ogre_Dialog->Ogre3D_Proc);

	SetWindowLongPtr(App->CL_Ogre->Ogre_Window_hWnd, GWL_STYLE, WS_BORDER);
	SetWindowPos(App->CL_Ogre->Ogre_Window_hWnd, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
	ShowWindow(App->CL_Ogre->Ogre_Window_hWnd, SW_SHOW);

	SetWindowPos(App->CL_Ogre->Ogre_Window_hWnd, NULL, 4, 4, 820, 450, SWP_NOZORDER);
	
	HWND Check_hWnd = NULL;
	Check_hWnd = SetParent(App->CL_Ogre->Ogre_Window_hWnd, App->CL_Ogre_Dialog->TestHwnd);

	//if (!Check_hWnd)
	{
		//Debug
	}

	App->CL_Ogre->mWindow->resize(810, 400);
	App->CL_Ogre->mWindow->windowMovedOrResized();
	App->CL_Ogre->mCamera->setAspectRatio((Ogre::Real)App->CL_Ogre->mWindow->getWidth() / (Ogre::Real)App->CL_Ogre->mWindow->getHeight());
	App->CL_Ogre->mCamera->yaw(Ogre::Radian(0));

	App->CL_Ogre->OgreIsRunning = 1;
	App->CL_Ogre->Ogre_Render_Loop();
	
	if (App->CL_Ogre->OgreIsRunning == 1)
	{
		App->Say("xxx");
		delete App->CL_Ogre->mRoot;
		App->CL_Ogre->mRoot = NULL;
		App->CL_Ogre->OgreIsRunning = 0;
	}
}

// *************************************************************************
// *			Start_Ogre_Dialog:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Ogre_Dialog::Start_Ogre_Dialog()
{
	TestHwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_OGREVIEWER, App->MainHwnd, (DLGPROC)Ogre_Dialog_Proc);
	Switch_3D_Window();
}

// **************************************************************************
// *				Ogre_Dialog_Proc:- Terry and Hazel Flanigan 2022		*
// **************************************************************************
LRESULT CALLBACK SB_Ogre_Dialog::Ogre_Dialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

		SetDlgItemText(hDlg, IDC_TITLENAME, (LPCTSTR)App->SBC_Dialogs->btext);

		SetDlgItemText(hDlg, IDC_EDITTEXT, (LPCTSTR)App->SBC_Dialogs->Chr_Text);*/

		//App->CL_Ogre_Dialog->OgreView_3D_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_3D_VIEWER, hDlg, (DLGPROC)OgreView_3D_Proc);
		//App->CL_Ogre->RenderHwnd = App->CL_Ogre_Dialog->OgreView_3D_hWnd;

		//App->CL_Ogre->InitOgre();

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

	case WM_MOUSEMOVE: // ok up and running and we have a loop for mouse
	{
		//App->Flash_Window();
		//SetFocus(App->SBC_MeshViewer->MeshView_3D_hWnd);
		break;
	}

	case WM_RBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{
		
		//if (App->OgreStarted == 1)
		//{
		//	SetCapture(App->SBC_MeshViewer->MeshView_3D_hWnd);// Bernie
		//	SetCursorPos(App->CursorPosX, App->CursorPosY);
		//	App->SBC_MeshViewer->RenderListener->Pl_RightMouseDown = 1;
		//	App->CUR = SetCursor(NULL);
		//	return 1;
		//}

		return 1;
	}

	case WM_COMMAND:
	{
		
		if (LOWORD(wParam) == IDC_TEST)
		{
			App->CL_Ogre->OgreListener->StopOgre = 1;
			return TRUE;
		}

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
// *		OgreView_3D_Proc:- Terry and Hazel Flanigan 2023 			   *
// *************************************************************************
LRESULT CALLBACK SB_Ogre_Dialog::Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	//case WM_MOUSEWHEEL:
	//{
	//	if (App->SBC_MeshViewer->RenderListener->Pl_LeftMouseDown == 0)
	//	{
	//		{
	//			int zDelta = (short)HIWORD(wParam);    // wheel rotation

	//			if (zDelta > 0)
	//			{
	//				App->SBC_MeshViewer->RenderListener->Wheel_Move = -1;
	//			}
	//			else if (zDelta < 0)
	//			{
	//				App->SBC_MeshViewer->RenderListener->Wheel_Move = 1;
	//			}
	//			return 1;
	//		}
	//	}

	//}

	case WM_MOUSEMOVE: // ok up and running and we have a loop for mouse
	{
	//	//SetFocus(App->SBC_MeshViewer->MeshView_3D_hWnd);
		break;
	}

	// Right Mouse Button
	case WM_RBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{
		
		if (App->CL_Ogre->OgreIsRunning == 1)
		{
			SetCapture(App->CL_Ogre->Ogre_Window_hWnd);// Bernie
			SetCursorPos(App->CursorPosX, App->CursorPosY);
			App->CL_Ogre->OgreListener->Pl_RightMouseDown = 1;
			App->CUR = SetCursor(NULL);
			return 1;
		}

		return 1;
	}
	case WM_RBUTTONUP:
	{
		if (App->CL_Ogre->OgreIsRunning == 1)
		{
			ReleaseCapture();
			App->CL_Ogre->OgreListener->Pl_RightMouseDown = 0;
			SetCursor(App->CUR);
			return 1;
		}

		return 1;
	}

	// Left Mouse Button
	case WM_LBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{
		if (App->CL_Ogre->OgreIsRunning == 1)
		{
			SetCapture(App->CL_Ogre->Ogre_Window_hWnd);// Bernie
			SetCursorPos(App->CursorPosX, App->CursorPosY);

			App->CL_Ogre->OgreListener->Pl_LeftMouseDown = 1;

			App->CUR = SetCursor(NULL);

			return 1;
		}

		return 1;
	}

	case WM_LBUTTONUP:
	{

		if (App->CL_Ogre->OgreIsRunning == 1)
		{
			ReleaseCapture();
			App->CL_Ogre->OgreListener->Pl_LeftMouseDown = 0;
			SetCursor(App->CUR);
			return 1;
		}

		return 1;
	}
	//case WM_KEYDOWN:
	//	switch (wParam)
	//	{
	//	case 'C':
	//		if (GetAsyncKeyState(VK_CONTROL))
	//		{
	//			//		//		App->CL10_Objects_Com->Copy_Object();
	//			//		//		return 1;
	//		}
	//	case 'V':
	//		if (GetAsyncKeyState(VK_CONTROL))
	//		{
	//			//		//		App->CL10_Objects_Com->Paste_Object();
	//			//		//		return 1;
	//		}
	//		//	return 1;
	//		//	//	// more keys here
	//	}break;
	}

	return DefWindowProc(hDlg, message, wParam, lParam);
}