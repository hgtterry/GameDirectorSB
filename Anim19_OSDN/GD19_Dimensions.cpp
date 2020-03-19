/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan B.Parkin H.C.Flanigan

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

#include "StdAfx.h"
#include "GD19_App.h"
#include "resource.h"
#include "GD19_Dimensions.h"

GD19_Dimensions::GD19_Dimensions(void)
{
	Last_Xpos = 0;
	Last_Ypos = 0;
	Last_Zpos = 0;

	Last_XScale = 0;
	Last_YScale = 0;
	Last_ZScale = 0;

	Last_XRotation = 0;
	Last_YRotation = 0;
	Last_ZRotation = 0;


	Use_Mouse = 0;
	Use_Mouse_X = 0;
	Use_Mouse_Y = 0;
	Use_Mouse_Z = 0;

	Model_XTranslate = 1;
	Model_YTranslate = 1;
	Model_ZTranslate = 1;

	Model_XRotate = 10;
	Model_YRotate = 10;
	Model_ZRotate = 10;

	Model_XScale = 0.10;
	Model_YScale = 0.10;
	Model_ZScale = 0.10;

	LockAxis = 1;
	PosStep = 0.01;

	MouseXE = 0;
	MouseYE = 0;
	OldMXE = 0;
	OldMYE = 0;

	Set_ScaleLock = 0;

	Pl_CenterX = 500;
	Pl_CenterY = 500;
	DeltaMouse = 0;

	Dimensions_Mode = Enums::Edit_Dimensions_PosX;
	Mouse_Move_Mode = Enums::Edit_Mouse_None;

	Object_Index;

	Position_Dlg_Active = 0;
	Rotation_Dlg_Active = 0;
	Scale_Dlg_Active = 0;

	PositionDlg_Hwnd = NULL;
	RotationDlg_Hwnd = NULL;
	ScaleDlg_Hwnd = NULL;
}

GD19_Dimensions::~GD19_Dimensions(void)
{
}

// *************************************************************************
// *	  				Start_Postion Terry	Bernie						   *
// *************************************************************************
bool GD19_Dimensions::Start_Postion()
{
	if (Position_Dlg_Active == 1) { return 1; }

	Position_Dlg_Active = 1;

	///PositionDlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_MODELPOSITION, App->Fdlg, (DLGPROC)Postion_Proc);
	return 1;
}
// *************************************************************************
// *        				Postion_Proc  Terry	Bernie					   *
// *************************************************************************
LRESULT CALLBACK GD19_Dimensions::Postion_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

		///SendDlgItemMessage(hDlg, IDC_STTRANSLATEMODEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		///SendDlgItemMessage(hDlg, IDC_STAXISTEXT, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));

		App->Cl_Dimensions->SetTransStepsOptions(hDlg);

		if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
		{
			App->Say("Player");
		}
		else
		{
			
			App->Cl_Dimensions->Object_Index = App->Cl_Properties->Current_Selected_Object;
			int Index = App->Cl_Dimensions->Object_Index;

			if (App->Cl_Scene_Data->Cl_Object[Index]->Type == Enums::Bullet_Type_Dynamic)
			{
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 0;

				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Pos;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos);

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}

			char buff[255];
			strcpy(buff, "Position - ");
			strcat(buff, App->Cl_Scene_Data->Cl_Object[Index]->Name);
			SetWindowText(hDlg, buff);

			App->Cl_Dimensions->Last_Xpos = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.x;
			App->Cl_Dimensions->Last_Ypos = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.y;
			App->Cl_Dimensions->Last_Zpos = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.z;

			char ChrX[255];
			char ChrY[255];
			char ChrZ[255];

			sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.x);
			sprintf(ChrY, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.y);
			sprintf(ChrZ, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.z);

			///SetDlgItemText(hDlg, IDC_HX2, (LPCTSTR)ChrX);
			///SetDlgItemText(hDlg, IDC_HY2, (LPCTSTR)ChrY);
			///SetDlgItemText(hDlg, IDC_HZ2, (LPCTSTR)ChrZ);

		}
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		//-------------------------------------------------- Translation

	///	if (GetDlgItem(hDlg, IDC_STAXISTEXT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

	///	if (GetDlgItem(hDlg, IDC_STTRANSLATEMODEL) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
	///	if (GetDlgItem(hDlg, IDC_STX2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	///	if (GetDlgItem(hDlg, IDC_STY2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	///	if (GetDlgItem(hDlg, IDC_STZ2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	///	if (GetDlgItem(hDlg, IDC_WSTEXTX2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	///	if (GetDlgItem(hDlg, IDC_WSTEXTY2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	///	if (GetDlgItem(hDlg, IDC_WSTEXTZ2) == (HWND)lParam)
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

	///	if (some_item->idFrom == IDC_TRANSLATEZPLUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Red(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_TRANSLATEZMINUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Red(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_TRANSLATEYPLUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Green(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_TRANSLATEYMINUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Green(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_TRANSLATEXPLUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Blue(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_TRANSLATEXMINUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Blue(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_ACCEPT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_CAN && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_USEMOUSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dimensions->Use_Mouse);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_MOUSEX && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dimensions->Use_Mouse_X);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_MOUSEY && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dimensions->Use_Mouse_Y);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_MOUSEZ && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dimensions->Use_Mouse_Z);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		// ----------------------------------------------------------Translate
	///	if (LOWORD(wParam) == IDC_TRANSLATEXPLUS)
		{
			int Index = App->Cl_Dimensions->Object_Index;
			char ChrX[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_PosX;
				App->Cl_Dimensions->Use_Mouse_X = 1;
				App->Cl_Dimensions->Use_Mouse_Y = 0;
				App->Cl_Dimensions->Use_Mouse_Z = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				float Delta = App->Cl_Dimensions->Model_XTranslate;
				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos;
				Pos.x += Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos);

				sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.x);
			///	SetDlgItemText(hDlg, IDC_HX2, (LPCTSTR)ChrX);
				App->Cl_Dimensions->Select_Properties_Update();


				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}

			return TRUE;
		}
	///	if (LOWORD(wParam) == IDC_TRANSLATEXMINUS)
		{
			int Index = App->Cl_Dimensions->Object_Index;
			char ChrX[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_PosX;
				App->Cl_Dimensions->Use_Mouse_X = 1;
				App->Cl_Dimensions->Use_Mouse_Y = 0;
				App->Cl_Dimensions->Use_Mouse_Z = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				float Delta = App->Cl_Dimensions->Model_XTranslate;
				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos;
				Pos.x -= Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos);

				

				sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.x);
			///	SetDlgItemText(hDlg, IDC_HX2, (LPCTSTR)ChrX);
				//App->GDCL_Dimensions->Select_Properties_Update();

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}

			return TRUE;
		}

	///	if (LOWORD(wParam) == IDC_TRANSLATEYPLUS)
		{
			int Index = App->Cl_Dimensions->Object_Index;
			char ChrY[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_PosY;
				App->Cl_Dimensions->Use_Mouse_X = 0;
				App->Cl_Dimensions->Use_Mouse_Y = 1;
				App->Cl_Dimensions->Use_Mouse_Z = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				float Delta = App->Cl_Dimensions->Model_YTranslate;
				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos;
				Pos.y += Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos);

				

				sprintf(ChrY, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.y);
			///	SetDlgItemText(hDlg, IDC_HY2, (LPCTSTR)ChrY);
				//App->GDCL_Dimensions->Select_Properties_Update();

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}
			return TRUE;
		}
	///	if (LOWORD(wParam) == IDC_TRANSLATEYMINUS)
		{
			int Index = App->Cl_Dimensions->Object_Index;
			char ChrY[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_PosY;
				App->Cl_Dimensions->Use_Mouse_X = 0;
				App->Cl_Dimensions->Use_Mouse_Y = 1;
				App->Cl_Dimensions->Use_Mouse_Z = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				float Delta = App->Cl_Dimensions->Model_YTranslate;
				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos;
				Pos.y -= Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos);

				

				sprintf(ChrY, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.y);
			//	SetDlgItemText(hDlg, IDC_HY2, (LPCTSTR)ChrY);
				//App->GDCL_Dimensions->Select_Properties_Update();

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}
			return TRUE;
		}
	///	if (LOWORD(wParam) == IDC_TRANSLATEZPLUS)
		{
			int Index = App->Cl_Dimensions->Object_Index;
			char ChrZ[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_PosZ;
				App->Cl_Dimensions->Use_Mouse_X = 0;
				App->Cl_Dimensions->Use_Mouse_Y = 0;
				App->Cl_Dimensions->Use_Mouse_Z = 1;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				float Delta = App->Cl_Dimensions->Model_ZTranslate;
				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos;

				Pos.z += Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos);

				

				sprintf(ChrZ, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.z);
				///SetDlgItemText(hDlg, IDC_HZ2, (LPCTSTR)ChrZ);
				//App->GDCL_Dimensions->Select_Properties_Update();

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}
			return TRUE;
		}
	///	if (LOWORD(wParam) == IDC_TRANSLATEZMINUS)
		{
			int Index = App->Cl_Dimensions->Object_Index;
			char ChrZ[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_PosZ;
				App->Cl_Dimensions->Use_Mouse_X = 0;
				App->Cl_Dimensions->Use_Mouse_Y = 0;
				App->Cl_Dimensions->Use_Mouse_Z = 1;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				float Delta = App->Cl_Dimensions->Model_ZTranslate;
				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos;
				Pos.z -= Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos);

				sprintf(ChrZ, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.z);
			///	SetDlgItemText(hDlg, IDC_HZ2, (LPCTSTR)ChrZ);
				//App->GDCL_Dimensions->Select_Properties_Update();

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}

			return TRUE;
		}
	///	if (LOWORD(wParam) == IDC_CBXTRANSLATE)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[255];
		///		GetDlgItemText(hDlg, IDC_CBXTRANSLATE, (LPTSTR)buff, 255);
				App->Cl_Dimensions->Model_XTranslate = (float)atof(buff);
			}
			}
		}
	///	if (LOWORD(wParam) == IDC_CBYTRANSLATE)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[255];
				///GetDlgItemText(hDlg, IDC_CBYTRANSLATE, (LPTSTR)buff, 255);
				App->Cl_Dimensions->Model_YTranslate = (float)atof(buff);
			}
			}
		}
	///	if (LOWORD(wParam) == IDC_CBZTRANSLATE)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[255];
				///GetDlgItemText(hDlg, IDC_CBZTRANSLATE, (LPTSTR)buff, 255);
				App->Cl_Dimensions->Model_ZTranslate = (float)atof(buff);
			}
			}
		}

	///	if (LOWORD(wParam) == IDC_EDPOSX)
		{
			////App->CL_Global_Model->Store_TranslateData();

			//char buff[255];
			//GetDlgItemText(hDlg, IDC_HX2, (LPTSTR)buff, 255);
			//strcpy(App->GDCL_Dialogs->Chr_Float, buff);
			//strcpy(App->GDCL_Dialogs->btext, "World Position along the X Axis");

			//App->GDCL_Dialogs->Dialog_Float();

			//float X = App->GDCL_Dialogs->mFloat;
			////float Y = App->CL_Global_Model->Stored_YTranslate;
			////float Z = App->CL_Global_Model->Stored_ZTranslate;

			///*App->CL_Global_Model->Centre_Model_Mid();
			//App->CL_Global_Model->Translate_Model(X,Y,Z);
			//App->CL_Global_Model->UpdatePositionData(hDlg);*/
			return 1;
		}
	///	if (LOWORD(wParam) == IDC_EDPOSY)
		{
			//App->CL_Global_Model->Store_TranslateData();

			//char buff[255];
			//GetDlgItemText(hDlg, IDC_HY2, (LPTSTR)buff, 255);
			//strcpy(App->GDCL_Dialogs->Chr_Float, buff);
			//strcpy(App->GDCL_Dialogs->btext, "World Position along the Y Axis");

			//App->GDCL_Dialogs->Dialog_Float();

			////float X = App->CL_Global_Model->Stored_XTranslate;
			//float Y = App->GDCL_Dialogs->mFloat;
			////float Z = App->CL_Global_Model->Stored_ZTranslate;

			///*App->CL_Global_Model->Centre_Model_Mid();
			//App->CL_Global_Model->Translate_Model(X,Y,Z);
			//App->CL_Global_Model->UpdatePositionData(hDlg);*/

			return 1;
		}
	///	if (LOWORD(wParam) == IDC_EDPOSZ)
		{
			////App->CL_Global_Model->Store_TranslateData();

			//char buff[255];
			//GetDlgItemText(hDlg, IDC_HZ2, (LPTSTR)buff, 255);
			//strcpy(App->GDCL_Dialogs->Chr_Float, buff);
			//strcpy(App->GDCL_Dialogs->btext, "World Position along the Z Axis");

			//App->GDCL_Dialogs->Dialog_Float();

			////float X = App->CL_Global_Model->Stored_XTranslate;
			////float Y = App->CL_Global_Model->Stored_YTranslate;
			//float Z = App->GDCL_Dialogs->mFloat;

			///*App->CL_Global_Model->Centre_Model_Mid();
			//App->CL_Global_Model->Translate_Model(X,Y,Z);
			//App->CL_Global_Model->UpdatePositionData(hDlg);*/


			return 1;
		}

