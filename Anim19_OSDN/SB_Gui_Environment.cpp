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
#include "SB_Gui_Environment.h"

SB_Gui_Environment::SB_Gui_Environment(void)
{
	Show_PropertyEditor = 0;
	PropertyEditor_Page = 0;

	Ambient_Int_Red = 0;
	Ambient_Int_Green = 0;
	Ambient_Int_Blue = 0;

	Fog_Colour_Int_Red = 0;
	Fog_Colour_Int_Green = 0;
	Fog_Colour_Int_Blue = 0;

	Float_PosX = 0;
	Float_PosY = 0;
	Float_StartPos = 0;

	Eviron_Index = 0;

	Is_Teleport = 0;

	ClickOnTrack = 0;
	ClickOnVolume = 0;
	ClickOnPlay = 0;
	ClickOnLoop = 0;

	ClickOnFogVisible = 0;
	ClickOnFogMode = 0;
	ClickOnFogColour = 0;
	ClickOnFogStart = 0;
	ClickOnFogEnd = 0;

	ClickOnSkyEnabled = 0;
	ClickOnSkyTiling = 0;
	ClickOnSkyCurve = 0;

}

SB_Gui_Environment::~SB_Gui_Environment(void)
{
}

// *************************************************************************
// *		 Reset_Evironment:- Terry and Hazel Flanigan 2023  			   *
// *************************************************************************
void SB_Gui_Environment::Reset_Class()
{
	if (App->SBC_Scene->Scene_Loaded == 1)
	{
		App->SBC_Ogre->mSceneMgr->setSkyDome(false, "Examples/CloudySky");

		Show_PropertyEditor = 0;
		PropertyEditor_Page = 0;

		Ambient_Int_Red = 0;
		Ambient_Int_Green = 0;
		Ambient_Int_Blue = 0;

		Fog_Colour_Int_Red = 0;
		Fog_Colour_Int_Green = 0;
		Fog_Colour_Int_Blue = 0;

		Float_PosX = 0;
		Float_PosY = 0;
		Float_StartPos = 0;

		Eviron_Index = 0;

		Is_Teleport = 0;

		ClickOnTrack = 0;
		ClickOnVolume = 0;
		ClickOnPlay = 0;
		ClickOnLoop = 0;

		ClickOnFogVisible = 0;
		ClickOnFogMode = 0;
		ClickOnFogColour = 0;
		ClickOnFogStart = 0;
		ClickOnFogEnd = 0;

		ClickOnSkyEnabled = 0;
		ClickOnSkyTiling = 0;
		ClickOnSkyCurve = 0;
	}
}


// *************************************************************************
// *	 Start_Environment_Editor:- Terry and Hazel Flanigan 2023  		   *
// *************************************************************************
void SB_Gui_Environment::Start_Environment_Editor(int Index,bool IsTeleport)
{
	Eviron_Index = Index;
	Is_Teleport = IsTeleport;

	Float_Exit = 0;

	Ambient_Colour_Copy.x = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->AmbientColour.x;
	Ambient_Colour_Copy.y = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->AmbientColour.y;
	Ambient_Colour_Copy.z = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->AmbientColour.z;

	Ambient_Colour.x = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->AmbientColour.x;
	Ambient_Colour.y = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->AmbientColour.y;
	Ambient_Colour.z = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->AmbientColour.z;

	Ambient_Int_Red = Ambient_Colour.x * 255;
	Ambient_Int_Green = Ambient_Colour.y * 255;
	Ambient_Int_Blue = Ambient_Colour.z * 255;

	Fog_Colour_Copy.x = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_Colour.x;
	Fog_Colour_Copy.y = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_Colour.y;
	Fog_Colour_Copy.z = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_Colour.z;

	Fog_Colour.x = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_Colour.x;
	Fog_Colour.y = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_Colour.y;
	Fog_Colour.z = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_Colour.z;

	Fog_Colour_Int_Red = Fog_Colour.x * 255;
	Fog_Colour_Int_Green = Fog_Colour.y * 255;
	Fog_Colour_Int_Blue = Fog_Colour.z * 255;


	/*App->Disable_Panels(true);
	App->Show_Panels(false);*/

	App->SBC_FileView->Show_FileView(false);
	App->SBC_Com_Environments->Set_Environment_By_Index(1, Eviron_Index);

	Show_PropertyEditor = 1;
}

