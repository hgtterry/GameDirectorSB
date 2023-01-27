/*
Copyright (c) 2022 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Gui_Dialogs.h"

SB_Gui_Dialogs::SB_Gui_Dialogs(void)
{
	Show_Dialog_Float = 0;
	Float_StartPos = 0;
	Float_PosX = 0;
	Float_PosY = 0;
	Float_Step = 0.05f;
	Float_Canceld = 0;
	Float_Exit = 0;
	strcpy(Float_Banner, "Banner");
	m_Dialog_Float_Copy = 0;
	m_Dialog_Float = 10.222;

	// ---------------------- 

	Centre_X_Selected = 0;
	Centre_Y_Selected = 0;
	MessageEditor_Canceld = 0;
	Show_Dialog_MessageEditor = 0;
	Message_Editor_StartPos = 0;
	Message_Editor_PosX = 10;
	Message_Editor_PosY = 10;
	Message_Index = 0;

	// -------------- Dialog Colour Picker
	Show_ColourPicker = 0;
	ColourPicker_Canceled = 0;
	Colour_Int_Red = 0;
	Colour_Int_Green = 0;
	Colour_Int_Blue = 0;

	// -------------- Physics Console
	Show_Physics_Console = 1;
	Physics_PosX = 500;
	Physics_PosY = 500;
	Physics_Console_StartPos = 0;

	// -------------- Light Editor
	Show_Light_Editor = 0;

	Show_Debug_Player = 0;
}

SB_Gui_Dialogs::~SB_Gui_Dialogs(void)
{
}

// *************************************************************************
// *			Close_All_Dialogs:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Gui_Dialogs::Close_All_Dialogs(void)
{
	Show_Dialog_Float = 0;
	Show_Dialog_MessageEditor = 0;
	Show_ColourPicker = 0;
	App->CL_Vm_ImGui->Show_Progress_Bar = 0;
}

// *************************************************************************
// *		BackGround_Render_Loop:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Gui_Dialogs::BackGround_Render_Loop(void)
{
	Ogre::WindowEventUtilities::messagePump();

	if (App->SBC_Ogre->mWindow->isClosed()) return;

	if (App->SBC_Ogre->FPStimer.getMilliseconds() > 3)
	{
		App->SBC_Ogre->mRoot->_fireFrameStarted();
		App->SBC_Ogre->mRoot->_updateAllRenderTargets();
		App->SBC_Ogre->mRoot->_fireFrameEnded();
		App->SBC_Ogre->FPStimer.reset();	
	}
}

// *************************************************************************
// *		Start_Dialog_Float:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Gui_Dialogs::Start_Dialog_Float(float Step, float StartValue,char* Banner)
{
	Float_Exit = 0;
	App->SBC_Gui_Dialogs->Float_Canceld = 0;
	App->SBC_Gui_Dialogs->Float_Step = Step;
	App->SBC_Gui_Dialogs->m_Dialog_Float = StartValue;
	strcpy(App->SBC_Gui_Dialogs->Float_Banner, Banner);

	m_Dialog_Float_Copy = StartValue;

	App->Disable_Panels(true);

	Float_PosX = ((float)App->SBC_Ogre->OgreListener->View_Width / 2) - (200 / 2);
	Float_PosY = ((float)App->SBC_Ogre->OgreListener->View_Height / 2) - (130 / 2);

	Float_StartPos = 0;

	App->SBC_Gui_Dialogs->Show_Dialog_Float = 1;
}

// *************************************************************************
// *			Dialog_Float:- Terry and Hazel Flanigan 2022  			   *
// *************************************************************************
void SB_Gui_Dialogs::Dialog_Float(void)
{
	
	ImGui::SetNextWindowPos(ImVec2(Float_PosX, Float_PosY), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(200, 130), ImGuiCond_FirstUseEver);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));

	if (!ImGui::Begin(Float_Banner, &Show_Dialog_Float, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize))
	{
		ImGui::End();
	}
	else
	{
		if (Float_StartPos == 0)
		{
			Float_PosX = ((float)App->SBC_Ogre->OgreListener->View_Width / 2) - (200 / 2);
			Float_PosY = ((float)App->SBC_Ogre->OgreListener->View_Height / 2) - (130 / 2);
			ImGui::SetWindowPos(Float_Banner, ImVec2(Float_PosX, Float_PosY));

			Float_StartPos = 1;
		}

		float spacingX = ImGui::GetStyle().ItemInnerSpacing.x;
		
		ImGui::Indent();
		ImGui::Spacing();

		ImGui::InputFloat("", &m_Dialog_Float, Float_Step, 0, "%.3f");

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Indent();

		if (ImGui::Button("Apply"))
		{
			Float_Exit = 1;
			Show_Dialog_Float = 0;
			Float_StartPos = 0;
			Float_Canceld = 0;
			ImGui::PopStyleColor();
			ImGui::End();
		}

		ImGui::SameLine(0.0f, spacingX);

		if (ImGui::Button("Close"))
		{
			Float_StartPos = 0;
			Float_Exit = 1;
			Show_Dialog_Float = 0;
			Float_Canceld = 1;
			ImGui::PopStyleColor();
			ImGui::End();
		}
		
		if (Float_Exit == 0)
		{
			Float_Canceld = 1;
			ImGui::PopStyleColor();
			ImGui::End();
		}
	}
}

// *************************************************************************
// *	 Start_Dialog_MessageEditor:- Terry and Hazel Flanigan 2022  	   *
// *************************************************************************
void SB_Gui_Dialogs::Start_Dialog_MessageEditor(int Index)
{

	Float_Exit = 0;
	MessageEditor_Canceld = 0;
	
	App->SBC_Gui_Dialogs->Float_Step = 1;

	App->Disable_Panels(true);
	App->Show_Panels(false);

	Message_Editor_PosX = 10;
	Message_Editor_PosY = 10;
	Message_Editor_StartPos = 0;
	Message_Index = Index;

	Centre_X_Selected = App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->PosXCentre_Flag;
	Centre_Y_Selected = App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->PosYCentre_Flag;

	Float_Colour = ImVec4(App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->Text_Colour.x / 255.0f,
		App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->Text_Colour.y / 255.0f,
		App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->Text_Colour.z / 255.0f,
		255);

	BackGround_color = ImVec4(App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->BackGround_Colour.x / 255.0f,
		App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->BackGround_Colour.y / 255.0f,
		App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->BackGround_Colour.z / 255.0f,
		255);

	App->SBC_Scene->B_Object[Index]->Show_Message_Flag = 1;

	Show_Dialog_MessageEditor = 1;
}

// *************************************************************************
// *		Dialog_MessageEditor:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Gui_Dialogs::Dialog_MessageEditor(void)
{

	ImGui::SetNextWindowPos(ImVec2(Message_Editor_PosX, Message_Editor_PosY), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(200, 340), ImGuiCond_FirstUseEver);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));

	if (!ImGui::Begin("Message Editor", &Show_Dialog_MessageEditor, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize))
	{
		ImGui::End();
	}
	else
	{
		if (Message_Editor_StartPos == 0)
		{
			Message_Editor_PosX = 10;
			Message_Editor_PosY = 10;
			ImGui::SetWindowPos("Message Editor", ImVec2(Message_Editor_PosX, Message_Editor_PosY));

			Message_Editor_StartPos = 1;
		}

		float spacingX = ImGui::GetStyle().ItemInnerSpacing.x;

		ImGui::Indent();
		ImGui::Spacing();

		// ------------------------------------------------------------- Pos X
		ImGui::InputFloat("X", &App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->Message_PosX, Float_Step, 0, "%.3f");
		
		ImGui::Checkbox("Centre X", &Centre_X_Selected);

		if (Centre_X_Selected)
		{
			App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->PosXCentre_Flag = 1;
		}
		else
		{
			App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->PosXCentre_Flag = 0;
		}

		ImGui::Separator();
		// ------------------------------------------------------------ - Pos Y
		ImGui::InputFloat("Y", &App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->Message_PosY, Float_Step, 0, "%.3f");

		ImGui::Checkbox("Centre Y", &Centre_Y_Selected);

		if (Centre_Y_Selected)
		{
			App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->PosYCentre_Flag = 1;
		}
		else
		{
			App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->PosYCentre_Flag = 0;
		}

		
		
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Unindent();

		ImGuiColorEditFlags misc_flags = (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8);


		ImGui::ColorEdit3("Text##1", (float*)&Float_Colour, misc_flags);

		App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->Text_Colour.x = Float_Colour.x * 255.0f;
		App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->Text_Colour.y = Float_Colour.y * 255.0f;
		App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->Text_Colour.z = Float_Colour.z * 255.0f;

		ImGui::ColorEdit3("BG##1", (float*)&BackGround_color, misc_flags);

		App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->BackGround_Colour.x = BackGround_color.x * 255.0f;
		App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->BackGround_Colour.y = BackGround_color.y * 255.0f;
		App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->BackGround_Colour.z = BackGround_color.z * 255.0f;

		ImGui::Checkbox("Show Back Ground", &App->SBC_Scene->B_Object[Message_Index]->S_Message[0]->Show_BackGround);

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Indent();
		ImGui::Indent();
		ImGui::Indent();

		ImGui::Separator();
		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Button("Close"))
		{
			Float_Exit = 1;
			Show_Dialog_MessageEditor = 0;
			MessageEditor_Canceld = 0;
			ImGui::PopStyleColor();
			ImGui::End();
		}

		//ImGui::SameLine(0.0f, spacingX);

		/*if (ImGui::Button("Close"))
		{
			Float_Exit = 1;
			Show_Dialog_MessageEditor = 0;
			MessageEditor_Canceld = 1;
			ImGui::End();
		}*/

		if (Float_Exit == 0)
		{
			MessageEditor_Canceld = 1;
			ImGui::PopStyleColor();
			ImGui::End();
		}
	}
}