///		if (LOWORD(wParam) == IDC_MOREPOSITION)
		{
			//DialogBox(App->hInst,(LPCTSTR)IDD_MOREPOSITION,App->MainHwnd,(DLGPROC)PositionMore_Proc);
			return 1;
		}

///		if (LOWORD(wParam) == IDC_USEMOUSE)
		{
			if (App->Cl_Dimensions->Use_Mouse == 1)
			{
				App->Cl_Dimensions->Use_Mouse = 0;
				App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_None;
			}
			else
			{
				App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_Active;
				App->Cl_Dimensions->Use_Mouse = 1;
			}
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_MOUSEX)
		{
			App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_PosX;
			App->Cl_Dimensions->Use_Mouse_X = 1;
			App->Cl_Dimensions->Use_Mouse_Y = 0;
			App->Cl_Dimensions->Use_Mouse_Z = 0;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_MOUSEY)
		{
			App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_PosY;
			App->Cl_Dimensions->Use_Mouse_X = 0;
			App->Cl_Dimensions->Use_Mouse_Y = 1;
			App->Cl_Dimensions->Use_Mouse_Z = 0;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_MOUSEZ)
		{
			App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_PosZ;
			App->Cl_Dimensions->Use_Mouse_X = 0;
			App->Cl_Dimensions->Use_Mouse_Y = 0;
			App->Cl_Dimensions->Use_Mouse_Z = 1;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		// -------------- Exit Routines
		if (LOWORD(wParam) == IDCANCEL) // Position
		{
			int Index = App->Cl_Properties->Current_Selected_Object;

			Ogre::Vector3 Pos;

			Pos.x = App->Cl_Dimensions->Last_Xpos;
			Pos.y = App->Cl_Dimensions->Last_Ypos;
			Pos.z = App->Cl_Dimensions->Last_Zpos;

			App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos;
			App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos);

			App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

			App->Cl_Dimensions->Position_Dlg_Active = 0;
			App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_None;
			App->Cl_Dimensions->Use_Mouse = 0;

			if (App->Cl_Scene_Data->Cl_Object[Index]->Type == Enums::Bullet_Type_Dynamic)
			{
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
				App->Cl_Bullet->Reset_Physics();
			}


			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_ACCEPT)
		{

			App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_None;
			App->Cl_Dimensions->Use_Mouse = 0;

			App->Cl_Dimensions->Position_Dlg_Active = 0;

			App->Cl_Visuals->MarkerBB_Addjust(App->Cl_Properties->Current_Selected_Object);

			App->Cl_Properties->Update_Transform_Dlg();

			if (App->Cl_Scene_Data->Cl_Object[App->Cl_Properties->Current_Selected_Object]->Type == Enums::Bullet_Type_Dynamic)
			{
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
				App->Cl_Bullet->Reset_Physics();
			}

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_CAN)
		{
			int Index = App->Cl_Properties->Current_Selected_Object;

			Ogre::Vector3 Pos;

			Pos.x = App->Cl_Dimensions->Last_Xpos;
			Pos.y = App->Cl_Dimensions->Last_Ypos;
			Pos.z = App->Cl_Dimensions->Last_Zpos;

			App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos;
			App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos);

			App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

			App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_None;
			App->Cl_Dimensions->Use_Mouse = 0;
			App->Cl_Dimensions->Position_Dlg_Active = 0;

			if (App->Cl_Scene_Data->Cl_Object[Index]->Type == Enums::Bullet_Type_Dynamic)
			{
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
				App->Cl_Bullet->Reset_Physics();
			}

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *	  				Start_Rotation_Dlg Terry Bernie			 		   *
// *************************************************************************
bool GD19_Dimensions::Start_Rotation_Dlg()
{
	if (Rotation_Dlg_Active == 1) { return 1; }

	Rotation_Dlg_Active = 1;

	///RotationDlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_MODELROTATION, App->Fdlg, (DLGPROC)Rotation_Proc);
	return 1;
}
// *************************************************************************
// *        				Rotation_Proc  Terry Bernie					   *
// *************************************************************************
LRESULT CALLBACK GD19_Dimensions::Rotation_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
	///	SendDlgItemMessage(hDlg, IDC_STROTATEMODEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
	///	SendDlgItemMessage(hDlg, IDC_STAXISTEXT, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));

		App->Cl_Dimensions->SetRotationStepsOptions(hDlg);

		if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
		{
			App->Say("Player");
		}
		else
		{
			App->Cl_Dialogs->Object_Index = App->Cl_Properties->Current_Selected_Object;
			int Index = App->Cl_Dialogs->Object_Index;

			if (App->Cl_Scene_Data->Cl_Object[Index]->Type == Enums::Bullet_Type_Dynamic)
			{
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 0;

				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Pos;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos);

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}

			char buff[255];
			strcpy(buff, "Rotaion - ");
			strcat(buff, App->Cl_Scene_Data->Cl_Object[Index]->Name);
			SetWindowText(hDlg, buff);

			App->Cl_Dimensions->Last_Rotation = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();

			char ChrX[255];
			char ChrY[255];
			char ChrZ[255];

			sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.x);
			sprintf(ChrY, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.y);
			sprintf(ChrZ, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.z);

			///SetDlgItemText(hDlg, IDC_HX3, (LPCTSTR)ChrX);
			///SetDlgItemText(hDlg, IDC_HY3, (LPCTSTR)ChrY);
			///SetDlgItemText(hDlg, IDC_HZ3, (LPCTSTR)ChrZ);

			App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_None;

		}
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		//-------------------------------------------------- Rotatiotion

	///	if (GetDlgItem(hDlg, IDC_STAXISTEXT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	///	if (GetDlgItem(hDlg, IDC_STROTATEMODEL) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
	///	if (GetDlgItem(hDlg, IDC_STX3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	///	if (GetDlgItem(hDlg, IDC_STY3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	///	if (GetDlgItem(hDlg, IDC_STZ3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	///	if (GetDlgItem(hDlg, IDC_WSTEXTX3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	///	if (GetDlgItem(hDlg, IDC_WSTEXTY3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	///	if (GetDlgItem(hDlg, IDC_WSTEXTZ3) == (HWND)lParam)
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

		///if (some_item->idFrom == IDC_ROTATEZPLUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Red(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_ROTATEZMINUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Red(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_ROTATEYPLUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Green(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_ROTATEYMINUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Green(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_ROTATEXPLUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Blue(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_ROTATEXMINUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Blue(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_USEMOUSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dimensions->Use_Mouse);
			return CDRF_DODEFAULT;
		}

