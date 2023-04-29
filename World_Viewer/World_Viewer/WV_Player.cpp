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
#include "WV_App.h"
#include "WV_Player.h"


WV_Player::WV_Player()
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

	Last_Message_Index = 0;

	Current_Position.ZERO;
	Physics_Position.setZero();
	Physics_Rotation = btQuaternion(1, 0, 0, 0);

}


WV_Player::~WV_Player()
{
}

// *************************************************************************
// *	  					Reset_Class Bernie							   *
// *************************************************************************
void WV_Player::Reset_Class(void)
{
	int Count = 0;

	while (Count < App->CL_Scene->Player_Count) // Remove Ogre Objects
	{
		if (App->CL_Scene->B_Player[Count])
		{
			if (App->CL_Scene->B_Player[Count]->Player_Ent && App->CL_Scene->B_Player[Count]->Player_Node)
			{
				App->CL_Ogre->mSceneMgr->destroySceneNode(App->CL_Scene->B_Player[Count]->Player_Node);
				App->CL_Ogre->mSceneMgr->destroyEntity(App->CL_Scene->B_Player[Count]->Player_Ent);
				App->CL_Ogre->mSceneMgr->destroyCamera(App->CL_Scene->B_Player[Count]->CameraPitch);
				App->CL_Scene->B_Player[Count]->Player_Ent = nullptr;
				App->CL_Scene->B_Player[Count]->Player_Node = nullptr;
				App->CL_Scene->B_Player[Count]->CameraPitch = nullptr;
			}

			delete App->CL_Scene->B_Player[Count];
			App->CL_Scene->B_Player[Count] = nullptr;
		}

		Count++;
	}

	App->CL_Scene->Player_Count = 0;
	App->CL_Scene->Player_Added = 0;

}


// *************************************************************************
// *	  					Create_Player_Object Bernie					   *
// *************************************************************************
void WV_Player::Create_Player_Object(void)
{
	int Index = App->CL_Scene->Player_Count;

	App->CL_Scene->B_Player[0] = nullptr;
	App->CL_Scene->B_Player[0] = new Base_Player();

	Initialize();

	App->CL_Scene->B_Player[0]->CameraPitch = App->CL_Ogre->mSceneMgr->createCamera("PlayerPitch");

	App->CL_Scene->Player_Count++;

}