// *************************************************************************
// *		 Start_Colour_Picker:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Gui_Dialogs::Start_Colour_Picker(Ogre::Vector3 Colour)
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

	Show_ColourPicker = 1;
}

// *************************************************************************
// *		Dialog_Colour_Picker:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Gui_Dialogs::Dialog_Colour_Picker(void)
{

	ImGui::SetNextWindowPos(ImVec2(10,10), ImGuiCond_FirstUseEver);
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
			ImGui::SetWindowPos("Colour Dialog", ImVec2(10,10));

			Float_StartPos = 1;
		}

		ImGui::PushStyleColor(ImGuiCol_SliderGrab, IM_COL32(0, 0, 0, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(255, 0, 0, 255));
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(255, 0, 0, 255));
		ImGui::VSliderInt("##r", ImVec2(100,400), &Colour_Int_Red, 0,255);
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

		/*int Index = App->SBC_Properties->Current_Selected_Object;
		App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour = Ogre::Vector3(App->SBC_Gui_Dialogs->Float_Colour.x, App->SBC_Gui_Dialogs->Float_Colour.y, App->SBC_Gui_Dialogs->Float_Colour.z);
		App->SBC_Ogre->mSceneMgr->setAmbientLight(ColourValue(App->SBC_Gui_Dialogs->Float_Colour.x, App->SBC_Gui_Dialogs->Float_Colour.y, App->SBC_Gui_Dialogs->Float_Colour.z));*/

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

