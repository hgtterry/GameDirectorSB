#include "StdAfx.h"
#include "GD19_App.h"
#include "resource.h"
#include "GD19_Object_Properties.h"


GD19_Object_Properties::GD19_Object_Properties(void)
{
	Selected_Object_Index = NULL;
	LastCellSelected = NULL;

	ToggleObjectDebug = 0;

	Edit_Type = Enums::Edit_None;
	Usage_Type = Enums::Usage_None;

	Is_Player = 0;

	Object_Selection = 1;
	Physics_Selection = 0;
}


GD19_Object_Properties::~GD19_Object_Properties(void)
{
}

// *************************************************************************
// *					Start_GD_Properties Terry Bernie   		 	 	   *
// *************************************************************************
void GD19_Object_Properties::Start_GD_Properties(void)
{
	//App->GD_Properties_Hwnd = CreateDialog(App->hInst,(LPCTSTR)IDD_GD_PROPERTIRS,App->Fdlg,(DLGPROC)GD_Properties_Proc);
	//ShowWindow(App->GD_Properties_Hwnd,0);

	Set_DataView();
	
}
// *************************************************************************
// *					GD_Properties_Proc Terry Bernie		  			   *
// *************************************************************************
LRESULT CALLBACK GD19_Object_Properties::GD_Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{	

			SendDlgItemMessage(hDlg,IDC_STOBJECTNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			///SendDlgItemMessage(hDlg,IDC_STTRANSFORM, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
			
			App->Cl_Object_Props->Edit_Type = Enums::FV_Edit_Object;
		}

	case WM_CTLCOLORSTATIC:
		{
			// all
			if(GetDlgItem(hDlg,IDC_STOBJECTNAME) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,0));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->DialogBackGround;
			}
			////--------------------------------------------
			//if(GetDlgItem(hDlg,IDC_STP1) == (HWND)lParam)
			//{	
			//	SetBkColor((HDC) wParam, RGB(0, 255, 0));	
			//	SetTextColor((HDC) wParam, RGB(0,0,0));
			//	SetBkMode((HDC) wParam, TRANSPARENT);
			//	return (UINT) App->Brush_White;
			//}

			//if(GetDlgItem(hDlg,IDC_STP2) == (HWND)lParam)
			//{	
			//	SetBkColor((HDC) wParam, RGB(0, 255, 0));	
			//	SetTextColor((HDC) wParam, RGB(0,0,0));
			//	SetBkMode((HDC) wParam, TRANSPARENT);
			//	return (UINT) App->Brush_White;
			//}

			//if(GetDlgItem(hDlg,IDC_STP3) == (HWND)lParam)
			//{	
			//	SetBkColor((HDC) wParam, RGB(0, 255, 0));	
			//	SetTextColor((HDC) wParam, RGB(0,0,0));
			//	SetBkMode((HDC) wParam, TRANSPARENT);
			//	return (UINT) App->Brush_White;
			//}
			////--------------------------------------------
			//if(GetDlgItem(hDlg,IDC_STR1) == (HWND)lParam)
			//{	
			//	SetBkColor((HDC) wParam, RGB(0, 255, 0));	
			//	SetTextColor((HDC) wParam, RGB(0,0,0));
			//	SetBkMode((HDC) wParam, TRANSPARENT);
			//	return (UINT) App->Brush_White;
			//}

			//if(GetDlgItem(hDlg,IDC_STR2) == (HWND)lParam)
			//{	
			//	SetBkColor((HDC) wParam, RGB(0, 255, 0));	
			//	SetTextColor((HDC) wParam, RGB(0,0,0));
			//	SetBkMode((HDC) wParam, TRANSPARENT);
			//	return (UINT) App->Brush_White;
			//}

			//if(GetDlgItem(hDlg,IDC_STR3) == (HWND)lParam)
			//{	
			//	SetBkColor((HDC) wParam, RGB(0, 255, 0));	
			//	SetTextColor((HDC) wParam, RGB(0,0,0));
			//	SetBkMode((HDC) wParam, TRANSPARENT);
			//	return (UINT) App->Brush_White;
			//}
			////--------------------------------------------
			//if(GetDlgItem(hDlg,IDC_STS1) == (HWND)lParam)
			//{	
			//	SetBkColor((HDC) wParam, RGB(0, 255, 0));	
			//	SetTextColor((HDC) wParam, RGB(0,0,0));
			//	SetBkMode((HDC) wParam, TRANSPARENT);
			//	return (UINT) App->Brush_White;
			//}

			//if(GetDlgItem(hDlg,IDC_STS2) == (HWND)lParam)
			//{	
			//	SetBkColor((HDC) wParam, RGB(0, 255, 0));	
			//	SetTextColor((HDC) wParam, RGB(0,0,0));
			//	SetBkMode((HDC) wParam, TRANSPARENT);
			//	return (UINT) App->Brush_White;
			//}

			//if(GetDlgItem(hDlg,IDC_STS3) == (HWND)lParam)
			//{	
			//	SetBkColor((HDC) wParam, RGB(0, 255, 0));	
			//	SetTextColor((HDC) wParam, RGB(0,0,0));
			//	SetBkMode((HDC) wParam, TRANSPARENT);
			//	return (UINT) App->Brush_White;
			//}

			////--------------------------------------------
			//if(GetDlgItem(hDlg,IDC_STTRANSFORM) == (HWND)lParam)
			//{	
			//	SetBkColor((HDC) wParam, RGB(0, 255, 0));	
			//	SetTextColor((HDC) wParam, RGB(0,0,255));
			//	SetBkMode((HDC) wParam, TRANSPARENT);
			//	return (UINT) App->DialogBackGround;
			//}

			return FALSE;
		}

	case WM_CTLCOLORDLG:
		{
			return (LONG)App->DialogBackGround;
		}

	case WM_CLOSE:
		{
			ShowWindow(App->GD_Properties_Hwnd,0);
			
			break;
		}
	case WM_NOTIFY:
		{
			LPNMHDR some_item = (LPNMHDR)lParam;
			
			///if (some_item->idFrom == IDC_BUTTRANSFORM && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Normal(item);
                return CDRF_DODEFAULT;
            }
			// ------------------------------------------ 
			///if (some_item->idFrom == IDC_BUTEDITPOS && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Normal(item);
                return CDRF_DODEFAULT;
            }

		///	if (some_item->idFrom == IDC_BUTEDITROT && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Normal(item);
                return CDRF_DODEFAULT;
            }

		///	if (some_item->idFrom == IDC_BUTEDITSCALE && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Normal(item);
                return CDRF_DODEFAULT;
            }
			// ------------------------------------------ 
        ///    if (some_item->idFrom == IDC_OBJECT_SEL && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Object_Props->Object_Selection);
                return CDRF_DODEFAULT;
            }

		///	if (some_item->idFrom == IDC_PHYSICS_SEL && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Object_Props->Physics_Selection);
                return CDRF_DODEFAULT;
            }

		///	if (some_item->idFrom == IDC_PHYSICSDEBUG && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Object_Props->ToggleObjectDebug);
                return CDRF_DODEFAULT;
            }


			return CDRF_DODEFAULT;
		}

	case WM_COMMAND:
		{
			///if (LOWORD(wParam) == IDC_BUTEDITPOS)
			{
				return 1;
			}

			///if (LOWORD(wParam) == IDC_BUTEDITROT)
			{
			
				return 1;
			}

			///if (LOWORD(wParam) == IDC_BUTEDITSCALE)
			{
				return 1;
			}

			///if (LOWORD(wParam) == IDC_BUTTRANSFORM)
			{
				
				return 1;
			}

		//	if (LOWORD(wParam) == IDC_OBJECT_SEL)
			{
				/*App->Cl_Object_Props->Object_Selection = 1;
				App->Cl_Object_Props->Physics_Selection = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->Cl_Object_Props->Edit_Type = Enums::Edit_Mesh_Object;

				if(App->Cl_Scene_Data->Cl_Object[App->Cl_Object_Props->Selected_Object_Index]->Usage == Enums::Usage_Sound)
				{
					App->Cl_Object_Props->Update_Properties_Sound();
					return 1;
				}

				if(App->Cl_Object_Props->Is_Player == 0)
				{
					App->Cl_Object_Props->Update_Properties_Mesh();
				}
				else
				{
					App->Cl_Object_Props->Update_Properties_Player();
				}*/
				return 1;
			}

		//	if (LOWORD(wParam) == IDC_PHYSICS_SEL)
			{
				App->Cl_Object_Props->Object_Selection = 0;
				App->Cl_Object_Props->Physics_Selection = 1;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->Cl_Object_Props->Edit_Type = Enums::Edit_Physics_Object;

				if(App->Cl_Object_Props->Is_Player == 0)
				{
					App->Cl_Object_Props->Update_Properties_Physics();
					return 1;
				}
				else
				{
					App->Cl_Object_Props->Update_Properties_Player_Physics();
				}

				return 1;
			}

			if (LOWORD(wParam) == IDC_PHYSICSDEBUG)
			{
		
				if(App->Cl_Object_Props->Is_Player == 1)
				{
					int f = App->SBC_Scene->SBC_Base_Player[0]->Phys_Body->getCollisionFlags();

					if(App->SBC_Player->ShowDebug == 1)
					{
						App->Cl_Object_Props->ToggleObjectDebug = 0;
						App->SBC_Player->ShowDebug = 0;
						App->SBC_Scene->SBC_Base_Player[0]->Phys_Body->setCollisionFlags(f^btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
					}
					else
					{
						App->Cl_Object_Props->ToggleObjectDebug = 1;
						App->SBC_Player->ShowDebug = 1;
						App->SBC_Scene->SBC_Base_Player[0]->Phys_Body->setCollisionFlags(f^btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
					}
					return 1;
				}
				else
				{
					/*int Index = App->Cl_Object_Props->Selected_Object_Index;

					if (App->Cl_Scene_Data->Cl_Object[Index]->Physics_Valid == 1)
					{
						int f = App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionFlags();

						if(App->Cl_Scene_Data->Cl_Object[Index]->Show_Debug == 1)
						{
							App->Cl_Object_Props->ToggleObjectDebug = 0;
							App->Cl_Scene_Data->Cl_Object[Index]->Show_Debug = 0;
							App->Cl_Scene_Data->Cl_Object[Index]->bt_body->setCollisionFlags(f^btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
						}
						else
						{
							App->Cl_Object_Props->ToggleObjectDebug = 1;
							App->Cl_Scene_Data->Cl_Object[Index]->Show_Debug = 1;
							App->Cl_Scene_Data->Cl_Object[Index]->bt_body->setCollisionFlags(f^btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
						}
					}*/

					return 1;
				}

				return 1;
			}

			break;
		}
	}
	return FALSE;
}

