/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "AB_App.h"
#include "SB_Environment.h"

SB_Environment::SB_Environment(void)
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

SB_Environment::~SB_Environment(void)
{
}

// *************************************************************************
// *		V_Set_Environ_Defaults:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Environment::V_Set_Environ_Defaults(int Index)
{
	Base_Object* V_Object = App->CLSB_Scene->V_Object[Index];

	V_Object->Altered = 0;
	
	V_Object->S_Environ[0]->Environment_ID = 0;
	strcpy(V_Object->S_Environ[0]->Environment_Name, "Not_Set");

	V_Object->S_Environ[0]->Environ_Enabled = 1;

	//----------------------- Sound
	strcpy(V_Object->S_Environ[0]->Sound_File, "The_Sun.ogg");
	V_Object->S_Environ[0]->SndFile = NULL;
	V_Object->S_Environ[0]->Play = 0;
	V_Object->S_Environ[0]->Loop = 1;
	V_Object->S_Environ[0]->SndVolume = 0.5;

	//----------------------- Light
	V_Object->S_Environ[0]->AmbientColour.x = 0.5;
	V_Object->S_Environ[0]->AmbientColour.y = 0.5;
	V_Object->S_Environ[0]->AmbientColour.z = 0.5;

	V_Object->S_Environ[0]->Light_Position.x = 0;
	V_Object->S_Environ[0]->Light_Position.y = 0;
	V_Object->S_Environ[0]->Light_Position.z = 0;

	// Sky
	V_Object->S_Environ[0]->Curvature = 15;
	V_Object->S_Environ[0]->Distance = 4000;
	V_Object->S_Environ[0]->Enabled = 1;
	strcpy(V_Object->S_Environ[0]->Material, "Examples/CloudySky");
	V_Object->S_Environ[0]->Tiling = 15;
	V_Object->S_Environ[0]->type = 1;

	// Fog
	V_Object->S_Environ[0]->Fog_On = 1;
	V_Object->S_Environ[0]->Fog_Mode = FOG_LINEAR;
	V_Object->S_Environ[0]->Fog_Density = 0.001000;
	V_Object->S_Environ[0]->Fog_Start = 150;
	V_Object->S_Environ[0]->Fog_End = 1000;
	V_Object->S_Environ[0]->Fog_Colour = Ogre::Vector3(1, 1, 1);

	V_Object->S_Environ[0]->IsMainEnvironment = 0;
}

// *************************************************************************
// *		Add_New_Environ_Entiry:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Environment::Add_New_Environ_Entity(bool FirstOne)
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->CLSB_Scene->Object_Count;

	App->CLSB_Scene->V_Object[Index] = new Base_Object();
	App->CLSB_Scene->V_Object[Index]->S_Environ[0] = new Environ_type;
	V_Set_Environ_Defaults(Index);


	App->CLSB_Scene->V_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->CLSB_Scene->V_Object[Index]->Shape = Enums::Shape_Box;
	//App->CLSB_Scene->V_Object[Index]->This_Object_UniqueID = App->CLSB_Scene->UniqueID_Object_Counter; // Unique ID

	strcpy(App->CLSB_Scene->V_Object[Index]->Mesh_FileName, "EnvironmentEntity_GD.mesh");

	strcpy_s(B_Name, "Environ_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->CLSB_Scene->V_Object[Index]->Mesh_Name, B_Name);

	//if (FirstOne == 0)
	//{
	//	Ogre::Vector3 Pos = App->CL_Object->GetPlacement(-50);
	//	App->SBC_Scene->V_Object[Index]->Mesh_Pos = Pos;
	//}
	//else
	//{
	//	Ogre::Vector3 Pos = Ogre::Vector3(0, 0, 0);
	//}

	//Create_Environ_Entity(Index);

	HTREEITEM Temp = App->CLSB_FileView->Add_Item(App->CLSB_FileView->FV_Evirons_Folder, App->CLSB_Scene->V_Object[Index]->Mesh_Name, Index, false);
	App->CLSB_Scene->V_Object[Index]->FileViewItem = Temp;

	App->CLSB_FileView->Set_FolderActive(App->CLSB_FileView->FV_Evirons_Folder);
	//App->SBC_FileView->SelectItem(App->SBC_Scene->V_Object[Index]->FileViewItem);

	//App->SBC_Scene->UniqueID_Object_Counter++;
	App->CLSB_Scene->Object_Count++;

	//App->CLSB_FileView->Set_FolderActive(App->CLSB_FileView->FV_Sounds_Folder);
	return 1;
}

