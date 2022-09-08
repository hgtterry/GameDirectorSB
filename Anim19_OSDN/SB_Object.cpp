/*
Copyright (c) 2022 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "GD19_App.h"
#include "resource.h"
#include "SB_Object.h"

SB_Object::SB_Object(void)
{
	Object_PropDlg_Hwnd = nullptr;

	Show_Physics_Debug = 0;
}

SB_Object::~SB_Object(void)
{
}

// *************************************************************************
// *					Start_Object_PropsPanel Terry Flanigan 	 	 	   *
// *************************************************************************
void SB_Object::Start_Object_PropsPanel(void)
{

	Object_PropDlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_OBJECT, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Object_PropsPanel_Proc);
	ShowWindow(App->GD_Properties_Hwnd,0);

	//Set_DataView();

}

// *************************************************************************
// *				Object_PropsPanel_Proc Terry Flanigan				   *
// *************************************************************************
LRESULT CALLBACK SB_Object::Object_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_PHYSICSOBJECTDEBUG, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_POSITION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->DialogBackGround;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_PHYSICSOBJECTDEBUG && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Object->Show_Physics_Debug);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_POSITION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Dimensions->Show_Dimensions);
			return CDRF_DODEFAULT;
		}

		
		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_PHYSICSOBJECTDEBUG)
		{
			int Index = App->SBC_Properties->Current_Selected_Object;

			int f = App->SBC_Scene->B_Object[Index]->Phys_Body->getCollisionFlags();

			if (App->SBC_Object->Show_Physics_Debug == 1)
			{
				App->SBC_Object->Show_Physics_Debug = 0;
				App->SBC_Scene->B_Object[Index]->Phys_Body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->Cl19_Ogre->RenderFrame();
				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 1;
			}
			else
			{
				App->SBC_Object->Show_Physics_Debug = 1;
				App->SBC_Scene->B_Object[Index]->Phys_Body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
			}

			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_POSITION)
		{
			
			if (App->SBC_Dimensions->Show_Dimensions == 1)
			{
				App->SBC_Dimensions->Show_Dimensions = 0;
			}
			else
			{
				App->SBC_Dimensions->Show_Dimensions = 1;
			}
			return 1;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *					Hide_Object_Dlg Terry Flanigan					   *
// *************************************************************************
void SB_Object::Hide_Object_Dlg(bool Show)
{
	ShowWindow(Object_PropDlg_Hwnd, Show);
}