///		if (some_item->idFrom == IDC_ACCEPT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

///		if (some_item->idFrom == IDC_CAN && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

///		if (some_item->idFrom == IDC_BTMORE_ROTATION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

	//	if (LOWORD(wParam) == IDC_SCALELOCK)
		{
			//App->GDCL_Dimensions->ScaleLock(hDlg);
			return 1;
		}
		// ---------------------------------------------------------- Rotate
	//	if (LOWORD(wParam) == IDC_ROTATEXPLUS)
		{
			int Index = App->Cl_Dialogs->Object_Index;
			char ChrX[255];
			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleX;
				App->Cl_Dimensions->Use_Mouse_X = 1;
				App->Cl_Dimensions->Use_Mouse_Y = 0;
				App->Cl_Dimensions->Use_Mouse_Z = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->pitch(Radian(Ogre::Degree(App->Cl_Dimensions->Model_XRotate)));
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.x += App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();

				// Physics
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Rot.x += App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();
				float w = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.w;
				float x = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.x;
				float y = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.y;
				float z = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.z;
				App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

				sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.x);
				//SetDlgItemText(hDlg, IDC_HX3, (LPCTSTR)ChrX);
				App->Cl_Dimensions->Select_Properties_Update();
			}
			return TRUE;
		}

	//	if (LOWORD(wParam) == IDC_ROTATEXMINUS)
		{
			int Index = App->Cl_Dialogs->Object_Index;
			char ChrX[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleX;
				App->Cl_Dimensions->Use_Mouse_X = 1;
				App->Cl_Dimensions->Use_Mouse_Y = 0;
				App->Cl_Dimensions->Use_Mouse_Z = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->pitch(Radian(Ogre::Degree(-App->Cl_Dimensions->Model_XRotate)));
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.x -= App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();

				// Physics
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Rot.x -= App->Cl_Dimensions->Model_XRotate;
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();
				float w = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.w;
				float x = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.x;
				float y = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.y;
				float z = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.z;
				App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

				sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.x);
			///	SetDlgItemText(hDlg, IDC_HX3, (LPCTSTR)ChrX);
				App->Cl_Dimensions->Select_Properties_Update();
			}

			return TRUE;
		}

	///	if (LOWORD(wParam) == IDC_ROTATEYPLUS)
		{
			int Index = App->Cl_Dialogs->Object_Index;
			char ChrY[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleY;
				App->Cl_Dimensions->Use_Mouse_X = 0;
				App->Cl_Dimensions->Use_Mouse_Y = 1;
				App->Cl_Dimensions->Use_Mouse_Z = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->yaw(Radian(Ogre::Degree(App->Cl_Dimensions->Model_YRotate)));
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.y += App->Cl_Dimensions->Model_YRotate;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();

				// Physics
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Rot.y += App->Cl_Dimensions->Model_YRotate;
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();
				float w = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.w;
				float x = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.x;
				float y = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.y;
				float z = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.z;
				App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

				sprintf(ChrY, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.y);
				///SetDlgItemText(hDlg, IDC_HY3, (LPCTSTR)ChrY);
				App->Cl_Dimensions->Select_Properties_Update();

			}

			return TRUE;
		}
	//	if (LOWORD(wParam) == IDC_ROTATEYMINUS)
		{
			int Index = App->Cl_Dialogs->Object_Index;
			char ChrY[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleY;
				App->Cl_Dimensions->Use_Mouse_X = 0;
				App->Cl_Dimensions->Use_Mouse_Y = 1;
				App->Cl_Dimensions->Use_Mouse_Z = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->yaw(Radian(Ogre::Degree(-App->Cl_Dimensions->Model_YRotate)));
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.y -= App->Cl_Dimensions->Model_YRotate;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();

				// Physics
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Rot.y -= App->Cl_Dimensions->Model_YRotate;
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();
				float w = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.w;
				float x = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.x;
				float y = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.y;
				float z = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.z;
				App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

				sprintf(ChrY, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.y);
				///SetDlgItemText(hDlg, IDC_HY3, (LPCTSTR)ChrY);
				App->Cl_Dimensions->Select_Properties_Update();

			}
			return TRUE;
		}
	///	if (LOWORD(wParam) == IDC_ROTATEZPLUS)
		{
			int Index = App->Cl_Dialogs->Object_Index;
			char ChrZ[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleZ;
				App->Cl_Dimensions->Use_Mouse_X = 0;
				App->Cl_Dimensions->Use_Mouse_Y = 0;
				App->Cl_Dimensions->Use_Mouse_Z = 1;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->roll(Radian(Ogre::Degree(App->Cl_Dimensions->Model_ZRotate)));
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.z += App->Cl_Dimensions->Model_ZRotate;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();

				// Physics
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Rot.z += App->Cl_Dimensions->Model_ZRotate;
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();
				float w = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.w;
				float x = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.x;
				float y = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.y;
				float z = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.z;
				App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

				sprintf(ChrZ, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.z);
			///	SetDlgItemText(hDlg, IDC_HZ3, (LPCTSTR)ChrZ);
				App->Cl_Dimensions->Select_Properties_Update();


			}
			return TRUE;
		}
	//	if (LOWORD(wParam) == IDC_ROTATEZMINUS)
		{
			int Index = App->Cl_Dialogs->Object_Index;
			char ChrZ[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleZ;
				App->Cl_Dimensions->Use_Mouse_X = 0;
				App->Cl_Dimensions->Use_Mouse_Y = 0;
				App->Cl_Dimensions->Use_Mouse_Z = 1;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->roll(Radian(Ogre::Degree(-App->Cl_Dimensions->Model_ZRotate)));
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.z -= App->Cl_Dimensions->Model_ZRotate;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();

				// Physics
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Rot.z -= App->Cl_Dimensions->Model_ZRotate;
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();
				float w = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.w;
				float x = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.x;
				float y = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.y;
				float z = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.z;
				App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

				sprintf(ChrZ, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.z);
			///	SetDlgItemText(hDlg, IDC_HZ3, (LPCTSTR)ChrZ);
				App->Cl_Dimensions->Select_Properties_Update();

			}

			return TRUE;
		}

		// ---------------------------------------------------------------------------
	///	if (LOWORD(wParam) == IDC_CBXROTATION)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[255];
			///	GetDlgItemText(hDlg, IDC_CBXROTATION, (LPTSTR)buff, 255);
				App->Cl_Dimensions->Model_XRotate = (float)atof(buff);
			}
			}
		}

