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
#include "SB_Scene.h"


SB_Scene::SB_Scene()
{
	Player_Count = 0;
	Area_Count = 0;
	Object_Count = 0;

	SBC_Base_Player[100] = { nullptr };
	SBC_Base_Area[100] = { nullptr };

	Scene_Loaded = 0;
	Player_Added = 0;
	Area_Added = 0;

}


SB_Scene::~SB_Scene()
{
}

// *************************************************************************
// *						Clear_Level Terry Flanigan					   *
// *************************************************************************
bool SB_Scene::Clear_Level()
{

	App->SBC_FileView->Reset_Class();
	App->SBC_TopTabs->Reset_Class();
	App->SBC_Properties->Reset_Class();

	App->Set_Main_TitleBar(" ");

	if (App->SBC_Scene->Scene_Loaded == 1)
	{
		App->SBC_Physics->Enable_Physics(0);

		App->SBC_Player->Reset_Class();
		App->SBC_Aera->Reset_Class();


		// Bullet Related
		int i;
		for (i = App->Cl_Bullet->dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = App->Cl_Bullet->dynamicsWorld->getCollisionObjectArray()[i];
			App->Cl_Bullet->dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}

		App->SBC_Resources->Unload_Game_Resources();
	}

	App->Cl_Scene_Data->ObjectCount = 0;

	Player_Count = 0;
	Area_Count = 0;

	Scene_Loaded = 0;
	Area_Added = 0;
	Player_Added = 0;

	App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamNone;

	App->SBC_Camera->Reset_View();
	return 1;
}