// *************************************************************************
// *		Environ_PropertyEditor:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Gui_Environment::Environ_PropertyEditor()
{

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(350, 190), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Environment Editor", &Show_PropertyEditor, ImGuiWindowFlags_NoResize| ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
		return;
	}

	ImGuiColorEditFlags misc_flags2 = (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8);

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(213, 222, 242, 255));

	ImGui::Columns(2);
	ImGui::SetColumnWidth(-1, 120);

	if (ImGui::Button(" Main Light ",ImVec2(100, 0)))
	{
		PropertyEditor_Page = 0;
	}

	if (ImGui::Button("Sound   ", ImVec2(100, 0)))
	{
		PropertyEditor_Page = 1;
	}

	if (ImGui::Button("Fog   ", ImVec2(100, 0)))
	{
		PropertyEditor_Page = 2;
	}

	if (ImGui::Button("Sky   ", ImVec2(100, 0)))
	{
		PropertyEditor_Page = 3;
	}

	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	
	// ---------------------------------------------------------------- Main Light
	if (PropertyEditor_Page == 0)
	{
		ImGui::NextColumn();
		ImGui::AlignTextToFramePadding();

		ImGui::Text("Ambient Colour:");
		ImGui::SameLine();

		if (ImGui::ColorEdit3("", (float*)&Ambient_Colour, ImGuiColorEditFlags_NoInputs | misc_flags2))
		{
			Ambient_Int_Red = Ambient_Colour.x * 255;
			Ambient_Int_Green = Ambient_Colour.y * 255;
			Ambient_Int_Blue = Ambient_Colour.z * 255;

			App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->AmbientColour = Ogre::Vector3(Ambient_Colour.x, Ambient_Colour.y, Ambient_Colour.z);
			App->SBC_Ogre->mSceneMgr->setAmbientLight(ColourValue(Ambient_Colour.x, Ambient_Colour.y, Ambient_Colour.z));

			App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
		}

	}

	// ---------------------------------------------------------------- Sound
	if (PropertyEditor_Page == 1)
	{
		ImGui::NextColumn();
		ImGui::AlignTextToFramePadding();
		
		ImGui::Selectable("Track:- ", &ClickOnTrack);
		ImGui::SameLine();
		ImGui::Text("%s", App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Sound_File);

		if (ClickOnTrack)
		{
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.24f, 1.f), "ON");

			App->SBC_SoundMgr->Accessed = 1;
			strcpy(App->SBC_SoundMgr->Access_File, App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Sound_File);

			App->SBC_Com_Environments->Set_Environment_By_Index(0, Eviron_Index);
			App->SBC_SoundMgr->Dialog_SoundFile();

			if (App->SBC_SoundMgr->IsCancelled == 0)
			{

				strcpy(App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Sound_File, App->SBC_SoundMgr->Access_File);
				App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->SndVolume = App->SBC_SoundMgr->SndVolume;

				App->SBC_Com_Environments->Set_Environment_By_Index(1, Eviron_Index);

				App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
			}
			else
			{
				App->SBC_Com_Environments->Set_Environment_By_Index(1, Eviron_Index);
			}

			ClickOnTrack = 0;
		}
		
		// ----------------- Volume
		ImGui::Selectable("Volume:- ", &ClickOnVolume);
		ImGui::SameLine();
		ImGui::Text("%f", App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->SndVolume);
		if (ClickOnVolume)
		{
			App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
			ClickOnVolume = 0;
		}

		// ----------------- Play
		ImGui::Selectable("Play:- ", &ClickOnPlay);
		ImGui::SameLine();
		ImGui::Text("%i", App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Play);
		if (ClickOnPlay)
		{
			strcpy(App->Cl_Dialogs->btext, "Set Play Sound Track");

			App->Cl_Dialogs->TrueFlase = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Play;

			App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

			if (App->Cl_Dialogs->Canceled == 0)
			{
				if (App->Cl_Dialogs->TrueFlase == 1)
				{
					App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Play = 1;
					App->SBC_Com_Environments->Set_Environment_By_Index(1, Eviron_Index);
				}
				else
				{
					App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Play = 0;
					App->SBC_Com_Environments->Set_Environment_By_Index(0, Eviron_Index);
				}

				App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
			}

			App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
			ClickOnPlay = 0;
		}

		// ----------------- Loop
		ImGui::Selectable("Loop:- ", &ClickOnLoop);
		ImGui::SameLine();
		ImGui::Text("%i", App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Loop);
		if (ClickOnLoop)
		{
			strcpy(App->Cl_Dialogs->btext, "Set Play Sound Loop");

			App->Cl_Dialogs->TrueFlase = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Loop;

			App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

			if (App->Cl_Dialogs->Canceled == 0)
			{
				if (App->Cl_Dialogs->TrueFlase == 1)
				{
					App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Loop = 1;
					App->SBC_Com_Environments->Set_Environment_By_Index(0, Eviron_Index);
					App->SBC_Com_Environments->Set_Environment_By_Index(1, Eviron_Index);
				}
				else
				{
					App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Loop = 0;
					App->SBC_Com_Environments->Set_Environment_By_Index(0, Eviron_Index);
					App->SBC_Com_Environments->Set_Environment_By_Index(1, Eviron_Index);
				}

				App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
			}

			ClickOnLoop = 0;
		}
	}

	// ---------------------------------------------------------------- Fog
	if (PropertyEditor_Page == 2)
	{
		ImGui::NextColumn();
		ImGui::AlignTextToFramePadding();

		// ----------------- Visible
		ImGui::Selectable("Visible:- ", &ClickOnFogVisible);
		ImGui::SameLine();
		ImGui::Text("%i", App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_On);
		if (ClickOnFogVisible)
		{
			strcpy(App->Cl_Dialogs->btext, "Set Fog Visiblity");

			App->Cl_Dialogs->TrueFlase = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_On;

			strcpy(App->Cl_Dialogs->btext, "Set Fog On/Off");
			App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

			if (App->Cl_Dialogs->Canceled == 0)
			{
				if (App->Cl_Dialogs->TrueFlase == 1)
				{
					App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_On = 1;
					EnableFog(true);
				}
				else
				{
					App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_On = 0;
					EnableFog(false);
				}

				App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
			}

	
			ClickOnFogVisible = 0;
		}

		// ----------------- Mode
		ImGui::Selectable("Mode:- ", &ClickOnFogMode);
		ImGui::SameLine();
		ImGui::Text("%i", App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_Mode);
		if (ClickOnFogMode)
		{
			ClickOnFogMode = 0;
		}

		// ----------------- Fog Colour
		ImGui::Text("Fog Colour:");
		ImGui::SameLine();

		if (ImGui::ColorEdit3("", (float*)&Fog_Colour, ImGuiColorEditFlags_NoInputs | misc_flags2))
		{
			Ambient_Int_Red = Fog_Colour.x * 255;
			Ambient_Int_Green = Fog_Colour.y * 255;
			Ambient_Int_Blue = Fog_Colour.z * 255;

			App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_Colour = Ogre::Vector3(Fog_Colour.x, Fog_Colour.y, Fog_Colour.z);

			if (App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_On == 1)
			{
				EnableFog(true);
			}

			App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
		}



		// ----------------- Start
		ImGui::Text("Start:- ", App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_Start);
		ImGui::SameLine();
		
		if (ImGui::InputFloat("##1", &App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_Start, 1, 0, "%.3f"))
		{
			if (App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_On == 1)
			{
				EnableFog(true);
			}

			App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
		}

		// ----------------- End
		ImGui::Text("End:-   ", App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_End);
		ImGui::SameLine();

		if (ImGui::InputFloat("##2", &App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_End, 1, 0, "%.3f"))
		{
			if (App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Fog_On == 1)
			{
				EnableFog(true);
			}

			App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
		}

	}

	// ---------------------------------------------------------------- Sky
	if (PropertyEditor_Page == 3)
	{
		ImGui::NextColumn();
		ImGui::AlignTextToFramePadding();

		// ----------------- Visible
		ImGui::Selectable("Enabled:- ", &ClickOnSkyEnabled);
		ImGui::SameLine();
		ImGui::Text("%i", App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Enabled);
		if (ClickOnSkyEnabled)
		{
			strcpy(App->Cl_Dialogs->btext, "Set Sky Visiblity");

			App->Cl_Dialogs->TrueFlase = App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Enabled;

			strcpy(App->Cl_Dialogs->btext, "Set Sky On/Off");
			App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

			if (App->Cl_Dialogs->Canceled == 0)
			{
				if (App->Cl_Dialogs->TrueFlase == 1)
				{
					App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Enabled = 1;
					SetSky(1);
				}
				else
				{
					App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Enabled = 0;
					SetSky(0);
				}

				App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
			}

			ClickOnSkyEnabled = 0;
		}

		// ----------------- Tiling
		ImGui::Text("Tiling:- ", App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Tiling);
		ImGui::SameLine();

		if (ImGui::InputFloat("##5", &App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Tiling, 0.5, 0, "%.3f"))
		{
			if (App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Enabled == 1)
			{
				SetSky(true);
			}

			App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
		}

		// ----------------- Curvature
		ImGui::Text("Curve:- ", App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Curvature);
		ImGui::SameLine();

		if (ImGui::InputFloat("##6", &App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Curvature, 0.5, 0, "%.3f"))
		{
			if (App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Enabled == 1)
			{
				SetSky(true);
			}

			App->SBC_Com_Environments->Mark_As_Altered_Environ(Eviron_Index);
		}

	}
	
	ImGui::PopStyleVar();
	ImGui::Columns(0);
	
	ImGui::Spacing();
	ImGui::Spacing();

	if (ImGui::Button("Close", ImVec2(100, 0)))
	{
		Close_Environment_Editor();

		ImGui::PopStyleColor();
		PropertyEditor_Page = 0;
		Show_PropertyEditor = 0;
	}

	if (Is_Teleport == 1)
	{
		ImGui::SameLine();
		if (ImGui::Button("Goto Location", ImVec2(120, 0)))
		{
			App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().setOrigin(App->SBC_Scene->B_Object[Eviron_Index]->S_Teleport[0]->Physics_Position);
			App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->SBC_Scene->B_Object[Eviron_Index]->S_Teleport[0]->Physics_Rotation);
			Set_To_PlayerView();
		}

		ImGui::SameLine();
		if (ImGui::Checkbox("Enabled", &App->SBC_Scene->B_Object[Eviron_Index]->S_Environ[0]->Environ_Enabled))
		{
			App->SBC_Properties->Update_ListView_Teleport();
		}
	}

	
	ImGui::End();
}

