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
#include "AB_App.h"
#include "resource.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "SB_ImGui.h"

#define	M_PI		((geFloat)3.14159265358979323846f)
#define Units_RadiansToDegrees(r) ((((geFloat)(r)) * 180.0f) / M_PI)

SB_ImGui::SB_ImGui()
{
	ImGui::CreateContext();
	ImGui_Set_Colours();
	Load_Font();

	PosX = 500;
	PosY = 500;

	Model_Data_PosX = 500;
	Model_Data_PosY = 500;

	Show_FPS = 1;
	StartPos = 0;
	
	Show_Model_Data_F = 0;
	Show_Camera_Pos_F = 0;
	Show_BB_Data_F = 0;

	PosX_Selected = 1;
	PosY_Selected = 0;
	PosZ_Selected = 0;

	// -------------- Physics Console
	Disable_Physics_Console = 0;
	Show_Physics_Console = 1;
	Physics_PosX = 500;
	Physics_PosY = 500;
	Physics_Console_StartPos = 0;

	m_pDoc = nullptr;
	pCameraEntity = nullptr;

}


SB_ImGui::~SB_ImGui()
{
}

// *************************************************************************
// *		ImGui_Editor_Loop:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_ImGui::ImGui_Editor_Loop(void)
{
	if (Show_Model_Data_F == 1)
	{
		Model_Data_GUI();
	}

	if (Show_Camera_Pos_F == 1)
	{
		Camera_Pos_GUI();
	}

	if (Show_BB_Data_F == 1)
	{
		Model_BB_GUI();
	}

	// SBC_Gui_Dialogs - Physics Console
	if (Show_Physics_Console == 1)
	{
		Physics_Console_Gui();
	}
}

// *************************************************************************
// *					Render_FPS  Terry Flanigan				   *
// *************************************************************************
void SB_ImGui::Render_FPS(void)
{
	if (Show_FPS == 1)
	{
		ImGui_FPS();
	}
}


// *************************************************************************
// *						Load_Font  Terry Bernie						   *
// *************************************************************************
void SB_ImGui::Load_Font(void)
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
void SB_ImGui::ImGui_Set_Colours(void)
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
void SB_ImGui::ImGui_FPS(void)
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

		int Stack_Memory = App->Get_Stack();
		float used = ((float)(2097152 - Stack_Memory) / 1024);
		ImGui::Text("Stack Used %f", used);
		
		
		ImVec2 Size = ImGui::GetWindowSize();
		PosX = ((float)App->CLSB_Ogre->OgreListener->View_Width / 2) - (Size.x / 2);
		PosY = 10;

		ImGui::End();
	}
}

// *************************************************************************
// *			Start_Model_Data:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_ImGui::Start_Model_Data(void)
{
	Show_Model_Data_F = 1;
}

// *************************************************************************
// *			Model_Data_GUI:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_ImGui::Model_Data_GUI(void)
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
		ImGui::Text("Model Name:- %s", App->CLSB_Model->JustName);
		ImGui::Text("Model File Name:- %s", App->CLSB_Model->FileName);
		ImGui::Text("Model Path:- %s", App->CLSB_Model->Path_FileName);
		ImGui::Text("Texture Path:- %s", App->CLSB_Model->Texture_FolderPath);
		ImGui::Text("  ");
		ImGui::Text("Vertices:- %i", App->CLSB_Model->VerticeCount);
		ImGui::Text("Faces:- %i", App->CLSB_Model->FaceCount);
		ImGui::Text("Groups:- %i", App->CLSB_Model->Get_Groupt_Count());
		ImGui::Text("Motions:- %i", App->CLSB_Model->MotionCount);
		ImGui::Text(" --------------------------- Brushes  ");
		ImGui::Text("XBrushes:- %i", App->CLSB_Model->XBrushCount);
		ImGui::Text("  ");

		ImVec2 Size = ImGui::GetWindowSize();
		Model_Data_PosX = ((float)App->CLSB_Ogre->OgreListener->View_Width / 2) - (Size.x / 2);
		Model_Data_PosY = ((float)App->CLSB_Ogre->OgreListener->View_Height / 2) - (Size.y / 2);;

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
void SB_ImGui::Close_Model_Data(void)
{
	Show_Model_Data_F = 0;
}

// *************************************************************************
// *		Start_Camera_Pos:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_ImGui::Start_Camera_Pos(void)
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	pCameraEntity = App->CLSB_Camera_WE->FindCameraEntity();

	//CameraPosition = pCameraEntity->mOrigin;

	Show_Camera_Pos_F = 1;
}

