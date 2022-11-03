/*
Copyright (c) 2021 EquitySB and EquityME -- HGTO Software W.T.Flanigan H.C.Flanigan

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

:- Terry and Hazel Flanigan 2022

*/

#include "stdafx.h"
#include "GD19_App.h"
#include "Base_Message.h"

Base_Message::Base_Message()
{
	Show_Panel_Flag = 0;

	FileViewItem = nullptr;

	Deleted = 0;
	Altered = 0;

	Unique_ID = 0;

	PosX = 250;
	PosY = 10;

	strcpy(TextMessage_Name, "TextMessage_1");
	strcpy(Text, "Test");

	strcpy(ImGui_Panel_Name, "TextMessage_");
}

Base_Message::~Base_Message()
{

}

// *************************************************************************
// *		Set_ImGui_Panel_Name:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void Base_Message::Set_ImGui_Panel_Name(void)
{
	char Num[10];
	_itoa(Unique_ID, Num, 10);

	strcat(ImGui_Panel_Name, Num);

}

// *************************************************************************
// *			Render_ImGui_Panel:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void Base_Message::Render_ImGui_Panel(void)
{
	ImGui::SetNextWindowPos(ImVec2(PosX,PosY));
		

	if (!ImGui::Begin(ImGui_Panel_Name, &Show_Panel_Flag, ImGuiWindowFlags_NoSavedSettings
		| ImGuiWindowFlags_AlwaysAutoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{

		ImGui::PushFont(App->CL_Vm_ImGui->font2);

		ImGui::Text("%s",Text);

		ImGui::PopFont();

		ImGui::End();
	}
}
