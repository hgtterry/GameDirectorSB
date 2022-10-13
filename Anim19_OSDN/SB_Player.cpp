/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "resource.h"
#include "GD19_App.h"
#include "SB_Player.h"


SB_Player::SB_Player()
{
	Player_Props_HWND = nullptr;

	ShowDebug = 0;
	Show_Physics_Debug = 1;

	Toggle_Objects_Flag = 1;
	Toggle_Physics_Flag = 0;

	Col_Object_Index = 0;
	Last_ColisionIndex = 0;

	Col_numManifolds = 0;
	Col_Player_Index = 0;

	Round = 0;
	Distance = 0;
	Life_Time = 0;

	is_Animated = 0;

	Current_Position.ZERO;
	Physics_Position.setZero();
	Physics_Rotation = btQuaternion(1, 0, 0, 0);
}


SB_Player::~SB_Player()
{
}

// *************************************************************************
// *	  					Reset_Class Bernie							   *
// *************************************************************************
void SB_Player::Reset_Class(void)
{
	int Count = 0;

	while (Count < App->SBC_Scene->Player_Count) // Remove Ogre Objects
	{
		if (App->SBC_Scene->B_Player[Count])
		{
			if (App->SBC_Scene->B_Player[Count]->Player_Ent && App->SBC_Scene->B_Player[Count]->Player_Node)
			{
				App->Cl19_Ogre->mSceneMgr->destroySceneNode(App->SBC_Scene->B_Player[Count]->Player_Node);
				App->Cl19_Ogre->mSceneMgr->destroyEntity(App->SBC_Scene->B_Player[Count]->Player_Ent);
				App->Cl19_Ogre->mSceneMgr->destroyCamera(App->SBC_Scene->B_Player[Count]->CameraPitch);
				App->SBC_Scene->B_Player[Count]->Player_Ent = nullptr;
				App->SBC_Scene->B_Player[Count]->Player_Node = nullptr;
				App->SBC_Scene->B_Player[Count]->CameraPitch = nullptr;
			}

			delete App->SBC_Scene->B_Player[Count];
			App->SBC_Scene->B_Player[Count] = nullptr;
		}

		Count++;
	}

	App->SBC_Scene->Player_Count = 0;
	App->SBC_Scene->Player_Added = 0;

}


// *************************************************************************
// *	  					Create_Player_Object Bernie					   *
// *************************************************************************
void SB_Player::Create_Player_Object(void)
{
	int Index = App->SBC_Scene->Player_Count;

	App->SBC_Scene->B_Player[Index] = new Base_Player();

	Initialize();

	App->SBC_Scene->B_Player[Index]->CameraPitch = App->Cl19_Ogre->mSceneMgr->createCamera("PlayerPitch");

	App->SBC_Scene->Player_Count++;

}

