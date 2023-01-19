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

	Show_ColourPicker = 0;
	ColourPicker_Canceled = 0;
	Colour_Int_Red = 0;
	Colour_Int_Green = 0;
	Colour_Int_Blue = 0;

	Float_PosX = 0;
	Float_PosY = 0;
	Float_StartPos = 0;

	ClickOnTrack = 0;
	ClickOnVolume = 0;
	ClickOnPlay = 0;
	ClickOnLoop = 0;

	ClickOnFogVisible = 0;
	ClickOnFogMode = 0;
	ClickOnFogColour = 0;
	ClickOnFogStart = 0;
	ClickOnFogEnd = 0;

}

SB_Gui_Environment::~SB_Gui_Environment(void)
{
}

// *************************************************************************
// *		Environ_PropertyEditor:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Gui_Environment::Environ_PropertyEditor()
{
	ImGui::SetNextWindowSize(ImVec2(350, 250), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin("Environment Editor", &Show_PropertyEditor, ImGuiWindowFlags_NoResize))
	{
		ImGui::End();
		return;
	}

	int Index = App->SBC_Properties->Current_Selected_Object;

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	
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

	if (ImGui::Button("Close", ImVec2(100, 0)))
	{
		Show_PropertyEditor = 0;
	}

	// ---------------------------------------------------------------- Main Light
	if (PropertyEditor_Page == 0)
	{
		ImGui::NextColumn();
		ImGui::AlignTextToFramePadding();

		ImGui::Text("Ambient Colour:");
		ImGui::SameLine();
		ImGuiColorEditFlags misc_flags2 = (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8);
		ImGui::ColorEdit3("", (float*)&Float_Colour, ImGuiColorEditFlags_NoInputs | misc_flags2);
		
		Colour_Int_Red = Float_Colour.x * 255;
		Colour_Int_Green = Float_Colour.y * 255;
		Colour_Int_Blue = Float_Colour.z * 255;

		App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour = Ogre::Vector3(Float_Colour.x, Float_Colour.y, Float_Colour.z);
		App->SBC_Ogre->mSceneMgr->setAmbientLight(ColourValue(Float_Colour.x, Float_Colour.y, Float_Colour.z));

		//Do_Colour_Picker();
	}

	// ---------------------------------------------------------------- Sound
	if (PropertyEditor_Page == 1)
	{
		ImGui::NextColumn();
		ImGui::AlignTextToFramePadding();
		
		ImGui::Selectable("Track:- ", &ClickOnTrack);
		ImGui::SameLine();
		ImGui::Text("%s", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Sound_File);

		if (ClickOnTrack)
		{
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.24f, 1.f), "ON");

			App->SBC_SoundMgr->Accessed = 1;
			strcpy(App->SBC_SoundMgr->Access_File, App->SBC_Scene->B_Object[Index]->S_Environ[0]->Sound_File);

			App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);
			App->SBC_SoundMgr->Dialog_SoundFile();

			if (App->SBC_SoundMgr->IsCancelled == 0)
			{

				strcpy(App->SBC_Scene->B_Object[Index]->S_Environ[0]->Sound_File, App->SBC_SoundMgr->Access_File);
				App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndVolume = App->SBC_SoundMgr->SndVolume;

				App->SBC_Com_Environments->Set_Environment_By_Index(1, Index);

				App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);
			}
			else
			{
				App->SBC_Com_Environments->Set_Environment_By_Index(1, Index);
			}

			ClickOnTrack = 0;
		}
		
		// ----------------- Volume
		ImGui::Selectable("Volume:- ", &ClickOnVolume);
		ImGui::SameLine();
		ImGui::Text("%f", App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndVolume);
		if (ClickOnVolume)
		{
			ClickOnVolume = 0;
		}

		// ----------------- Play
		ImGui::Selectable("Play:- ", &ClickOnPlay);
		ImGui::SameLine();
		ImGui::Text("%i", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Play);
		if (ClickOnPlay)
		{
			ClickOnPlay = 0;
		}

		// ----------------- Loop
		ImGui::Selectable("Loop:- ", &ClickOnLoop);
		ImGui::SameLine();
		ImGui::Text("%i", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Loop);
		if (ClickOnLoop)
		{
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
		ImGui::Text("%i", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On);
		if (ClickOnFogVisible)
		{
			strcpy(App->Cl_Dialogs->btext, "Set Fog Visiblity");

			App->Cl_Dialogs->TrueFlase = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On;

			strcpy(App->Cl_Dialogs->btext, "Set Fog On/Off");
			App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

			if (App->Cl_Dialogs->Canceled == 0)
			{
				if (App->Cl_Dialogs->TrueFlase == 1)
				{
					App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On = 1;
					App->Cl_Environment->EnableFog(true);
				}
				else
				{
					App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On = 0;
					App->Cl_Environment->EnableFog(false);
				}

				App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);
			}

			ClickOnFogVisible = 0;
		}

		// ----------------- Mode
		ImGui::Selectable("Mode:- ", &ClickOnFogMode);
		ImGui::SameLine();
		ImGui::Text("%i", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Mode);
		if (ClickOnFogMode)
		{
			ClickOnFogMode = 0;
		}


		// ----------------- Start
		ImGui::Text("Start:- ", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Start);
		ImGui::SameLine();
		
		if (ImGui::InputFloat("##1", &App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Start, 0.5, 0, "%.3f"))
		{
			if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On == 1)
			{
				App->Cl_Environment->EnableFog(true);
			}
		}

		// ----------------- End
		ImGui::Text("End:-   ", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_End);
		ImGui::SameLine();

		if (ImGui::InputFloat("##2", &App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_End, 0.5, 0, "%.3f"))
		{
			if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On == 1)
			{
				App->Cl_Environment->EnableFog(true);
			}
		}

	}

	ImGui::PopStyleVar();
	ImGui::Columns(0);

	if (ImGui::Button("Close2", ImVec2(100, 0)))
	{
		Show_PropertyEditor = 0;
	}

	ImGui::End();
}

