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
#include "Bass_Front_Dialog.h"

Bass_Front_Dialog::Bass_Front_Dialog()
{
	Use_Front_Dlg_Flag = 0;
	Show_Front_Dlg_Flag = 0;
	PosX = 500;
	PosY = 500;
}

Bass_Front_Dialog::~Bass_Front_Dialog()
{
}

// *************************************************************************
// *			Render_ImGui_Panel:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void Bass_Front_Dialog::Render_ImGui_Panel(void)
{

	ImGui::SetNextWindowPos(ImVec2(PosX, PosY));

	ImGuiWindowFlags window_flags = 0;

	//if (S_Message[0]->Show_BackGround == 1)
	{
		window_flags |= ImGuiWindowFlags_NoSavedSettings;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
	}
	/*else
	{
		window_flags |= ImGuiWindowFlags_NoSavedSettings;
		window_flags |= ImGuiWindowFlags_NoResize;
		window_flags |= ImGuiWindowFlags_NoTitleBar;
		window_flags |= ImGuiWindowFlags_AlwaysAutoResize;
		window_flags |= ImGuiWindowFlags_NoBackground;
	}*/

	//ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(BackGround_Colour.x, BackGround_Colour.y, BackGround_Colour.z, 255));
	
	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));

	if (!ImGui::Begin("Front_Dialog", &Show_Front_Dlg_Flag, window_flags))
	{
		ImGui::End();
	}
	else
	{

		ImGui::PushFont(App->CL_Vm_ImGui->font2);

		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Button("Start Game"))
		{
			SetCapture(App->ViewGLhWnd);
			App->SBC_Ogre->OgreListener->Pl_LeftMouseDown = 1;
			App->CUR = SetCursor(NULL);
			App->SBC_Ogre->OgreListener->Block_Mouse = 0;
			App->SBC_Keyboard->Block_Keyboard = 0;
			Show_Front_Dlg_Flag = 0;
		}

		/*if (ImGui::Button("Resume Game"))
		{

		}

		if (ImGui::Button("Restart Game"))
		{

		}*/

		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Button("       Quit      "))
		{
			App->SBC_Ogre->OgreListener->Pl_LeftMouseDown = 0;
			App->SBC_Ogre->OgreListener->Block_Mouse = 0;
			App->SBC_Keyboard->Block_Keyboard = 0;
			App->Block_Mouse_Buttons = 0;
			App->SBC_Ogre->ExitFullScreen();
			Use_Front_Dlg_Flag = 0; // Temp
			Show_Front_Dlg_Flag = 0;

		}

		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::PopFont();

		ImVec2 Size = ImGui::GetWindowSize();
		PosX = ((float)App->SBC_Ogre->OgreListener->View_Width / 2) - (Size.x / 2);
		PosY = ((float)App->SBC_Ogre->OgreListener->View_Height / 2) - (Size.y / 2);

		ImGui::PopStyleColor();
		ImGui::End();

	}
}