// *************************************************************************
// *			Camera_Pos_GUI:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_ImGui::Camera_Pos_GUI(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Camera_Pos", &Show_Camera_Pos_F, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Columns(2);
		ImGui::SetColumnWidth(10, 120);

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));

		geVec3d Angles;
		pCameraEntity->GetAngles(&Angles, Level_GetEntityDefs(m_pDoc->pLevel));

		ImGui::Text("World Editor Position");
		ImGui::Text("X = %f", pCameraEntity->mOrigin.X);
		ImGui::Text("Y = %f", pCameraEntity->mOrigin.Y);
		ImGui::Text("Z = %f", pCameraEntity->mOrigin.Z);
		
		ImGui::Text("  ");
		ImGui::Text("Equity Position");

		ImGui::Text("X = %f", App->CLSB_Ogre->mCamera->getPosition().x);
		ImGui::Text("Y = %f", App->CLSB_Ogre->mCamera->getPosition().y);
		ImGui::Text("Z = %f", App->CLSB_Ogre->mCamera->getPosition().z);
		ImGui::Text("  ");

		// --------------------------------------------------
		ImGui::NextColumn();
	
		ImGui::Text("World Editor Rotation");
		ImGui::Text("X = %f", Units_RadiansToDegrees(Angles.X));
		ImGui::Text("Y = %f", Units_RadiansToDegrees(Angles.Y));
		ImGui::Text("Z = %f", Units_RadiansToDegrees(Angles.Z));

		ImGui::Text("  ");
		ImGui::Text("Equity Rotation");

		ImGui::Text("X = %f", App->CLSB_Ogre->mCamera->getOrientation().getPitch().valueDegrees());
		ImGui::Text("Y = %f", App->CLSB_Ogre->mCamera->getOrientation().getYaw().valueDegrees());
		ImGui::Text("Z = %f", App->CLSB_Ogre->mCamera->getOrientation().getRoll().valueDegrees());

		ImVec2 Size = ImGui::GetWindowSize();
		Model_Data_PosX = ((float)App->CLSB_Ogre->OgreListener->View_Width / 2) - (Size.x / 2);
		Model_Data_PosY = ((float)App->CLSB_Ogre->OgreListener->View_Height / 2) - (Size.y / 2);;

		ImGui::PopStyleVar();
		ImGui::Columns(0);

		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Button("Close"))
		{
			Close_Camera_Pos();
		}

		ImGui::End();
	}
}

// *************************************************************************
// *			Close_Camera_Pos:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_ImGui::Close_Camera_Pos(void)
{
	Show_Camera_Pos_F = 0;
}

// *************************************************************************
// *			Start_BB_Data:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_ImGui::Start_BB_Data(void)
{
	Show_BB_Data_F = 1;
}