// *************************************************************************
// *		Set_First_Environment:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Environment::Set_First_Environment(int Index)
{
	float x = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->AmbientColour.x;
	float y = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->AmbientColour.y;
	float z = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->AmbientColour.z;

	App->CLSB_Ogre->mSceneMgr->setAmbientLight(ColourValue(x, y, z));

	if (App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_On == 1)
	{
		float Start = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Start;
		float End = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_End;
		float Density = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Density;

		float x = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Colour.x;
		float y = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Colour.y;
		float z = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Colour.z;

		App->CLSB_Ogre->mSceneMgr->setFog(FOG_LINEAR, ColourValue(x, y, z), Density, (Ogre::Real)Start, (Ogre::Real)End);
	}
	else
	{
		App->CLSB_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}

	if (App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Enabled == 1)
	{
		App->CLSB_Ogre->mSceneMgr->setSkyDome(true,
			App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Material,
			App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Curvature,
			App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Tiling,
			App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Distance);
	}
	else
	{

	}

	App->CLSB_Scene->V_Object[Index]->S_Environ[0]->IsMainEnvironment = 1;
	App->CLSB_Scene->V_Object[Index]->Usage = Enums::Usage_EnvironEntity;
}

// *************************************************************************
// *	Mark_As_Altered_Environ:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
void SB_Environment::Mark_As_Altered_Environ(int Index)
{
	App->CLSB_Scene->V_Object[Index]->Altered = 1;

	App->CLSB_Scene->Scene_Modified = 1;

	App->CLSB_FileView->Mark_Altered(App->CLSB_Scene->V_Object[Index]->FileViewItem);
}

// *************************************************************************
// *		Set_Environment_By_Index:- Terry and Hazel Flanigan 2022 	   *
// *************************************************************************
int SB_Environment::Set_Environment_By_Index(bool PlayMusic, int Index)
{

	float x = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->AmbientColour.x;
	float y = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->AmbientColour.y;
	float z = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->AmbientColour.z;
	App->CLSB_Ogre->mSceneMgr->setAmbientLight(ColourValue(x, y, z));


	// Fog
	if (App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_On == 1)
	{
		float Start = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Start;
		float End = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_End;
		float Density = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Density;

		float x = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Colour.x;
		float y = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Colour.y;
		float z = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Colour.z;

		App->CLSB_Ogre->mSceneMgr->setFog(FOG_LINEAR, ColourValue(x, y, z), Density, (Ogre::Real)Start, (Ogre::Real)End);
	}
	else
	{
		App->CLSB_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}

	if (PlayMusic == 1)
	{
		char buff[1024];
		strcpy(buff, App->WorldEditor_Directory);
		strcat(buff, "\\Media\\Sounds\\");

		if (App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Play == 1)
		{
			strcat(buff, App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Sound_File);

			App->CLSB_Scene->V_Object[Index]->S_Environ[0]->SndFile = App->CLSB_SoundMgr->SoundEngine->play2D(buff, App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Loop, true, true);

			App->CLSB_Scene->V_Object[Index]->S_Environ[0]->SndFile->setVolume(App->CLSB_Scene->V_Object[Index]->S_Environ[0]->SndVolume);
			App->CLSB_Scene->V_Object[Index]->S_Environ[0]->SndFile->setIsPaused(false);
		}
	}
	else
	{
		if (App->CLSB_Scene->V_Object[Index]->S_Environ[0]->SndFile == NULL)
		{
		}
		else
		{
			App->CLSB_Scene->V_Object[Index]->S_Environ[0]->SndFile->setIsPaused(true);
			App->CLSB_Scene->V_Object[Index]->S_Environ[0]->SndFile->drop();
			App->CLSB_Scene->V_Object[Index]->S_Environ[0]->SndFile = NULL;
		}
	}

	return 1;
}

// *************************************************************************
// *		Get_First_Environ:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
int SB_Environment::Get_First_Environ()
{
	int Count = 0;
	while (Count < App->CLSB_Scene->Object_Count)
	{
		if (App->CLSB_Scene->V_Object[Count]->Usage == Enums::Usage_EnvironEntity && App->CLSB_Scene->V_Object[Count]->S_Environ[0]->IsMainEnvironment == 1)
		{
			return Count;
		}

		Count++;
	}

	return -1;
}