// *************************************************************************
// *	  					Initialize Terry Bernie						   *
// *************************************************************************
void SB_Player::Initialize()
{
	Ogre::Vector3 Pos;

	int Index = App->SBC_Scene->Player_Count;

	Base_Player* pBase = App->SBC_Scene->B_Player[Index];

	// ------------------- Ogre
	if (pBase->Player_Ent && pBase->Player_Node)
	{
		App->Cl19_Ogre->mSceneMgr->destroySceneNode(pBase->Player_Node);
		App->Cl19_Ogre->mSceneMgr->destroyEntity(pBase->Player_Ent);
		App->Cl19_Ogre->mSceneMgr->destroyCamera(pBase->CameraPitch);
		pBase->Player_Ent = nullptr;
		pBase->Player_Node = nullptr;
		pBase->CameraPitch = nullptr;
	}

	pBase->Player_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("Player_1", "axes.mesh", App->Cl19_Ogre->App_Resource_Group);
	pBase->Player_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	pBase->Player_Node->attachObject(pBase->Player_Ent);

	Pos.x = pBase->StartPos.x;
	Pos.y = pBase->StartPos.y;
	Pos.z = pBase->StartPos.z;

	pBase->Player_Node->setPosition(Pos.x, Pos.y, Pos.z);

	pBase->Player_Node->setVisible(true);

	// ------------------------ Bulet
	btVector3 pos = btVector3(Pos.x, Pos.y, Pos.z);
	btVector3 inertia = btVector3(0, 0, 0);
	btQuaternion rot = btQuaternion(1,0,0,0);
	btDefaultMotionState *state = new btDefaultMotionState(btTransform(rot, pos));

	//mShape = new btSphereShape(btScalar(radius));
	pBase->Phys_Shape = new btCapsuleShape(btScalar(pBase->Capsule_Radius), btScalar(pBase->Capsule_Height));
	pBase->Phys_Body = new btRigidBody(pBase->Capsule_Mass, state, pBase->Phys_Shape, inertia);
	pBase->Phys_Body->setActivationState(DISABLE_DEACTIVATION);
	pBase->Phys_Body->setAngularFactor(0.0);

	pBase->Phys_Body->setUserPointer(pBase->Player_Node);

	pBase->Phys_Body->setUserIndex(Enums::Usage_Player);


	int f = pBase->Phys_Body->getCollisionFlags();
	pBase->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	//pBase->Phys_Body->getWorldTransform().setRotation(btQuaternion(1,0,1,1));
	App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->SBC_Scene->B_Player[0]->Physics_Rotation);
	App->Cl_Bullet->dynamicsWorld->addRigidBody(pBase->Phys_Body);

	// Save for later
	Current_Position = pBase->Player_Node->getPosition();
	Physics_Position = pBase->Phys_Body->getWorldTransform().getOrigin();
	Physics_Rotation = pBase->Phys_Body->getWorldTransform().getRotation();

	//pBase->Physics_Rotation = pBase->Phys_Body->getWorldTransform().getRotation();

	App->SBC_Scene->Player_Added = 1;

}

// *************************************************************************
// *	  			Start_Player_PropsPanel Terry Bernie				   *
// *************************************************************************
bool SB_Player::Start_Player_PropsPanel()
{

	Player_Props_HWND = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_PLAYER, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Player_PropsPanel_Proc);
	return 1;
}
// *************************************************************************
// *		  	Player_PropsPanel_Proc  Terry Bernie					   *
// *************************************************************************
LRESULT CALLBACK SB_Player::Player_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BTSAVE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTOBJECT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTPHYSICS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_PHYSICSDEBUG, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_GOTO, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_BTPL_LOCATIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_COLLISIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

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
		

		if (some_item->idFrom == IDC_BTSAVE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTLOOKAT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTPL_LOCATIONS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_GOTO && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		// ------------------------------------------ 
		if (some_item->idFrom == IDC_BTOBJECT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Player->Toggle_Objects_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTPHYSICS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Player->Toggle_Physics_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_PHYSICSDEBUG && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Player->Show_Physics_Debug);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_COLLISIONS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_ImGui->Show_Collision_Debug);
			return CDRF_DODEFAULT;
		}
		
		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BTPL_LOCATIONS)
		{
			App->SBC_Player->Start_Locations_Dlg();
			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_COLLISIONS)
		{
			if (App->CL_Vm_ImGui->Show_Collision_Debug == 1)
			{
				App->CL_Vm_ImGui->Show_Collision_Debug = 0;
			}
			else
			{
				App->CL_Vm_ImGui->Show_Collision_Debug = 1;
			}

			return 1;
		}
		
		if (LOWORD(wParam) == IDC_BT_GOTO)
		{

			App->Cl19_Ogre->mCamera->setPosition(Ogre::Vector3(App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getOrigin()));
			
			App->SBC_Scene->B_Player[0]->Phys_Body->setWorldTransform(App->SBC_Scene->B_Player[0]->Player_Xform);
			return 1;
		}

		if (LOWORD(wParam) == IDC_BTSAVE)
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{

				App->SBC_Scene->B_Player[0]->StartPos = Ogre::Vector3(App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getOrigin());
			
				App->SBC_Scene->B_Player[0]->Physics_Rotation = App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getRotation();

				App->SBC_Scene->B_Player[0]->Player_Xform = App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform();
				
				App->SBC_Scene->B_Player[0]->Altered = 1;
				App->SBC_Scene->Scene_Modified = 1;
				App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

				App->SBC_Properties->Update_ListView_Player();

				App->Say("Player Saved");
			}
			return 1;
		}

		if (LOWORD(wParam) == IDC_BTOBJECT)
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				App->SBC_Properties->Edit_Physics = 0;
				App->SBC_Properties->Update_ListView_Player();

				App->SBC_Player->Toggle_Objects_Flag = 1;
				App->SBC_Player->Toggle_Physics_Flag = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			return 1;
		}

		if (LOWORD(wParam) == IDC_BTPHYSICS)
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				App->SBC_Properties->Edit_Physics = 1;
				App->SBC_Properties->Update_ListView_Player_Physics();

				App->SBC_Player->Toggle_Objects_Flag = 0;
				App->SBC_Player->Toggle_Physics_Flag = 1;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			return 1;
		}

		if (LOWORD(wParam) == IDC_PHYSICSDEBUG)
		{
			int f = App->SBC_Scene->B_Player[0]->Phys_Body->getCollisionFlags();

			if (App->SBC_Player->Show_Physics_Debug == 1)
			{
				App->SBC_Player->Show_Physics_Debug = 0;
				App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f | (1 << 5));

				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->Cl19_Ogre->RenderFrame();
				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 1;
			}
			else
			{
				App->SBC_Player->Show_Physics_Debug = 1;
				App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f & (~(1 << 5)));
			}
			
			return 1;
		}


		break;
	}
	return FALSE;
}