// *************************************************************************
// *	 Close_Environment_Editor:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Gui_Environment::Close_Environment_Editor()
{
	/*App->Disable_Panels(false);
	App->Show_Panels(true);*/

	App->SBC_FileView->Show_FileView(true);
	int Index = App->SBC_Properties->Current_Selected_Object;
	App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);

	Index = App->SBC_Com_Environments->Get_First_Environ();
	App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);
}

// *************************************************************************
// *		 Set_To_PlayerView:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Gui_Environment::Set_To_PlayerView()
{
	App->SBC_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;
	App->SBC_TopTabs->Toggle_FirstCam_Flag = 1;
	App->SBC_TopTabs->Toggle_FreeCam_Flag = 0;

	App->SBC_Scene->B_Player[0]->Player_Node->setVisible(false);

	int f = App->SBC_Scene->B_Player[0]->Phys_Body->getCollisionFlags();
	App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f | (1 << 5));

	App->SBC_Ogre->BulletListener->Render_Debug_Flag = 0;
	App->SBC_Ogre->BulletListener->Render_Debug_Flag = 1;

	App->SBC_Ogre->OgreListener->GD_Run_Physics = 1;

	RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *	  		SetSky:- Terry and Hazel Flanigan 2023					   *
// *************************************************************************
void SB_Gui_Environment::SetSky(bool Enable)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	App->SBC_Ogre->mSceneMgr->setSkyDome(Enable,
		App->SBC_Scene->B_Object[Index]->S_Environ[0]->Material,
		App->SBC_Scene->B_Object[Index]->S_Environ[0]->Curvature,
		App->SBC_Scene->B_Object[Index]->S_Environ[0]->Tiling,
		App->SBC_Scene->B_Object[Index]->S_Environ[0]->Distance);
}

// *************************************************************************
// *	  		EnableFog:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
bool SB_Gui_Environment::EnableFog(bool SetFog)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	if (SetFog == true)
	{
		float Start = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Start;
		float End = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_End;
		float Density = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Density;

		float x = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.x;
		float y = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.y;
		float z = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.z;

		App->SBC_Ogre->mSceneMgr->setFog(FOG_LINEAR, ColourValue(x, y, z), Density, (Ogre::Real)Start, (Ogre::Real)End);
	}
	else
	{
		App->SBC_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}

	return 1;
}
