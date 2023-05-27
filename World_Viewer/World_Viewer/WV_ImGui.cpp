#include "stdafx.h"
#include "WV_App.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "WV_ImGui.h"


WV_ImGui::WV_ImGui()
{
	ImGui::CreateContext();
	ImGui_Set_Colours();
	Load_Font();

	PosX = 500;
	PosY = 500;

	Model_Data_PosX = 500;
	Model_Data_PosY = 500;

	Model_Camera_PosX = 0;
	Model_Camera_PosY = 0;

	Show_FPS_F = 0;

	Show_Model_Data_F = 0;
	Show_Camera_Data_F = 0;

	StartPos = 0;
}


WV_ImGui::~WV_ImGui()
{

}


// *************************************************************************
// *			Load_Font:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void WV_ImGui::Load_Font(void)
{
	ImGuiIO& io = ImGui::GetIO();
	font1 = io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 20);
	font2 = io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 48);
	font0 = io.Fonts->AddFontFromFileTTF("Roboto-Medium.ttf", 18);

	io.IniFilename = NULL;
}

// *************************************************************************
// *	  		ImGui_Set_Colours:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void WV_ImGui::ImGui_Set_Colours(void)
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
// *		ImGui_Editor_Loop:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void WV_ImGui::ImGui_Editor_Loop(void)
{
	if (Show_FPS_F == 1)
	{
		ImGui_FPS();
	}

	if (Show_Model_Data_F == 1)
	{
		Model_Data_GUI();
	}

	if (Show_Camera_Data_F == 1)
	{
		Model_Camera_GUI();
	}
}

// *************************************************************************
// *						ImGui_FPS  Terry Bernie						   *
// *************************************************************************
void WV_ImGui::ImGui_FPS(void)
{
	ImGui::SetNextWindowPos(ImVec2(PosX, PosY));

	if (!ImGui::Begin("Ogre Data", &Show_FPS_F, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize
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
		PosX = ((float)App->CL_Ogre->OgreListener->View_Width / 2) - (Size.x / 2);
		PosY = 10;

		ImGui::End();
	}
}

// *************************************************************************
// *			Start_Model_Data:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void WV_ImGui::Start_Model_Data(void)
{
	Show_Model_Data_F = 1;
}

// *************************************************************************
// *			Model_Data_GUI:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void WV_ImGui::Model_Data_GUI(void)
{
	ImGui::SetNextWindowPos(ImVec2(Model_Data_PosX, Model_Data_PosY));

	if (!ImGui::Begin("Model Data", &Show_Model_Data_F, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		/*int BrushCount = App->CL_CBrush->Get_Brush_Count();
		int Count = 0;

		while (Count < BrushCount)
		{
			Brush* b = App->CL_Brushes->Get_Brush_ByIndex(Count);
			ImGui::Text("Names:- %s", b->Name);
			Count++;
		}*/
		

		/*ImGui::Spacing();
		ImGui::Text("Model Info");
		ImGui::Text("  ");
		ImGui::Text("Model Name:- %s", App->CL_Scene->JustName);
		ImGui::Text("Model File Name:- %s", App->CL_Scene->FileName);
		ImGui::Text("Model Path:- %s", App->CL_Scene->Path_FileName);
		ImGui::Text("Texture Path:- %s", App->CL_Scene->Texture_FolderPath);
		ImGui::Text("  ");
		ImGui::Text("Vertices:- %i", App->CL_Scene->VerticeCount);
		ImGui::Text("Faces:- %i", App->CL_Scene->FaceCount);
		ImGui::Text("Groups:- %i", App->CL_Scene->Get_Groupt_Count());
		ImGui::Text("Motions:- %i", App->CL_Scene->MotionCount);
		ImGui::Text("  ");

		ImGui::Text("Came Pos:- %f %f %f", App->CL_Ogre->mCamera->getPosition().x, 
			App->CL_Ogre->mCamera->getPosition().y,
			App->CL_Ogre->mCamera->getPosition().z);


		ImGui::Text("Came Angles:- %f %f %f", App->CL_Scene->Start_Cam_Angles.x,
			App->CL_Scene->Start_Cam_Angles.y,
			App->CL_Scene->Start_Cam_Angles.z);

		ImGui::Text("Pitch:- %f",App->CL_Ogre->mCamera->getOrientation().getPitch().valueDegrees());
		ImGui::Text("Yaw:- %f", App->CL_Ogre->mCamera->getOrientation().getYaw().valueDegrees());
		
		ImGui::Text("  ");
		ImGui::Text("Player Added:- %i", App->CL_Scene->Player_Added);
		ImGui::Text("Physics Running:- %i", App->CL_Ogre->OgreListener->GD_Run_Physics);


		ImVec2 Size = ImGui::GetWindowSize();
		Model_Data_PosX = ((float)App->CL_Ogre->OgreListener->View_Width / 2) - (Size.x / 2);
		Model_Data_PosY = ((float)App->CL_Ogre->OgreListener->View_Height / 2) - (Size.y / 2);;*/

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
void WV_ImGui::Close_Model_Data(void)
{
	Show_Model_Data_F = 0;
}

// *************************************************************************
// *			Start_Camera_Data:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void WV_ImGui::Start_Camera_Data(void)
{
	Show_Camera_Data_F = 1;
}

// *************************************************************************
// *			Model_Camera_GUI:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void WV_ImGui::Model_Camera_GUI(void)
{
	//ImGui::SetNextWindowPos(ImVec2(Model_Camera_PosX, Model_Camera_PosY));

	if (!ImGui::Begin("Camera Data", &Show_Camera_Data_F, ImGuiWindowFlags_NoSavedSettings ))
	{
		ImGui::End();
	}
	else
	{

		ImGui::Spacing();
		ImGui::Text("Camera");
		ImGui::Text("  ");
		ImGui::Text("Camera X:- %f", App->CL_Ogre->mCamera->getPosition().x);
		ImGui::Text("Camera Y:- %f", App->CL_Ogre->mCamera->getPosition().y);
		ImGui::Text("Camera Z:- %f", App->CL_Ogre->mCamera->getPosition().z);
		
		ImGui::Separator();

		if (ImGui::Button("Close"))
		{
			Close_Camera_Data();
		}

		ImGui::End();
	}
}

// *************************************************************************
// *			Close_Model_Data:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void WV_ImGui::Close_Camera_Data(void)
{
	Show_Camera_Data_F = 0;
}