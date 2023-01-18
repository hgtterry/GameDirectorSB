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
#include "SB_Gui_Dialogs.h"

SB_Gui_Dialogs::SB_Gui_Dialogs(void)
{
	Show_Progress_Bar2 = 0;
	progress = 0;
	Progress_Count = 0;
	Progress_Delta = 0;
	StartPos_PB = 0;

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
// *			Gui_Render_Loop:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Gui_Dialogs::Gui_Render_Loop(void)
{
	if (Show_Dialog_Float == 1)
	{
		Dialog_Float();
	}

	if (Show_Dialog_MessageEditor == 1)
	{
		Dialog_MessageEditor();
	}

	if (Show_ColourPicker == 1)
	{
		Dialog_Colour_Picker();
	}

	if (Show_Progress_Bar2 == 1)
	{
		ImGui_ProgressBar2();
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
// *					ImGui_ProgressBar2  Terry Bernie				   *
// *************************************************************************
void SB_Gui_Dialogs::ImGui_ProgressBar2(void)
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));

	ImGui::SetNextWindowPos(ImVec2(500, 500), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(350, 90), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("ProgressBar", &Show_Progress_Bar2, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		if (StartPos_PB == 0)
		{
			ImGui::SetWindowPos("ProgressBar", ImVec2(400, 250));
			ImGui::SetWindowSize(ImVec2(350, 90));
			StartPos_PB = 1;
		}

		//progress = 0.0f,
		progress += 0.0001;

		float progress_saturated = (progress < 0.0f) ? 0.0f : (progress > 1.0f) ? 1.0f : progress;

		char buf[32];
		sprintf(buf, "%d/%d", (int)(progress_saturated * Progress_Count), (int)Progress_Count);
		ImGui::ProgressBar(progress, ImVec2(0.f, 0.f), buf);



		float progress_saturated2 = (progress < 0.0f) ? 0.0f : (progress > 1.0f) ? 1.0f : progress;
		char buf2[32];
		sprintf(buf2, "%d/%d", (int)(progress_saturated2 * 100), 100);
		ImGui::ProgressBar(progress, ImVec2(0.f, 0.f), buf2);

		ImGui::PopStyleColor();
		ImGui::End();
	}
}

// *************************************************************************
// *					Start_ProgressBar  Terry Bernie					   *
// *************************************************************************
void SB_Gui_Dialogs::Start_ProgressBar(void)
{
	StartPos_PB = 0;
	Show_Progress_Bar2 = 1;
}

// *************************************************************************
// *					Stop_ProgressBar  Terry Bernie					   *
// *************************************************************************
void SB_Gui_Dialogs::Stop_ProgressBar(void)
{
	StartPos_PB = 0;
	progress = 0.0f,
	Show_Progress_Bar2 = 0;
}

// *************************************************************************
// *					Set_ProgressCount  Terry Bernie					   *
// *************************************************************************
void SB_Gui_Dialogs::Set_ProgressCount(float Count)
{
	Progress_Count = Count;
	Progress_Delta = 1 / Count;
}

// *************************************************************************
// *								Nudge 								   *
// *************************************************************************
bool SB_Gui_Dialogs::Nudge()
{
	progress += 0.1;// Progress_Delta;

	Ogre::Root::getSingletonPtr()->renderOneFrame();

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

// ----------------- Keep for later
//static char buf2[64] = ""; ImGui::InputText("decimal", buf2, 64, ImGuiInputTextFlags_CharsDecimal);
/*const float   f32_zero = 0.f, f32_one = 1.f, f32_lo_a = -10000000000.0f, f32_hi_a = +10000000000.0f;
		static bool inputs_step = true;
		static float  f32_v = 0.123f;
		ImGui::InputScalar("input float", ImGuiDataType_Float, &f32_v, inputs_step ? &f32_one : NULL);*/

		/*if (StartPos == 0)
		{
			ImGui::SetWindowPos("Ogre Data", ImVec2(500, 5));
			ImGui::SetWindowSize(ImVec2(350, 90));
			StartPos = 1;
		}*/