/*
Copyright (c) 2022- 2023 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "resource.h"
#include "ME_Editor_Gui.h"

ME_Editor_Gui::ME_Editor_Gui()
{
	Show_Model_Data_F = 0;
	Show_Group_Data_F = 0;
	Show_App_Data_F = 0;

	Model_Data_PosX = 500;
	Model_Data_PosY = 500;

	Group_Data_PosX = 500;
	Group_Data_PosY = 500;

	App_Data_PosX = 500;
	App_Data_PosY = 500;
}

ME_Editor_Gui::~ME_Editor_Gui()
{
}

// *************************************************************************
// *		ImGui_Editor_Loop:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void ME_Editor_Gui::ImGui_Editor_Loop(void)
{
	if (App->CL_Prefs->Show_Preferences_GUI == 1)
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
	}

	if (Show_App_Data_F == 1)
	{
		App_Data_GUI();
	}
}

// *************************************************************************
// *			Start_Model_Data:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void ME_Editor_Gui::Start_Model_Data(void)
{
	HWND Temp = GetDlgItem(App->CL_TopBar->TabsHwnd, IDC_TBINFO);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfoOn_Bmp);

	App->CL_Panels->Enable_Panels(0);

	Show_Model_Data_F = 1;
}

// *************************************************************************
// *			Model_Data_GUI:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void ME_Editor_Gui::Model_Data_GUI(void)
{
	ImGui::SetNextWindowPos(ImVec2(Model_Data_PosX, Model_Data_PosY));

	if (!ImGui::Begin("Model Data", &Show_Model_Data_F, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Spacing();
		ImGui::Text("Model Info");
		ImGui::Text("  ");
		ImGui::Text("Model Name:- %s", App->CL_Model->JustName);
		ImGui::Text("Model File Name:- %s", App->CL_Model->FileName);
		ImGui::Text("Model Path:- %s", App->CL_Model->Path_FileName);
		ImGui::Text("Texture Path:- %s", App->CL_Model->Texture_FolderPath);
		ImGui::Text("  ");
		ImGui::Text("Vertices:- %i", App->CL_Model->VerticeCount);
		ImGui::Text("Faces:- %i", App->CL_Model->FaceCount);
		ImGui::Text("Groups:- %i", App->CL_Model->Get_Groupt_Count());
		ImGui::Text("Motions:- %i", App->CL_Model->MotionCount);
		ImGui::Text("  ");

		ImVec2 Size = ImGui::GetWindowSize();
		Model_Data_PosX = ((float)App->CL_Ogre->Ogre_Listener->View_Width / 2) - (Size.x / 2);
		Model_Data_PosY = ((float)App->CL_Ogre->Ogre_Listener->View_Height / 2) - (Size.y / 2);;

		ImGui::Separator();

		if (ImGui::Button("Close"))
		{
			Close_Model_Data();
		}

		ImGui::End();
	}
}

// *************************************************************************
// *			Close_Model_Data:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void ME_Editor_Gui::Close_Model_Data(void)
{
	App->CL_Panels->Enable_Panels(1);

	HWND Temp = GetDlgItem(App->CL_TopBar->TabsHwnd, IDC_TBINFO);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfo_Bmp);

	Show_Model_Data_F = 0;
}

// *************************************************************************
// *			Start_Group_Data:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void ME_Editor_Gui::Start_Group_Data(void)
{

	//App->CL_Panels->Enable_Panels(0);

	Show_Group_Data_F = 1;
}

// *************************************************************************
// *			Group_Data_GUI:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void ME_Editor_Gui::Group_Data_GUI(void)
{
	int Index = App->CL_Groups->Selected_Group;

	ImGui::SetNextWindowPos(ImVec2(Group_Data_PosX, Group_Data_PosY));

	if (!ImGui::Begin("Group Data", &Show_Group_Data_F, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Spacing();
		ImGui::Text("Group Info");
		ImGui::Text("  ");
		ImGui::Text("Group Name:- %s", App->CL_Model->Group[Index]->GroupName);
		ImGui::Text("Group Vertices:- %i", App->CL_Model->Group[Index]->GroupVertCount);
		ImGui::Text("Group Faces:- %i", App->CL_Model->Group[Index]->GroupFaceCount);
		ImGui::Text("  ");
		ImGui::Text("Material Name:- %s", App->CL_Model->Group[Index]->MaterialName);
		ImGui::Text("Texture Name:- %s", App->CL_Model->Group[Index]->Text_FileName);
		ImGui::Text("  ");
		ImGui::Text("Bit Depth:- %i", App->CL_Model->Group[Index]->Depth);
		ImGui::Text("Dimensions:- %i x %i", App->CL_Model->Group[Index]->Width, App->CL_Model->Group[Index]->Height);
		ImGui::Text("  ");

		ImVec2 Size = ImGui::GetWindowSize();
		Group_Data_PosX = ((float)App->CL_Ogre->Ogre_Listener->View_Width / 2) - (Size.x / 2);
		Group_Data_PosY = ((float)App->CL_Ogre->Ogre_Listener->View_Height / 2) - (Size.y / 2);;

		ImGui::Separator();

		if (ImGui::Button("Close"))
		{
			Close_Group_Data();
		}

		ImGui::End();
	}
}

// *************************************************************************
// *			Close_Group_Data:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void ME_Editor_Gui::Close_Group_Data(void)
{
	//App->CL_Panels->Enable_Panels(1);
	Show_Group_Data_F = 0;

	RedrawWindow(App->CL_Groups->RightGroups_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *			Start_App_Data:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void ME_Editor_Gui::Start_App_Data(void)
{

	App->CL_Panels->Enable_Panels(0);

	Show_App_Data_F = 1;
}

// *************************************************************************
// *			App_Data_GUI:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void ME_Editor_Gui::App_Data_GUI(void)
{
	int Index = App->CL_Groups->Selected_Group;

	ImGui::SetNextWindowPos(ImVec2(App_Data_PosX, App_Data_PosY));

	if (!ImGui::Begin("App Data", &Show_App_Data_F, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Spacing();
		ImGui::Text("App Info");
		ImGui::Text("  ");

		int Count = 0;
		while (Count < 20)
		{
			ImGui::Text("Group Hwnd:- %i %i", Count, App->CL_Model->Group[Count]);
			Count++;
		}

		ImGui::Text("  ");

		ImGui::Text("Render View:- %i %i", App->CL_Ogre->Ogre_Listener->View_Width, App->CL_Ogre->Ogre_Listener->View_Height);


		//App->CL_Ogre->Get_View_Height_Width();


		ImVec2 Size = ImGui::GetWindowSize();
		App_Data_PosX = ((float)App->CL_Ogre->Ogre_Listener->View_Width / 2) - (Size.x / 2);
		App_Data_PosY = ((float)App->CL_Ogre->Ogre_Listener->View_Height / 2) - (Size.y / 2);;

		ImGui::Separator();

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
void ME_Editor_Gui::Close_App_Data(void)
{
	App->CL_Panels->Enable_Panels(1);
	Show_App_Data_F = 0;
}
