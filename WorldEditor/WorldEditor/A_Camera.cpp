/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "AB_App.h"
#include "A_Camera.h"

#include "Entity.h"

A_Camera::A_Camera(void)
{
	pCameraEntity = NULL;

	CameraPosition.X = 0;
	CameraPosition.Y = 0;
	CameraPosition.Z = 0;

	Angles.X = 0;
	Angles.Y = 0;
	Angles.Z = 0;
}

A_Camera::~A_Camera(void)
{
}

// *************************************************************************
// *	  		Start_Move_Camera:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_Camera::Start_Move_Camera()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	pCameraEntity = m_pDoc->FindCameraEntity();

	CameraPosition = pCameraEntity->mOrigin;


	DialogBox(App->hInst, (LPCTSTR)IDD_SB_MOVECAMERA, App->MainHwnd, (DLGPROC)Move_Camera_Proc);

}
// *************************************************************************
// *        Move_Camera_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_Camera::Move_Camera_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_STCAMERA, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STPOSITION, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STANGLES, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STCAMX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EDCAMX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STCAMY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EDCAMY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STCAMZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EDCAMZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));


		SendDlgItemMessage(hDlg, IDC_STCAMANGLEX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EDCAMANGLEX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STCAMANGLEY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EDCAMANGLEY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STCAMANGLEZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EDCAMANGLEZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BTRESETPOSITION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTRESETANGLES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		char buf[255];

		sprintf(buf, "%f", App->CL_Camera->CameraPosition.X);
		SetDlgItemText(hDlg, IDC_EDCAMX,buf);

		sprintf(buf, "%f", App->CL_Camera->CameraPosition.Y);
		SetDlgItemText(hDlg, IDC_EDCAMY,buf);

		sprintf(buf, "%f", App->CL_Camera->CameraPosition.Z);
		SetDlgItemText(hDlg, IDC_EDCAMZ,buf);


		geVec3d Angles;
		App->CL_Camera->pCameraEntity->GetAngles( &Angles, Level_GetEntityDefs (App->CL_Camera->m_pDoc->pLevel) );

		sprintf(buf, "%f", Angles.X);
		SetDlgItemText(hDlg, IDC_EDCAMANGLEX,buf);

		sprintf(buf, "%f", Angles.Y);
		SetDlgItemText(hDlg, IDC_EDCAMANGLEY,buf);

		sprintf(buf, "%f", Angles.Z);
		SetDlgItemText(hDlg, IDC_EDCAMANGLEZ,buf);

		return TRUE;

	}
	case WM_CTLCOLORSTATIC:
	{

		if (GetDlgItem(hDlg, IDC_STCAMERA) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STPOSITION) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STANGLES) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STCAMX) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STCAMY) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STCAMZ) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STCAMANGLEX) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STCAMANGLEY) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STCAMANGLEZ) == (HWND)lParam)
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

	case WM_DRAWITEM:
		{

			LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT)lParam;

			if (lpDIS->CtlID == IDC_BTRESETPOSITION)
			{
				App->Custom_Button_Normal_MFC(lpDIS,hDlg);
				return TRUE;
			}

			if (lpDIS->CtlID == IDC_BTRESETANGLES)
			{
				App->Custom_Button_Normal_MFC(lpDIS,hDlg);
				return TRUE;
			}

			return TRUE;
		}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BTRESETANGLES)
		{
	
			App->CL_Camera->Reset_Camera_Angles();

			char buf[100];

			sprintf(buf, "%f", App->CL_Camera->Angles.X);
			SetDlgItemText(hDlg, IDC_EDCAMANGLEX,buf);

			sprintf(buf, "%f", App->CL_Camera->Angles.Y);
			SetDlgItemText(hDlg, IDC_EDCAMANGLEY,buf);

			sprintf(buf, "%f", App->CL_Camera->Angles.Z);
			SetDlgItemText(hDlg, IDC_EDCAMANGLEZ,buf);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTRESETPOSITION)
		{
	
			App->CL_Camera->Reset_Camera_Position();

			char buf[100];

			sprintf(buf, "%f", App->CL_Camera->CameraPosition.X);
			SetDlgItemText(hDlg, IDC_EDCAMX,buf);

			sprintf(buf, "%f", App->CL_Camera->CameraPosition.Y);
			SetDlgItemText(hDlg, IDC_EDCAMY,buf);

			sprintf(buf, "%f", App->CL_Camera->CameraPosition.Z);
			SetDlgItemText(hDlg, IDC_EDCAMZ,buf);

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDOK)
		{
			//App->CL_Camera->pCameraEntity->mOrigin.X = 0;//App->CL_Camera->CameraPosition;
			//App->CL_Camera->pCameraEntity->mOrigin.Y = 0;
			//App->CL_Camera->pCameraEntity->mOrigin.Z = 0;

			App->CL_Camera->Get_Values_Dlg(hDlg);

			//geVec3d Angles2 = ;
			//Angles.X = 3.141593; // Radians
			//Angles.Y = 0;
			//Angles.Z = 0;

			App->CL_Camera->pCameraEntity->SetAngles(&App->CL_Camera->Angles, Level_GetEntityDefs (App->CL_Camera->m_pDoc->pLevel) );

			App->CL_Camera->m_pDoc->SetRenderedViewCamera( &(App->CL_Camera->pCameraEntity->mOrigin), &App->CL_Camera->Angles) ;
			App->CL_Camera->m_pDoc->UpdateAllViews( UAV_ALLVIEWS, NULL );

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
// *		 Get_Values_Dlg:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_Camera::Get_Values_Dlg(HWND hDlg) 
{

	char buff[MAX_PATH];

	GetDlgItemText(hDlg,IDC_EDCAMX,(LPTSTR)buff,MAX_PATH);
	pCameraEntity->mOrigin.X = (float)atof(buff);

	GetDlgItemText(hDlg,IDC_EDCAMY,(LPTSTR)buff,MAX_PATH);
	pCameraEntity->mOrigin.Y = (float)atof(buff);

	GetDlgItemText(hDlg,IDC_EDCAMZ,(LPTSTR)buff,MAX_PATH);
	pCameraEntity->mOrigin.Z = (float)atof(buff);

	GetDlgItemText(hDlg,IDC_EDCAMANGLEX,(LPTSTR)buff,MAX_PATH);
	Angles.X = (float)atof(buff);

	GetDlgItemText(hDlg,IDC_EDCAMANGLEY,(LPTSTR)buff,MAX_PATH);
	Angles.Y = (float)atof(buff);

	GetDlgItemText(hDlg,IDC_EDCAMANGLEZ,(LPTSTR)buff,MAX_PATH);
	Angles.Z = (float)atof(buff);

}

// *************************************************************************
// *		 Get_Camera_Position:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
geVec3d A_Camera::Get_Camera_Position() 
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	pCameraEntity = m_pDoc->FindCameraEntity();

	return pCameraEntity->mOrigin;
}

