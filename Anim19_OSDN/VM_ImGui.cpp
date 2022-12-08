#include "stdafx.h"
#include "GD19_App.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "VM_ImGui.h"


VM_ImGui::VM_ImGui()
{
	ImGui::CreateContext();
	ImGui_Set_Colours();
	ImGuiStyle& style = ImGui::GetStyle();
	style.FrameBorderSize = 1.0;
	Load_Font();

	StartPos = 0;
	StartPos_PB = 0;
	Show_FPS = 1;
	Show_ImGui_Test = 0;
	Show_Rotation = 0;
	Show_Position = 0;
	Show_Scale = 0;
	Show_Image = 0;
	Show_Group_List = 0;
	Show_Motion_List = 0;
	Show_ImGui_TextureData = 0;
	Show_Model_Data = 0;
	Show_App_Data = 0;
	Show_Progress_Bar = 0;
	Show_Object_Data = 0;
	Show_Collision_Debug = 0;
	Show_Object_Selection = 0;

	Model_XTranslate = 2;
	Model_YTranslate = 2;
	Model_ZTranslate = 2;

	Test = 180;

	Block = 0;
	Block_Motion = 0;
	Reset_Groups = 0;

	progress = 0;
	Progress_Count = 0;
	Progress_Delta = 0;

	Object_Index = 0;
}


VM_ImGui::~VM_ImGui()
{
}

// *************************************************************************
// *					Reset_Class  Terry Bernie						   *
// *************************************************************************
void VM_ImGui::Reset_Class(void)
{
	Reset_Groups = 1;

	StartPos = 0;
	Show_FPS = 1;
	Show_ImGui_Test = 0;
	Show_Rotation = 0;
	Show_Position = 0;
	Show_Scale = 0;
	Show_Object_Data = 0;

	Model_XTranslate = 2;
	Model_YTranslate = 2;
	Model_ZTranslate = 2;

	Test = 180;
}

// *************************************************************************
// *						Load_Font  Terry Bernie						   *
// *************************************************************************
void VM_ImGui::Load_Font(void)
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
void VM_ImGui::ImGui_Set_Colours(void)
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
// *					ImGui_Render_Loop  Terry Flanigan				   *
// *************************************************************************
void VM_ImGui::ImGui_Render_Loop(void)
{
	if (Show_FPS == 1)
	{
		ImGui_FPS();
	}

	if (Show_Model_Data == 1)
	{
		ImGui_Model_Data();
	}

	if (Show_App_Data == 1)
	{
		ImGui_App_Data();
	}

	if (Show_ImGui_Test == 1)
	{
		ImGui::ShowDemoWindow();
	}

	if (Show_Object_Data == 1)
	{
		ImGui_Object_Data();
	}

	if (Show_Collision_Debug == 1)
	{
		ImGui_Collision_Debug();
	}

	if (Show_Object_Selection == 1)
	{
		Object_Selection();
	}


}

// *************************************************************************
// *					Tabs_Render_Camera  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::Tabs_Render_Camera(void)
{
	if (Show_FPS == 1)
	{
		ImGui_FPS();
	}

	if (Show_Model_Data == 1)
	{
		ImGui_Model_Data();
	}

	if (Show_App_Data == 1)
	{
		ImGui_App_Data();
	}

	if (Show_ImGui_Test == 1)
	{
		ImGui::ShowDemoWindow();
	}

	if (Show_Position == 1)
	{
		
	}

	if (Show_Object_Data == 1)
	{
		ImGui_Object_Data();
	}
	
}

// *************************************************************************
// *					Tabs_Render_Motions  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::Tabs_Render_Motions(void)
{
	if (Show_FPS == 1)
	{
		ImGui_FPS();
	}

	if (Show_Model_Data == 1)
	{
		ImGui_Model_Data();
	}

	if (Show_App_Data == 1)
	{
		ImGui_App_Data();
	}

	if (Show_Motion_List == 1)
	{
		ImGui_MotionList();
	}

	if (Show_Object_Data == 1)
	{
		ImGui_Object_Data();
	}
}

// *************************************************************************
// *					Tabs_Render_Dimensions  Terry Bernie			   *
// *************************************************************************
void VM_ImGui::Tabs_Render_Dimensions(void)
{
	if (Show_FPS == 1)
	{
		ImGui_FPS();
	}

	if (Show_Model_Data == 1)
	{
		ImGui_Model_Data();
	}

	if (Show_App_Data == 1)
	{
		ImGui_App_Data();
	}

	if (Show_Rotation == 1)
	{
		
	}

	if (Show_Position == 1)
	{
		
	}

	if (Show_Scale == 1)
	{
		
	}

	if (Show_Object_Data == 1)
	{
		ImGui_Object_Data();
	}

}

