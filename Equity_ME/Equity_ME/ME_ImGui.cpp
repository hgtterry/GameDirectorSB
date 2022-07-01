/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "imgui.h"
#include "imgui_internal.h"
#include "ME_ImGui.h"


ME_ImGui::ME_ImGui()
{
	ImGui::CreateContext();
	ImGui_Set_Colours();
	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameBorderSize = 1.0;
	Load_Font();

	Show_FPS = 1;
	StartPos = 0;
	Show_Rotation = 0;
}


ME_ImGui::~ME_ImGui()
{
}

// *************************************************************************
// *						Load_Font  Terry Bernie						   *
// *************************************************************************
void ME_ImGui::Load_Font(void)
{
	ImGuiIO& io = ImGui::GetIO();
	font1 = io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 20);
	font2 = io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 48);
	font0 = io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 18);
	fontDroid = io.Fonts->AddFontFromFileTTF("DroidSans.ttf", 12);

	io.IniFilename = NULL;
}

// *************************************************************************
// *	  				ImGui_Set_Colours Terry Bernie					   *
// *************************************************************************
void ME_ImGui::ImGui_Set_Colours(void)
{
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;

	colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.94f, 0.94f, 0.94f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.96f, 0.96f, 0.96f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 1.00f, 1.00f, 0.51f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.98f, 0.98f, 0.98f, 0.53f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.46f, 0.54f, 0.80f, 0.60f);
	colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.06f, 0.53f, 0.98f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.26f, 0.59f, 0.98f, 0.31f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	colors[ImGuiCol_Separator] = ImVec4(0.39f, 0.39f, 0.39f, 0.62f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.14f, 0.44f, 0.80f, 0.78f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.14f, 0.44f, 0.80f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_Tab] = ImLerp(colors[ImGuiCol_Header], colors[ImGuiCol_TitleBgActive], 0.90f);
	colors[ImGuiCol_TabHovered] = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_TabActive] = ImLerp(colors[ImGuiCol_HeaderActive], colors[ImGuiCol_TitleBgActive], 0.60f);
	colors[ImGuiCol_TabUnfocused] = ImLerp(colors[ImGuiCol_Tab], colors[ImGuiCol_TitleBg], 0.80f);
	colors[ImGuiCol_TabUnfocusedActive] = ImLerp(colors[ImGuiCol_TabActive], colors[ImGuiCol_TitleBg], 0.40f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
	colors[ImGuiCol_NavHighlight] = colors[ImGuiCol_HeaderHovered];
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.70f, 0.70f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

// *************************************************************************
// *					Tabs_Render_Camera  Terry Bernie				   *
// *************************************************************************
void ME_ImGui::Tabs_Render_Camera(void)
{
	if (Show_FPS == 1)
	{
		ImGui_FPS();
	}

	if (Show_Rotation == 1)
	{
		ImGui_Rotation();
	}
}

// *************************************************************************
// *						ImGui_FPS  Terry Bernie						   *
// *************************************************************************
void ME_ImGui::ImGui_FPS(void)
{
	if (!ImGui::Begin("Ogre Data", &Show_FPS, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		if (StartPos == 0)
		{
			ImGui::SetWindowPos("Ogre Data", ImVec2(10, 550));
			ImGui::SetWindowSize(ImVec2(350, 90));
			StartPos = 1;
		}

		ImGui::Spacing();
		ImGui::Text("FPS average %.0f", ImGui::GetIO().Framerate);
		//ImGui::PopFont();

		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Rotation  Terry Bernie				   *
// *************************************************************************
void ME_ImGui::ImGui_Rotation(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Rotation2", &Show_Rotation, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Text("Position");
		ImGui::Separator();
		ImGui::Spacing();

		//geVec3d pos = App->CL_Vm_Genesis3D->Actor_Position;
		//ImGui::Text("X %.3f Y %.3f Z %.3f", pos.X, pos.Y, pos.Z);

		ImGui::Spacing();

		// ---------------------------------------------------------------------------------- Position X
		ImGui::Text("X ");
		ImGui::SameLine();

		float spacingPos = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftPosX", ImGuiDir_Left))
		{
		//	/*if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
		//	{
		//		App->CL_Vm_Genesis3D->Actor_Position.X += Model_XTranslate;
		//		App->CL_Vm_Genesis3D->MoveActor();
		//	}*/
		}

		ImGui::SameLine(0.0f, spacingPos);
		if (ImGui::ArrowButton("##rightPosX", ImGuiDir_Right))
		{
		///*	if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
		//	{
		//		App->CL_Vm_Genesis3D->Actor_Position.X -= Model_XTranslate;
		//		App->CL_Vm_Genesis3D->MoveActor();
		//	}*/
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsPosX[] = { "1", "2", "5", "10", "20" };
		static int XitemPosX = 1;
		bool ChangedPos = ImGui::Combo("Step Pos X", &XitemPosX, XitemsPosX, IM_ARRAYSIZE(XitemsPosX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedPos == 1)
		{
			//Model_XTranslate = (float)atof(XitemsX[XitemX]);
		}

		// ------------------------------------------ Position y
		ImGui::Text("Y ");
		ImGui::SameLine();

		float spacingPos2 = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftPosY", ImGuiDir_Left))
		{
			/*if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Position.Y += Model_YTranslate;
				App->CL_Vm_Genesis3D->MoveActor();
			}*/
		}
		ImGui::SameLine(0.0f, spacingPos2);
		if (ImGui::ArrowButton("##rightPosY", ImGuiDir_Right))
		{
			/*if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Position.Y -= Model_YTranslate;
				App->CL_Vm_Genesis3D->MoveActor();
			}*/
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsPosY[] = { "1", "2", "5", "10", "20" };
		static int XitemPosY = 1;
		bool ChangedPosY = ImGui::Combo("Step Pos Y", &XitemPosY, XitemsPosY, IM_ARRAYSIZE(XitemsPosY));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedPosY == 1)
		{
			//Model_YTranslate = (float)atof(XitemsY[XitemY]);
		}

		// ------------------------------------------ Position z
		ImGui::Text("Z ");
		ImGui::SameLine();

		float spacingPos3 = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftPosZ", ImGuiDir_Left))
		{
			/*if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Position.Z += Model_ZTranslate;
				App->CL_Vm_Genesis3D->MoveActor();
			}*/
		}
		ImGui::SameLine(0.0f, spacingPos3);
		if (ImGui::ArrowButton("##rightPosZ", ImGuiDir_Right))
		{
			/*if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Position.Z -= Model_ZTranslate;
				App->CL_Vm_Genesis3D->MoveActor();
			}*/
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsPosZ[] = { "1", "2", "5", "10", "20" };
		static int XitemPosZ = 1;
		bool ChangedPosZ = ImGui::Combo("Step Pos Z", &XitemPosZ, XitemsPosZ, IM_ARRAYSIZE(XitemsPosZ));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedPosZ == 1)
		{
			//Model_ZTranslate = (float)atof(XitemsZ[XitemZ]);
		}

		ImGui::Spacing();
		ImGui::Indent();
		ImGui::Indent();

		if (ImGui::Button("Middle of Bounding Box", ImVec2(200, 40)))
		{
			App->CL_Dimensions->Centre_Model_Mid();
		}

		if (ImGui::Button("Base of Bounding Box", ImVec2(200, 40)))
		{
			App->CL_Dimensions->Centre_Model_Base();
		}
		ImGui::Unindent();
		ImGui::Unindent();
		//*************************************************************************************** Rotation

		ImGui::Text("Rotation");
		ImGui::Separator();
		ImGui::Spacing();

		//geVec3d pos = App->CL_Vm_Genesis3D->Actor_Rotation;
		//ImGui::Text("X %.3f Y %.3f Z %.3f", pos.X, pos.Y, pos.Z);

		ImGui::Spacing();

		// ------------------------------------------ Rotation X
		ImGui::Text("X ");
		ImGui::SameLine();

		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##left", ImGuiDir_Left))
		{
			if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
			{
				App->CL_Dimensions->Rotate_X_Model(App->CL_Dimensions->Model_X_Rotation);
			}
		}

		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right))
		{
			if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
			{
				App->CL_Dimensions->Rotate_X_Model(-App->CL_Dimensions->Model_X_Rotation);
			}
		}
		ImGui::PopButtonRepeat();

		//------------------------------------------------------------------------------
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsRotX[] = { "0.5", "1", "10", "45", "90", "180" };
		static int XitemRotX = 4;
		bool Changed = ImGui::Combo("Step Rot X", &XitemRotX, XitemsRotX, IM_ARRAYSIZE(XitemsRotX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (Changed == 1)
		{
			App->CL_Dimensions->Model_X_Rotation = (float)atof(XitemsRotX[XitemRotX]);
		}

		// ------------------------------------------ Rotation y
		ImGui::Text("Y ");
		ImGui::SameLine();

		float spacing2 = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftY", ImGuiDir_Left))
		{
			if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
			{
				App->CL_Dimensions->Rotate_Y_Model(App->CL_Dimensions->Model_Y_Rotation);
			}
		}
		ImGui::SameLine(0.0f, spacing2);
		if (ImGui::ArrowButton("##rightY", ImGuiDir_Right))
		{
			if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
			{
				App->CL_Dimensions->Rotate_Y_Model(-App->CL_Dimensions->Model_Y_Rotation);
			}
		}
		ImGui::PopButtonRepeat();

		//------------------------------------------------------------------------------
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsY[] = { "0.5", "1", "10", "45", "90", "180" };
		static int XitemY = 4;
		bool ChangedY = ImGui::Combo("Step Rot Y", &XitemY, XitemsY, IM_ARRAYSIZE(XitemsY));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedY == 1)
		{
			App->CL_Dimensions->Model_Y_Rotation = (float)atof(XitemsY[XitemY]);
		}

		// ------------------------------------------ Rotation z
		ImGui::Text("Z ");
		ImGui::SameLine();

		float spacing3 = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftZ", ImGuiDir_Left))
		{
			if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
			{
				App->CL_Dimensions->Rotate_Z_Model(App->CL_Dimensions->Model_Z_Rotation);
			}
		}
		ImGui::SameLine(0.0f, spacing3);
		if (ImGui::ArrowButton("##rightZ", ImGuiDir_Right))
		{
			if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
			{
				App->CL_Dimensions->Rotate_Z_Model(-App->CL_Dimensions->Model_Z_Rotation);
			}
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsZ[] = { "0.5", "1", "10", "45", "90", "180" };
		static int XitemZ = 4;
		bool ChangedZ = ImGui::Combo("Step Rot Z", &XitemZ, XitemsZ, IM_ARRAYSIZE(XitemsZ));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedZ == 1)
		{
			App->CL_Dimensions->Model_Z_Rotation = (float)atof(XitemsZ[XitemZ]);
		}

		if (ImGui::Button("Close"))
		{
			Show_Rotation = 0;
			App->CL_Panels->Show_Panels(1);
			App->CL_TopBar->Toggle_Dimensions_Flag = 0;
			RedrawWindow(App->CL_TopBar->Model_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		}

		ImGui::End();
	}
}
