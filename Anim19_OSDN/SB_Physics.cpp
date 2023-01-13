/*
Copyright (c) 2021 Stage Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Physics.h"


SB_Physics::SB_Physics()
{
	PhysicsPannel_Hwnd = nullptr;

	Toggle_Enable_Flag = 0;

	Physics_Console_Dlg_Active = 0;
}


SB_Physics::~SB_Physics()
{
}

// *************************************************************************
// *	  				Start_Physics_Consol Terry Bernie				   *
// *************************************************************************
void SB_Physics::Start_Physics_Console(void)
{
	if (Physics_Console_Dlg_Active == 1)
	{
		return;
	}

	Physics_Console_Dlg_Active = 1;

	CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_CHECKED);

	App->Physics_Console_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PHYSICS_CONSOLE, App->Fdlg, (DLGPROC)Physics_Console_Proc);
	Init_Bmps_Physics();
}

// *************************************************************************
// *        			Physics_Console_Proc  Terry	Bernie				   *
// *************************************************************************
LRESULT CALLBACK SB_Physics::Physics_Console_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_RESETTRIGGERS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_RESETPHYSICS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_PHYSICS_ON, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->DialogBackGround;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_RESETPHYSICS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_RESETTRIGGERS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (App->SBC_Scene->Scene_Loaded == 1)
		{
			if (some_item->idFrom == IDC_PHYSICS_ON && some_item->code == NM_CUSTOMDRAW)
			{
				LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item, App->SBC_Ogre->OgreListener->GD_Run_Physics);
				return CDRF_DODEFAULT;
			}
		}
		else
		{
			if (some_item->idFrom == IDC_PHYSICS_ON && some_item->code == NM_CUSTOMDRAW)
			{
				LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item, 0);
				return CDRF_DODEFAULT;
			}
		}

		if (some_item->idFrom == IDC_BT_INFO_CONPHYSICS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}


		return CDRF_DODEFAULT;
	}
	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_RESETTRIGGERS)
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				App->SBC_Physics->Reset_Triggers();
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_RESETPHYSICS)
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				App->SBC_Physics->Reset_Physics();

				App->RedrawWindow_Dlg(App->Physics_Console_Hwnd);
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_PHYSICS_ON)
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				if (App->SBC_Ogre->OgreListener->GD_Run_Physics == 1)
				{
					App->SBC_Ogre->OgreListener->GD_Run_Physics = 0;
				}
				else
				{
					App->SBC_Ogre->OgreListener->GD_Run_Physics = 1;
				}

				App->RedrawWindow_Dlg(App->Physics_Console_Hwnd);
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_INFO_CONPHYSICS)
		{
			App->Cl_Utilities->OpenHTML("Help\\Physics_Console.html");

			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->SBC_Physics->Physics_Console_Dlg_Active = 0;
			CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_UNCHECKED);
			ShowWindow(App->Physics_Console_Hwnd, 0);
			//EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *			Init_Bmps_Physics:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Physics::Init_Bmps_Physics()
{

	HWND Temp = GetDlgItem(App->Physics_Console_Hwnd, IDC_BT_INFO_CONPHYSICS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_InfoSmall_Bmp);

	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	Temp = GetDlgItem(App->Physics_Console_Hwnd, IDC_BT_INFO_CONPHYSICS);
	TOOLINFO ti1 = { 0 };
	ti1.cbSize = sizeof(ti1);
	ti1.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti1.uId = (UINT_PTR)Temp;
	ti1.lpszText = "Show Help File";
	ti1.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti1);

	Temp = GetDlgItem(App->Physics_Console_Hwnd, IDC_RESETTRIGGERS);
	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Reset All Entites and Triggers";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	Temp = GetDlgItem(App->Physics_Console_Hwnd, IDC_RESETPHYSICS);
	TOOLINFO ti3 = { 0 };
	ti3.cbSize = sizeof(ti3);
	ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti3.uId = (UINT_PTR)Temp;
	ti3.lpszText = "Stop and Reset Physics";
	ti3.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti3);

	Temp = GetDlgItem(App->Physics_Console_Hwnd, IDC_PHYSICS_ON);
	TOOLINFO ti4 = { 0 };
	ti4.cbSize = sizeof(ti4);
	ti4.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti4.uId = (UINT_PTR)Temp;
	ti4.lpszText = "Turn Physics On and Off";
	ti4.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti4);
	
}

// *************************************************************************
// *				Start_Physics_Pannel Terry Flanigan		  		 	   *
// *************************************************************************
bool SB_Physics::Start_Physics_Pannel()
{
	PhysicsPannel_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PHYSICSPANEL, App->Fdlg, (DLGPROC)Start_Physics_Proc);
	ShowWindow(PhysicsPannel_Hwnd, 0);
	return 1;
}

// *************************************************************************
// *						Groups_Proc Terry Bernie		  			   *
// *************************************************************************
LRESULT CALLBACK SB_Physics::Start_Physics_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_BTPHYTEST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

	}

	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_RGGROUPNAME) == (HWND)lParam)
		{
		SetBkColor((HDC)wParam, RGB(0, 255, 0));
		SetTextColor((HDC)wParam, RGB(0, 0, 0));
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (UINT)App->AppBackground;
		}*/

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_CLOSE:
	{
		ShowWindow(App->SBC_Physics->PhysicsPannel_Hwnd, 0);

		break;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BTPHYTEST && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Physics->Toggle_Enable_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{

		if (LOWORD(wParam) == IDC_BTPHYLOAD)
		{
			/*App->SBC_Import->Bullet_Load_Room("Ogre3D   *.mesh\0*.mesh\0", "Ogre3D");
			strcpy(App->Cl_Vm_Preferences->Pref_Ogre_JustFileName, App->CL_Vm_Model->FileName);
			strcpy(App->Cl_Vm_Preferences->Pref_Ogre_Path, App->CL_Vm_Model->Model_FolderPath);
			App->Cl_Vm_Preferences->Write_Preferences();*/

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTPHYRESET)
		{
			//if (App->Cl_Scene_Data->SceneLoaded == 1)
			{
				App->SBC_Physics->Reset_Physics();
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTUPDATEMODEL)
		{
			App->SBC_Physics->Update_Model();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTPHYTEST)
		{
			int f = App->SBC_Scene->B_Player[0]->Phys_Body->getCollisionFlags();

			if (App->SBC_Ogre->OgreListener->Dubug_Physics_Draw == 0)
			{
				App->SBC_Physics->Enable_Physics(1);
			}
			else
			{
				App->SBC_Physics->Enable_Physics(0);
			}
			return TRUE;
		}
	}
	}

	return FALSE;
}