// *************************************************************************
// *					Debug Player  Terry Bernie						   *
// *************************************************************************
void SB_Gui_Dialogs::Debug_Player(void)
{
	ImGui::SetNextWindowPos(ImVec2(500, 100), ImGuiCond_FirstUseEver);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));

	if (!ImGui::Begin("Debug_Player", &Show_Debug_Player))
	{
		ImGui::End();
	}
	else
	{
		if (App->Debug_App == 1)
		{
			/*ImGui::Text("Delay Timer %l", App->SBC_Ogre->FPStimer.getMicroseconds());
			ImGui::Text("Ogre Frame Time %f", App->SBC_Ogre->OgreListener->OgreFrameTime);
			ImGui::Text("Distance To Floor: = %f", App->SBC_Ogre->OgreListener->DistanceToCollision);*/

			if (App->SBC_Scene->Player_Added == 1)
			{
	
				ImGui::Text("Distance To Floor: = %f", App->SBC_Ogre->OgreListener->DistanceToCollision);

				ImGui::Text("AddGravity %i", App->SBC_DCC->AddGravity);
				ImGui::Text("Is_On_Ground %i",App->SBC_DCC->Is_On_Ground);
				ImGui::Text("mWorld_Height %f %f %f", App->SBC_DCC->mWorld_Height.getX(), App->SBC_DCC->mWorld_Height.getY(), App->SBC_DCC->mWorld_Height.getZ());
				ImGui::Text("mGroundPoint %f %f %f", App->SBC_DCC->mGroundPoint.getX(), App->SBC_DCC->mGroundPoint.getY(), App->SBC_DCC->mGroundPoint.getZ());
				
			}
		}

		
		ImGui::PopStyleColor();
		ImGui::End();
	}
}