// *************************************************************************
// *	  				Start_Projection Terry Bernie					   *
// *************************************************************************
void SB_Player::Start_Locations_Dlg()
{
	/*if (Location_Dlg_Active == 1)
	{
		Location_Dlg_Active = 0;
		EndDialog(LocationDlg_hWnd, 0);
		return;
	}

	Location_Dlg_Active = 1;*/

	//LocationDlg_hWnd =
	CreateDialog(App->hInst, (LPCTSTR)IDD_PROJECTION, App->Fdlg, (DLGPROC)Locations_Proc);
}
// *************************************************************************
// *					Projection_Proc Terry Bernie		 			   *
// *************************************************************************
LRESULT CALLBACK SB_Player::Locations_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

			App->SBC_Dialogs->YesNo(tag, "Are you sure", 1);
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
			//App->Cl_Dialogs->Location_Dlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

// *************************************************************************
// *					Hide_Player_Dlg Terry Bernie 					   *
// *************************************************************************
void SB_Player::Hide_Player_Dlg(bool Show)
{
	ShowWindow(Player_Props_HWND, Show);
}

// *************************************************************************
// *	  					Adjust_CapsuleTerry Bernie					   *
// *************************************************************************
void SB_Player::Adjust_Capsule(void)
{
	App->SBC_Scene->B_Player[0]->Phys_Shape = new btCapsuleShape(btScalar(App->SBC_Scene->B_Player[0]->Capsule_Radius), btScalar(App->SBC_Scene->B_Player[0]->Capsule_Height));
	App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionShape(App->SBC_Scene->B_Player[0]->Phys_Shape);

}

// *************************************************************************
// *	  					Rotate Terry Bernie							   *
// *************************************************************************
bool SB_Player::OnGround() const
{
	return App->SBC_Scene->B_Player[0]->mOnGround;
}

// need to use ray cast for ground collision to handle stair case
#define __RAYTEST__