// ----------------------------------------------------------------------------------------------------------------
// *************************************************************************
// *	 Start_Environment_Editor:- Terry and Hazel Flanigan 2023  		   *
// *************************************************************************
void SB_Environment::Start_Environment_Editor(int Index, bool IsTeleport)
{
	Eviron_Index = Index;
	Is_Teleport = IsTeleport;

	Float_Exit = 0;

	Ambient_Colour_Copy.x = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->AmbientColour.x;
	Ambient_Colour_Copy.y = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->AmbientColour.y;
	Ambient_Colour_Copy.z = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->AmbientColour.z;

	Ambient_Colour.x = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->AmbientColour.x;
	Ambient_Colour.y = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->AmbientColour.y;
	Ambient_Colour.z = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->AmbientColour.z;

	Ambient_Int_Red = Ambient_Colour.x * 255;
	Ambient_Int_Green = Ambient_Colour.y * 255;
	Ambient_Int_Blue = Ambient_Colour.z * 255;

	Fog_Colour_Copy.x = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_Colour.x;
	Fog_Colour_Copy.y = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_Colour.y;
	Fog_Colour_Copy.z = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_Colour.z;

	Fog_Colour.x = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_Colour.x;
	Fog_Colour.y = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_Colour.y;
	Fog_Colour.z = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_Colour.z;

	Fog_Colour_Int_Red = Fog_Colour.x * 255;
	Fog_Colour_Int_Green = Fog_Colour.y * 255;
	Fog_Colour_Int_Blue = Fog_Colour.z * 255;


	/*App->Disable_Panels(true);
	App->Show_Panels(false);*/

	App->CLSB_FileView->Show_FileView(false);
	//App->CLSB_Com_Environments->Set_Environment_By_Index(1, Eviron_Index);

	Show_PropertyEditor = 1;
}