// *************************************************************************
// *					Tabs_Render_Groups  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::Tabs_Render_Groups(void)
{
	if (Show_FPS == 1)
	{
		ImGui_FPS();
	}

	if (Show_Model_Data == 1)
	{
		ImGui_Model_Data();
	}

	if (Show_App_Data == 1)
	{
		ImGui_App_Data();
	}

	if (Show_ImGui_TextureData == 1)
	{
		ImGui_Texture_Data();
	}

	if (Show_Group_List == 1)
	{
		ImGui_GroupList();
	}

	if (Show_Position == 1)
	{
		
	}

	if (Show_Object_Data == 1)
	{
		ImGui_Object_Data();
	}

}


// *************************************************************************
// *		Object_Selection:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void VM_ImGui::Object_Selection(void)
{
	ImGui::SetNextWindowPos(ImVec2(230, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Selection_Data", &Show_Object_Selection, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{

		ImGui::Text("Selected Object");
		ImGui::Separator();

		ImGui::Text("Internal Name: = %s",App->SBC_Ogre->OgreListener->Pl_Entity_Name.c_str());
		ImGui::Text("Object Name: = %s",App->SBC_Ogre->OgreListener->Selected_Object_Name);
		
		ImGui::Text("");

		ImGui::Text("Edit Selected Object");
		ImGui::Separator();

		ImGui::Indent();
		ImGui::Indent();
		ImGui::Indent();

		if (ImGui::Button("Yes"))
		{
			App->SBC_TopTabs->Toggle_Select_Flag = 0;
			App->SBC_Visuals->mPickSight->hide();
			App->SBC_Ogre->OgreListener->GD_Selection_Mode = 0;

			RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			//App->SBC_FileView->Select_Item(App->SBC_Ogre->OgreListener->Selected_Entity_Index);
			App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[App->SBC_Ogre->OgreListener->Selected_Entity_Index]->FileViewItem);
			Show_Object_Selection = 0;
		}

		ImGui::SameLine();

		if (ImGui::Button("No"))
		{
			App->SBC_TopTabs->Toggle_Select_Flag = 0;
			App->SBC_Visuals->mPickSight->hide();
			App->SBC_Ogre->OgreListener->GD_Selection_Mode = 0;

			RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			Show_Object_Selection = 0;
		}

		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_FPS  Terry Bernie						   *
// *************************************************************************
void VM_ImGui::ImGui_FPS(void)
{
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

		ImGui::Text("FPS average %.0f", ImGui::GetIO().Framerate);
		//ImGui::PopFont();

		ImGui::End();
	}
}

// *************************************************************************
// *					ImGui_Collision_Debug  Terry Flanigan			   *
// *************************************************************************
void VM_ImGui::ImGui_Collision_Debug(void)
{
	ImGui::SetNextWindowPos(ImVec2(530,50), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Collisions_Debug", &Show_Collision_Debug, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{

		ImGui::Spacing();

		ImGui::Text("Manifolds %i", App->SBC_Player->Col_numManifolds);
		ImGui::Text("PlayerIndex %i", App->SBC_Player->Col_Player_Index);
		ImGui::Text("Object_ID %i", App->SBC_Player->Col_Object_Index);
		ImGui::Text("Usage %i", App->SBC_Player->Col_Usage_Index);

		ImGui::Text(" ");

		ImGui::Text("Round %i", App->SBC_Player->Round);
		ImGui::Text("Distance %i", App->SBC_Player->Distance);
		ImGui::Text("Life_Time %i", App->SBC_Player->Life_Time);

		if (ImGui::Button("Close"))
		{
			Show_Collision_Debug = 0;
		}

		ImGui::End();
	}
}

// *************************************************************************
// *					ImGui_ProgressBar  Terry Bernie					   *
// *************************************************************************
void VM_ImGui::ImGui_ProgressBar(void)
{
	if (!ImGui::Begin("ProgressBar1", &Show_Progress_Bar, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		if (StartPos_PB == 0)
		{
			ImGui::SetWindowPos("ProgressBar1", ImVec2(400, 250));
			ImGui::SetWindowSize(ImVec2(350, 90));
			StartPos_PB = 1;
		}

		//progress = 0.0f,
		//progress += 0.0001;

		float progress_saturated = (progress < 0.0f) ? 0.0f : (progress > 1.0f) ? 1.0f : progress;

		char buf[32];
		sprintf(buf, "%d/%d", (int)(progress_saturated * Progress_Count), (int)Progress_Count);
		ImGui::ProgressBar(progress, ImVec2(0.f, 0.f), buf);

		ImGui::End();
	}
}

// *************************************************************************
// *					Start_ProgressBar  Terry Bernie					   *
// *************************************************************************
void VM_ImGui::Start_ProgressBar(void)
{
	StartPos_PB = 0;
	Show_Progress_Bar = 1;
}

// *************************************************************************
// *					Stop_ProgressBar  Terry Bernie					   *
// *************************************************************************
void VM_ImGui::Stop_ProgressBar(void)
{
	StartPos_PB = 0;
	progress = 0.0f,
	Show_Progress_Bar = 0;
}

// *************************************************************************
// *					Set_ProgressCount  Terry Bernie					   *
// *************************************************************************
void VM_ImGui::Set_ProgressCount(float Count)
{
	Progress_Count = Count;
	Progress_Delta = 1 / Count;
}

// *************************************************************************
// *								Nudge 								   *
// *************************************************************************
bool VM_ImGui::Nudge()
{
	progress += Progress_Delta;

	Ogre::Root::getSingletonPtr()->renderOneFrame();

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}

// *************************************************************************
// *						ImGui_Image  Terry Bernie					   *
// *************************************************************************
void VM_ImGui::ImGui_Image(void)
{
	
}

// *************************************************************************
// *						ImGui_GroupList  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::ImGui_GroupList(void)
{
	
}

// *************************************************************************
// *						ImGui_MotionList  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::ImGui_MotionList(void)
{
	
}

// *************************************************************************
// *					ImGui_Texture_Data  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::ImGui_Texture_Data(void)
{
	ImGui::SetNextWindowSize(ImVec2(530, 250), ImGuiCond_FirstUseEver);

	ImGui::OpenPopup("Texture Data");

	if (!ImGui::BeginPopupModal("Texture Data", &Show_ImGui_TextureData, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::EndPopup();
	}
	else
	{

		//ImGui::SetWindowPos(ImVec2(400, 40));
		//ImGui::SetWindowSize(ImVec2(350, 90));

		if (ImGui::Button("Close"))
		{
			Show_ImGui_TextureData = 0;
		}

		ImGui::EndPopup();
	}
}

// *************************************************************************
// *					ImGui_Model_Data  Terry Bernie					   *
// *************************************************************************
void VM_ImGui::ImGui_Model_Data(void)
{
	ImGui::SetNextWindowSize(ImVec2(530, 250), ImGuiCond_FirstUseEver);

	ImGui::OpenPopup("Level Data");

	if (!ImGui::BeginPopupModal("Level Data", &Show_Model_Data, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::EndPopup();
	}
	else
	{

		ImGui::Text("Level Name: = %s", App->SBC_Project->m_Level_File_Name);
		ImGui::Text("Level File Name: = %s", App->SBC_Project->m_Level_File_Name);
		ImGui::Text("Level Path: = %s", App->SBC_Project->m_Project_Sub_Folder);
		ImGui::Text("Asset Path: = %s", App->SBC_Project->m_Main_Assets_Path);

		ImGui::Spacing();

		// ----------------------------- Players
		char Header[255];
		int PlayerCount = App->SBC_Scene->Player_Count;
		sprintf(Header, "%s %i", "Playes", PlayerCount);

		if (ImGui::CollapsingHeader(Header))
		{
			int Count = 0;
			while (Count < App->SBC_Scene->Player_Count)
			{
				ImGui::Text("%s", App->SBC_Scene->B_Player[0]->Player_Name);
				Count++;
			}
		}

		ImGui::Spacing();

		// ----------------------------- App
		sprintf(Header, "%s", "App");

		if (ImGui::CollapsingHeader(Header))
		{
			ImGui::Text("%s %i", "Camera Count = ", App->SBC_Scene->Camera_Count);
			ImGui::Text("%s %i", "Player Count = ", App->SBC_Scene->Player_Count);
			ImGui::Text("%s %i", "Area Count = ", App->SBC_Scene->Area_Count);
			ImGui::Text("%s %i", "Area Added = ", App->SBC_Scene->Area_Added);
			ImGui::Text("%s %i", "Object Count = ", App->SBC_Scene->Object_Count);

			ImGui::Text("%s %i", "Project Loaded = ", App->SBC_Project->Project_Loaded);
			ImGui::Text("%s %i", "Level Loaded = ",App->SBC_Scene->Scene_Loaded);
			ImGui::Text("%s %i", "Player Added = ", App->SBC_Scene->Player_Added);

			ImGui::Text("%s %i", "Physics Running = ", App->SBC_Ogre->OgreListener->GD_Run_Physics);
			ImGui::Text("%s %i", "Physics Debuging = ", App->SBC_Ogre->OgreListener->Dubug_Physics_Draw);

		}

		//ImGui::Spacing();

		//// ----------------------------- Bones
		//int BoneCount = App->CL_Vm_Model->BoneCount;
		//sprintf(Header, "%s %i", "Bones", BoneCount);

		//if (ImGui::CollapsingHeader(Header))
		//{
		//	int Count = 0;
		//	while (Count < BoneCount)
		//	{
		//		ImGui::Text("%s", App->CL_Vm_Model->S_Bones[Count]->BoneName);
		//		Count++;
		//	}
		//}

		//// ----------------------------- Groups
		//int GroupCount = App->CL_Vm_Model->GroupCount;
		//sprintf(Header, "%s %i", "Groups", GroupCount);

		//if (ImGui::CollapsingHeader(Header))
		//{
		//	/*int Count = 0;
		//	while (Count < BoneCount)
		//	{
		//	ImGui::Text("%s", App->CL_Vm_Model->S_Bones[Count]->BoneName);
		//	Count++;
		//	}*/
		//}
		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Button("Close"))
		{
			Show_Model_Data = 0;
		}

		ImGui::EndPopup();
	}
}

// *************************************************************************
// *					ImGui_App_Data  Terry Bernie					   *
// *************************************************************************
void VM_ImGui::ImGui_App_Data(void)
{
	ImGui::SetNextWindowSize(ImVec2(530, 250), ImGuiCond_FirstUseEver);

	//ImGui::OpenPopup("Level Data");

	if (!ImGui::Begin("App Data", &Show_App_Data, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::EndPopup();
	}
	else
	{
		char Header[255];
		// ----------------------------- Project
		
		//ImGui::Text("Project Folder Location: = %s", App->SBC_Project->);
		
		
		ImGui::Spacing();

		// ----------------------------- Scene
		sprintf(Header, "%s", "Scene");

		if (ImGui::CollapsingHeader(Header))
		{
			ImGui::Text("%s %i", "Project Loaded = ", App->SBC_Project->Project_Loaded);
			ImGui::Text("%s %i", "Scene Loaded = ", App->SBC_Scene->Scene_Loaded);

			ImGui::Text("%s %i", "Player Added = ", App->SBC_Scene->Player_Added);
			ImGui::Text("%s %i", "Player Count = ", App->SBC_Scene->Player_Count);

			ImGui::Text("%s %i", "Aera Added = ", App->SBC_Scene->Player_Added);
			ImGui::Text("%s %i", "Aera Count = ", App->SBC_Scene->Area_Count);

			ImGui::Text("%s %i", "Camera Added = ", App->SBC_Scene->Camera_Added);
			ImGui::Text("%s %i", "Camera Count = ", App->SBC_Scene->Camera_Count);

			ImGui::Text("%s %i", "Objects Added = ", App->SBC_Scene->Objects_Added);
			ImGui::Text("%s %i", "Objects Count = ", App->SBC_Scene->Object_Count);

			ImGui::Text("%s %i", "Physics Running = ", App->SBC_Ogre->OgreListener->GD_Run_Physics);
			ImGui::Text("%s %i", "Physics Debuging = ", App->SBC_Ogre->OgreListener->Dubug_Physics_Draw);

		}

		// ----------------------------- Players

		int PlayerCount = App->SBC_Scene->Player_Count;
		sprintf(Header, "%s %i", "Players", PlayerCount);

		if (ImGui::CollapsingHeader(Header))
		{
			int Count = 0;
			while (Count < App->SBC_Scene->Player_Count)
			{
				ImGui::Text("%s", App->SBC_Scene->B_Player[0]->Player_Name);
				Count++;
			}
		}

		ImGui::Spacing();

		// ----------------------------- Camera
		sprintf(Header, "%s", "Camera");
		if (ImGui::CollapsingHeader(Header))
		{
			ImGui::Text("%s %f", "Pos_X = ", App->SBC_Ogre->mCamera->getPosition().x);
			ImGui::Text("%s %f", "Pos_Y = ", App->SBC_Ogre->mCamera->getPosition().y);
			ImGui::Text("%s %f", "Pos_Z = ", App->SBC_Ogre->mCamera->getPosition().z);

			ImGui::Text("%s %f", "Rot_X = ", App->SBC_Ogre->mCamera->getOrientation().x);
			ImGui::Text("%s %f", "Rot_Y = ", App->SBC_Ogre->mCamera->getOrientation().y);
			ImGui::Text("%s %f", "Rot_Z = ", App->SBC_Ogre->mCamera->getOrientation().z);
		}

		ImGui::Spacing();

		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Button("Close"))
		{
			Show_App_Data = 0;
		}

		ImGui::End();
	}
}

// *************************************************************************
// *					ImGui_Object_Data  Terry Bernie					   *
// *************************************************************************
void VM_ImGui::ImGui_Object_Data(void)
{
	ImGui::SetNextWindowSize(ImVec2(530, 150), ImGuiCond_FirstUseEver);

	ImGui::OpenPopup("Object Data");

	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;
	
	if (!ImGui::BeginPopupModal("Object Data", &Show_Object_Data, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::EndPopup();
	}
	else
	{
		int Index = App->SBC_Properties->Current_Selected_Object;
		/*ImGuiIO& io = ImGui::GetIO();
		ImFont* font = io.Fonts->Fonts[0];
		ImGui::PushID((void*)font);
		io.FontDefault = font;
		ImGui::PopID();*/

		ImGui::Text("Name: = %s", App->SBC_Scene->B_Object[Index]->Mesh_Name);
		ImGui::Text("Mesh File Name: = %s", App->SBC_Scene->B_Object[Index]->Mesh_FileName);
		ImGui::Text("Path: = %s", App->SBC_Scene->B_Object[Index]->Mesh_Resource_Path);
		ImGui::Text("Type: = %s", App->SBC_LookUps->Chr_Type);
		ImGui::Text("Shape: = %s", App->SBC_LookUps->Chr_Shape);
		ImGui::Text("Usage: = %s", App->SBC_LookUps->Chr_Usage);
		ImGui::Text("Object_ID: = %i", App->SBC_Scene->B_Object[Index]->This_Object_UniqueID);

		ImGui::Spacing();
		
		/*x = App->SBC_Scene->B_Object[Index]->Mesh_Pos.x;
		y = App->SBC_Scene->B_Object[Index]->Mesh_Pos.y;
		z = App->SBC_Scene->B_Object[Index]->Mesh_Pos.z;
		ImGui::Text("Mesh_Pos: = %f,%f,%f", x, y, z);
		
		x = App->SBC_Scene->B_Object[Index]->Mesh_Scale.x;
		y = App->SBC_Scene->B_Object[Index]->Mesh_Scale.y;
		z = App->SBC_Scene->B_Object[Index]->Mesh_Scale.z;
		ImGui::Text("Mesh_Scale: = %f,%f,%f", x, y, z);

		w = App->SBC_Scene->B_Object[Index]->Mesh_Quat.w;
		x = App->SBC_Scene->B_Object[Index]->Mesh_Quat.x;
		y = App->SBC_Scene->B_Object[Index]->Mesh_Quat.y;
		z = App->SBC_Scene->B_Object[Index]->Mesh_Quat.z;
		ImGui::Text("Mesh_Quat: = %f,%f,%f,%f", w, x, y, z);*/

		// Collectables
		if (App->SBC_Properties->Edit_Category == Enums::Edit_Collectable)
		{
			ImGui::Text("------------ Collectable");
			ImGui::Text("Sound_File: = %s", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Sound_File);
			ImGui::Text("Sound_Volume: = %f", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->SndVolume);
			ImGui::Text("Sound_Play: = %i", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Play);

			ImGui::Text("Counter_Name: = %s", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_Name);
			ImGui::Text("Counter_ID: = %i", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_ID);
			ImGui::Text("Counter_Value: = %i", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Value);
			ImGui::Text("Counter_Maths: = %i", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths);
			ImGui::Text("Counter_Disabled: = %i", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_Disabled);

			return;
		}

		// Move Entity
		if (App->SBC_Properties->Edit_Category == Enums::Edit_Move_Entity)
		{
			ImGui::Text("------------ Move Entity");
			//ImGui::Text("Sound_File: = %s", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Sound_File);
			//ImGui::Text("Sound_Volume: = %f", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->SndVolume);
			//ImGui::Text("Sound_Play: = %i", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Play);

			//ImGui::Text("Counter_Name: = %s", App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Object_To_Move_Index);
		
			//ImGui::Text("Counter_Name: = %s", App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Counter_Name);
			//ImGui::Text("Counter_ID: = %i", App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Counter_ID);
			//ImGui::Text("Counter_Value: = %i", App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Trigger_Value);
			////ImGui::Text("Counter_Maths: = %i", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths);
			//ImGui::Text("Counter_Disabled: = %i", App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Counter_Disabled);

			return;
		}



		/*ImGui::Text("Physics_Mass: = %f", App->SBC_Scene->B_Object[Index]->Physics_Mass);
		ImGui::Text("Physics_Restitution: = %f", App->SBC_Scene->B_Object[Index]->Physics_Restitution);

		x = App->SBC_Scene->B_Object[Index]->Physics_Pos.x;
		y = App->SBC_Scene->B_Object[Index]->Physics_Pos.y;
		z = App->SBC_Scene->B_Object[Index]->Physics_Pos.z;
		ImGui::Text("Physics_Pos: = %f,%f,%f", x, y, z);

		x = App->SBC_Scene->B_Object[Index]->Physics_Scale.x;
		y = App->SBC_Scene->B_Object[Index]->Physics_Scale.y;
		z = App->SBC_Scene->B_Object[Index]->Physics_Scale.z;
		ImGui::Text("Physics_Scale: = %f,%f,%f", x, y, z);

		w = App->SBC_Scene->B_Object[Index]->Physics_Quat.w;
		x = App->SBC_Scene->B_Object[Index]->Physics_Quat.x;
		y = App->SBC_Scene->B_Object[Index]->Physics_Quat.y;
		z = App->SBC_Scene->B_Object[Index]->Physics_Quat.z;
		ImGui::Text("Physics_Quat: = %f,%f,%f,%f", w, x, y, z);*/

		if (ImGui::Button("Close"))
		{
			Show_Object_Data = 0;
		}

		ImGui::EndPopup();
	}
}


//x = App->SBC_Scene->B_Object[Index]->Object_Node->getPosition().x;
//y = App->SBC_Scene->B_Object[Index]->Object_Node->getPosition().y;
//z = App->SBC_Scene->B_Object[Index]->Object_Node->getPosition().z;
//ImGui::Text("Mesh_Pos: = %f,%f,%f", x, y, z);
//
//x = App->SBC_Scene->B_Object[Index]->Object_Node->getScale().x;
//y = App->SBC_Scene->B_Object[Index]->Object_Node->getScale().y;
//z = App->SBC_Scene->B_Object[Index]->Object_Node->getScale().z;
//ImGui::Text("Mesh_Scale: = %f,%f,%f", x, y, z);
//
//w = App->SBC_Scene->B_Object[Index]->Mesh_Quat.w;
//x = App->SBC_Scene->B_Object[Index]->Mesh_Quat.x;
//y = App->SBC_Scene->B_Object[Index]->Mesh_Quat.y;
//z = App->SBC_Scene->B_Object[Index]->Mesh_Quat.z;
//ImGui::Text("Mesh_Quat: = %f,%f,%f,%f", w, x, y, z);
//
//ImGui::Spacing();
//ImGui::Spacing();
//
//ImGui::Text("Physics_Mass: = %f", App->SBC_Scene->B_Object[Index]->Physics_Mass);
//ImGui::Text("Physics_Restitution: = %f", App->SBC_Scene->B_Object[Index]->Physics_Restitution);
//
//x = App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().getOrigin().getX();
//y = App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().getOrigin().getY();
//z = App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().getOrigin().getZ();
//ImGui::Text("Physics_Pos: = %f,%f,%f", x, y, z);
//
//x = App->SBC_Scene->B_Object[Index]->Phys_Body->getCollisionShape()->getLocalScaling().getX();
//y = App->SBC_Scene->B_Object[Index]->Phys_Body->getCollisionShape()->getLocalScaling().getY();
//z = App->SBC_Scene->B_Object[Index]->Phys_Body->getCollisionShape()->getLocalScaling().getZ();
//ImGui::Text("Physics_Scale: = %f,%f,%f", x, y, z);
//
//w = App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().getRotation().getW();
//x = App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().getRotation().getX();
//y = App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().getRotation().getY();;
//z = App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().getRotation().getZ();;
//ImGui::Text("Physics_Quat: = %f,%f,%f,%f", w, x, y, z);