///		if (LOWORD(wParam) == IDC_CBYROTATION)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[255];
			///	GetDlgItemText(hDlg, IDC_CBYROTATION, (LPTSTR)buff, 255);
				App->Cl_Dimensions->Model_YRotate = (float)atof(buff);
			}
			}
		}

///		if (LOWORD(wParam) == IDC_CBZROTATION)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[255];
			///	GetDlgItemText(hDlg, IDC_CBZROTATION, (LPTSTR)buff, 255);
				App->Cl_Dimensions->Model_ZRotate = (float)atof(buff);
			}
			}
		}

		// ---------------------------------------------------------------------------
///		if (LOWORD(wParam) == IDC_EDPOSX)
		{
			//App->CL_Global_Model->Store_TranslateData();

			char buff[255];
		///	GetDlgItemText(hDlg, IDC_HX2, (LPTSTR)buff, 255);
			strcpy(App->Cl_Dialogs->Chr_Float, buff);
			strcpy(App->Cl_Dialogs->btext, "World Position along the X Axis");

			App->Cl_Dialogs->Dialog_Float();

			float X = App->Cl_Dialogs->mFloat;
			//float Y = App->CL_Global_Model->Stored_YTranslate;
			//float Z = App->CL_Global_Model->Stored_ZTranslate;

			/*App->CL_Global_Model->Centre_Model_Mid();
			App->CL_Global_Model->Translate_Model(X,Y,Z);
			App->CL_Global_Model->UpdatePositionData(hDlg);*/
			return 1;
		}
///		if (LOWORD(wParam) == IDC_EDPOSY)
		{
			//App->CL_Global_Model->Store_TranslateData();

			char buff[255];
		///	GetDlgItemText(hDlg, IDC_HY2, (LPTSTR)buff, 255);
			strcpy(App->Cl_Dialogs->Chr_Float, buff);
			strcpy(App->Cl_Dialogs->btext, "World Position along the Y Axis");

			App->Cl_Dialogs->Dialog_Float();

			//float X = App->CL_Global_Model->Stored_XTranslate;
			float Y = App->Cl_Dialogs->mFloat;
			//float Z = App->CL_Global_Model->Stored_ZTranslate;

			/*App->CL_Global_Model->Centre_Model_Mid();
			App->CL_Global_Model->Translate_Model(X,Y,Z);
			App->CL_Global_Model->UpdatePositionData(hDlg);*/

			return 1;
		}
///		if (LOWORD(wParam) == IDC_EDPOSZ)
		{
			//App->CL_Global_Model->Store_TranslateData();

			char buff[255];
		///	GetDlgItemText(hDlg, IDC_HZ2, (LPTSTR)buff, 255);
			strcpy(App->Cl_Dialogs->Chr_Float, buff);
			strcpy(App->Cl_Dialogs->btext, "World Position along the Z Axis");

			App->Cl_Dialogs->Dialog_Float();

			//float X = App->CL_Global_Model->Stored_XTranslate;
			//float Y = App->CL_Global_Model->Stored_YTranslate;
			float Z = App->Cl_Dialogs->mFloat;

			/*App->CL_Global_Model->Centre_Model_Mid();
			App->CL_Global_Model->Translate_Model(X,Y,Z);
			App->CL_Global_Model->UpdatePositionData(hDlg);*/


			return 1;
		}

///		if (LOWORD(wParam) == IDC_BTMORE_ROTATION)
		{
		//	DialogBox(App->hInst, (LPCTSTR)IDD_MORE_ROTATION, App->MainHwnd, (DLGPROC)More_Rotation_Proc);
			return 1;
		}

///		if (LOWORD(wParam) == IDC_USEMOUSE)
		{
			/*if(App->GDCL_Dimensions->LockAxis == 1)
			{
				App->GDCL_Dialogs->Dimensions_Mode = Enums::Edit_Dimensions_ScaleAll;
			}

			if(App->GDCL_Dimensions->Use_Mouse == 1)
			{
				App->GDCL_Dimensions->Use_Mouse = 0;
				App->GDCL_Dialogs->Mouse_Move_Mode = Enums::Edit_Mouse_None;
			}
			else
			{
				App->GDCL_Dialogs->Mouse_Move_Mode = Enums::Edit_Mouse_Active;
				App->GDCL_Dimensions->Use_Mouse = 1;
			}*/
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_MOUSEX)
		{
			App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_RotateX;
			App->Cl_Dimensions->Use_Mouse_X = 1;
			App->Cl_Dimensions->Use_Mouse_Y = 0;
			App->Cl_Dimensions->Use_Mouse_Z = 0;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_MOUSEY)
		{
			App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_RotateY;
			App->Cl_Dimensions->Use_Mouse_X = 0;
			App->Cl_Dimensions->Use_Mouse_Y = 1;
			App->Cl_Dimensions->Use_Mouse_Z = 0;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_MOUSEZ)
		{
			App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_RotateZ;
			App->Cl_Dimensions->Use_Mouse_X = 0;
			App->Cl_Dimensions->Use_Mouse_Y = 0;
			App->Cl_Dimensions->Use_Mouse_Z = 1;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		// Exit Routines
///		if (LOWORD(wParam) == IDCANCEL) // Rotation
		{
			int Index = App->Cl_Properties->Current_Selected_Object;
			App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setOrientation(App->Cl_Dimensions->Last_Rotation);

			float w = App->Cl_Dimensions->Last_Rotation.w;
			float x = App->Cl_Dimensions->Last_Rotation.x;
			float y = App->Cl_Dimensions->Last_Rotation.y;
			float z = App->Cl_Dimensions->Last_Rotation.z;
			App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

			App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

			App->Cl_Dimensions->Rotation_Dlg_Active = 0;
			App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_None;
			App->Cl_Dimensions->Use_Mouse = 0;

			if (App->Cl_Scene_Data->Cl_Object[Index]->Type == Enums::Bullet_Type_Dynamic)
			{
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
				App->Cl_Bullet->Reset_Physics();
			}

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_ACCEPT)
		{
			App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_None;
			App->Cl_Dimensions->Use_Mouse = 0;

			App->Cl_Dimensions->Rotation_Dlg_Active = 0;

			App->Cl_Visuals->MarkerBB_Addjust(App->Cl_Properties->Current_Selected_Object);

			App->Cl_Properties->Update_Transform_Dlg();

			if (App->Cl_Scene_Data->Cl_Object[App->Cl_Properties->Current_Selected_Object]->Type == Enums::Bullet_Type_Dynamic)
			{
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
				App->Cl_Bullet->Reset_Physics();
			}

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_CAN)
		{
			int Index = App->Cl_Properties->Current_Selected_Object;
			App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setOrientation(App->Cl_Dimensions->Last_Rotation);

			float w = App->Cl_Dimensions->Last_Rotation.w;
			float x = App->Cl_Dimensions->Last_Rotation.x;
			float y = App->Cl_Dimensions->Last_Rotation.y;
			float z = App->Cl_Dimensions->Last_Rotation.z;
			App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));
			
			App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

			App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_None;
			App->Cl_Dimensions->Use_Mouse = 0;
			App->Cl_Dimensions->Rotation_Dlg_Active = 0;

			if (App->Cl_Scene_Data->Cl_Object[Index]->Type == Enums::Bullet_Type_Dynamic)
			{
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
				App->Cl_Bullet->Reset_Physics();
			}

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *        	More_Rotation_Proc  Terry	Bernie						   *
// *************************************************************************
LRESULT CALLBACK GD19_Dimensions::More_Rotation_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		/*App->SetTitleBar(hDlg);

		HFONT Font;
		HFONT Font2;
		Font = CreateFont(-20, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
		Font2 = CreateFont(-15, 0, 0, 0, 0, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");

		SendDlgItemMessage(hDlg, IDC_STTEXTLONG, WM_SETFONT, (WPARAM)Font2, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BANNER, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_STTEXTLONG, App->CL_Dialogs->Message_Text);*/

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_BANNER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		if (GetDlgItem(hDlg, IDC_STTEXTLONG) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
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
	//	if (some_item->idFrom == IDC_BTZEROALL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}
	case WM_COMMAND:

		
	//	if (LOWORD(wParam) == IDC_BTZEROALL)
		{
			int Index = App->Cl_Dialogs->Object_Index;

			//  Zero Ogre
			Ogre::Quaternion mZero;
			mZero.IDENTITY;

			App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setOrientation(mZero);
			App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.x = 0;
			App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.y = 0;
			App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Rot.z = 0;
			App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();

			//  Zero Physics
			btQuaternion Bzero;
			Bzero.getIdentity();

			App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setRotation(btQuaternion(Bzero));
			App->Cl_Scene_Data->Cl_Object[Index]->Physics_Rot.x = 0;
			App->Cl_Scene_Data->Cl_Object[Index]->Physics_Rot.y = 0;
			App->Cl_Scene_Data->Cl_Object[Index]->Physics_Rot.z = 0;
			App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();
			
			App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

			App->Cl19_Ogre->RenderFrame();
			App->Cl19_Ogre->RenderFrame();
			
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

		break;
	}
	return FALSE;
}