// *************************************************************************
// *		Environ_PropertyEditor:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Environment::Environ_PropertyEditor()
{

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(350, 190), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Environment Editor", &Show_PropertyEditor, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
		return;
	}

	ImGuiColorEditFlags misc_flags2 = (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8);

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(213, 222, 242, 255));

	ImGui::Columns(2);
	ImGui::SetColumnWidth(-1, 120);

	if (ImGui::Button(" Main Light ", ImVec2(100, 0)))
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

			App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->AmbientColour = Ogre::Vector3(Ambient_Colour.x, Ambient_Colour.y, Ambient_Colour.z);
			App->CLSB_Ogre->mSceneMgr->setAmbientLight(ColourValue(Ambient_Colour.x, Ambient_Colour.y, Ambient_Colour.z));

			Mark_As_Altered_Environ(Eviron_Index);
		}

	}

	// ---------------------------------------------------------------- Sound
	if (PropertyEditor_Page == 1)
	{
		ImGui::NextColumn();
		ImGui::AlignTextToFramePadding();

		ImGui::Selectable("Track:- ", &ClickOnTrack);
		ImGui::SameLine();
		ImGui::Text("%s", App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Sound_File);

		if (ClickOnTrack)
		{
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.24f, 1.f), "ON");

			App->CLSB_SoundMgr->Accessed = 1;
			strcpy(App->CLSB_SoundMgr->Access_File, App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Sound_File);

			App->CLSB_Environment->Set_Environment_By_Index(0, Eviron_Index);
			App->CLSB_SoundMgr->Dialog_SoundFile();

			if (App->CLSB_SoundMgr->IsCancelled == 0)
			{

				strcpy(App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Sound_File, App->CLSB_SoundMgr->Access_File);
				App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->SndVolume = App->CLSB_SoundMgr->SndVolume;

				App->CLSB_Environment->Set_Environment_By_Index(1, Eviron_Index);

				App->CLSB_Environment->Mark_As_Altered_Environ(Eviron_Index);
			}
			else
			{
				App->CLSB_Environment->Set_Environment_By_Index(1, Eviron_Index);
			}

			ClickOnTrack = 0;
		}

		// ----------------- Volume
		ImGui::Selectable("Volume:- ", &ClickOnVolume);
		ImGui::SameLine();
		ImGui::Text("%f", App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->SndVolume);
		if (ClickOnVolume)
		{
			Mark_As_Altered_Environ(Eviron_Index);
			ClickOnVolume = 0;
		}

		// ----------------- Play
		ImGui::Selectable("Play:- ", &ClickOnPlay);
		ImGui::SameLine();
		ImGui::Text("%i", App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Play);
		if (ClickOnPlay)
		{
			strcpy(App->CLSB_Dialogs->btext, "Set Play Sound Track");

			App->CLSB_Dialogs->TrueFlase = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Play;

			App->CLSB_Dialogs->Dialog_TrueFlase();

			if (App->CLSB_Dialogs->Canceled == 0)
			{
				if (App->CLSB_Dialogs->TrueFlase == 1)
				{
					App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Play = 1;
					App->CLSB_Environment->Set_Environment_By_Index(1, Eviron_Index);
				}
				else
				{
					App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Play = 0;
					App->CLSB_Environment->Set_Environment_By_Index(0, Eviron_Index);
				}

				Mark_As_Altered_Environ(Eviron_Index);
			}

			Mark_As_Altered_Environ(Eviron_Index);

			ClickOnPlay = 0;
		}

		// ----------------- Loop
		ImGui::Selectable("Loop:- ", &ClickOnLoop);
		ImGui::SameLine();
		ImGui::Text("%i", App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Loop);
		if (ClickOnLoop)
		{
			strcpy(App->CLSB_Dialogs->btext, "Set Play Sound Loop");

			App->CLSB_Dialogs->TrueFlase = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Loop;

			App->CLSB_Dialogs->Dialog_TrueFlase();

			if (App->CLSB_Dialogs->Canceled == 0)
			{
				if (App->CLSB_Dialogs->TrueFlase == 1)
				{
					App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Loop = 1;
					Set_Environment_By_Index(0, Eviron_Index);
					Set_Environment_By_Index(1, Eviron_Index);
				}
				else
				{
					App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Loop = 0;
					Set_Environment_By_Index(0, Eviron_Index);
					Set_Environment_By_Index(1, Eviron_Index);
				}

				Mark_As_Altered_Environ(Eviron_Index);
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
		ImGui::Text("%i", App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_On);
		if (ClickOnFogVisible)
		{
			strcpy(App->CLSB_Dialogs->btext, "Set Fog Visiblity");

			App->CLSB_Dialogs->TrueFlase = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_On;

			strcpy(App->CLSB_Dialogs->btext, "Set Fog On/Off");
			App->CLSB_Dialogs->Dialog_TrueFlase();

			if (App->CLSB_Dialogs->Canceled == 0)
			{
				if (App->CLSB_Dialogs->TrueFlase == 1)
				{
					App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_On = 1;
					EnableFog(true);
				}
				else
				{
					App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_On = 0;
					EnableFog(false);
				}

				Mark_As_Altered_Environ(Eviron_Index);
			}


			ClickOnFogVisible = 0;
		}

		// ----------------- Mode
		ImGui::Selectable("Mode:- ", &ClickOnFogMode);
		ImGui::SameLine();
		ImGui::Text("%i", App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_Mode);
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

			App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_Colour = Ogre::Vector3(Fog_Colour.x, Fog_Colour.y, Fog_Colour.z);

			if (App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_On == 1)
			{
				EnableFog(true);
			}

			Mark_As_Altered_Environ(Eviron_Index);
		}



		// ----------------- Start
		ImGui::Text("Start:- ", App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_Start);
		ImGui::SameLine();

		if (ImGui::InputFloat("##1", &App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_Start, 1, 0, "%.3f"))
		{
			if (App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_On == 1)
			{
				EnableFog(true);
			}

			Mark_As_Altered_Environ(Eviron_Index);
		}

		// ----------------- End
		ImGui::Text("End:-   ", App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_End);
		ImGui::SameLine();

		if (ImGui::InputFloat("##2", &App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_End, 1, 0, "%.3f"))
		{
			if (App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Fog_On == 1)
			{
				EnableFog(true);
			}

			Mark_As_Altered_Environ(Eviron_Index);
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
		ImGui::Text("%i", App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Enabled);
		if (ClickOnSkyEnabled)
		{
			strcpy(App->CLSB_Dialogs->btext, "Set Sky Visiblity");

			App->CLSB_Dialogs->TrueFlase = App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Enabled;

			strcpy(App->CLSB_Dialogs->btext, "Set Sky On/Off");
			App->CLSB_Dialogs->Dialog_TrueFlase();

			if (App->CLSB_Dialogs->Canceled == 0)
			{
				if (App->CLSB_Dialogs->TrueFlase == 1)
				{
					App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Enabled = 1;
					SetSky(1);
				}
				else
				{
					App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Enabled = 0;
					SetSky(0);
				}

				Mark_As_Altered_Environ(Eviron_Index);
			}

			ClickOnSkyEnabled = 0;
		}

		// ----------------- Tiling
		ImGui::Text("Tiling:- ", App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Tiling);
		ImGui::SameLine();

		if (ImGui::InputFloat("##5", &App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Tiling, 0.5, 0, "%.3f"))
		{
			if (App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Enabled == 1)
			{
				SetSky(true);
			}

			Mark_As_Altered_Environ(Eviron_Index);
		}

		// ----------------- Curvature
		ImGui::Text("Curve:- ", App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Curvature);
		ImGui::SameLine();

		if (ImGui::InputFloat("##6", &App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Curvature, 0.5, 0, "%.3f"))
		{
			if (App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Enabled == 1)
			{
				SetSky(true);
			}

			Mark_As_Altered_Environ(Eviron_Index);
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
			//App->CLSB_Scene->B_Player[0]->Phys_Body->getWorldTransform().setOrigin(App->CLSB_Scene->V_Object[Eviron_Index]->S_Teleport[0]->Physics_Position);
			//App->CLSB_Scene->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->CLSB_Scene->V_Object[Eviron_Index]->S_Teleport[0]->Physics_Rotation);
			//Set_To_PlayerView();
		}

		ImGui::SameLine();
		if (ImGui::Checkbox("Enabled", &App->CLSB_Scene->V_Object[Eviron_Index]->S_Environ[0]->Environ_Enabled))
		{
			//App->SBC_Properties->Update_ListView_Teleport();
		}
	}


	ImGui::End();
}

