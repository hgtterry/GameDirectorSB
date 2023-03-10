#include "stdafx.h"
#include "GD19_App.h"
#include "imgui.h"
#include "imgui_internal.h"
#include "VM_ImGui.h"


VM_ImGui::VM_ImGui()
{
	ImGui::CreateContext();
	ImGui_Set_Colours();
	Load_Font();

	StartPos = 0;
	StartPos_PB = 0;
	Show_FPS = 1;
	Show_ImGui_Test = 0;
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
	Show_Fire_Target = 0;

	Model_XTranslate = 2;
	Model_YTranslate = 2;
	Model_ZTranslate = 2;

	PosX = 500;
	PosY = 500;

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

	//float fontSize = 18.0f;// *2.0f;
	//font3 = io.Fonts->AddFontFromFileTTF("fonts/opensans/OpenSans-Bold.ttf", fontSize);

	//fontDroid = io.Fonts->AddFontFromFileTTF("DroidSans.ttf", 12);

	io.IniFilename = NULL;

	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
}

// *************************************************************************
// *	  				ImGui_Set_Colours Terry Bernie					   *
// *************************************************************************
void VM_ImGui::ImGui_Set_Colours(void)
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
// *					ImGui_Editor_Loop  Terry Flanigan				   *
// *************************************************************************
void VM_ImGui::ImGui_Editor_Loop(void)
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

	if (Show_Fire_Target == 1)
	{
		Fire_Target();
	}

	if (App->SBC_Gui_Environ->Show_PropertyEditor == 1)
	{
		App->SBC_Gui_Environ->Environ_PropertyEditor();
	}

	// SBC_Debug
	if (App->SBC_Debug->Show_Debug_Camera == 1)
	{
		App->SBC_Debug->ImGui_Debug_Camera();
	}

	if (App->SBC_Debug->Show_Debug_Project == 1)
	{
		App->SBC_Debug->ImGui_Debug_Project();
	}

	// SBC_Dimensions
	if (App->SBC_Dimensions->Show_Position == 1 || App->SBC_Dimensions->Show_Scale == 1 || App->SBC_Dimensions->Show_Rotation == 1)
	{
		App->SBC_Dimensions->Show_Dimensions = 1;
		App->SBC_Dimensions->ImGui_Dimensions();
	}
	else
	{
		App->SBC_Dimensions->Show_Dimensions = 0;
	}

	// SBC_Gui_Dialogs
	if (App->SBC_Gui_Dialogs->Show_Dialog_Float == 1)
	{
		App->SBC_Gui_Dialogs->Dialog_Float();
	}

	if (App->SBC_Gui_Dialogs->Show_Dialog_MessageEditor == 1)
	{
		App->SBC_Gui_Dialogs->Dialog_MessageEditor();
	}

	if (App->SBC_Gui_Dialogs->Show_ColourPicker == 1)
	{
		App->SBC_Gui_Dialogs->Dialog_Colour_Picker();
	}

	// SBC_Gui_Dialogs - Debug Player
	if (App->SBC_Gui_Dialogs->Show_Debug_Player == 1)
	{
		App->SBC_Gui_Dialogs->Debug_Player();
	}

	// SBC_Gui_Dialogs - Preferences
	if (App->CL_Prefs->Show_Preferences_GUI == 1)
	{
		App->CL_Prefs->Preferences_GUI();
	}

	// SBC_Gui_Dialogs - Physics Console
	if (App->SBC_Gui_Dialogs->Show_Physics_Console == 1)
	{
		App->SBC_Gui_Dialogs->Physics_Console_Gui();
	}

	// SBC_Gui_Dialogs - Light Editor
	if (App->SBC_Gui_Dialogs->Show_Light_Editor == 1)
	{
		App->SBC_Gui_Dialogs->Light_Property_Editor_Gui();
	}

	// SBC_Gui_Dialogs - Light Editor
	if (App->SBC_Materials->Show_Material_Editor == 1)
	{
		App->SBC_Materials->Material_Editor_Gui();
	}

	// SBC_Gui_Dialogs - Properties Panel
	if (App->SBC_Gui_Propreties->Show_Properties_Panel_Flag == 1)
	{
		App->SBC_Gui_Propreties->Properties_Panel_Gui();
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

		ImGui::Text("Internal Name: = %s",App->CL_Ogre->OgreListener->Pl_Entity_Name.c_str());
		ImGui::Text("Object Name: = %s",App->CL_Ogre->OgreListener->Selected_Object_Name);
		
		ImGui::Text("");

		ImGui::Text("Edit Selected Object");
		ImGui::Separator();

		ImGui::Indent();
		ImGui::Indent();
		ImGui::Indent();

		if (ImGui::Button("Yes"))
		{
			App->SBC_TopTabs->Toggle_Select_Flag = 0;
			App->SBC_Markers->mPickSight->hide();
			App->CL_Ogre->OgreListener->GD_Selection_Mode = 0;

			RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			//App->SBC_FileView->Select_Item(App->CL_Ogre->OgreListener->Selected_Entity_Index);
			App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[App->CL_Ogre->OgreListener->Selected_Entity_Index]->FileViewItem);
			Show_Object_Selection = 0;
		}

		ImGui::SameLine();

		if (ImGui::Button("No"))
		{
			App->SBC_TopTabs->Toggle_Select_Flag = 0;
			App->SBC_Markers->mPickSight->hide();
			App->CL_Ogre->OgreListener->GD_Selection_Mode = 0;

			RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			Show_Object_Selection = 0;
		}

		ImGui::End();
	}
}

