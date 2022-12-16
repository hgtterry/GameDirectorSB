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
	Show_Dialog_Float = 0;
	StartPos = 0;
	Message_PosX = 0;
	Message_PosY = 0;
	Float_Step = 0.05f;
	Canceld = 0;
	Float_Exit = 0;
	strcpy(Banner, "Banner");
	m_Dialog_Float_Copy = 0;
	m_Dialog_Float = 10.222;
}

SB_Gui_Dialogs::~SB_Gui_Dialogs(void)
{
}

// *************************************************************************
// *			Ogre_Render_Loop:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Gui_Dialogs::Ogre_Render_Loop(void)
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
}

// *************************************************************************
// *		Start_Dialog_Float:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Gui_Dialogs::Start_Dialog_Float(float Step, float StartValue,char* Banner)
{
	Float_Exit = 0;
	App->SBC_Gui_Dialogs->Canceld = 0;
	App->SBC_Gui_Dialogs->Float_Step = Step;
	App->SBC_Gui_Dialogs->m_Dialog_Float = StartValue;
	strcpy(App->SBC_Gui_Dialogs->Banner, Banner);

	m_Dialog_Float_Copy = StartValue;

	App->Disable_Panels(true);

	Message_PosX = ((float)App->SBC_Ogre->OgreListener->View_Width / 2) - (200 / 2);
	Message_PosY = ((float)App->SBC_Ogre->OgreListener->View_Height / 2) - (130 / 2);
	StartPos = 0;

	App->SBC_Gui_Dialogs->Show_Dialog_Float = 1;
}

// *************************************************************************
// *			Dialog_Float:- Terry and Hazel Flanigan 2022  			   *
// *************************************************************************
void SB_Gui_Dialogs::Dialog_Float(void)
{
	
	ImGui::SetNextWindowPos(ImVec2(Message_PosX, Message_PosY), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(200, 130), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin(Banner, &Show_Dialog_Float, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize))
	{
		ImGui::End();
	}
	else
	{
		if (StartPos == 0)
		{
			Message_PosX = ((float)App->SBC_Ogre->OgreListener->View_Width / 2) - (200 / 2);
			Message_PosY = ((float)App->SBC_Ogre->OgreListener->View_Height / 2) - (130 / 2);
			ImGui::SetWindowPos(Banner, ImVec2(Message_PosX, Message_PosY));

			StartPos = 1;
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
			Canceld = 0;
			ImGui::End();
		}

		ImGui::SameLine(0.0f, spacingX);

		if (ImGui::Button("Close"))
		{
			Float_Exit = 1;
			Show_Dialog_Float = 0;
			Canceld = 1;
			ImGui::End();
		}
		
		if (Float_Exit == 0)
		{
			Canceld = 1;
			ImGui::End();
		}
	}
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