// *************************************************************************
// *	  				Start_Scale_Dlg Terry	Bernie					   *
// *************************************************************************
bool GD19_Dimensions::Start_Scale_Dlg()
{
	if (Scale_Dlg_Active == 1) { return 1; }

	Scale_Dlg_Active = 1;

///	ScaleDlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_MODELSCALE, App->Fdlg, (DLGPROC)Scale_Proc);
	return 1;
}
// *************************************************************************
// *        				Scale_Proc  Terry	Bernie					   *
// *************************************************************************
LRESULT CALLBACK GD19_Dimensions::Scale_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		///SendDlgItemMessage(hDlg, IDC_STTRANSLATEMODEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		///SendDlgItemMessage(hDlg, IDC_STAXISTEXT, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));

		App->Cl_Dimensions->SetTransStepsOptions(hDlg);


	//	if (App->GDCL_Object_Props->Edit_Type == Enums::Edit_Mesh_Object)
		{
			//App->GDCL_Dialogs->Object_Index = App->GDCL_Object_Props->Selected_Object_Index;
			App->Cl_Dialogs->Object_Index = App->Cl_Properties->Current_Selected_Object;
			int Index = App->Cl_Dialogs->Object_Index;

			if (App->Cl_Scene_Data->Cl_Object[Index]->Type == Enums::Bullet_Type_Dynamic)
			{
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 0;

				Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Pos;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos);

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}

			char buff[255];
			strcpy(buff, "Scale - ");
			strcat(buff, App->Cl_Scene_Data->Cl_Object[Index]->Name);
			SetWindowText(hDlg, buff);

			App->Cl_Dimensions->Last_XScale = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.x;
			App->Cl_Dimensions->Last_YScale = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.y;
			App->Cl_Dimensions->Last_ZScale = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.z;

			char ChrX[255];
			char ChrY[255];
			char ChrZ[255];


			sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.x);
			sprintf(ChrY, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.y);
			sprintf(ChrZ, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.z);

			///SetDlgItemText(hDlg, IDC_HX2, (LPCTSTR)ChrX);
			///SetDlgItemText(hDlg, IDC_HY2, (LPCTSTR)ChrY);
			///SetDlgItemText(hDlg, IDC_HZ2, (LPCTSTR)ChrZ);

			App->Cl_Dimensions->LockAxis = 0; // Set  0 for 1;
			///HWND temp = GetDlgItem(hDlg, IDC_SCALELOCK);
			///SendMessage(temp, BM_SETCHECK, 1, 0);

			App->Cl_Dimensions->ScaleLock(hDlg);

			App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleAll;

		}
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		//-------------------------------------------------- Translation

	///	if (GetDlgItem(hDlg, IDC_STAXISTEXT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

	///	if (GetDlgItem(hDlg, IDC_STTRANSLATEMODEL) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
	///	if (GetDlgItem(hDlg, IDC_STX2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
///		if (GetDlgItem(hDlg, IDC_STY2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
///		if (GetDlgItem(hDlg, IDC_STZ2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
///		if (GetDlgItem(hDlg, IDC_WSTEXTX2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
///		if (GetDlgItem(hDlg, IDC_WSTEXTY2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
///		if (GetDlgItem(hDlg, IDC_WSTEXTZ2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

	///	if (GetDlgItem(hDlg, IDC_SCALELOCK) == (HWND)lParam)
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

	///	if (some_item->idFrom == IDC_TRANSLATEZPLUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Red(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_TRANSLATEZMINUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Red(item);
			return CDRF_DODEFAULT;
		}

///		if (some_item->idFrom == IDC_TRANSLATEYPLUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Green(item);
			return CDRF_DODEFAULT;
		}

	///	if (some_item->idFrom == IDC_TRANSLATEYMINUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Green(item);
			return CDRF_DODEFAULT;
		}

///		if (some_item->idFrom == IDC_TRANSLATEXPLUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Blue(item);
			return CDRF_DODEFAULT;
		}

///		if (some_item->idFrom == IDC_TRANSLATEXMINUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Blue(item);
			return CDRF_DODEFAULT;
		}

///		if (some_item->idFrom == IDC_ACCEPT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

///		if (some_item->idFrom == IDC_CAN && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

///		if (some_item->idFrom == IDC_USEMOUSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dimensions->Use_Mouse);
			return CDRF_DODEFAULT;
		}

///		if (some_item->idFrom == IDC_MOUSEX && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dimensions->Use_Mouse_X);
			return CDRF_DODEFAULT;
		}

///		if (some_item->idFrom == IDC_MOUSEY && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dimensions->Use_Mouse_Y);
			return CDRF_DODEFAULT;
		}

///		if (some_item->idFrom == IDC_MOUSEZ && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dimensions->Use_Mouse_Z);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

///		if (LOWORD(wParam) == IDC_SCALELOCK)
		{
			App->Cl_Dimensions->ScaleLock(hDlg);
			return 1;
		}
		// ----------------------------------------------------------Translate
///		if (LOWORD(wParam) == IDC_TRANSLATEXPLUS)
		{
			int Index = App->Cl_Dialogs->Object_Index;
			char ChrX[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				if (App->Cl_Dimensions->LockAxis == 1)
				{
					App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleAll;
					App->Cl_Dimensions->Use_Mouse_X = 1;
					App->Cl_Dimensions->Use_Mouse_Y = 1;
					App->Cl_Dimensions->Use_Mouse_Z = 1;
					RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

					float Delta = App->Cl_Dimensions->Model_XScale;
					Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale;
					Scale.x += Delta;
					Scale.y += Delta;
					Scale.z += Delta;

					App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setScale(Scale);

					Scale = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale;
					Scale.x += Delta;
					Scale.y += Delta;
					Scale.z += Delta;
					App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					App->Cl_Dimensions->Set_Physics_Position(Index);

					sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.x);
					///SetDlgItemText(hDlg, IDC_HX2, (LPCTSTR)ChrX);

					sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.y);
					///SetDlgItemText(hDlg, IDC_HY2, (LPCTSTR)ChrX);

					sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.z);
					///SetDlgItemText(hDlg, IDC_HZ2, (LPCTSTR)ChrX);

					App->Cl_Dimensions->Select_Properties_Update();

					App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
				}
				else
				{
					App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleX;
					App->Cl_Dimensions->Use_Mouse_X = 1;
					App->Cl_Dimensions->Use_Mouse_Y = 0;
					App->Cl_Dimensions->Use_Mouse_Z = 0;
					RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

					float Delta = App->Cl_Dimensions->Model_XScale;
					Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale;
					Scale.x += Delta;
					App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setScale(Scale);

					Scale = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale;
					Scale.x += Delta;
					App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					App->Cl_Dimensions->Set_Physics_Position(Index);

					sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.x);
					///SetDlgItemText(hDlg, IDC_HX2, (LPCTSTR)ChrX);
					App->Cl_Dimensions->Select_Properties_Update();

					App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
				}
			}

			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_TRANSLATEXMINUS)
		{
			int Index = App->Cl_Dialogs->Object_Index;
			char ChrX[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{

				if (App->Cl_Dimensions->LockAxis == 1)
				{
					App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleAll;
					App->Cl_Dimensions->Use_Mouse_X = 1;
					App->Cl_Dimensions->Use_Mouse_Y = 1;
					App->Cl_Dimensions->Use_Mouse_Z = 1;
					RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

					float Delta = App->Cl_Dimensions->Model_XScale;
					Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale;
					Scale.x -= Delta;
					Scale.y -= Delta;
					Scale.z -= Delta;

					App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setScale(Scale);

					Scale = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale;
					Scale.x -= Delta;
					Scale.y -= Delta;
					Scale.z -= Delta;
					App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));
					App->Cl_Bullet->dynamicsWorld->updateAabbs();

					App->Cl_Dimensions->Set_Physics_Position(Index);

					sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.x);
				///	SetDlgItemText(hDlg, IDC_HX2, (LPCTSTR)ChrX);

					sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.y);
				///	SetDlgItemText(hDlg, IDC_HY2, (LPCTSTR)ChrX);

					sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.z);
				///	SetDlgItemText(hDlg, IDC_HZ2, (LPCTSTR)ChrX);

					App->Cl_Dimensions->Select_Properties_Update();

					App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
				}
				else
				{
					App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleX;
					App->Cl_Dimensions->Use_Mouse_X = 1;
					App->Cl_Dimensions->Use_Mouse_Y = 0;
					App->Cl_Dimensions->Use_Mouse_Z = 0;
					RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

					float Delta = App->Cl_Dimensions->Model_XScale;;
					Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale;
					Scale.x -= Delta;
					App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setScale(Scale);

					Scale = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale;
					Scale.x -= Delta;
					App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale = Scale;
					App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					App->Cl_Dimensions->Set_Physics_Position(Index);

					sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.x);
					///SetDlgItemText(hDlg, IDC_HX2, (LPCTSTR)ChrX);
					App->Cl_Dimensions->Select_Properties_Update();

					App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
				}
			}

			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_TRANSLATEYPLUS)
		{
			int Index = App->Cl_Dialogs->Object_Index;
			char ChrY[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleY;
				App->Cl_Dimensions->Use_Mouse_X = 0;
				App->Cl_Dimensions->Use_Mouse_Y = 1;
				App->Cl_Dimensions->Use_Mouse_Z = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				float Delta = App->Cl_Dimensions->Model_YScale;
				Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale;
				Scale.y += Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale = Scale;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setScale(Scale);

				Scale = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale;
				Scale.y += Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale = Scale;
				App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				App->Cl_Dimensions->Set_Physics_Position(Index);

				sprintf(ChrY, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.y);
				///SetDlgItemText(hDlg, IDC_HY2, (LPCTSTR)ChrY);
				App->Cl_Dimensions->Select_Properties_Update();

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}
			return TRUE;
		}