// *************************************************************************
// *	  					Initialize Terry Bernie						   *
// *************************************************************************
void WV_Player::Initialize()
{
	Ogre::Vector3 Pos;

	int Index = 0;// App->CL_Scene->Player_Count;

	Base_Player* pBase = App->CL_Scene->B_Player[Index];

	// ------------------- Ogre
	if (pBase->Player_Ent && pBase->Player_Node)
	{
		App->CL_Ogre->mSceneMgr->destroySceneNode(pBase->Player_Node);
		App->CL_Ogre->mSceneMgr->destroyEntity(pBase->Player_Ent);
		App->CL_Ogre->mSceneMgr->destroyCamera(pBase->CameraPitch);
		pBase->Player_Ent = nullptr;
		pBase->Player_Node = nullptr;
		pBase->CameraPitch = nullptr;
	}

	pBase->Player_Ent = App->CL_Ogre->mSceneMgr->createEntity("Player_1", "axes.mesh", App->CL_Ogre->App_Resource_Group);
	pBase->Player_Node = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	pBase->Player_Node->attachObject(pBase->Player_Ent);
	pBase->Player_Node->setVisible(true);

	Pos.x = pBase->StartPos.x;
	Pos.y = pBase->StartPos.y;
	Pos.z = pBase->StartPos.z;

	pBase->Player_Node->setPosition(Pos.x, Pos.y, Pos.z);

	// ------------------------ Bulet
	btVector3 pos = btVector3(Pos.x, Pos.y, Pos.z);
	btVector3 inertia = btVector3(0, 0, 0);
	btQuaternion rot = btQuaternion(0,0,0,1);
	btDefaultMotionState *state = new btDefaultMotionState(btTransform(rot, pos));

	pBase->Phys_Shape = new btCapsuleShape(btScalar(pBase->Capsule_Radius), btScalar(pBase->Capsule_Height));
	pBase->Phys_Body = new btRigidBody(pBase->Capsule_Mass, state, pBase->Phys_Shape, inertia);
	//pBase->Phys_Body->setActivationState(DISABLE_DEACTIVATION);
	pBase->Phys_Body->setSleepingThresholds(0.0, 0.0);
	pBase->Phys_Body->setAngularFactor(0.0);

	pBase->Phys_Body->setUserPointer(pBase->Player_Node);

	pBase->Phys_Body->setUserIndex(123);// Enums::Usage_Player);


	int f = pBase->Phys_Body->getCollisionFlags();
	pBase->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->CL_Scene->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->CL_Scene->B_Player[0]->Physics_Rotation);
	App->CL_Bullet->dynamicsWorld->addRigidBody(pBase->Phys_Body);

	// Save for later
	Current_Position = pBase->Player_Node->getPosition();
	Physics_Position = pBase->Phys_Body->getWorldTransform().getOrigin();
	Physics_Rotation = pBase->Phys_Body->getWorldTransform().getRotation();



	App->CL_DCC = new DynamicCharacterController(pBase->Phys_Body, NULL);
	App->CL_DCC->mShapeRadius = pBase->Capsule_Radius;
	App->CL_DCC->mShapeHalfHeight = pBase->Capsule_Height/2;

	App->CL_DCC->setMovementDirection(btVector3(0, 0, 1));
	//App->CL_DCC->updateAction(App->CL_Bullet->dynamicsWorld,1);

	App->CL_Scene->Player_Added = 1;

}