// *************************************************************************
// *						Physics_Console  Terry Bernie				   *
// *************************************************************************
void SB_Gui_Dialogs::Physics_Console_Gui(void)
{
	ImGui::SetNextWindowPos(ImVec2(Physics_PosX, Physics_PosY), ImGuiCond_FirstUseEver);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));
	ImGuiStyle* style = &ImGui::GetStyle();

	if (!ImGui::Begin("Physics_Console", &Show_Physics_Console, ImGuiWindowFlags_NoSavedSettings |ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Text("Physics Console");
		
		ImGui::SameLine(0,270);
		if (ImGui::Button("H"))
		{
			App->Cl_Utilities->OpenHTML("Help\\Physics_Console.html");
		}

		ImGui::SameLine();
		if (ImGui::Button("X"))
		{
			CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_UNCHECKED);
			Physics_Console_StartPos = 0;
			Show_Physics_Console = 0;
		}

		ImGui::Separator();

		if (App->SBC_Ogre->OgreListener->GD_Run_Physics == 1)
		{
			style->Colors[ImGuiCol_Button] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
		}
		else
		{
			style->Colors[ImGuiCol_Button] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
		}

		if (ImGui::Button("Physics On"))
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
		}
		
		style->Colors[ImGuiCol_Button] = ImVec4(1, 1, 0.58,1); // Yellow
		

		ImGui::SameLine();
		if (ImGui::Button("Reset Physics"))
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				App->SBC_Physics->Reset_Physics();

				App->RedrawWindow_Dlg(App->Physics_Console_Hwnd);
			}
		}

		ImGui::SameLine();
		if (ImGui::Button("Reset Entities"))
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				App->SBC_Physics->Reset_Triggers();
			}
		}

		ImGui::SameLine();
		if (ImGui::Button("Reset Scene"))
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				
				int Saved = App->SBC_Ogre->OgreListener->GD_CameraMode;
				App->SBC_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;

				App->SBC_Physics->Reset_Physics();
				App->SBC_Ogre->OgreListener->GD_Run_Physics = 1;
				App->SBC_Physics->Reset_Triggers();
				App->SBC_Ogre->OgreListener->GD_Run_Physics = 1;
				
				App->SBC_TopTabs->Toggle_FirstCam_Flag = 1;
				App->SBC_TopTabs->Toggle_FreeCam_Flag = 0;
				RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				/*App->SBC_TopTabs->Toggle_FirstCam_Flag = 0;
				App->SBC_TopTabs->Toggle_FreeCam_Flag = 1;
				RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				App->SBC_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;*/

				App->SBC_Com_Environments->GameMode(0);

			}
		}

		if (Physics_Console_StartPos == 0)
		{
			ImVec2 Size = ImGui::GetWindowSize();
			Physics_PosX = 10;
			Physics_PosY = ((float)App->SBC_Ogre->OgreListener->View_Height) - (Size.y) - 10;
			ImGui::SetWindowPos("Physics_Console", ImVec2(Physics_PosX, Physics_PosY));

			Physics_Console_StartPos = 1;
		}

		style->Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		ImGui::PopStyleColor();
		ImGui::End();
	}
}

