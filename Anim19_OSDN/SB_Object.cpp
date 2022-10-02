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
	Show_Mesh_Debug = 1;
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
		SendDlgItemMessage(hDlg, IDC_BT_SHOWMESH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_PHYSICSOBJECTDEBUG, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_POSITION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_ROTATION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_SCALE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_GOTO, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_DETAIL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
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

		if (some_item->idFrom == IDC_BT_GOTO && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_PHYSICSOBJECTDEBUG && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Object->Show_Physics_Debug);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_POSITION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Dimensions->Show_Position);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_SCALE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Dimensions->Show_Scale);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_ROTATION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Dimensions->Show_Rotation);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_SHOWMESH && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Object->Show_Mesh_Debug);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BT_SHOWMESH)
		{
			int Index = App->SBC_Properties->Current_Selected_Object;

			if (App->SBC_Object->Show_Mesh_Debug == 1)
			{
				App->SBC_Scene->B_Object[Index]->Object_Node->setVisible(false);
				App->SBC_Object->Show_Mesh_Debug = 0;
			}
			else
			{
				App->SBC_Scene->B_Object[Index]->Object_Node->setVisible(true);
				App->SBC_Object->Show_Mesh_Debug = 1;
			}

			return 1;
		}

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

		if (LOWORD(wParam) == IDC_BT_DETAIL)
		{
			if (App->CL_Vm_ImGui->Show_Object_Data == 1)
			{
				App->CL_Vm_ImGui->Show_Object_Data = 0;
			}
			else
			{
				App->SBC_Object->Update_Types();
				App->CL_Vm_ImGui->Show_Object_Data = 1;
			}
			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_GOTO)
		{
			//App->Cl_ToolBar->FreeCam_Active = 1;
			//App->Cl_ToolBar->FirstPerson_Active = 0;
			App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;

			//RedrawWindow(App->Cl_ToolBar->TB_1, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			int Index = App->SBC_Properties->Current_Selected_Object;
			Ogre::Vector3 Centre = App->SBC_Scene->B_Object[Index]->Object_Node->getAttachedObject(0)->getBoundingBox().getCenter();
			Ogre::Vector3 WS = App->SBC_Scene->B_Object[Index]->Object_Node->convertLocalToWorldPosition(Centre);
			App->Cl19_Ogre->mCamera->setPosition(WS);
			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_POSITION)
		{
			
			if (App->SBC_Dimensions->Show_Position == 1)
			{
				App->SBC_Dimensions->Show_Position = 0;
				App->SBC_Markers->Hide_Axis_Marker();
			}
			else
			{
				App->SBC_Markers->Hide_Axis_Marker();
				App->SBC_Dimensions->Show_Position = 1;
				App->SBC_Dimensions->Show_Scale = 0;
				App->SBC_Dimensions->Show_Rotation = 0;
			}

			RedrawWindow(App->SBC_Object->Object_PropDlg_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_SCALE)
		{

			if (App->SBC_Dimensions->Show_Scale == 1)
			{
				App->SBC_Dimensions->Show_Scale = 0;
				App->SBC_Markers->Hide_Axis_Marker();
			}
			else
			{
				App->SBC_Markers->Hide_Axis_Marker();
				App->SBC_Dimensions->Show_Scale = 1;
				App->SBC_Dimensions->Show_Position = 0;
				App->SBC_Dimensions->Show_Rotation = 0;
			}

			RedrawWindow(App->SBC_Object->Object_PropDlg_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			return 1;
		}
		
		if (LOWORD(wParam) == IDC_BT_ROTATION)
		{

			if (App->SBC_Dimensions->Show_Rotation == 1)
			{
				App->SBC_Dimensions->Show_Rotation = 0;
				App->SBC_Markers->Hide_Axis_Marker();
			}
			else
			{
				App->SBC_Markers->Hide_Axis_Marker();
				App->SBC_Dimensions->Show_Rotation = 1;
				App->SBC_Dimensions->Show_Position = 0;
				App->SBC_Dimensions->Show_Scale = 0;
			}

			RedrawWindow(App->SBC_Object->Object_PropDlg_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

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

// *************************************************************************
// *					Update_Types  Terry Flanigan					   *
// *************************************************************************
bool SB_Object::Update_Types()
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	Get_Type(Index);
	Get_Shape(Index);
	Get_Usage(Index);

	return 0;
}

// *************************************************************************
// *						Get_Type  Terry Flanigan					   *
// *************************************************************************
bool SB_Object::Get_Type(int Index)
{
	int Type = App->SBC_Scene->B_Object[Index]->Type;

	switch (Type)
	{

	case Enums::Bullet_Type_Dynamic:
	{
		strcpy(Chr_Type, "Dynamic");
		return 1;
	}
	case Enums::Bullet_Type_Static:
	{
		strcpy(Chr_Type, "Static");
		return 1;
	}

	break;

	}

	strcpy(Chr_Type, "None");
	return 0;
}

// *************************************************************************
// *						Get_Shape  Terry Flanigan					   *
// *************************************************************************
bool SB_Object::Get_Shape(int Index)
{
	int Shape = App->SBC_Scene->B_Object[Index]->Shape;

	switch (Shape)
	{

	case Enums::Shape_Box:
	{
		strcpy(Chr_Shape, "Box");
		return 1;
	}
	case Enums::Sphere:
	{
		strcpy(Chr_Shape, "Sphere");
		return 1;
	}

	case Enums::Capsule:
	{
		strcpy(Chr_Shape, "Capsule");
		return 1;
	}

	break;

	}

	strcpy(Chr_Shape, "None");
	return 0;
}

// *************************************************************************
// *						Get_Usage  Terry Flanigan					   *
// *************************************************************************
bool SB_Object::Get_Usage(int Index)
{
	int Usage = App->SBC_Scene->B_Object[Index]->Usage;

	switch (Usage)
	{

	case Enums::Usage_Room:
	{
		strcpy(Chr_Usage, "Usage_Room");
		return 1;
	}
	case Enums::Usage_Static:
	{
		strcpy(Chr_Usage, "Usage_Static");
		return 1;
	}

	case Enums::Usage_Dynamic:
	{
		strcpy(Chr_Usage, "Usage_Dynamic");
		return 1;
	}

	case Enums::Usage_Object:
	{
		strcpy(Chr_Usage, "Usage_Object");
		return 1;
	}

	case Enums::Usage_Message:
	{
		strcpy(Chr_Usage, "Usage_Message");
		return 1;
	}

	break;

	}

	strcpy(Chr_Usage, "None");
	return 0;
}

// *************************************************************************
// *					Rename_Object Terry Flanigan					   *
// *************************************************************************
void SB_Object::Rename_Object(int Index)
{
	Base_Object* Object = App->SBC_Scene->B_Object[Index];

	strcpy(App->Cl_Dialogs->btext, "Change Object Name");
	strcpy(App->Cl_Dialogs->Chr_Text, Object->Mesh_Name);

	App->Cl_Dialogs->Dialog_Text(1);

	if (App->Cl_Dialogs->Canceled == 1)
	{
		return;
	}

	// Needs Duplicate Name test 
	strcpy(Object->Mesh_Name, App->Cl_Dialogs->Chr_Text);

	App->SBC_FileView->Change_Item_Name(Object->ListViewItem, Object->Mesh_Name);
}

// *************************************************************************
//					Get_BoundingBox_World_Centre Terry Bernie			   *
// *************************************************************************
Ogre::Vector3 SB_Object::Get_BoundingBox_World_Centre(int Object_Index)
{
	AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Object_Index]->Object_Ent->getBoundingBox();
	worldAAB.transformAffine(App->SBC_Scene->B_Object[Object_Index]->Object_Node->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();

	return Centre;
}

// *************************************************************************
//					Get_BoundingBox_World_Centre Terry Bernie			   *
// *************************************************************************
void SB_Object::Copy_Object(int Object_Index)
{
	Base_Object* Object = App->SBC_Scene->B_Object[Object_Index];

	char ConNum[256];
	char NewName[MAX_PATH];
	int Object_Count = App->SBC_Scene->Object_Count;

	strcpy_s(NewName, "Object_");
	_itoa(Object_Count, ConNum, 10);
	strcat(NewName, ConNum);

	strcpy(App->Cl_Dialogs->btext, "New Object Name");
	strcpy(App->Cl_Dialogs->Chr_Text, NewName);

	App->Cl_Dialogs->Dialog_Text(1);

	if (App->Cl_Dialogs->Canceled == 1)
	{
		return ;
	}

	App->SBC_Scene->B_Object[Object_Count] = new Base_Object();
	Base_Object* New_Object = App->SBC_Scene->B_Object[Object_Count];

	strcpy(New_Object->Mesh_Name, App->Cl_Dialogs->Chr_Text);
	strcpy(New_Object->Mesh_FileName, Object->Mesh_FileName);
	strcpy(New_Object->Mesh_Resource_Path, Object->Mesh_Resource_Path);

	New_Object->Type = Object->Type;
	New_Object->Shape = Object->Shape;

	New_Object->Mesh_Pos = Object->Mesh_Pos;
	New_Object->Mesh_Scale = Object->Mesh_Scale;
	New_Object->Mesh_Rot = Object->Mesh_Rot;
	New_Object->Mesh_Quat = Object->Mesh_Quat;
	New_Object->Physics_Quat = Object->Physics_Quat;

	App->SBC_Objects_Create->Add_New_Object(Object_Count);

	App->SBC_Scene->Object_Count++;

	App->Say("Copied");
}

// *************************************************************************
// *				Clear_Modified_Objects Terry Flanigan				   *
// *************************************************************************
void SB_Object::Clear_Modified_Objects()
{
	int Count = 0;

	while (Count < App->SBC_Scene->Camera_Count)
	{
		if (App->SBC_Scene->B_Camera[Count]->Altered == 1)
		{
			App->SBC_Scene->B_Camera[Count]->Altered = 0;
			App->SBC_FileView->Mark_Clear(App->SBC_Scene->B_Camera[Count]->FileViewItem);
		}

		Count++;
	}
}