// *************************************************************************
// *				Update_Model (Terry Bernie)							   *
// *************************************************************************
void SB_Physics::Update_Model(void)
{
	/*strcpy(App->CL_Vm_Model->Model_FolderPath, App->Cl_Vm_Preferences->Pref_Ogre_Path);
	strcpy(App->CL_Vm_Model->FileName, App->Cl_Vm_Preferences->Pref_Ogre_JustFileName);

	App->CL_Bullet_AddRoom->AddToScene(0);

	App->Say("Model Updated");*/
}

// *************************************************************************
// *		 Enable_Physics:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Physics::Enable_Physics(bool Enable)
{
	App->Log_Messageg("void SB_Physics::Enable_Physics(bool Enable)");

	int f = App->SBC_Scene->B_Player[0]->Phys_Body->getCollisionFlags();

	App->SBC_Ogre->OgreListener->Dubug_Physics_Draw = Enable;
	//App->SBC_Ogre->OgreListener->GD_Run_Physics = Enable;
	App->SBC_Ogre->BulletListener->Render_Debug_Flag = Enable;

	App->SBC_Player->ShowDebug = Enable;

	App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->SBC_Physics->Toggle_Enable_Flag = Enable;

	RedrawWindow(App->SBC_Physics->PhysicsPannel_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

}

// *************************************************************************
// *			 Physics_On:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Physics::Physics_On(bool Enable)
{
	App->SBC_Ogre->OgreListener->GD_Run_Physics = Enable;
	RedrawWindow(App->Physics_Console_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}


// *************************************************************************
// *	  		Reset_Physics:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Physics::Reset_Physics(void)
{
	App->Log_Messageg("void GD19_Bullet::Reset_Physics(void)");

	App->SBC_Ogre->OgreListener->GD_Run_Physics = 0;

	float w = 1;
	float x = 0;
	float y = 0;
	float z = 0;

	int Count = 0;
	while (Count < App->SBC_Scene->Object_Count)
	{
		if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Dynamic)
		{
			btVector3 zeroVector(0, 0, 0);

			x = App->SBC_Scene->B_Object[Count]->Physics_Pos.x;
			y = App->SBC_Scene->B_Object[Count]->Physics_Pos.y;
			z = App->SBC_Scene->B_Object[Count]->Physics_Pos.z;
			btVector3 initialPosition(x, y, z);

			btTransform startTransform;
			startTransform.setIdentity();

			startTransform.setRotation(btQuaternion(App->SBC_Scene->B_Object[Count]->Physics_Quat.x,
				App->SBC_Scene->B_Object[Count]->Physics_Quat.y,
				App->SBC_Scene->B_Object[Count]->Physics_Quat.z,
				App->SBC_Scene->B_Object[Count]->Physics_Quat.w));

			startTransform.setOrigin(initialPosition);

			App->SBC_Scene->B_Object[Count]->Phys_Body->clearForces();
			App->SBC_Scene->B_Object[Count]->Phys_Body->setLinearVelocity(zeroVector);
			App->SBC_Scene->B_Object[Count]->Phys_Body->setAngularVelocity(zeroVector);

			App->SBC_Scene->B_Object[Count]->Phys_Body->setWorldTransform(startTransform);
			App->SBC_Scene->B_Object[Count]->Phys_Body->getMotionState()->setWorldTransform(startTransform);
			App->SBC_Scene->B_Object[Count]->Phys_Body->activate(true);

			App->SBC_Scene->B_Object[Count]->Object_Node->setPosition(App->SBC_Scene->B_Object[Count]->Mesh_Pos);
			App->SBC_Scene->B_Object[Count]->Object_Node->setOrientation(App->SBC_Scene->B_Object[Count]->Mesh_Quat);

		}

		/*if(App->GDCL_Scene_Data->CL_Object[Count]->Usage == Enums::Usage_Sound)
		{
			btVector3 zeroVector(0,0,0);

			x = App->GDCL_Scene_Data->CL_Object[Count]->Physics_Pos.x;
			y = App->GDCL_Scene_Data->CL_Object[Count]->Physics_Pos.y;
			z = App->GDCL_Scene_Data->CL_Object[Count]->Physics_Pos.z;
			btVector3 initialPosition(x,y,z);

			btTransform startTransform;
			startTransform.setIdentity();
			startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f));
			startTransform.setOrigin(initialPosition);

			App->GDCL_Scene_Data->CL_Object[Count]->bt_body->clearForces();
			App->GDCL_Scene_Data->CL_Object[Count]->bt_body->setLinearVelocity(zeroVector);
			App->GDCL_Scene_Data->CL_Object[Count]->bt_body->setAngularVelocity(zeroVector);

			App->GDCL_Scene_Data->CL_Object[Count]->bt_body->setWorldTransform(startTransform);
			App->GDCL_Scene_Data->CL_Object[Count]->bt_body->getMotionState()->setWorldTransform(startTransform);
			App->GDCL_Scene_Data->CL_Object[Count]->bt_body->activate(true);
		}*/

		Count++;
	}

	if (App->SBC_Scene->Player_Added == 1)// && GD_Reset_Player == 1)
	{
		btVector3 zeroVector(0, 0, 0);

		x = App->SBC_Scene->B_Player[0]->StartPos.x;
		y = App->SBC_Scene->B_Player[0]->StartPos.y;
		z = App->SBC_Scene->B_Player[0]->StartPos.z;

		btVector3 initialPosition(x, y, z);

		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setRotation(btQuaternion(1.0f, 0.0f, 0.0f, 0.0f));
		startTransform.setOrigin(initialPosition);

		App->SBC_Scene->B_Player[0]->Phys_Body->clearForces();
		App->SBC_Scene->B_Player[0]->Phys_Body->setLinearVelocity(zeroVector);
		App->SBC_Scene->B_Player[0]->Phys_Body->setAngularVelocity(zeroVector);

		App->SBC_Scene->B_Player[0]->Phys_Body->setWorldTransform(startTransform);
		App->SBC_Scene->B_Player[0]->Phys_Body->getMotionState()->setWorldTransform(startTransform);
		App->SBC_Scene->B_Player[0]->Phys_Body->activate(true);

		App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->SBC_Scene->B_Player[0]->Physics_Rotation);
	}

	//App->SBC_Ogre->OgreListener->GD_Run_Physics = 1;
}