///		if (LOWORD(wParam) == IDC_TRANSLATEYMINUS)
		{
			int Index = App->Cl_Dialogs->Object_Index;
			char ChrY[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleY;
				App->Cl_Dimensions->Use_Mouse_X = 0;
				App->Cl_Dimensions->Use_Mouse_Y = 1;
				App->Cl_Dimensions->Use_Mouse_Z = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				float Delta = App->Cl_Dimensions->Model_YScale;
				Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale;
				Scale.y -= Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale = Scale;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setScale(Scale);

				Scale = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale;
				Scale.y -= Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale = Scale;
				App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				App->Cl_Dimensions->Set_Physics_Position(Index);

				sprintf(ChrY, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.y);
				///SetDlgItemText(hDlg, IDC_HY2, (LPCTSTR)ChrY);
				App->Cl_Dimensions->Select_Properties_Update();

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}
			return TRUE;
		}
///		if (LOWORD(wParam) == IDC_TRANSLATEZPLUS)
		{
			int Index = App->Cl_Dialogs->Object_Index;
			char ChrZ[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleZ;
				App->Cl_Dimensions->Use_Mouse_X = 0;
				App->Cl_Dimensions->Use_Mouse_Y = 0;
				App->Cl_Dimensions->Use_Mouse_Z = 1;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				float Delta = App->Cl_Dimensions->Model_ZScale;
				Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale;
				Scale.z += Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale = Scale;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setScale(Scale);

				Scale = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale;
				Scale.z += Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale = Scale;
				App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				App->Cl_Dimensions->Set_Physics_Position(Index);

				sprintf(ChrZ, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.z);
			///	SetDlgItemText(hDlg, IDC_HZ2, (LPCTSTR)ChrZ);
				App->Cl_Dimensions->Select_Properties_Update();

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}
			return TRUE;
		}
///		if (LOWORD(wParam) == IDC_TRANSLATEZMINUS)
		{
			int Index = App->Cl_Dialogs->Object_Index;
			char ChrZ[255];

			if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
			{
				App->Say("Player");
			}
			else
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleZ;
				App->Cl_Dimensions->Use_Mouse_X = 0;
				App->Cl_Dimensions->Use_Mouse_Y = 0;
				App->Cl_Dimensions->Use_Mouse_Z = 1;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				float Delta = App->Cl_Dimensions->Model_ZScale;
				Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale;
				Scale.z -= Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale = Scale;
				App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setScale(Scale);

				Scale = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale;
				Scale.z -= Delta;
				App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale = Scale;
				App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				App->Cl_Dimensions->Set_Physics_Position(Index);

				sprintf(ChrZ, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.z);
			///	SetDlgItemText(hDlg, IDC_HZ2, (LPCTSTR)ChrZ);
				App->Cl_Dimensions->Select_Properties_Update();

				App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
			}

			return TRUE;
		}
///		if (LOWORD(wParam) == IDC_CBXTRANSLATE)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[255];
			//	GetDlgItemText(hDlg, IDC_CBXTRANSLATE, (LPTSTR)buff, 255);
				App->Cl_Dimensions->Model_XScale = (float)atof(buff);
			}
			}
		}
///		if (LOWORD(wParam) == IDC_CBYTRANSLATE)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[255];
			//	GetDlgItemText(hDlg, IDC_CBYTRANSLATE, (LPTSTR)buff, 255);
				App->Cl_Dimensions->Model_YScale = (float)atof(buff);
			}
			}
		}
///		if (LOWORD(wParam) == IDC_CBZTRANSLATE)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[255];
			///	GetDlgItemText(hDlg, IDC_CBZTRANSLATE, (LPTSTR)buff, 255);
				App->Cl_Dimensions->Model_ZScale = (float)atof(buff);
			}
			}
		}

///		if (LOWORD(wParam) == IDC_EDPOSX)
		{
			//App->CL_Global_Model->Store_TranslateData();

			char buff[255];
		///	GetDlgItemText(hDlg, IDC_HX2, (LPTSTR)buff, 255);
			strcpy(App->Cl_Dialogs->Chr_Float, buff);
			strcpy(App->Cl_Dialogs->btext, "World Position along the X Axis");

			App->Cl_Dialogs->Dialog_Float();

			float X = App->Cl_Dialogs->mFloat;
			//float Y = App->CL_Global_Model->Stored_YTranslate;
			//float Z = App->CL_Global_Model->Stored_ZTranslate;

			/*App->CL_Global_Model->Centre_Model_Mid();
			App->CL_Global_Model->Translate_Model(X,Y,Z);
			App->CL_Global_Model->UpdatePositionData(hDlg);*/
			return 1;
		}
///		if (LOWORD(wParam) == IDC_EDPOSY)
		{
			//App->CL_Global_Model->Store_TranslateData();

			char buff[255];
		///	GetDlgItemText(hDlg, IDC_HY2, (LPTSTR)buff, 255);
			strcpy(App->Cl_Dialogs->Chr_Float, buff);
			strcpy(App->Cl_Dialogs->btext, "World Position along the Y Axis");

			App->Cl_Dialogs->Dialog_Float();

			//float X = App->CL_Global_Model->Stored_XTranslate;
			float Y = App->Cl_Dialogs->mFloat;
			//float Z = App->CL_Global_Model->Stored_ZTranslate;

			/*App->CL_Global_Model->Centre_Model_Mid();
			App->CL_Global_Model->Translate_Model(X,Y,Z);
			App->CL_Global_Model->UpdatePositionData(hDlg);*/

			return 1;
		}
///		if (LOWORD(wParam) == IDC_EDPOSZ)
		{
			//App->CL_Global_Model->Store_TranslateData();

			char buff[255];
		//	GetDlgItemText(hDlg, IDC_HZ2, (LPTSTR)buff, 255);
			strcpy(App->Cl_Dialogs->Chr_Float, buff);
			strcpy(App->Cl_Dialogs->btext, "World Position along the Z Axis");

			App->Cl_Dialogs->Dialog_Float();

			//float X = App->CL_Global_Model->Stored_XTranslate;
			//float Y = App->CL_Global_Model->Stored_YTranslate;
			float Z = App->Cl_Dialogs->mFloat;

			/*App->CL_Global_Model->Centre_Model_Mid();
			App->CL_Global_Model->Translate_Model(X,Y,Z);
			App->CL_Global_Model->UpdatePositionData(hDlg);*/


			return 1;
		}

///		if (LOWORD(wParam) == IDC_MOREPOSITION)
		{
			//DialogBox(App->hInst,(LPCTSTR)IDD_MOREPOSITION,App->MainHwnd,(DLGPROC)PositionMore_Proc);
			return 1;
		}