// *************************************************************************
// *	  			Start_Player_PropsPanel Terry Bernie				   *
// *************************************************************************
bool WV_Player::Start_Player_PropsPanel()
{

	//Player_Props_HWND = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_PLAYER, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Player_PropsPanel_Proc);
	return 1;
}
// *************************************************************************
// *		  	Player_PropsPanel_Proc  Terry Bernie					   *
// *************************************************************************
LRESULT CALLBACK WV_Player::Player_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		/*SendDlgItemMessage(hDlg, IDC_BTSAVE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTOBJECT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTPHYSICS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_PHYSICSDEBUG, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_GOTO, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_BTPL_LOCATIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_COLLISIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));*/

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
		

		//if (some_item->idFrom == IDC_BTSAVE && some_item->code == NM_CUSTOMDRAW)
		//{
		//	LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		//	App->Custom_Button_Normal(item);
		//	return CDRF_DODEFAULT;
		//}

		//if (some_item->idFrom == IDC_BTLOOKAT && some_item->code == NM_CUSTOMDRAW)
		//{
		//	LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		//	App->Custom_Button_Normal(item);
		//	return CDRF_DODEFAULT;
		//}

		//if (some_item->idFrom == IDC_BTPL_LOCATIONS && some_item->code == NM_CUSTOMDRAW)
		//{
		//	LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		//	App->Custom_Button_Normal(item);
		//	return CDRF_DODEFAULT;
		//}

		//if (some_item->idFrom == IDC_BT_GOTO && some_item->code == NM_CUSTOMDRAW)
		//{
		//	LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		//	App->Custom_Button_Normal(item);
		//	return CDRF_DODEFAULT;
		//}

		//// ------------------------------------------ 
		//if (some_item->idFrom == IDC_BTOBJECT && some_item->code == NM_CUSTOMDRAW)
		//{
		//	LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		//	App->Custom_Button_Toggle(item, App->SBC_Player->Toggle_Objects_Flag);
		//	return CDRF_DODEFAULT;
		//}

		//if (some_item->idFrom == IDC_BTPHYSICS && some_item->code == NM_CUSTOMDRAW)
		//{
		//	LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		//	App->Custom_Button_Toggle(item, App->SBC_Player->Toggle_Physics_Flag);
		//	return CDRF_DODEFAULT;
		//}

		//if (some_item->idFrom == IDC_PHYSICSDEBUG && some_item->code == NM_CUSTOMDRAW)
		//{
		//	LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		//	App->Custom_Button_Toggle(item, App->SBC_Player->Show_Physics_Debug);
		//	return CDRF_DODEFAULT;
		//}

		//if (some_item->idFrom == IDC_BT_COLLISIONS && some_item->code == NM_CUSTOMDRAW)
		//{
		//	LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		//	App->Custom_Button_Toggle(item, App->CL_Vm_ImGui->Show_Collision_Debug);
		//	return CDRF_DODEFAULT;
		//}
		
		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		//if (LOWORD(wParam) == IDC_BTPL_LOCATIONS)
		//{
		//	App->SBC_Locations->Start_Locations_Dlg();
		//	return 1;
		//}

		//if (LOWORD(wParam) == IDC_BT_COLLISIONS)
		//{
		//	if (App->CL_Vm_ImGui->Show_Collision_Debug == 1)
		//	{
		//		App->CL_Vm_ImGui->Show_Collision_Debug = 0;
		//	}
		//	else
		//	{
		//		App->CL_Vm_ImGui->Show_Collision_Debug = 1;
		//	}

		//	return 1;
		//}
		//
		//if (LOWORD(wParam) == IDC_BT_GOTO)
		//{

		//	//App->CL_Ogre->mCamera->setPosition(Ogre::Vector3(App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getOrigin()));
		//	
		//	float x = App->SBC_Scene->B_Player[0]->StartPos.x;
		//	float y = App->SBC_Scene->B_Player[0]->StartPos.y;
		//	float z = App->SBC_Scene->B_Player[0]->StartPos.z;

		//	App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().setOrigin(btVector3(x,y,z));
		//	App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->SBC_Scene->B_Player[0]->Physics_Rotation);
		//	

		//	return 1;
		//}

		//if (LOWORD(wParam) == IDC_BTSAVE)
		//{
		//	if (App->SBC_Scene->Scene_Loaded == 1)
		//	{

		//		App->SBC_Scene->B_Player[0]->StartPos = Ogre::Vector3(App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getOrigin());
		//		App->SBC_Scene->B_Player[0]->Physics_Rotation = App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getRotation();
		//		
		//		App->SBC_Scene->B_Locations[0]->Physics_Position = App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getOrigin();
		//		App->SBC_Scene->B_Locations[0]->Physics_Rotation = App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getRotation();

		//		App->SBC_Scene->B_Player[0]->Altered = 1;
		//		App->SBC_Scene->Scene_Modified = 1;
		//		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

		//		App->SBC_Properties->Update_ListView_Player();

		//		App->Say("Player Saved");
		//	}
		//	return 1;
		//}

		//if (LOWORD(wParam) == IDC_BTOBJECT)
		//{
		//	if (App->SBC_Scene->Scene_Loaded == 1)
		//	{
		//		App->SBC_Properties->Edit_Physics = 0;
		//		App->SBC_Properties->Update_ListView_Player();

		//		App->SBC_Player->Toggle_Objects_Flag = 1;
		//		App->SBC_Player->Toggle_Physics_Flag = 0;
		//		RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		//	}
		//	return 1;
		//}

		//if (LOWORD(wParam) == IDC_BTPHYSICS)
		//{
		//	if (App->SBC_Scene->Scene_Loaded == 1)
		//	{
		//		App->SBC_Properties->Edit_Physics = 1;
		//		App->SBC_Properties->Update_ListView_Player_Physics();

		//		App->SBC_Player->Toggle_Objects_Flag = 0;
		//		App->SBC_Player->Toggle_Physics_Flag = 1;
		//		RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		//	}
		//	return 1;
		//}

		//if (LOWORD(wParam) == IDC_PHYSICSDEBUG)
		//{
		//	int f = App->SBC_Scene->B_Player[0]->Phys_Body->getCollisionFlags();

		//	if (App->SBC_Player->Show_Physics_Debug == 1)
		//	{
		//		App->SBC_Player->Show_Physics_Debug = 0;
		//		App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f | (1 << 5));

		//		App->CL_Ogre->BulletListener->Render_Debug_Flag = 0;
		//		App->CL_Ogre->RenderFrame();
		//		App->CL_Ogre->BulletListener->Render_Debug_Flag = 1;
		//	}
		//	else
		//	{
		//		App->SBC_Player->Show_Physics_Debug = 1;
		//		App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f & (~(1 << 5)));
		//	}
		//	
		//	return 1;
		//}


		break;
	}
	return FALSE;
}