// *************************************************************************
// *	 Close_Environment_Editor:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Environment::Close_Environment_Editor()
{
	/*App->Disable_Panels(false);
	App->Show_Panels(true);*/

	App->CLSB_FileView->Show_FileView(true);
	int Index = App->CLSB_Properties->Current_Selected_Object;
	Set_Environment_By_Index(0, Index);

	Index = App->CLSB_Environment->Get_First_Environ();
	Set_Environment_By_Index(0, Index);
}

// *************************************************************************
// *		 Set_To_PlayerView:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Environment::Set_To_PlayerView()
{
	App->CLSB_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;
	//App->CLSB_TopTabs->Toggle_FirstCam_Flag = 1;
	//App->CLSB_TopTabs->Toggle_FreeCam_Flag = 0;

	App->CLSB_Scene->B_Player[0]->Player_Node->setVisible(false);

	int f = App->CLSB_Scene->B_Player[0]->Phys_Body->getCollisionFlags();
	App->CLSB_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f | (1 << 5));

	App->CLSB_Ogre->BulletListener->Render_Debug_Flag = 0;
	App->CLSB_Ogre->BulletListener->Render_Debug_Flag = 1;

	App->CLSB_Ogre->OgreListener->GD_Run_Physics = 1;

	//RedrawWindow(App->CLSB_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *	  		SetSky:- Terry and Hazel Flanigan 2023					   *
// *************************************************************************
void SB_Environment::SetSky(bool Enable)
{
	int Index = App->CLSB_Properties->Current_Selected_Object;

	App->CLSB_Ogre->mSceneMgr->setSkyDome(Enable,
		App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Material,
		App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Curvature,
		App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Tiling,
		App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Distance);
}

// *************************************************************************
// *	  		EnableFog:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
bool SB_Environment::EnableFog(bool SetFog)
{
	int Index = App->CLSB_Properties->Current_Selected_Object;

	if (SetFog == true)
	{
		float Start = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Start;
		float End = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_End;
		float Density = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Density;

		float x = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Colour.x;
		float y = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Colour.y;
		float z = App->CLSB_Scene->V_Object[Index]->S_Environ[0]->Fog_Colour.z;

		App->CLSB_Ogre->mSceneMgr->setFog(FOG_LINEAR, ColourValue(x, y, z), Density, (Ogre::Real)Start, (Ogre::Real)End);
	}
	else
	{
		App->CLSB_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}

	return 1;
}