///		if (LOWORD(wParam) == IDC_USEMOUSE)
		{
			if (App->Cl_Dimensions->LockAxis == 1)
			{
				App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleAll;
			}

			if (App->Cl_Dimensions->Use_Mouse == 1)
			{
				App->Cl_Dimensions->Use_Mouse = 0;
				App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_None;
			}
			else
			{
				App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_Active;
				App->Cl_Dimensions->Use_Mouse = 1;
			}
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_MOUSEX)
		{
			App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleX;
			App->Cl_Dimensions->Use_Mouse_X = 1;
			App->Cl_Dimensions->Use_Mouse_Y = 0;
			App->Cl_Dimensions->Use_Mouse_Z = 0;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_MOUSEY)
		{
			App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleY;
			App->Cl_Dimensions->Use_Mouse_X = 0;
			App->Cl_Dimensions->Use_Mouse_Y = 1;
			App->Cl_Dimensions->Use_Mouse_Z = 0;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_MOUSEZ)
		{
			App->Cl_Dimensions->Dimensions_Mode = Enums::Edit_Dimensions_ScaleZ;
			App->Cl_Dimensions->Use_Mouse_X = 0;
			App->Cl_Dimensions->Use_Mouse_Y = 0;
			App->Cl_Dimensions->Use_Mouse_Z = 1;
			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		// Exit Routines
///		if (LOWORD(wParam) == IDCANCEL) // Scale
		{

			int Index = App->Cl_Properties->Current_Selected_Object;

			Ogre::Vector3 Scale;

			Scale.x = App->Cl_Dimensions->Last_XScale;
			Scale.y = App->Cl_Dimensions->Last_YScale;
			Scale.z = App->Cl_Dimensions->Last_ZScale;

			App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale = Scale;
			App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setScale(Scale);

			App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale = Scale;
			App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));



			App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

			App->Cl_Dimensions->Scale_Dlg_Active = 0;
			App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_None;
			App->Cl_Dimensions->Use_Mouse = 0;

			if (App->Cl_Scene_Data->Cl_Object[Index]->Type == Enums::Bullet_Type_Dynamic)
			{
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
				App->Cl_Bullet->Reset_Physics();
			}
			

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_ACCEPT)
		{
			int Index = App->Cl_Dialogs->Object_Index;

			//float p = App->GDCL_Add_Objects->GetMesh_Center(Index,App->GDCL_Scene_Data->CL_Object[Index]->OgreNode).y;
			//float p1 = App->GDCL_Add_Objects->GetMesh_Center(Index,App->GDCL_Scene_Data->CL_Object[Index]->OgreNode).x;

			//float Scalex = App->GDCL_Scene_Data->CL_Object[Index]->OgreNode->getScale().x;
			//float Scaley = App->GDCL_Scene_Data->CL_Object[Index]->OgreNode->getScale().y;
			//float Scalez = App->GDCL_Scene_Data->CL_Object[Index]->OgreNode->getScale().z;
			//
			////btTransform startTransform;
			////startTransform.setIdentity();
			////startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1)); // Needs Proper Vals
			////btVector3 initialPosition(Posx,Posy,Posz);
			////startTransform.setOrigin(initialPosition);

			//App->GDCL_Scene_Data->CL_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scalex,Scaley,Scalez));
			

			App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_None;
			App->Cl_Dimensions->Use_Mouse = 0;

			App->Cl_Dimensions->Scale_Dlg_Active = 0;

			App->Cl_Visuals->MarkerBB_Addjust(App->Cl_Properties->Current_Selected_Object);

			App->Cl_Properties->Update_Transform_Dlg();

			if (App->Cl_Scene_Data->Cl_Object[Index]->Type == Enums::Bullet_Type_Dynamic)
			{
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
				App->Cl_Bullet->Reset_Physics();
			}

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

///		if (LOWORD(wParam) == IDC_CAN)
		{
			int Index = App->Cl_Properties->Current_Selected_Object;

			Ogre::Vector3 Scale;

			Scale.x = App->Cl_Dimensions->Last_XScale;
			Scale.y = App->Cl_Dimensions->Last_YScale;
			Scale.z = App->Cl_Dimensions->Last_ZScale;

			App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale = Scale;
			App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setScale(Scale);

			App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale = Scale;
			App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

			App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

			App->Cl_Dimensions->Mouse_Move_Mode = Enums::Edit_Mouse_None;
			App->Cl_Dimensions->Use_Mouse = 0;
			App->Cl_Dimensions->Scale_Dlg_Active = 0;

			if (App->Cl_Scene_Data->Cl_Object[Index]->Type == Enums::Bullet_Type_Dynamic)
			{
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
				App->Cl_Bullet->Reset_Physics();
			}

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}


// *************************************************************************
// *	  				SetTransStepsOptions Terry Bernie				   *
// *************************************************************************
void GD19_Dimensions::SetTransStepsOptions(HWND hDlg)
{
	/// all HWND temp = GetDlgItem(hDlg, IDC_CBXTRANSLATE);
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.25");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.5");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"10");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"100");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1000");
	//SendMessage(temp, CB_SETCURSEL, 2, 0);

	//temp = GetDlgItem(hDlg, IDC_CBYTRANSLATE);
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.25");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.5");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"10");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"100");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1000");
	//SendMessage(temp, CB_SETCURSEL, 2, 0);

	//temp = GetDlgItem(hDlg, IDC_CBZTRANSLATE);
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.25");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.5");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"10");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"100");
	//SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1000");
	//SendMessage(temp, CB_SETCURSEL, 2, 0);
}

// *************************************************************************
// *	  				SetRotationStepsOptions Terry Bernie			   *
// *************************************************************************
void GD19_Dimensions::SetRotationStepsOptions(HWND hDlg)
{
	/// all
	/*HWND temp = GetDlgItem(hDlg, IDC_CBXROTATION);
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.5");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"10");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"45");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"90");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"180");
	SendMessage(temp, CB_SETCURSEL, 2, 0);

	temp = GetDlgItem(hDlg, IDC_CBYROTATION);
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.5");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"10");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"45");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"90");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"180");
	SendMessage(temp, CB_SETCURSEL, 2, 0);

	temp = GetDlgItem(hDlg, IDC_CBZROTATION);
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.5");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"10");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"45");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"90");
	SendMessage(temp, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"180");
	SendMessage(temp, CB_SETCURSEL, 2, 0);*/
}

// *************************************************************************
// *	  				Set_Physics_Position Terry Bernie				   *
// *************************************************************************
void GD19_Dimensions::Set_Physics_Position(int Index)
{

	if (App->Cl_Scene_Data->Cl_Object[Index]->Shape == Enums::Shape_TriMesh)
	{
		Ogre::Vector3 Centre = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getPosition();
		App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
		App->Cl_Scene_Data->Cl_Object[Index]->Physics_Pos = Centre;
	}
	else
	{
		Ogre::Vector3 Centre = App->Cl_Objects_New->Get_BoundingBox_World_Centre(Index);
		App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
		App->Cl_Scene_Data->Cl_Object[Index]->Physics_Pos = Centre;
	}
}

// *************************************************************************
// *	  				Select_Properties_Update Terry Bernie			   *
// *************************************************************************
void GD19_Dimensions::Select_Properties_Update(void)
{
	if (App->Cl_Scene_Data->Cl_Object[App->Cl_Object_Props->Selected_Object_Index]->Usage == Enums::Usage_Sound)
	{
		App->Cl_Object_Props->Update_Properties_Sound();
		return;
	}

	App->Cl_Object_Props->Update_Properties_Mesh();
}