// *************************************************************************
// *	  				Check_Collisions Terry Bernie					   *
// *************************************************************************
void SB_Player::Check_Collisions(void)
{
	int PlayerIndex = 0;
	int UsageIndex = 0;

	/* Browse all collision pairs */
	int numManifolds = App->Cl_Bullet->dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i<numManifolds; i++)
	{
		btPersistentManifold* contactManifold = App->Cl_Bullet->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

		PlayerIndex = obA->getUserIndex(); // Should Be Player

		if (PlayerIndex == Enums::Usage_Player)
		{
			Life_Time = 0;
			//Distance = 0;
			Col_Object_Index = obB->getUserIndex2(); // Object Index

			UsageIndex = obB->getUserIndex();

			// Sound Entity
			if (UsageIndex == Enums::Usage_Sound)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j<numContacts; j++)
				{

					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					/*if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
						{
							///App->Cl_Scene_Data->Sound_Entity(ColisionIndex);
							Last_ColisionIndex = Col_Object_Index;
						}
					}
					else if (Life_Time < 10)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
						{
							App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered = 0;
						}
					}*/
				}
			}

			// Message Entity
			if (UsageIndex == Enums::Usage_Message)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j<numContacts; j++)
				{

					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					/*if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
						{
							App->Cl_Collision->Message_Entity(Col_Object_Index);
						}
					}
					else if (Round == 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
						{
							int Stock_Index = App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Entity[0].Stock_mIndex;
							App->Cl_Panels_Com->Show_Overlay(0, Stock_Index);
							App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered = 0;
						}
					}*/
				}
			}

			// Move Entity
			if (UsageIndex == Enums::Usage_Move)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j<numContacts; j++)
				{

					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					//if (Round < 0)
					//{
					//	if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
					//	{
					//		App->Cl_Collision->Move_Entity(Col_Object_Index);
					//	}
					//}
					//else if (Round == 0)
					//{
					//	if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
					//	{
					//		/*int Stock_Index = App->GDCL_Scene_Data->CL_Object[ColisionIndex]->Entity[0].Stock_mIndex;
					//		App->GDCL_Scene_Data->S_Messages[Stock_Index]->overlay->hide();
					//		App->GDCL_Scene_Data->CL_Object[ColisionIndex]->Triggered = 0;*/
					//	}
					//}
				}
			}

			// Collectable Entity
			if (UsageIndex == Enums::Usage_Colectable)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j < numContacts; j++)
				{
					//App->Cl_Collision->Do_Collectable(Col_Object_Index);
					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					/*if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
						{

							App->Cl_Collision->Do_Collectable(Col_Object_Index);
						}
					}
					else if (Round == 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
						{

						}
					}*/
				}
			}

			// Teleport Entity
			if (UsageIndex == Enums::Usage_Teleport)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j < numContacts; j++)
				{
					//App->Cl_Collision->Do_Teleport(Col_Object_Index);
					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					/*if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
						{

							///	App->Cl_Scene_Data->Do_Teleport(ColisionIndex);
						}
					}
					else if (Round == 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
						{

						}
					}*/
				}
			}

			// Environment Entity
			if (UsageIndex == Enums::Usage_Environment)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j < numContacts; j++)
				{

					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					/*if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
						{

							App->Cl_Collision->Do_Environment(Col_Object_Index);
							Last_ColisionIndex = Col_Object_Index;
						}
					}
					else if (Round < 10)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
						{
							App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered = 0;
						}
					}*/
				}
			}
		}

	}
}