// *************************************************************************
// *		 Start_Light_Editor:- Terry and Hazel Flanigan 2023  		   *
// *************************************************************************
void SB_Gui_Dialogs::Start_Light_Editor()
{
	
	Show_Light_Editor = 1;
}

// *************************************************************************
// *		Light_Property_Editor_Gui:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
void SB_Gui_Dialogs::Light_Property_Editor_Gui()
{
	int Index = App->SBC_Properties->Current_Selected_Object;
	ImGui::SetNextWindowPos(ImVec2(200, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(350, 490), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Environment Editor", &Show_Light_Editor, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
		return;
	}

	ImGuiColorEditFlags misc_flags2 = (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(213, 222, 242, 255));

	ImGui::Spacing();
	ImGui::Spacing();

	// ---------------------------------------------------------------- Main Light

	ImGui::Text("Range");
	ImGui::Separator();

	float Inner = App->SBC_Scene->B_Object[Index]->S_Light[0]->light->getSpotlightInnerAngle().valueDegrees();
	float Outer = App->SBC_Scene->B_Object[Index]->S_Light[0]->light->getSpotlightOuterAngle().valueDegrees();
	float Limit = App->SBC_Scene->B_Object[Index]->S_Light[0]->light->getAttenuationRange();
	float Const = App->SBC_Scene->B_Object[Index]->S_Light[0]->light->getAttenuationConstant();
	float Linear = App->SBC_Scene->B_Object[Index]->S_Light[0]->light->getAttenuationLinear();
	float Quadric = App->SBC_Scene->B_Object[Index]->S_Light[0]->light->getAttenuationQuadric();

	// ----------------- Outer
	ImGui::Text("Outer:- ");
	ImGui::SameLine();
	if (ImGui::InputFloat("##1", &Outer, 1, 0, "%.3f"))
	{
		App->SBC_Scene->B_Object[Index]->S_Light[0]->light->setSpotlightRange(Degree(Inner), Degree(Outer));
	}

	// ----------------- Inner
	ImGui::Text("Inner:-  ");
	ImGui::SameLine();
	if (ImGui::InputFloat("##2", &Inner, 1, 0, "%.3f"))
	{
		App->SBC_Scene->B_Object[Index]->S_Light[0]->light->setSpotlightRange(Degree(Inner), Degree(Outer));
	}

	ImGui::Text("Attenuation");
	ImGui::Separator();
	// ----------------- Range
	ImGui::Text("Range:- ");
	ImGui::SameLine();
	if (ImGui::InputFloat("##3", &Limit, 1, 0, "%.3f"))
	{
		App->SBC_Scene->B_Object[Index]->S_Light[0]->light->setAttenuation(Limit, Const, Linear, Quadric);
	}

	// ----------------- Const
	ImGui::Text("Const:- ");
	ImGui::SameLine();
	if (ImGui::InputFloat("##4", &Const, 0.1, 0, "%f"))
	{
		App->SBC_Scene->B_Object[Index]->S_Light[0]->light->setAttenuation(Limit, Const, Linear, Quadric);
	}

	// ----------------- Linear
	ImGui::Text("Linear:- ");
	ImGui::SameLine();
	if (ImGui::InputFloat("##5", &Linear, 0.1, 0, "%f"))
	{
		App->SBC_Scene->B_Object[Index]->S_Light[0]->light->setAttenuation(Limit, Const, Linear, Quadric);
	}

	// ----------------- Quadric
	ImGui::Text("Quadric:- ");
	ImGui::SameLine();
	if (ImGui::InputFloat("##6", &Quadric, 0.1, 0, "%f"))
	{
		App->SBC_Scene->B_Object[Index]->S_Light[0]->light->setAttenuation(Limit, Const, Linear, Quadric);
	}

	ImGui::Spacing();
	ImGui::Spacing();

	if (ImGui::Button("Close", ImVec2(100, 0)))
	{
		//Close_Environment_Editor();

		ImGui::PopStyleColor();
		Show_Light_Editor = 0;
	}

	ImGui::End();
}