// *************************************************************************
// *		 Start_Colour_Picker:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Gui_Environment::Start_Colour_Picker(Ogre::Vector3 Colour)
{
	Float_Exit = 0;
	ColourPicker_Canceled = 0;

	Float_Colour_Copy.x = Colour.x;
	Float_Colour_Copy.y = Colour.y;
	Float_Colour_Copy.z = Colour.z;

	Float_Colour.x = Colour.x;
	Float_Colour.y = Colour.y;
	Float_Colour.z = Colour.z;

	Colour_Int_Red = Float_Colour.x * 255;
	Colour_Int_Green = Float_Colour.y * 255;
	Colour_Int_Blue = Float_Colour.z * 255;

	App->Disable_Panels(true);
	App->Show_Panels(false);

	Show_PropertyEditor = 1;

}

// *************************************************************************
// *		 Do__Colour_Picker:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Gui_Environment::Do_Colour_Picker()
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	Ogre::Real mRed = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.x;
	Ogre::Real mGreen = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.y;
	Ogre::Real mBlue = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.z;

	ImGui::Text("Colour %.2f %.2f %.2f", mRed, mGreen, mBlue);


	ImGui::PushStyleColor(ImGuiCol_SliderGrab, IM_COL32(0, 0, 0, 255));
	ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(255, 0, 0, 255));
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(255, 0, 0, 255));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(255, 0, 0, 255));
	ImGui::VSliderInt("##r", ImVec2(100, 300), &Colour_Int_Red, 0, 255);
	ImGui::PopStyleColor(4);

	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_SliderGrab, IM_COL32(0, 0, 0, 255));
	ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 255, 0, 255));
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(0, 255, 0, 255));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(0, 255, 0, 255));
	ImGui::VSliderInt("##g", ImVec2(100, 300), &Colour_Int_Green, 0, 255);
	ImGui::PopStyleColor(4);

	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_SliderGrab, IM_COL32(0, 0, 0, 255));
	ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 255, 255));
	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(0, 0, 255, 255));
	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(0, 0, 255, 255));
	ImGui::VSliderInt("##b", ImVec2(100, 300), &Colour_Int_Blue, 0, 255);
	ImGui::PopStyleColor(4);

	ImGui::PushItemWidth(100);
	ImGui::InputInt("##ir", &Colour_Int_Red, 1, 0);
	ImGui::SameLine();
	ImGui::InputInt("##ig", &Colour_Int_Green, 1, 0);
	ImGui::SameLine();
	ImGui::InputInt("##ib", &Colour_Int_Blue, 1, 0);
	ImGui::PopItemWidth();

	Float_Colour.x = float(Colour_Int_Red) / 255;
	Float_Colour.y = float(Colour_Int_Green) / 255;
	Float_Colour.z = float(Colour_Int_Blue) / 255;


	ImGui::Spacing();
	ImGui::Text("Colour widget:");
	ImGui::SameLine();
	ImGuiColorEditFlags misc_flags2 = (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8);
	ImGui::ColorEdit3("", (float*)&Float_Colour, ImGuiColorEditFlags_NoInputs | misc_flags2);
	ImGui::Spacing();

	Colour_Int_Red = Float_Colour.x * 255;
	Colour_Int_Green = Float_Colour.y * 255;
	Colour_Int_Blue = Float_Colour.z * 255;

	App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour = Ogre::Vector3(Float_Colour.x, Float_Colour.y, Float_Colour.z);
	App->SBC_Ogre->mSceneMgr->setAmbientLight(ColourValue(Float_Colour.x, Float_Colour.y, Float_Colour.z));
}