// *************************************************************************
// *	  				Check_Collisions_New Terry Flanigan				   *
// *************************************************************************
void SB_Player::Check_Collisions_New(void)
{
	int UsageIndex = 0;
	Col_Player_Index = 0;
	Col_Usage_Index = 0;
	Col_numManifolds = 0;

	/* Browse all collision pairs */
	Col_numManifolds = App->Cl_Bullet->dynamicsWorld->getDispatcher()->getNumManifolds();

	for (int i = 0; i < Col_numManifolds; i++)
	{
		btPersistentManifold* contactManifold = App->Cl_Bullet->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

		Col_Player_Index = obA->getUserIndex();  // Should Be Player
		Col_Object_Index = obB->getUserIndex2(); // Object Index

		UsageIndex = obB->getUserIndex();
		if (Col_Player_Index == Enums::Usage_Player)
		{
			Col_Object_Index = obB->getUserIndex2(); // Object Index
			Col_Usage_Index = obB->getUserIndex();

			if (Col_Usage_Index == 123)
			{
				//App->CL_Vm_ImGui->Show_Collision_Debug = 0;
			}
			else
			{
				//App->CL_Vm_ImGui->Show_Collision_Debug = 1;

				Col_Usage_Index = obB->getUserIndex();

				// -------------------- Message Collision
				if (Col_Usage_Index == Enums::Usage_Message)
				{
				
					int numContacts = contactManifold->getNumContacts();
					for (int j = 0; j < numContacts; j++)
					{
						btManifoldPoint& pt = contactManifold->getContactPoint(j);

						Life_Time = pt.getLifeTime();
						Distance = pt.getDistance();
						Round = (int)Distance;

						if (Round < 0)
						{
							if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 0)
							{
								App->SBC_Collision->Message_Entity(Col_Object_Index);
							}
						}
						else if (Round == 0)
						{
							if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 1)
							{
								App->CL_Vm_ImGui->Show_Test_Text = 0;
								App->SBC_Scene->B_Object[Col_Object_Index]->Triggered = 0;

							}
						}
					}
				}

				if (Col_Usage_Index == Enums::Usage_Sound)
				{
					int numContacts = contactManifold->getNumContacts();
					for (int j = 0; j < numContacts; j++)
					{

						btManifoldPoint& pt = contactManifold->getContactPoint(j);

						Life_Time = pt.getLifeTime();
						Distance = pt.getDistance();
						Round = (int)Distance;

						if (Round < 0)
						{
							if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 0)
							{
								App->SBC_Collision->Play_Sound(Col_Object_Index);
								Last_ColisionIndex = Col_Object_Index;
							}
						}
						else if (Life_Time < 10)
						{
							if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 1)
							{
								App->SBC_Scene->B_Object[Col_Object_Index]->Triggered = 0;
							}
						}
					}
				}

				if (Col_Usage_Index == Enums::Usage_Move)
				{
					FlashWindow(App->MainHwnd, true);

					int numContacts = contactManifold->getNumContacts();
					for (int j = 0; j < numContacts; j++)
					{
						btManifoldPoint& pt = contactManifold->getContactPoint(j);

						Life_Time = pt.getLifeTime();
						Distance = pt.getDistance();
						Round = (int)Distance;

						if (Round < 0)
						{
							if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 0)
							{
								App->SBC_Collision->Move_Entity_Collision(Col_Object_Index);
							}
						}
						else if (Round == 0)
						{
							if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 1)
							{
								
							}
						}
						
					}
				}

				// -------------------- 
			}
		}
	}

}
// *************************************************************************
// *	  					Save_Location Terry							   *
// *************************************************************************
void SB_Player::Save_Location(char* name)
{

	int Count = App->Cl_Scene_Data->Player_Location_Count;

	App->Cl_Scene_Data->S_Player_Locations[Count] = new Player_Location_type();
	App->Cl_Scene_Data->S_Player_Locations[Count]->Deleted = 0;

	App->Cl_Scene_Data->S_Player_Locations[Count]->Location_ID = App->Cl_Scene_Data->Locations_ID_Counter;
	App->Cl_Scene_Data->Locations_ID_Counter++;


	strcpy(App->Cl_Scene_Data->S_Player_Locations[Count]->Name, name);
	App->Cl_Scene_Data->S_Player_Locations[Count]->Current_Position = App->SBC_Scene->B_Player[0]->Player_Node->getPosition();
	App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Position = App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getOrigin();
	App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Rotation = App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getRotation();
	App->Cl_Scene_Data->Player_Location_Count++;

}

// *************************************************************************
// *	  					Goto_Locatio Terry							   *
// *************************************************************************
void SB_Player::Goto_Location(int Index)
{

	App->SBC_Scene->B_Player[0]->Player_Node->setPosition(App->Cl_Scene_Data->S_Player_Locations[Index]->Current_Position);

	App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().setOrigin(App->Cl_Scene_Data->S_Player_Locations[Index]->Physics_Position);

	App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->Cl_Scene_Data->S_Player_Locations[Index]->Physics_Rotation);
}