// *************************************************************************
// *					Hide_Player_Dlg Terry Bernie 					   *
// *************************************************************************
void WV_Player::Hide_Player_Dlg(bool Show)
{
	ShowWindow(Player_Props_HWND, Show);
}

// *************************************************************************
// *	  					Adjust_CapsuleTerry Bernie					   *
// *************************************************************************
void WV_Player::Adjust_Capsule(void)
{
	//App->SBC_Scene->B_Player[0]->Phys_Shape = new btCapsuleShape(btScalar(App->SBC_Scene->B_Player[0]->Capsule_Radius), btScalar(App->SBC_Scene->B_Player[0]->Capsule_Height));
	//App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionShape(App->SBC_Scene->B_Player[0]->Phys_Shape);

}

// *************************************************************************
// *	  					Rotate Terry Bernie							   *
// *************************************************************************
bool WV_Player::OnGround() const
{
	return App->CL_Scene->B_Player[0]->mOnGround;
}

// need to use ray cast for ground collision to handle stair case
#define __RAYTEST__


// *************************************************************************
// *	  				Check_Collisions Terry Bernie					   *
// *************************************************************************
void WV_Player::Check_Collisions(void)
{
	//int PlayerIndex = 0;
	//int UsageIndex = 0;

	///* Browse all collision pairs */
	//int numManifolds = App->SBC_Bullet->dynamicsWorld->getDispatcher()->getNumManifolds();
	//for (int i = 0; i<numManifolds; i++)
	//{
	//	btPersistentManifold* contactManifold = App->SBC_Bullet->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
	//	btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
	//	btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

	//	PlayerIndex = obA->getUserIndex(); // Should Be Player

	//	if (PlayerIndex == Enums::Usage_Player)
	//	{
	//		Life_Time = 0;
	//		Distance = 0;
	//		Col_Object_Index = obB->getUserIndex2(); // Object Index

	//		UsageIndex = obB->getUserIndex();

	//		 Sound Entity
	//		if (UsageIndex == Enums::Usage_Sound)
	//		{
	//			int numContacts = contactManifold->getNumContacts();
	//			for (int j = 0; j<numContacts; j++)
	//			{

	//				btManifoldPoint& pt = contactManifold->getContactPoint(j);

	//				Life_Time = pt.getLifeTime();
	//				Distance = pt.getDistance();
	//				Round = (int)Distance;

	//				/*if (Round < 0)
	//				{
	//					if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
	//					{
	//						App->Cl_Scene_Data->Sound_Entity(ColisionIndex);
	//						Last_ColisionIndex = Col_Object_Index;
	//					}
	//				}
	//				else if (Life_Time < 10)
	//				{
	//					if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
	//					{
	//						App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered = 0;
	//					}
	//				}*/
	//			}
	//		}

	//		 Message Entity
	//		if (UsageIndex == Enums::Usage_Message)
	//		{
	//			int numContacts = contactManifold->getNumContacts();
	//			for (int j = 0; j<numContacts; j++)
	//			{

	//				btManifoldPoint& pt = contactManifold->getContactPoint(j);

	//				Life_Time = pt.getLifeTime();
	//				Distance = pt.getDistance();
	//				Round = (int)Distance;

	//				/*if (Round < 0)
	//				{
	//					if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
	//					{
	//						App->Cl_Collision->Message_Entity(Col_Object_Index);
	//					}
	//				}
	//				else if (Round == 0)
	//				{
	//					if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
	//					{
	//						int Stock_Index = App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Entity[0].Stock_mIndex;
	//						App->Cl_Panels_Com->Show_Overlay(0, Stock_Index);
	//						App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered = 0;
	//					}
	//				}*/
	//			}
	//		}

	//		 Move Entity
	//		if (UsageIndex == Enums::Usage_Move)
	//		{
	//			int numContacts = contactManifold->getNumContacts();
	//			for (int j = 0; j<numContacts; j++)
	//			{

	//				btManifoldPoint& pt = contactManifold->getContactPoint(j);

	//				Life_Time = pt.getLifeTime();
	//				Distance = pt.getDistance();
	//				Round = (int)Distance;

	//				if (Round < 0)
	//				{
	//					if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
	//					{
	//						App->Cl_Collision->Move_Entity(Col_Object_Index);
	//					}
	//				}
	//				else if (Round == 0)
	//				{
	//					if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
	//					{
	//						/*int Stock_Index = App->GDCL_Scene_Data->CL_Object[ColisionIndex]->Entity[0].Stock_mIndex;
	//						App->GDCL_Scene_Data->S_Messages[Stock_Index]->overlay->hide();
	//						App->GDCL_Scene_Data->CL_Object[ColisionIndex]->Triggered = 0;*/
	//					}
	//				}
	//			}
	//		}

	//		 Collectable Entity
	//		if (UsageIndex == Enums::Usage_Colectable)
	//		{
	//			int numContacts = contactManifold->getNumContacts();
	//			for (int j = 0; j < numContacts; j++)
	//			{
	//				App->Cl_Collision->Do_Collectable(Col_Object_Index);
	//				btManifoldPoint& pt = contactManifold->getContactPoint(j);

	//				Life_Time = pt.getLifeTime();
	//				Distance = pt.getDistance();
	//				Round = (int)Distance;

	//				/*if (Round < 0)
	//				{
	//					if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
	//					{

	//						App->Cl_Collision->Do_Collectable(Col_Object_Index);
	//					}
	//				}
	//				else if (Round == 0)
	//				{
	//					if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
	//					{

	//					}
	//				}*/
	//			}
	//		}

	//		 Teleport Entity
	//		if (UsageIndex == Enums::Usage_Teleport)
	//		{
	//			int numContacts = contactManifold->getNumContacts();
	//			for (int j = 0; j < numContacts; j++)
	//			{
	//				App->Cl_Collision->Do_Teleport(Col_Object_Index);
	//				btManifoldPoint& pt = contactManifold->getContactPoint(j);

	//				Life_Time = pt.getLifeTime();
	//				Distance = pt.getDistance();
	//				Round = (int)Distance;

	//				/*if (Round < 0)
	//				{
	//					if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
	//					{

	//							App->Cl_Scene_Data->Do_Teleport(ColisionIndex);
	//					}
	//				}
	//				else if (Round == 0)
	//				{
	//					if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
	//					{

	//					}
	//				}*/
	//			}
	//		}

	//		 Environment Entity
	//		if (UsageIndex == Enums::Usage_Environment)
	//		{
	//			int numContacts = contactManifold->getNumContacts();
	//			for (int j = 0; j < numContacts; j++)
	//			{

	//				btManifoldPoint& pt = contactManifold->getContactPoint(j);

	//				Life_Time = pt.getLifeTime();
	//				Distance = pt.getDistance();
	//				Round = (int)Distance;

	//				/*if (Round < 0)
	//				{
	//					if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
	//					{

	//						App->Cl_Collision->Do_Environment(Col_Object_Index);
	//						Last_ColisionIndex = Col_Object_Index;
	//					}
	//				}
	//				else if (Round < 10)
	//				{
	//					if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
	//					{
	//						App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered = 0;
	//					}
	//				}*/
	//			}
	//		}
	//	}

	//}
}

