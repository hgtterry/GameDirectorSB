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
#include "SB_Debug.h"



SB_Debug::SB_Debug()
{
	Allow_Debug = 1;

	Show_Debug_Camera = 0;
	Show_Debug_Project = 0;
}

SB_Debug::~SB_Debug()
{
}

// *************************************************************************
// *						Debug_Render_Loop  Terry Flanigan			   *
// *************************************************************************
void SB_Debug::Debug_Render_Loop(void)
{
	if (Show_Debug_Camera == 1)
	{
		ImGui_Debug_Camera();
	}

	if (Show_Debug_Project == 1)
	{
		ImGui_Debug_Project();
	}
}

// *************************************************************************
// *					ImGui_Debug_Camera  Terry Flanigan				   *
// *************************************************************************
void SB_Debug::ImGui_Debug_Camera(void)
{
	ImGui::SetNextWindowPos(ImVec2(500, 30), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Camera_Debug", &Show_Debug_Camera, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		
		ImGui::Text("%s %f", "Pos_X = ", App->Cl19_Ogre->mCamera->getPosition().x);
		ImGui::Text("%s %f", "Pos_Y = ", App->Cl19_Ogre->mCamera->getPosition().y);
		ImGui::Text("%s %f", "Pos_Z = ", App->Cl19_Ogre->mCamera->getPosition().z);

		ImGui::Text("%s %.3f", "Rot_X = ", App->Cl19_Ogre->mCamera->getOrientation().getPitch().valueDegrees());
		ImGui::Text("%s %.3f", "Rot_Y = ", App->Cl19_Ogre->mCamera->getOrientation().getYaw().valueDegrees());

		App->Cl19_Ogre->mCamera->roll(Ogre::Degree(0));

		//App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getRotation()

		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Button("Close"))
		{
			Show_Debug_Camera = 0;
		}

		ImGui::End();
	}
}

// *************************************************************************
// *					ImGui_Debug_Project  Terry Bernie				   *
// *************************************************************************
void SB_Debug::ImGui_Debug_Project(void)
{
	ImGui::SetNextWindowPos(ImVec2(250, 30), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Project_Debug", &Show_Debug_Project, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		
		ImGui::Text("Sub_Folder: = %s", App->SBC_Project->m_Project_Sub_Folder);
		ImGui::Text("Asset_Path: = %s", App->SBC_Project->m_Main_Assets_Path);

		ImGui::Text("SourceFile: = %s", App->SBC_Objects_Create->SourceFile);
		ImGui::Text("DestFile: = %s", App->SBC_Objects_Create->DestinationFile);
		
		//ImGui::Text(" ");

		//ImGui::Text("Project Name: = %s", App->SBC_Project->m_Project_Name);
		//ImGui::Text("Level Name: = %s", App->SBC_Project->m_Level_Name);
		//ImGui::Text("Level File Name: = %s", App->SBC_Project->m_Level_File_Name);

		//ImGui::Text(" ");

		//ImGui::Text("Aera Folder Path: = %s", App->SBC_Project->m_Aera_Folder_Path);
		//ImGui::Text("Level Folder Path: = %s", App->SBC_Project->m_Level_Folder_Path);
		//ImGui::Text("Player Folder Path: = %s", App->SBC_Project->m_Players_Folder_Path);
		//
		//ImGui::Text(" ");

		////ImGui::Text("Project Folder Location: = %s", App->SBC_Project->m_Project_Folder_Path);
		//ImGui::Text("Ini Location: = %s", App->SBC_Project->m_Ini_Path_File_Name);
		//ImGui::Text("Sub Folder Location: = %s", App->SBC_Project->m_Project_Sub_Folder);
		//
		//ImGui::Spacing();
		//ImGui::Spacing();

		if (ImGui::Button("Close"))
		{
			Show_Debug_Project = 0;
		}

		ImGui::End();
	}
}