// *************************************************************************
// *	  		Reset_Triggers:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Physics::Reset_Triggers(void)
{
	App->SBC_Collision->DoMove = 0;

	if (App->SBC_Scene->GameMode_Running_Flag == 0)
	{
		App->SBC_SoundMgr->SoundEngine->stopAllSounds();
	}

	Ogre::Vector3 M_Pos;
	Ogre::Vector3 P_Pos;

	int Count = 0;
	int Total = App->SBC_Scene->Object_Count;

	while (Count < Total)
	{
		if (App->SBC_Scene->B_Object[Count]->Deleted == 0)
		{
			// ------------------------------------- Move Entities
			if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Move)
			{
				int ObjectToMove = App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Object_To_Move_Index;

				M_Pos = App->SBC_Scene->B_Object[ObjectToMove]->Mesh_Pos;
				P_Pos = App->SBC_Scene->B_Object[ObjectToMove]->Physics_Pos;

				App->SBC_Scene->B_Object[Count]->S_MoveType[0]->MeshPos = Ogre::Vector3(M_Pos);
				App->SBC_Scene->B_Object[Count]->S_MoveType[0]->PhysicsPos = Ogre::Vector3(P_Pos);

				App->SBC_Scene->B_Object[ObjectToMove]->Object_Node->setPosition(M_Pos);
				App->SBC_Scene->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(P_Pos.x, P_Pos.y, P_Pos.z));

				App->SBC_Scene->B_Object[Count]->Triggered = 0;
			}

			// ------------------------------------- Colectables
			if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Colectable)
			{
				App->SBC_Scene->B_Object[Count]->Object_Ent->setVisible(TRUE);

				App->SBC_Scene->B_Object[Count]->Object_Node->setPosition(App->SBC_Scene->B_Object[Count]->Mesh_Pos);

				P_Pos = App->SBC_Scene->B_Object[Count]->Physics_Pos;
				App->SBC_Scene->B_Object[Count]->Phys_Body->getWorldTransform().setOrigin(btVector3(P_Pos.x, P_Pos.y, P_Pos.z));

				App->SBC_Scene->B_Object[Count]->Triggered = 0;

			}

			// ------------------------------------- Messages
			if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Message)
			{
				App->SBC_Scene->B_Object[Count]->Show_Message_Flag = 0;
			}
		}

		Count++;
	}

	Count = 0;
	Total = App->SBC_Scene->Counters_Count;
	while (Count < Total)
	{
		App->SBC_Scene->B_Counter[Count]->Counter = App->SBC_Scene->B_Counter[Count]->Start_Value;
		Count++;
	}
}

// *************************************************************************
//							Set_Physics Terry Bernie					   *
// *************************************************************************
void SB_Physics::Set_Physics(int Index)
{
	App->SBC_Scene->B_Object[Index]->Physics_Quat = App->SBC_Scene->B_Object[Index]->Object_Node->getOrientation();

	float w = App->SBC_Scene->B_Object[Index]->Physics_Quat.w;
	float x = App->SBC_Scene->B_Object[Index]->Physics_Quat.x;
	float y = App->SBC_Scene->B_Object[Index]->Physics_Quat.y;
	float z = App->SBC_Scene->B_Object[Index]->Physics_Quat.z;
	App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

	App->SBC_Scene->B_Object[Index]->Object_Node->setScale(App->SBC_Scene->B_Object[Index]->Mesh_Scale);

	Ogre::Vector3 Scale = App->SBC_Scene->B_Object[Index]->Object_Node->getScale();
	App->SBC_Scene->B_Object[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

	App->SBC_Dimensions->UpDate_Physics_And_Visuals(Index);

	App->SBC_Scene->B_Object[Index]->Physics_Valid = 1;
}