// *************************************************************************
// *		Dialog_Colour_Picker:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Gui_Environment::Dialog_Colour_Picker(void)
{

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(340, 550), ImGuiCond_FirstUseEver);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));

	if (!ImGui::Begin("Colour Dialog", &Show_ColourPicker, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize))
	{
		ImGui::End();
	}
	else
	{
		if (Float_StartPos == 0)
		{
			Float_PosX = ((float)App->SBC_Ogre->OgreListener->View_Width / 2) - (340 / 2);
			Float_PosY = ((float)App->SBC_Ogre->OgreListener->View_Height / 2) - (550 / 2);
			ImGui::SetWindowPos("Colour Dialog", ImVec2(10, 10));

			Float_StartPos = 1;
		}

		ImGui::PushStyleColor(ImGuiCol_SliderGrab, IM_COL32(0, 0, 0, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(255, 0, 0, 255));
		ImGui::VSliderInt("##r", ImVec2(100, 400), &Colour_Int_Red, 0, 255);
		ImGui::PopStyleColor(4);

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_SliderGrab, IM_COL32(0, 0, 0, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 255, 0, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(0, 255, 0, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(0, 255, 0, 255));
		ImGui::VSliderInt("##g", ImVec2(100, 400), &Colour_Int_Green, 0, 255);
		ImGui::PopStyleColor(4);

		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_SliderGrab, IM_COL32(0, 0, 0, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 255, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(0, 0, 255, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(0, 0, 255, 255));
		ImGui::VSliderInt("##b", ImVec2(100, 400), &Colour_Int_Blue, 0, 255);
		ImGui::PopStyleColor(4);

		ImGui::PushItemWidth(100);
		ImGui::InputInt("##ir", &Colour_Int_Red, 1, 0);
		ImGui::SameLine();
		ImGui::InputInt("##ig", &Colour_Int_Green, 1, 0);
		ImGui::SameLine();
		ImGui::InputInt("##ib", &Colour_Int_Blue, 1, 0);
		ImGui::PopItemWidth();

		Float_Colour.x = float(Colour_Int_Red) / 255;
		Float_Colour.y = float(Colour_Int_Green) / 255;
		Float_Colour.z = float(Colour_Int_Blue) / 255;

		//ImGui::Indent();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Text("Colour widget:");
		ImGui::SameLine();
		ImGuiColorEditFlags misc_flags2 = (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8);
		ImGui::ColorEdit3("MyColor##1", (float*)&Float_Colour, ImGuiColorEditFlags_NoInputs | misc_flags2);
		ImGui::Separator();
		ImGui::Spacing();

		Colour_Int_Red = Float_Colour.x * 255;
		Colour_Int_Green = Float_Colour.y * 255;
		Colour_Int_Blue = Float_Colour.z * 255;

		ImGui::Indent();
		ImGui::Indent();
		ImGui::Indent();
		ImGui::Indent();
		ImGui::Indent();

		int Index = App->SBC_Properties->Current_Selected_Object;
		App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour = Ogre::Vector3(Float_Colour.x, Float_Colour.y, Float_Colour.z);
		App->SBC_Ogre->mSceneMgr->setAmbientLight(ColourValue(Float_Colour.x, Float_Colour.y, Float_Colour.z));

		if (ImGui::Button("Apply"))
		{
			Float_Exit = 1;

			Float_StartPos = 0;
			ColourPicker_Canceled = 0;

			ImGui::PopStyleColor();
			Show_ColourPicker = 0;
			ImGui::End();
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel"))
		{
			Float_Exit = 1;
			ColourPicker_Canceled = 1;

			ImGui::PopStyleColor();
			Show_ColourPicker = 0;
			ImGui::End();
		}

		if (Float_Exit == 0)
		{
			ColourPicker_Canceled = 1;

			ImGui::PopStyleColor();
			//Show_ColourPicker = 0;
			ImGui::End();
		}

		ImGui::End();
	}
}