// *************************************************************************
// *			Model_BB_GUI:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_ImGui::Model_BB_GUI(void)
{
	ImGui::SetNextWindowPos(ImVec2(Model_Data_PosX, Model_Data_PosY));

	if (!ImGui::Begin("BB Data", &Show_BB_Data_F, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Spacing();
		ImGui::Text("Bounding Box Info");
		ImGui::Text("  ");
		ImGui::Text("Min X:- %f", App->CLSB_Model->BB_Min.x);
		ImGui::Text("Min Y:- %f", App->CLSB_Model->BB_Min.y);
		ImGui::Text("Min Z:- %f", App->CLSB_Model->BB_Min.z);
		ImGui::Text("  ");
		ImGui::Text("Max X:- %f", App->CLSB_Model->BB_Max.x);
		ImGui::Text("Max Y:- %f", App->CLSB_Model->BB_Max.y);
		ImGui::Text("Max Z:- %f", App->CLSB_Model->BB_Max.z);
		ImGui::Text("  ");
		ImGui::Text("Size X:- %f", App->CLSB_Model->Size.x);
		ImGui::Text("Size Y:- %f", App->CLSB_Model->Size.y);
		ImGui::Text("Size Z:- %f", App->CLSB_Model->Size.z);
		ImGui::Text("  ");
		ImGui::Text("Centre X:- %f", App->CLSB_Model->Centre.x);
		ImGui::Text("Centre Y:- %f", App->CLSB_Model->Centre.y);
		ImGui::Text("Centre Z:- %f", App->CLSB_Model->Centre.z);
		ImGui::Text("  ");
		ImGui::Text("Radius:- %f", App->CLSB_Model->radius);

		ImVec2 Size = ImGui::GetWindowSize();
		Model_Data_PosX = ((float)App->CLSB_Ogre->OgreListener->View_Width / 2) - (Size.x / 2);
		Model_Data_PosY = ((float)App->CLSB_Ogre->OgreListener->View_Height / 2) - (Size.y / 2);;

		ImGui::Separator();

		if (ImGui::Button("Close"))
		{
			Close_BB_Data();
		}

		ImGui::End();
	}
}

// *************************************************************************
// *			Close_BB_Data:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_ImGui::Close_BB_Data(void)
{
	Show_BB_Data_F = 0;
}

// *************************************************************************
// *						Physics_Console  Terry Bernie				   *
// *************************************************************************
void SB_ImGui::Physics_Console_Gui(void)
{
	ImGui::SetNextWindowPos(ImVec2(Physics_PosX, Physics_PosY), ImGuiCond_FirstUseEver);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));
	ImGuiStyle* style = &ImGui::GetStyle();

	if (!ImGui::Begin("Physics_Console", &Show_Physics_Console, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		if (Disable_Physics_Console == 1)
		{
			ImGui::BeginDisabled(true);
		}

		ImGui::Text("Physics Console");

		ImGui::SameLine(0, 270);
		if (ImGui::Button("H"))
		{
			//App->Cl_Utilities->OpenHTML("Help\\Physics_Console.html");
		}

		ImGui::SameLine();
		if (ImGui::Button("X"))
		{
			//CheckMenuItem(App->mMenu, ID_WINDOWS_SHOWPHYSICSPANEL, MF_BYCOMMAND | MF_UNCHECKED);
			Physics_Console_StartPos = 0;
			Show_Physics_Console = 0;
		}

		ImGui::Separator();

		if (App->CLSB_Ogre->OgreListener->GD_Run_Physics == 1)
		{
			style->Colors[ImGuiCol_Button] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
		}
		else
		{
			style->Colors[ImGuiCol_Button] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
		}

		if (ImGui::Button("Physics On"))
		{
			if (App->CLSB_Model->Model_Loaded == 1)
			{
				if (App->CLSB_Ogre->OgreListener->GD_Run_Physics == 1)
				{
					App->CLSB_Ogre->OgreListener->GD_Run_Physics = 0;
				}
				else
				{
					App->CLSB_Ogre->OgreListener->GD_Run_Physics = 1;
				}

				//App->RedrawWindow_Dlg(App->Physics_Console_Hwnd);
			}
		}

		if (App->CLSB_Ogre->OgreListener->Dubug_Physics_Draw == 1)
		{
			style->Colors[ImGuiCol_Button] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
		}
		else
		{
			style->Colors[ImGuiCol_Button] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
		}

		/*ImGui::SameLine();
		if (ImGui::Button("Physics Outline"))
		{
			if (App->CLSB_Ogre->OgreListener->Dubug_Physics_Draw == 1)
			{
				App->CLSB_Ogre->OgreListener->Dubug_Physics_Draw = 0;
				App->CLSB_Ogre->BulletListener->Render_Debug_Flag = 0;
			}
			else
			{
				App->CLSB_Ogre->OgreListener->Dubug_Physics_Draw = 1;
				App->CLSB_Ogre->BulletListener->Render_Debug_Flag = 1;
			}
		}*/

		ImGui::SameLine();
		if (ImGui::Button("Reset Physics"))
		{
			if (App->CLSB_Model->Model_Loaded == 1)
			{
				App->CLSB_Bullet->Reset_Physics();
			}
		}

		//ImGui::SameLine();
		//if (ImGui::Button("Reset Entities"))
		//{
		//	/*if (App->SBC_Scene->Scene_Loaded == 1)
		//	{
		//		App->SBC_Physics->Reset_Triggers();
		//	}*/
		//}

		ImGui::SameLine();
		//if (ImGui::Button("Reset Scene"))
		//{
		//	//if (App->SBC_Scene->Scene_Loaded == 1)
		//	//{

		//	//	int Saved = App->CL_Ogre->OgreListener->GD_CameraMode;
		//	//	App->CL_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;

		//	//	App->SBC_Physics->Reset_Physics();
		//	//	App->CL_Ogre->OgreListener->GD_Run_Physics = 1;
		//	//	App->SBC_Physics->Reset_Triggers();
		//	//	App->CL_Ogre->OgreListener->GD_Run_Physics = 1;

		//	//	App->SBC_TopTabs->Toggle_FirstCam_Flag = 1;
		//	//	App->SBC_TopTabs->Toggle_FreeCam_Flag = 0;
		//	//	RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

		//	//	/*App->SBC_TopTabs->Toggle_FirstCam_Flag = 0;
		//	//	App->SBC_TopTabs->Toggle_FreeCam_Flag = 1;
		//	//	RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		//	//	App->CL_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;*/

		//	//	App->SBC_Com_Environments->GameMode(0);

		//	//}
		//}

		if (Physics_Console_StartPos == 0)
		{
			ImVec2 Size = ImGui::GetWindowSize();
			Physics_PosX = 10;
			Physics_PosY = ((float)App->CLSB_Ogre->OgreListener->View_Height) - (Size.y) - 50;
			ImGui::SetWindowPos("Physics_Console", ImVec2(Physics_PosX, Physics_PosY));

			Physics_Console_StartPos = 1;
		}

		style->Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
		ImGui::PopStyleColor();


		if (Disable_Physics_Console == 1)
		{
			ImGui::EndDisabled();
		}

		ImGui::End();
	}
}


