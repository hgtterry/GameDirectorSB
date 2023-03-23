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
#include "ME_Motions.h"


ME_Motions::ME_Motions()
{
	RightMotions_Hwnd = nullptr;

	Current_StartTime = 0;
	Current_EndTime = 0;

	RightMotions_Visable = 0;

	Selected_Motion_FV_Index = 0;

	Selected_Motion_Name[0] = 0;
	Decode_MotionByName[0] = 0;
}


ME_Motions::~ME_Motions()
{
}

// *************************************************************************
// *		Start_Motions_Dialog:- Terry and Hazel Flanigan 2023  	 	   *
// *************************************************************************
bool ME_Motions::Start_Motions_Dialog()
{
	RightMotions_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_RIGHTMOTIONS, App->MainHwnd, (DLGPROC)Motions_Proc);
	RightMotions_Visable = 0;

	return 1;
}

// *************************************************************************
// *	  Groups_Proc Terry Bernie:- Terry and Hazel Flanigan 2023	 	   *
// *************************************************************************
LRESULT CALLBACK ME_Motions::Motions_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_RGMOTIONNAME, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STSTART, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STEND, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STARTTIME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ENDTTIME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

	}

	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_RGMOTIONNAME) == (HWND)lParam)
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STSTART) == (HWND)lParam)
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STEND) == (HWND)lParam)
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STARTTIME) == (HWND)lParam)
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ENDTTIME) == (HWND)lParam)
		{
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

	case WM_CLOSE:
	{
		ShowWindow(App->CL_Motions->RightMotions_Hwnd, 0);
		App->CL_Motions->RightMotions_Visable = 0;
		//CheckMenuItem(App->mMenu, ID_WINDOWS_GROUPS, MF_BYCOMMAND | MF_UNCHECKED);*/
		break;
	}


	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDC_BTCHANGETEXTURE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTGROUPINFO && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		/*if (LOWORD(wParam) == IDC_BTCHANGETEXTURE)
		{
			if (App->CL_Model->Model_Loaded == 1)
			{
				App->CL_Panels->Enable_Panels(0);
				App->CL_Textures->ChangeTexture_Model();
				App->CL_Panels->Enable_Panels(1);
			}
			return TRUE;
		}*/
	}

	}
	return FALSE;
}

// *************************************************************************
// *			Update_Motions:- Terry and Hazel Flanigan 2023	 	 	   *
// *************************************************************************
bool ME_Motions::Update_Motions()
{

	if (App->CL_Model->Model_Type == Enums::LoadedFile_Actor)
	{
		App->CL_Genesis3D->GetMotion(Selected_Motion_Name);
	}

	if (App->CL_Model->ItsAnOgreModel == 1)
	{
		Ogre::SkeletonInstance *skeletonInstance = App->CL_Ogre3D->OgreModel_Ent->getSkeleton();
		if (skeletonInstance)
		{
			if (App->CL_Model->MotionCount > 0)
			{
				Ogre::Animation *Animation = skeletonInstance->getAnimation(Selected_Motion_Name);
				
				Current_StartTime = 0.00;
				Current_EndTime = Animation->getLength();
				
			}
		}

		Change_SelectedMotion(Selected_Motion_Name);
	}

	SetDlgItemText(RightMotions_Hwnd, IDC_RGMOTIONNAME, Selected_Motion_Name);


	char buf[20];
	sprintf(buf, "%f", Current_StartTime);
	SetDlgItemText(RightMotions_Hwnd, IDC_STARTTIME, buf);
	
	sprintf(buf, "%f", Current_EndTime);
	SetDlgItemText(RightMotions_Hwnd, IDC_ENDTTIME, buf);
	
	RightMotions_Visable = 1;
	ShowWindow(RightMotions_Hwnd, 1);
	
	App->CL_TopBar->Show_Animation_TB();
	
	App->CL_Ogre->Ogre_Listener->ImGui_Render_Tab = Enums::ImGui_Render_Model;

	return 1;
}

// *************************************************************************
// *		Change_SelectedMotion:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void ME_Motions::Change_SelectedMotion(char* mMotionName)
{
	bool retsart = 0;

	if (App->CL_Ogre->Ogre_Listener->Animate_Ogre == 1)
	{
		retsart = 1;
	}

	App->CL_Ogre->Ogre_Listener->Animate_Ogre = 0;

	Stop_SelectedMotion();

	App->CL_Ogre->Ogre_Listener->Animate_State = App->CL_Ogre3D->OgreModel_Ent->getAnimationState(mMotionName);
	//App->CL_Motions->Goto_KeyFrame_Ogre(0);

	if (retsart == 1)
	{
		App->CL_Ogre->Ogre_Listener->Animate_State->setEnabled(true);
		App->CL_Ogre->Ogre_Listener->Animate_Ogre = 1;
	}
}

// *************************************************************************
// *		Play_SelectedMotion:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void ME_Motions::Play_SelectedMotion(void)
{
	//------------------------------------------------------- RF Model
	if (App->CL_Model->Model_Loaded == 0) { return; }
	if (App->CL_Model->MotionCount == 0) { return; }

	if (App->CL_Model->Model_Type == Enums::LoadedFile_Actor)
	{
		App->CL_Genesis3D->m_CurrentPose = 0; // Reset to frame 0;
		App->CL_Genesis3D->GetMotion(App->CL_Genesis3D->MotionName);

		App->CL_Ogre->RenderListener->PlayActive = 1;

		//App->CL_Motions->PlayButtonActive = 1;
		//App->CL_Motions->TogglePlayBmp();
	}

	//------------------------------------------------------- Ogre3D Model
	if (App->CL_Model->ItsAnOgreModel == 1)
	{
		App->CL_Ogre->Ogre_Listener->Animate_State = App->CL_Ogre3D->OgreModel_Ent->getAnimationState(Selected_Motion_Name);
		App->CL_Ogre->Ogre_Listener->Animate_State->setEnabled(true);
		App->CL_Ogre->Ogre_Listener->Animate_Ogre = 1;

		//OgreMotionIsPlaying = 1;

		App->CL_Ogre3D->AnimationExtract_Mesh(1); // Get Default Pose Mesh
		App->CL_Ogre->Ogre_Listener->Animate_Ogre = 1;
		//App->CL_Motions->PlayButtonActive = 1;
		//App->CL_Motions->TogglePlayBmp();
	}
}

// *************************************************************************
// *		Stop_SelectedMotion:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void ME_Motions::Stop_SelectedMotion(void)
{
	if (App->CL_Model->Model_Loaded == 0) { return; }
	if (App->CL_Model->MotionCount == 0) { return; }

	//------------------------------------------------------- RF Model
	if (App->CL_Model->Model_Type == Enums::LoadedFile_Actor)
	{
		App->CL_Ogre->RenderListener->PlayActive = 0;
		//App->CL_Motions->PlayButtonActive = 0;
		//App->CL_Motions->TogglePlayBmp();
	}
	//------------------------------------------------------- Ogre3D Model
	if (App->CL_Model->ItsAnOgreModel == 1)
	{
		App->CL_Ogre->Ogre_Listener->Animate_Ogre = 0;
		App->CL_Ogre->Ogre_Listener->Animate_State->setEnabled(false);
		//OgreMotionIsPlaying = 0;

		//App->CL_Motions->PlayButtonActive = 0;
		//App->CL_Motions->TogglePlayBmp();
	}
}
