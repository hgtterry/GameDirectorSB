/*
Copyright (c) 2023 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "imgui.h"
#include "imgui_internal.h"
#include "ME_ImGui.h"


ME_ImGui::ME_ImGui()
{
	ImGui::CreateContext();
	ImGui_Set_Colours();
	Load_Font();

	PosX = 500;
	PosY = 500;

	Show_FPS = 1;
	StartPos = 0;
	Show_Dimensions = 0;
	Show_ImGui_Test = 0;

	PosX_Selected = 1;
	PosY_Selected = 0;
	PosZ_Selected = 0;

}


ME_ImGui::~ME_ImGui()
{
}

// *************************************************************************
// *					Render_FPS  Terry Flanigan				   *
// *************************************************************************
void ME_ImGui::Render_FPS(void)
{
	if (Show_FPS == 1)
	{
		ImGui_FPS();
	}

	if (Show_ImGui_Test == 1)
	{
		ImGui::ShowDemoWindow();
	}
}

// *************************************************************************
// *					Render_FPS  Terry Flanigan				   *
// *************************************************************************
void ME_ImGui::ImGui_Render_Model(void)
{
	if (Show_Dimensions == 1)
	{
		ImGui_Dimensions();
	}
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

	style->WindowRounding = 6.0;
	style->FrameRounding = 0.0;
	style->WindowBorderSize = 0;
	style->FrameBorderSize = 1.0;

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
// *						ImGui_FPS  Terry Bernie						   *
// *************************************************************************
void ME_ImGui::ImGui_FPS(void)
{
	ImGui::SetNextWindowPos(ImVec2(PosX, PosY));

	if (!ImGui::Begin("Ogre Data", &Show_FPS, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		if (StartPos == 0)
		{
			ImGui::SetWindowPos("Ogre Data", ImVec2(500, 5));
			ImGui::SetWindowSize(ImVec2(350, 90));
			StartPos = 1;
		}

		ImGui::Spacing();
		ImGui::Text("FPS average %.0f", ImGui::GetIO().Framerate);
		
		ImVec2 Size = ImGui::GetWindowSize();
		PosX = ((float)App->CL_Ogre->Ogre_Listener->View_Width / 2) - (Size.x / 2);
		PosY = 10;

		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Dimensions  Terry Bernie				   *
// *************************************************************************
void ME_ImGui::ImGui_Dimensions(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	ImGuiStyle* style = &ImGui::GetStyle();

	if (!ImGui::Begin("Rotation2", &Show_Dimensions, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		App->CL_Ogre->RenderListener->Show_Crosshair = 1;

		
		//*************************************************************************************** Rotation
		ImGui_Position();

		ImGui_Rotation();

		ImGui::Text("Scale");
		ImGui::Separator();
		ImGui::Spacing();

		// ---------------------------------------------------------------------------------- Scale X
		style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);
		ImGui::Text("X ");
		style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
		ImGui::SameLine();

		float Delta = App->CL_Dimensions->Model_XScale;

		float spacingScalePosX = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftScaleX", ImGuiDir_Left))
		{
			App->CL_Dimensions->Scale_Model(1, Delta *4, 1,1);
		}

		ImGui::SameLine(0.0f, spacingScalePosX);
		if (ImGui::ArrowButton("##rightScaleX", ImGuiDir_Right))
		{
			App->CL_Dimensions->Scale_Model(0, Delta, 1,1);
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsScaleX[] = { "0.5" };
		static int XitemScaleX = 0;
		bool ChangedScaleX = ImGui::Combo("Step Scale X", &XitemScaleX, XitemsScaleX, IM_ARRAYSIZE(XitemsScaleX));
		if (ChangedScaleX == 1)
		{
			App->CL_Dimensions->Model_XScale = (float)atof(XitemsScaleX[XitemScaleX]);
		}

		// ---------------------------------------------------------------------------------- Scale Y
		style->Colors[ImGuiCol_Text] = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
		ImGui::Text("Y ");
		style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
		ImGui::SameLine();

		Delta = App->CL_Dimensions->Model_YScale;

		float spacingScalePosY = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftScaleY", ImGuiDir_Left))
		{
			App->CL_Dimensions->Scale_Model(1, 1, Delta*4, 1);
		}

		ImGui::SameLine(0.0f, spacingScalePosY);
		if (ImGui::ArrowButton("##rightScaleY", ImGuiDir_Right))
		{
			App->CL_Dimensions->Scale_Model(1, 1, Delta, 1);
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsScaleY[] = { "0.5" };
		static int XitemScaleY = 0;
		bool ChangedScaleY = ImGui::Combo("Step Scale Y", &XitemScaleY, XitemsScaleY, IM_ARRAYSIZE(XitemsScaleY));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedScaleY == 1)
		{
			App->CL_Dimensions->Model_YScale = (float)atof(XitemsScaleY[XitemScaleY]);
		}

		// ---------------------------------------------------------------------------------- Scale Z
		style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
		ImGui::Text("Z ");
		style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
		ImGui::SameLine();

		Delta = App->CL_Dimensions->Model_ZScale;

		float spacingScalePosZ = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftScaleZ", ImGuiDir_Left))
		{
			App->CL_Dimensions->Scale_Model(1, 1, 1,Delta*4);
		}

		ImGui::SameLine(0.0f, spacingScalePosZ);
		if (ImGui::ArrowButton("##rightScaleZ", ImGuiDir_Right))
		{
			App->CL_Dimensions->Scale_Model(1, 1, 1, Delta);
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsScaleZ[] = { "0.5" };
		static int XitemScaleZ = 0;
		bool ChangedScaleZ = ImGui::Combo("Step Scale Z", &XitemScaleZ, XitemsScaleZ, IM_ARRAYSIZE(XitemsScaleZ));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedScaleZ == 1)
		{
			App->CL_Dimensions->Model_ZScale = (float)atof(XitemsScaleZ[XitemScaleZ]);
		}

		if (ImGui::Button("Close"))
		{
			Show_Dimensions = 0;
			App->CL_Panels->Show_Panels(1);
			App->CL_TopBar->Toggle_Dimensions_Flag = 0;
			RedrawWindow(App->CL_TopBar->Model_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			App->CL_Ogre->RenderListener->Show_Crosshair = 0;
		}

		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Position  Terry Bernie				   *
// *************************************************************************
void ME_ImGui::ImGui_Position(void)
{
	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::Text("Position");
	ImGui::Separator();
	ImGui::Spacing();

	Ogre::Vector3 pos;
	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
	{
		pos.x = App->CL_Model->S_BoundingBox[0]->Centre->x;
		pos.y = App->CL_Model->S_BoundingBox[0]->Centre->y;
		pos.z = App->CL_Model->S_BoundingBox[0]->Centre->z;

		App->CL_Ogre->RenderListener->Hair_1PosX = pos.x;
		App->CL_Ogre->RenderListener->Hair_1PosY = pos.y;
		App->CL_Ogre->RenderListener->Hair_1PosZ = pos.z;
	}

	ImGui::Indent();
	ImGui::Indent();
	ImGui::Text("X %.3f Y %.3f Z %.3f", pos.x, pos.y, pos.z);

	ImGui::Spacing();

	// ----------------------------------------------------------------------------- Position

	float spacingX = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);
	if (ImGui::ArrowButton("##leftXX", ImGuiDir_Left))
	{
		if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
		{
			if (PosX_Selected == 1)
			{
				App->CL_Dimensions->Translate_Model(-App->CL_Dimensions->Model_X_Position, 0, 0);
			}

			if (PosY_Selected == 1)
			{
				App->CL_Dimensions->Translate_Model(0, -App->CL_Dimensions->Model_X_Position, 0);
			}

			if (PosZ_Selected == 1)
			{
				App->CL_Dimensions->Translate_Model(0, 0, -App->CL_Dimensions->Model_X_Position);
			}
		}
	}

	ImGui::SameLine(0.0f, spacingX);
	if (ImGui::ArrowButton("##rightXX", ImGuiDir_Right))
	{
		if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
		{
			if (PosX_Selected == 1)
			{
				App->CL_Dimensions->Translate_Model(App->CL_Dimensions->Model_X_Position, 0, 0);
			}

			if (PosY_Selected == 1)
			{
				App->CL_Dimensions->Translate_Model(0, App->CL_Dimensions->Model_X_Position, 0);
			}

			if (PosZ_Selected == 1)
			{
				App->CL_Dimensions->Translate_Model(0, 0, App->CL_Dimensions->Model_X_Position);
			}
		}
	}
	ImGui::PopButtonRepeat();

	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	const char* XitemsPosXX[] = { "0.001","0.01","0.1","1", "2", "5", "10", "20" };
	static int XitemPosXX = 3;
	bool ChangedPosX = ImGui::Combo("Step Pos", &XitemPosXX, XitemsPosXX, IM_ARRAYSIZE(XitemsPosXX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
	if (ChangedPosX == 1)
	{
		App->CL_Dimensions->Model_X_Position = (float)atof(XitemsPosXX[XitemPosXX]);
	}

	// ----------------------------------------------------------------------------- Pos X
	ImGui::Indent();

	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);
	ImGui::Checkbox("X", &PosX_Selected);
	if (PosX_Selected == 1)
	{
		PosY_Selected = 0;
		PosZ_Selected = 0;
	}
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	//------------------------------------------------------------------------------- Pos Y
	ImGui::SameLine();
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
	ImGui::Checkbox("Y", &PosY_Selected);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

	if (PosY_Selected)
	{
		PosX_Selected = 0;
		PosZ_Selected = 0;
	}

	//------------------------------------------------------------------------------- Pos Z
	ImGui::SameLine();
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
	ImGui::Checkbox("Z", &PosZ_Selected);
	if (PosZ_Selected)
	{
		PosX_Selected = 0;
		PosY_Selected = 0;
	}
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);


	style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

	ImGui::Spacing();
	ImGui::Unindent();

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
}

// *************************************************************************
// *						ImGui_Rotation  Terry Bernie				   *
// *************************************************************************
void ME_ImGui::ImGui_Rotation(void)
{
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
}
