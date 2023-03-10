/*
Copyright (c) 2022 - 2023 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Editor_Gui.h"

SB_Editor_Gui::SB_Editor_Gui()
{
	Show_App_Data_F = 0;

	AppData_DoOnce = 0;

	App_Data_PosX = 500;
	App_Data_PosY = 500;
}

SB_Editor_Gui::~SB_Editor_Gui()
{
}

// *************************************************************************
// *		ImGui_Editor_Loop:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Editor_Gui::ImGui_Editor_Loop(void)
{
	/*if (App->CL_Prefs->Show_Preferences_GUI == 1)
	{
		App->CL_Prefs->Preferences_GUI();
	}

	if (Show_Model_Data_F == 1)
	{
		Model_Data_GUI();
	}

	if (Show_Group_Data_F == 1)
	{
		Group_Data_GUI();
	}*/

	if (Show_App_Data_F == 1)
	{
		App_Data_GUI();
	}

	if (App->CL_Logger->Show_Log_Data_F == 1)
	{
		App->CL_Logger->Log_Data_GUI();
	}

}

// *************************************************************************
// *			Start_App_Data:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Editor_Gui::Start_App_Data(void)
{

	//App->CL_Panels->Enable_Panels(0);
	
	App_Data_PosX = ((float)App->CL_Ogre->OgreListener->View_Width / 2) - (530 / 2);
	App_Data_PosY = ((float)App->CL_Ogre->OgreListener->View_Height / 2) - (550 / 2);

	AppData_DoOnce = 0;
	Show_App_Data_F = 1;
}

// *************************************************************************
// *			App_Data_GUI:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Editor_Gui::App_Data_GUI(void)
{
	
	ImGui::SetNextWindowPos(ImVec2(App_Data_PosX, App_Data_PosY), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(530, 550), ImGuiCond_FirstUseEver);


	if (!ImGui::Begin("App Data", &Show_App_Data_F, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		if (AppData_DoOnce == 0)
		{
			App_Data_PosX = ((float)App->CL_Ogre->OgreListener->View_Width / 2) - (530 / 2);
			App_Data_PosY = ((float)App->CL_Ogre->OgreListener->View_Height / 2) - (550 / 2);
			ImGui::SetWindowPos("App Data", ImVec2(App_Data_PosX, App_Data_PosY));
			AppData_DoOnce = 1;
		}

		ImGui::Spacing();
		ImGui::Text("App Info");
		ImGui::Separator();
		ImGui::Text("  ");


		// ----------------------------- Camera
		char Header[255];

		// ----------------------------- Scene
		sprintf(Header, "%s", "Scene        ");

		if (ImGui::CollapsingHeader(Header))
		{
			ImGui::Text("%s %i", "Project Loaded = ", App->SBC_Project->Project_Loaded);
			ImGui::Text("%s %i", "Scene Loaded = ", App->SBC_Scene->Scene_Loaded);

			ImGui::Text("%s %i", "Player Added = ", App->SBC_Scene->Player_Added);
			ImGui::Text("%s %i", "Player Count = ", App->SBC_Scene->Player_Count);

			ImGui::Text("%s %i", "Aera Added = ", App->SBC_Scene->Player_Added);
			ImGui::Text("%s %i", "Aera Count = ", App->SBC_Scene->Area_Count);

			ImGui::Text("%s %i", "Camera Added = ", App->SBC_Scene->Camera_Added);
			ImGui::Text("%s %i", "Camera Count = ", App->SBC_Scene->Camera_Count);

			ImGui::Text("%s %i", "Objects Added = ", App->SBC_Scene->Objects_Added);
			ImGui::Text("%s %i", "Objects Count = ", App->SBC_Scene->Object_Count);

			ImGui::Text("%s %i", "Physics Running = ", App->CL_Ogre->OgreListener->GD_Run_Physics);
			ImGui::Text("%s %i", "Physics Debuging = ", App->CL_Ogre->OgreListener->Dubug_Physics_Draw);
			ImGui::Text(" ");
			ImGui::Text("Vectors");
			ImGui::Text("%s %i", "Object Vector Size = ", App->SBC_Scene->Get_Object_SizeCounter());
			ImGui::Text("%s %i", "Object Capacity = ", App->SBC_Scene->V_Object.capacity());
			ImGui::Text("%s %i", "Object Capacity = ", App->SBC_Scene->V_Object.max_size());
		}


		sprintf(Header, "%s", "Camera        ");
		if (ImGui::CollapsingHeader(Header))
		{
			
			ImGui::Text("Camera Mode:- %i", App->CL_Ogre->OgreListener->GD_CameraMode);
			ImGui::Text(" ");
			ImGui::Text("%s %f", "Pos_X = ", App->CL_Ogre->mCamera->getPosition().x);
			ImGui::Text("%s %f", "Pos_Y = ", App->CL_Ogre->mCamera->getPosition().y);
			ImGui::Text("%s %f", "Pos_Z = ", App->CL_Ogre->mCamera->getPosition().z);

			ImGui::Text("%s %f", "Rot_X = ", App->CL_Ogre->mCamera->getOrientation().x);
			ImGui::Text("%s %f", "Rot_Y = ", App->CL_Ogre->mCamera->getOrientation().y);
			ImGui::Text("%s %f", "Rot_Z = ", App->CL_Ogre->mCamera->getOrientation().z);
		}

		ImGui::SetCursorPos(ImVec2(460,5));
		
		if (ImGui::Button("Close"))
		{
			Close_App_Data();
		}

		ImGui::End();
	}
}

// *************************************************************************
// *			Close_App_Data:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Editor_Gui::Close_App_Data(void)
{
	AppData_DoOnce = 0;
	//App->CL_Panels->Enable_Panels(1);
	Show_App_Data_F = 0;
}