// *************************************************************************
// *					Update_Properties_Player Terry Bernie    	 	   *
// *************************************************************************
void GD19_Object_Properties::Update_Properties_Player(void)
{


}

// *************************************************************************
// *			Update_Properties_Player_Physics Terry Bernie   	 	   *
// *************************************************************************
void GD19_Object_Properties::Update_Properties_Player_Physics(void)
{
	
}

// *************************************************************************
// *					Update_Properties_Physics Terry Bernie   	 	   *
// *************************************************************************
void GD19_Object_Properties::Update_Properties_Physics(void)
{
	
}
// *************************************************************************
// *					Update_Properties_Mesh Terry Bernie   		 	   *
// *************************************************************************
void GD19_Object_Properties::Update_Properties_Mesh(void)
{
	
}

// *************************************************************************
// *					Update_Properties_Sound Terry Bernie   		 	   *
// *************************************************************************
void GD19_Object_Properties::Update_Properties_Sound(void)
{
	
}

// *************************************************************************
// *					Update_Properties_Move Terry Bernie   			   *
// *************************************************************************
void GD19_Object_Properties::Update_Properties_Move(void)
{
	
}

// *************************************************************************
// *					Set_DataView Terry Bernie				 	 	   *
// *************************************************************************
void GD19_Object_Properties::Set_DataView(void)
{

}

