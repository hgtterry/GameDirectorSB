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
#include "GD19_App.h"
#include "resource.h"
#include "SB_Aera.h"


SB_Aera::SB_Aera()
{
	Area_Props_HWND = nullptr;

	Show_Physics_Debug = 0;
}


SB_Aera::~SB_Aera()
{
}

// *************************************************************************
// *	  				Start_Area_PropsPanel Terry Bernie				   *
// *************************************************************************
bool SB_Aera::Start_Area_PropsPanel()
{

	Area_Props_HWND = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_AERA, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Area_PropsPanel_Proc);
	return 1;
}
// *************************************************************************
// *				Area_PropsPanel_Proc  Terry Bernie					   *
// *************************************************************************
LRESULT CALLBACK SB_Aera::Area_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		
		SendDlgItemMessage(hDlg, IDC_PHYSICSAREADEBUG, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

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

		if (some_item->idFrom == IDC_PHYSICSAREADEBUG && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Aera->Show_Physics_Debug);
			return CDRF_DODEFAULT;
		}
		
		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_PHYSICSAREADEBUG)
		{
			int f = App->Cl_Scene_Data->Cl_Object[0]->bt_body->getCollisionFlags();

			if (App->SBC_Aera->Show_Physics_Debug == 1)
			{
				App->SBC_Aera->Show_Physics_Debug = 0;
				App->Cl_Scene_Data->Cl_Object[0]->bt_body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->Cl19_Ogre->RenderFrame();
				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 1;
			}
			else
			{
				App->SBC_Aera->Show_Physics_Debug = 1;
				App->Cl_Scene_Data->Cl_Object[0]->bt_body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
			}

			return 1;
		}


		break;
	}
	return FALSE;
}

// *************************************************************************
// *						Hide_Area_Dlg Terry Bernie 					   *
// *************************************************************************
void SB_Aera::Hide_Area_Dlg(bool Show)
{
	ShowWindow(Area_Props_HWND, Show);
}

// *************************************************************************
// *					Add_Area Terry Flanigan 						   *
// *************************************************************************
void SB_Aera::Add_Area()
{
	int Index = App->SBC_Scene->Area_Count;


	if (App->SBC_Scene->SBC_Base_Area[Index])
	{
		if (App->SBC_Scene->SBC_Base_Area[Index]->Area_Ent && App->SBC_Scene->SBC_Base_Area[Index]->Area_Node)
		{
			App->SBC_Scene->SBC_Base_Area[Index]->Area_Node->detachAllObjects();
			App->Cl19_Ogre->mSceneMgr->destroySceneNode(App->SBC_Scene->SBC_Base_Area[Index]->Area_Node);
			App->Cl19_Ogre->mSceneMgr->destroyEntity(App->SBC_Scene->SBC_Base_Area[Index]->Area_Ent);
			App->SBC_Scene->SBC_Base_Area[Index]->Area_Ent = NULL;
			App->SBC_Scene->SBC_Base_Area[Index]->Area_Node = NULL;

			delete App->SBC_Scene->SBC_Base_Area[Index];
			App->SBC_Scene->SBC_Base_Area[Index] = nullptr;
		}
	}

	App->SBC_Scene->SBC_Base_Area[Index] = new Base_Area();
	App->SBC_Scene->SBC_Base_Area[Index]->Object_ID = 0; //App->Cl_Scene_Data->Object_ID_Counter;

	Base_Area* Object = App->SBC_Scene->SBC_Base_Area[Index];

	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(App->Cl19_Ogre->Level_Resource_Group);
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(App->Cl19_Ogre->Level_Resource_Group);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(App->CL_Vm_Model->Model_FolderPath,
		"FileSystem",
		App->Cl19_Ogre->Level_Resource_Group);

	try
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch (...)
	{

	}

	Object->Area_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("UserMesh", App->CL_Vm_Model->FileName, App->Cl19_Ogre->Level_Resource_Group);
	Object->Area_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->Area_Node->attachObject(Object->Area_Ent);

	Object->Area_Node->setVisible(true);
	Object->Area_Node->setPosition(0, 0, 0);
	Object->Area_Node->setScale(1, 1, 1);

	Object->create_New_Trimesh(Object->Area_Ent);

	Object->Usage = Enums::Usage_Room;

	App->SBC_Scene->Area_Added = 1;

	App->Cl_Grid->Grid_SetVisible(1);

	App->Cl_Scene_Data->ObjectCount++;
}