// *************************************************************************
// *	  					ScaleLock Terry Bernie						   *
// *************************************************************************
void GD19_Dimensions::ScaleLock(HWND hDlg)
{
	/*HWND temp = GetDlgItem(hDlg, IDC_SCALELOCK);
	if (LockAxis == 1)
	{
		LockAxis = 0;
		SendMessage(temp, BM_SETCHECK, 0, 0);
		EnableWindow(GetDlgItem(hDlg, IDC_TRANSLATEYMINUS), 1);
		EnableWindow(GetDlgItem(hDlg, IDC_TRANSLATEYPLUS), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_TRANSLATEYMINUS), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_TRANSLATEYPLUS), 1);

		EnableWindow(GetDlgItem(hDlg, IDC_TRANSLATEZMINUS), 1);
		EnableWindow(GetDlgItem(hDlg, IDC_TRANSLATEZPLUS), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_TRANSLATEZMINUS), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_TRANSLATEZPLUS), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_CBYTRANSLATE), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_CBZTRANSLATE), 1);

		ShowWindow(GetDlgItem(hDlg, IDC_STY2), 1);
		ShowWindow(GetDlgItem(hDlg, IDC_STZ2), 1);

		SetDlgItemText(hDlg, IDC_STX2, (LPCTSTR)"X");
	}
	else
	{
		LockAxis = 1;
		SendMessage(temp, BM_SETCHECK, 1, 0);
		EnableWindow(GetDlgItem(hDlg, IDC_TRANSLATEYMINUS), 0);
		EnableWindow(GetDlgItem(hDlg, IDC_TRANSLATEYPLUS), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_TRANSLATEYMINUS), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_TRANSLATEYPLUS), 0);

		EnableWindow(GetDlgItem(hDlg, IDC_TRANSLATEZMINUS), 0);
		EnableWindow(GetDlgItem(hDlg, IDC_TRANSLATEZPLUS), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_TRANSLATEZMINUS), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_TRANSLATEZPLUS), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_CBYTRANSLATE), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_CBZTRANSLATE), 0);

		ShowWindow(GetDlgItem(hDlg, IDC_STY2), 0);
		ShowWindow(GetDlgItem(hDlg, IDC_STZ2), 0);

		SetDlgItemText(hDlg, IDC_STX2, (LPCTSTR)"All");
	}*/
}

// *************************************************************************
// *						DecodeMovment Terry Bernie  				   *
// *************************************************************************
void GD19_Dimensions::DecodeMovment(void)
{
	if (Mouse_Move_Mode == Enums::Edit_Mouse_Active && MouseXE != OldMXE && Dimensions_Mode == Enums::Edit_Dimensions_PosX) // is it to the left?
	{
		MoveObject(Ogre::Vector3(1, 0, 0));
		SetCursorPos(500, 500);
		OldMXE = MouseXE;
	}

	if (Mouse_Move_Mode == Enums::Edit_Mouse_Active && MouseXE != OldMXE && Dimensions_Mode == Enums::Edit_Dimensions_PosY) // is it to the left?
	{
		MoveObject(Ogre::Vector3(0, 1, 0));
		SetCursorPos(500, 500);
		OldMXE = MouseXE;
	}

	if (Mouse_Move_Mode == Enums::Edit_Mouse_Active && MouseXE != OldMXE && Dimensions_Mode == Enums::Edit_Dimensions_PosZ) // is it to the left?
	{
		MoveObject(Ogre::Vector3(0, 0, 1));
		SetCursorPos(500, 500);
		OldMXE = MouseXE;
	}

	// ------------------------------------------

	if (Mouse_Move_Mode == Enums::Edit_Mouse_Active && MouseXE != OldMXE && Dimensions_Mode == Enums::Edit_Dimensions_ScaleAll) // is it to the left?
	{
		ScaleObject(Ogre::Vector3(1, 1, 1));
		SetCursorPos(500, 500);
		OldMXE = MouseXE;
	}

	if (Mouse_Move_Mode == Enums::Edit_Mouse_Active && MouseXE != OldMXE && Dimensions_Mode == Enums::Edit_Dimensions_ScaleX) // is it to the left?
	{
		ScaleObject(Ogre::Vector3(1, 0, 0));
		SetCursorPos(500, 500);
		OldMXE = MouseXE;
	}

	if (Mouse_Move_Mode == Enums::Edit_Mouse_Active && MouseXE != OldMXE && Dimensions_Mode == Enums::Edit_Dimensions_ScaleY) // is it to the left?
	{
		ScaleObject(Ogre::Vector3(0, 1, 0));
		SetCursorPos(500, 500);
		OldMXE = MouseXE;
	}

	if (Mouse_Move_Mode == Enums::Edit_Mouse_Active && MouseXE != OldMXE && Dimensions_Mode == Enums::Edit_Dimensions_ScaleZ) // is it to the left?
	{
		ScaleObject(Ogre::Vector3(0, 0, 1));
		SetCursorPos(500, 500);
		OldMXE = MouseXE;
	}
}

// *************************************************************************
// *					ScaleObject Terry Bernie					 	   *
// *************************************************************************
bool GD19_Dimensions::ScaleObject(Ogre::Vector3 Direction)
{
	Ogre::Vector3 Scale;

	int Index = App->Cl_Properties->Current_Selected_Object;

	GetCursorPos(&MousePoint);
	float Pl_MouseX = (float)MousePoint.x;
	float Pl_MouseY = (float)MousePoint.y;

	DeltaMouse = float(Pl_CenterX - Pl_MouseX);

	Scale = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getScale();


	if (Pl_MouseX < Pl_CenterX)
	{
		if (Direction.x == 1)
		{
			Scale.x = Scale.x - DeltaMouse * PosStep;
		}
		if (Direction.y == 1)
		{
			Scale.y = Scale.y - DeltaMouse * PosStep;
		}
		if (Direction.z == 1)
		{
			Scale.z = Scale.z - DeltaMouse * PosStep;
		}
	}
	else if (Pl_MouseX > Pl_CenterX)
	{
		if (Direction.x == 1)
		{
			Scale.x = Scale.x - DeltaMouse * PosStep;
		}
		if (Direction.y == 1)
		{
			Scale.y = Scale.y - DeltaMouse * PosStep;
		}
		if (Direction.z == 1)
		{
			Scale.z = Scale.z - DeltaMouse * PosStep;
		}
	}

	App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale = Scale;
	App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setScale(Scale);

	App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale = Scale;
	App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

	char ChrX[255];
	sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.x);
///	SetDlgItemText(App->Cl_Dimensions->ScaleDlg_Hwnd, IDC_HX2, (LPCTSTR)ChrX);
	
	App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

	return 1;
}
// *************************************************************************
// *					MoveObject Terry Bernie						 	   *
// *************************************************************************
bool GD19_Dimensions::MoveObject(Ogre::Vector3 Direction)
{
	Ogre::Vector3 Pos;
	Ogre::Vector3 Physics_Pos;

	int Index = App->Cl_Properties->Current_Selected_Object;

	GetCursorPos(&MousePoint);
	float Pl_MouseX = (float)MousePoint.x;
	float Pl_MouseY = (float)MousePoint.y;

	DeltaMouse = float(Pl_CenterX - Pl_MouseX);

	Pos = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getPosition();
	Physics_Pos = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Pos;

	if (Pl_MouseX < Pl_CenterX)
	{
		if (Direction.x == 1)
		{
			Pos.x = Pos.x - DeltaMouse * Model_XTranslate;
			Physics_Pos.x = Physics_Pos.x - DeltaMouse * PosStep;
		}
		if (Direction.y == 1)
		{
			Pos.y = Pos.y - DeltaMouse * PosStep;
			Physics_Pos.y = Physics_Pos.y - DeltaMouse * PosStep;
		}
		if (Direction.z == 1)
		{
			Pos.z = Pos.z - DeltaMouse * PosStep;
			Physics_Pos.z = Physics_Pos.z - DeltaMouse * PosStep;
		}
	}
	else if (Pl_MouseX > Pl_CenterX)
	{
		if (Direction.x == 1)
		{
			Pos.x = Pos.x - DeltaMouse * Model_XTranslate;
			Physics_Pos.x = Physics_Pos.x - DeltaMouse * PosStep;
		}
		if (Direction.y == 1)
		{
			Pos.y = Pos.y - DeltaMouse * PosStep;
			Physics_Pos.y = Physics_Pos.y - DeltaMouse * PosStep;
		}
		if (Direction.z == 1)
		{
			Pos.z = Pos.z - DeltaMouse * PosStep;
			Physics_Pos.z = Physics_Pos.z - DeltaMouse * PosStep;
		}
	}

	App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos;
	App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos);

	App->Cl_Scene_Data->Cl_Object[Index]->Physics_Pos = Physics_Pos;
	btTransform Transform;
	Transform = App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform();
	Transform.setOrigin(btVector3(Physics_Pos.x, Physics_Pos.y, Physics_Pos.z));
	App->Cl_Scene_Data->Cl_Object[Index]->bt_body->setWorldTransform(Transform);

	char ChrX[255];
	sprintf(ChrX, "%.3f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos.x);
//	SetDlgItemText(PositionDlg_Hwnd, IDC_HX2, (LPCTSTR)ChrX);
	
	App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

	return 1;
}

// *************************************************************************
// *					UpDate_Physics_And_Visuals Terry			 	   *
// *************************************************************************
void GD19_Dimensions::UpDate_Physics_And_Visuals(int Index)
{

	App->Cl_Dimensions->Set_Physics_Position(Index);
	App->Cl_Visuals->MarkerBB_Addjust(Index);
}