// *************************************************************************
// *	  				Check_Collisions_New Terry Flanigan				   *
// *************************************************************************
void WV_Player::Check_Collisions_New(void)
{
	//int UsageIndex = 0;
	//Col_Player_Index = 0;
	//Col_Usage_Index = 0;
	//Col_numManifolds = 0;

	///* Browse all collision pairs */
	//Col_numManifolds = App->SBC_Bullet->dynamicsWorld->getDispatcher()->getNumManifolds();

	//for (int i = 0; i < Col_numManifolds; i++)
	//{
	//	btPersistentManifold* contactManifold = App->SBC_Bullet->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
	//	btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
	//	btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

	//	Col_Player_Index = obA->getUserIndex();  // Should Be Player
	//	Col_Object_Index = obB->getUserIndex2(); // Object Index

	//	UsageIndex = obB->getUserIndex();
	//	if (Col_Player_Index == Enums::Usage_Player)
	//	{
	//		Col_Object_Index = obB->getUserIndex2(); // Object Index
	//		Col_Usage_Index = obB->getUserIndex();


	//		if (Col_Usage_Index == 123)// && App->SBC_Scene->V_Object[Last_Message_Index]->Triggered == 1)
	//		{
	//			if (App->SBC_Scene->Object_Count > 0)
	//			{
	//				App->SBC_Scene->V_Object[Last_Message_Index]->Show_Message_Flag = 0;
	//				App->SBC_Scene->V_Object[Last_Message_Index]->Triggered = 0;
	//			}
	//		}
	//		else
	//		{
	//			//App->CL_Vm_ImGui->Show_Collision_Debug = 1;

	//			Col_Usage_Index = obB->getUserIndex();

	//			// -------------------- Message Collision
	//			if (Col_Usage_Index == Enums::Usage_Message)
	//			{
	//			
	//				int numContacts = contactManifold->getNumContacts();
	//				for (int j = 0; j < numContacts; j++)
	//				{
	//					btManifoldPoint& pt = contactManifold->getContactPoint(j);

	//					Life_Time = pt.getLifeTime();
	//					Distance = pt.getDistance();
	//					Round = (int)Distance;

	//					if (Round < 0)
	//					{
	//						if (App->SBC_Scene->V_Object[Col_Object_Index]->Triggered == 0)
	//						{
	//							Last_Message_Index = Col_Object_Index;
	//							App->SBC_Collision->Message_Entity(Col_Object_Index);
	//						}
	//					}
	//					else if (Round == 0)
	//					{
	//						if (App->SBC_Scene->V_Object[Col_Object_Index]->Triggered == 1)
	//						{
	//							App->SBC_Scene->V_Object[Col_Object_Index]->Show_Message_Flag = 0;
	//							App->SBC_Scene->V_Object[Col_Object_Index]->Triggered = 0;

	//						}
	//					}
	//				}
	//			}
	//			
	//			// -------------------- Sound Collision
	//			if (Col_Usage_Index == Enums::Usage_Sound)
	//			{
	//				int numContacts = contactManifold->getNumContacts();
	//				for (int j = 0; j < numContacts; j++)
	//				{

	//					btManifoldPoint& pt = contactManifold->getContactPoint(j);

	//					Life_Time = pt.getLifeTime();
	//					Distance = pt.getDistance();
	//					Round = (int)Distance;

	//					if (Round < 0)
	//					{
	//						if (App->SBC_Scene->V_Object[Col_Object_Index]->Triggered == 0)
	//						{
	//							App->SBC_Collision->Play_Sound(Col_Object_Index);
	//							Last_ColisionIndex = Col_Object_Index;
	//						}
	//					}
	//					else if (Life_Time < 10)
	//					{
	//						if (App->SBC_Scene->V_Object[Col_Object_Index]->Triggered == 1)
	//						{
	//							App->SBC_Scene->V_Object[Col_Object_Index]->Triggered = 0;
	//						}
	//					}
	//				}
	//			}

	//			// -------------------- Move Collision
	//			if (Col_Usage_Index == Enums::Usage_Move)
	//			{

	//				int numContacts = contactManifold->getNumContacts();
	//				for (int j = 0; j < numContacts; j++)
	//				{
	//					btManifoldPoint& pt = contactManifold->getContactPoint(j);

	//					Life_Time = pt.getLifeTime();
	//					Distance = pt.getDistance();
	//					Round = (int)Distance;

	//					if (Round < 0)
	//					{
	//						if (App->SBC_Scene->V_Object[Col_Object_Index]->Triggered == 0)
	//						{
	//							App->SBC_Collision->Move_Entity_Collision(Col_Object_Index);
	//						}
	//					}
	//					else if (Round == 0)
	//					{
	//						if (App->SBC_Scene->V_Object[Col_Object_Index]->Triggered == 1)
	//						{
	//							
	//						}
	//					}
	//					
	//				}
	//			}

	//			// -------------------- Collectable Collision
	//			if (UsageIndex == Enums::Usage_Colectable)
	//			{
	//				int numContacts = contactManifold->getNumContacts();
	//				for (int j = 0; j < numContacts; j++)
	//				{
	//					if (App->SBC_Scene->V_Object[Col_Object_Index]->Triggered == 0)
	//					{
	//						App->SBC_Collision->Do_Collectable(Col_Object_Index);
	//					}
	//				}

	//			}

	//			// -------------------- Teleport Collision
	//			if (UsageIndex == Enums::Usage_Teleport)
	//			{
	//				int numContacts = contactManifold->getNumContacts();
	//				for (int j = 0; j < numContacts; j++)
	//				{
	//					App->SBC_Collision->Do_Teleport(Col_Object_Index);
	//					btManifoldPoint& pt = contactManifold->getContactPoint(j);

	//					Life_Time = pt.getLifeTime();
	//					Distance = pt.getDistance();
	//					Round = (int)Distance;

	//					if (Round < 0)
	//					{
	//						if (App->SBC_Scene->V_Object[Col_Object_Index]->Triggered == 0)
	//						{

	//							App->SBC_Collision->Do_Teleport(Col_Object_Index);
	//						}
	//					}
	//					else if (Round == 0)
	//					{
	//						if (App->SBC_Scene->V_Object[Col_Object_Index]->Triggered == 1)
	//						{

	//						}
	//					}
	//				}
	//			}

	//			// -------------------- EnvironEntity Collision
	//			if (UsageIndex == Enums::Usage_EnvironEntity)
	//			{
	//				int numContacts = contactManifold->getNumContacts();
	//				for (int j = 0; j < numContacts; j++)
	//				{
	//					btManifoldPoint& pt = contactManifold->getContactPoint(j);

	//					Life_Time = pt.getLifeTime();
	//					Distance = pt.getDistance();
	//					Round = (int)Distance;

	//					if (Round < 0)
	//					{
	//						if (App->SBC_Scene->V_Object[Col_Object_Index]->Triggered == 0)
	//						{
	//							App->SBC_Collision->Do_Environment(Col_Object_Index);
	//						}
	//					}
	//					else if (Round == 0)
	//					{
	//						if (App->SBC_Scene->V_Object[Col_Object_Index]->Triggered == 1)
	//						{
	//							App->SBC_Scene->V_Object[Col_Object_Index]->Triggered = 0;
	//						}
	//					}
	//				}
	//			}

	//			// ----------------
	//		}
	//	}
	//	
	//}

}