// *************************************************************************
// *			Fire_Target:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void VM_ImGui::Fire_Target(void)
{
	ImGui::SetNextWindowPos(ImVec2(230, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Target_Data", &Show_Fire_Target, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{

		ImGui::Text("Target Data");
		ImGui::Separator();

		ImGui::Text("Internal Name: = %s", App->SBC_3DT->Pl_Entity_Name.c_str());
		ImGui::Text("Object Name: = %s", App->SBC_3DT->Selected_Object_Name);
		ImGui::Text("");
		ImGui::Text("Distance: = %f", App->SBC_3DT->DistanceToCollision);
		ImGui::Text("");
		ImGui::Text("Point_X: = %f", App->SBC_3DT->Point.x);
		ImGui::Text("Point_Y: = %f", App->SBC_3DT->Point.y);
		ImGui::Text("Point_Z: = %f", App->SBC_3DT->Point.z);
		
		ImGui::Separator();

		ImGui::Indent();
		ImGui::Indent();
		ImGui::Indent();

	
		if (ImGui::Button("Close"))
		{
			
			App->SBC_Markers->mPickSight->hide();
			Show_Fire_Target = 0;

		}

		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_FPS  Terry Bernie						   *
// *************************************************************************
void VM_ImGui::ImGui_FPS(void)
{
	ImGui::SetNextWindowPos(ImVec2(PosX, PosY));

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239,239, 239, 255));

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
		
		ImVec2 Size = ImGui::GetWindowSize();
		PosX = ((float)App->CL_Ogre->OgreListener->View_Width / 2) - (Size.x / 2);
		PosY = 10;

		ImGui::PopStyleColor();
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

			ImGui::Text("%s %i", "Physics Running = ", App->CL_Ogre->OgreListener->GD_Run_Physics);
			ImGui::Text("%s %i", "Physics Debuging = ", App->CL_Ogre->OgreListener->Dubug_Physics_Draw);

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

			ImGui::Text("%s %i", "Physics Running = ", App->CL_Ogre->OgreListener->GD_Run_Physics);
			ImGui::Text("%s %i", "Physics Debuging = ", App->CL_Ogre->OgreListener->Dubug_Physics_Draw);

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
			ImGui::Text("%s %f", "Pos_X = ", App->CL_Ogre->mCamera->getPosition().x);
			ImGui::Text("%s %f", "Pos_Y = ", App->CL_Ogre->mCamera->getPosition().y);
			ImGui::Text("%s %f", "Pos_Z = ", App->CL_Ogre->mCamera->getPosition().z);

			ImGui::Text("%s %f", "Rot_X = ", App->CL_Ogre->mCamera->getOrientation().x);
			ImGui::Text("%s %f", "Rot_Y = ", App->CL_Ogre->mCamera->getOrientation().y);
			ImGui::Text("%s %f", "Rot_Z = ", App->CL_Ogre->mCamera->getOrientation().z);
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

		if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
		{
			ImGui::Text("Name: = %s", App->SBC_Scene->B_Area[Index]->Area_Name);
			ImGui::Text("Mesh File Name: = %s", App->SBC_Scene->B_Area[Index]->Area_FileName);
			ImGui::Text("Path: = %s", App->SBC_Scene->B_Area[Index]->Area_Resource_Path);
			ImGui::Text("Type: = %s", App->SBC_LookUps->Chr_Type);
			ImGui::Text("Shape: = %s", App->SBC_LookUps->Chr_Shape);
			ImGui::Text("Usage: = %s", App->SBC_LookUps->Chr_Usage);
			ImGui::Text("Object_ID: = %i", App->SBC_Scene->B_Area[Index]->This_Object_UniqueID);
			ImGui::Text("CollisionFlags: = %i", App->SBC_Scene->B_Area[Index]->Phys_Body->getCollisionFlags());
		}
		else
		{
			ImGui::Text("Name: = %s", App->SBC_Scene->B_Object[Index]->Mesh_Name);
			ImGui::Text("Mesh File Name: = %s", App->SBC_Scene->B_Object[Index]->Mesh_FileName);
			ImGui::Text("Path: = %s", App->SBC_Scene->B_Object[Index]->Mesh_Resource_Path);
			ImGui::Text("Type: = %s", App->SBC_LookUps->Chr_Type);
			ImGui::Text("Shape: = %s", App->SBC_LookUps->Chr_Shape);
			ImGui::Text("Usage: = %s", App->SBC_LookUps->Chr_Usage);
			ImGui::Text("Object_ID: = %i", App->SBC_Scene->B_Object[Index]->This_Object_UniqueID);

			if (App->SBC_Scene->B_Object[Index]->Phys_Body)
			{
				ImGui::Text("CollisionFlags: = %i", App->SBC_Scene->B_Object[Index]->Phys_Body->getCollisionFlags());
			}
		}

		ImGui::Spacing();
		
		
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