// *************************************************************************
// *		 Reset_Camera_Position:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_Camera::Reset_Camera_Position()
{
	App->Get_Current_Document();

	pCameraEntity = App->m_pDoc->FindCameraEntity();
	
	App->CL_Camera->CameraPosition.X = 0;
	App->CL_Camera->CameraPosition.Y = 0;
	App->CL_Camera->CameraPosition.Z = 0;

	App->CL_Camera->pCameraEntity->SetOrigin(App->CL_Camera->CameraPosition.X, App->CL_Camera->CameraPosition.Y, App->CL_Camera->CameraPosition.Z, Level_GetEntityDefs(App->m_pDoc->pLevel));

	App->m_pDoc->SetRenderedViewCamera(&(App->CL_Camera->pCameraEntity->mOrigin), &App->CL_Camera->Angles);
	App->m_pDoc->UpdateAllViews(UAV_ALLVIEWS, NULL);

}

// *************************************************************************
// *		 Reset_Camera_Angles:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_Camera::Reset_Camera_Angles()
{
	App->Get_Current_Document();

	pCameraEntity = App->m_pDoc->FindCameraEntity();
	
	App->CL_Camera->Angles.X = 3.141593; // Radians
	App->CL_Camera->Angles.Y = 0;
	App->CL_Camera->Angles.Z = 0;

	App->CL_Camera->pCameraEntity->SetAngles(&App->CL_Camera->Angles, Level_GetEntityDefs(App->m_pDoc->pLevel));

	App->m_pDoc->SetRenderedViewCamera(&(App->CL_Camera->pCameraEntity->mOrigin), &App->CL_Camera->Angles);
	App->m_pDoc->UpdateAllViews(UAV_ALLVIEWS, NULL);

}