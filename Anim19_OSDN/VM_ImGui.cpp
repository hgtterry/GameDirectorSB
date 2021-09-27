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
	Show_Progress_Bar = 0;

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

	if (Show_ImGui_Test == 1)
	{
		ImGui::ShowDemoWindow();
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

	if (Show_Motion_List == 1)
	{
		ImGui_MotionList();
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

	if (Show_Rotation == 1)
	{
		ImGui_Rotation2();
	}

	if (Show_Position == 1)
	{
		ImGui_Position();
	}

	if (Show_Scale == 1)
	{
		ImGui_Scale();
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

	if (Show_ImGui_TextureData == 1)
	{
		ImGui_Texture_Data();
	}

	if (Show_Group_List == 1)
	{
		ImGui_GroupList();
	}

}

// *************************************************************************
// *						ImGui_FPS  Terry Bernie						   *
// *************************************************************************
void VM_ImGui::ImGui_FPS(void)
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
// *						ImGui_Rotation2  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::ImGui_Rotation2(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Rotation2", &Show_Rotation, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Text("Rotation");
		ImGui::Separator();
		ImGui::Spacing();

		geVec3d pos = App->CL_Vm_Genesis3D->Actor_Rotation;
		ImGui::Text("X %.3f Y %.3f Z %.3f", pos.X, pos.Y, pos.Z);

		ImGui::Spacing();

		// ------------------------------------------ Rotation X
		ImGui::Text("X ");
		ImGui::SameLine();

		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##left", ImGuiDir_Left))
		{
			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Rotation.X += App->Cl_Vm_Dimensions->Model_X_Rotation;
				App->CL_Vm_Genesis3D->MoveActor();
			}

			if (App->CL_Vm_Model->Model_Type == LoadedFile_Assimp)
			{
				App->Cl_Vm_Dimensions->Rotate_X_Model(App->Cl_Vm_Dimensions->Model_X_Rotation);
			}
		}

		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right))
		{
			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Rotation.X -= App->Cl_Vm_Dimensions->Model_X_Rotation;
				App->CL_Vm_Genesis3D->MoveActor();
			}

			if (App->CL_Vm_Model->Model_Type == LoadedFile_Assimp)
			{
				App->Cl_Vm_Dimensions->Rotate_X_Model(-App->Cl_Vm_Dimensions->Model_X_Rotation);
			}
		}
		ImGui::PopButtonRepeat();

		//------------------------------------------------------------------------------
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsX[] = { "0.5", "1", "10", "45", "90", "180" };
		static int XitemX = 4;
		bool Changed = ImGui::Combo("Step X", &XitemX, XitemsX, IM_ARRAYSIZE(XitemsX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (Changed == 1)
		{
			App->Cl_Vm_Dimensions->Model_X_Rotation = (float)atof(XitemsX[XitemX]);
		}

		// ------------------------------------------ Rotation y
		ImGui::Text("Y ");
		ImGui::SameLine();

		float spacing2 = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftY", ImGuiDir_Left))
		{
			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Rotation.Y += App->Cl_Vm_Dimensions->Model_Y_Rotation;
				App->CL_Vm_Genesis3D->MoveActor();
			}

			if (App->CL_Vm_Model->Model_Type == LoadedFile_Assimp)
			{
				App->Cl_Vm_Dimensions->Rotate_Y_Model(App->Cl_Vm_Dimensions->Model_Y_Rotation);
			}
		}
		ImGui::SameLine(0.0f, spacing2);
		if (ImGui::ArrowButton("##rightY", ImGuiDir_Right))
		{
			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Rotation.Y -= App->Cl_Vm_Dimensions->Model_Y_Rotation;
				App->CL_Vm_Genesis3D->MoveActor();
			}

			if (App->CL_Vm_Model->Model_Type == LoadedFile_Assimp)
			{
				App->Cl_Vm_Dimensions->Rotate_Y_Model(-App->Cl_Vm_Dimensions->Model_Y_Rotation);
			}
		}
		ImGui::PopButtonRepeat();

		//------------------------------------------------------------------------------
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsY[] = { "0.5", "1", "10", "45", "90", "180" };
		static int XitemY = 4;
		bool ChangedY = ImGui::Combo("Step Y", &XitemY, XitemsY, IM_ARRAYSIZE(XitemsY));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedY == 1)
		{
			App->Cl_Vm_Dimensions->Model_Y_Rotation = (float)atof(XitemsY[XitemY]);
		}

		// ------------------------------------------ Rotation z
		ImGui::Text("Z ");
		ImGui::SameLine();

		float spacing3 = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftZ", ImGuiDir_Left))
		{
			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Rotation.Z += App->Cl_Vm_Dimensions->Model_Z_Rotation;
				App->CL_Vm_Genesis3D->MoveActor();
			}

			if (App->CL_Vm_Model->Model_Type == LoadedFile_Assimp)
			{
				App->Cl_Vm_Dimensions->Rotate_Z_Model(App->Cl_Vm_Dimensions->Model_Z_Rotation);
			}
		}
		ImGui::SameLine(0.0f, spacing3);
		if (ImGui::ArrowButton("##rightZ", ImGuiDir_Right))
		{
			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Rotation.Z -= App->Cl_Vm_Dimensions->Model_Z_Rotation;
				App->CL_Vm_Genesis3D->MoveActor();
			}

			if (App->CL_Vm_Model->Model_Type == LoadedFile_Assimp)
			{
				App->Cl_Vm_Dimensions->Rotate_Z_Model(-App->Cl_Vm_Dimensions->Model_Z_Rotation);
			}
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsZ[] = { "0.5", "1", "10", "45", "90", "180" };
		static int XitemZ = 4;
		bool ChangedZ = ImGui::Combo("Step Z", &XitemZ, XitemsZ, IM_ARRAYSIZE(XitemsZ));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedZ == 1)
		{
			App->Cl_Vm_Dimensions->Model_Z_Rotation = (float)atof(XitemsZ[XitemZ]);
		}

		// ----------------------------- 
		/*ImGui::Spacing();
		ImGui::Indent();
		if (ImGui::Button("Middle of Bounding Box", ImVec2(200, 40)))
		{
			App->Cl_Vm_Dimensions->Centre_Model_Mid();
		}

		if (ImGui::Button("Base of Bounding Box", ImVec2(200, 40)))
		{
			App->Cl_Vm_Dimensions->Centre_Model_Base();
		}*/

		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Position  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::ImGui_Position(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Position", &Show_Position, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Text("Position");
		ImGui::Separator();
		ImGui::Spacing();

		geVec3d pos = App->CL_Vm_Genesis3D->Actor_Position;
		ImGui::Text("X %.3f Y %.3f Z %.3f", pos.X, pos.Y, pos.Z);
	
		ImGui::Spacing();

		// ------------------------------------------ Position X
		ImGui::Text("X ");
		ImGui::SameLine();

		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##left", ImGuiDir_Left))
		{
			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Position.X += Model_XTranslate;
				App->CL_Vm_Genesis3D->MoveActor();
			}
		}

		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right))
		{
			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Position.X -= Model_XTranslate;
				App->CL_Vm_Genesis3D->MoveActor();
			}
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsX[] = { "1", "2", "5", "10", "20" };
		static int XitemX = 1;
		bool Changed = ImGui::Combo("Step X", &XitemX, XitemsX, IM_ARRAYSIZE(XitemsX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (Changed == 1)
		{
			Model_XTranslate = (float)atof(XitemsX[XitemX]);
		}

		// ------------------------------------------ Position y
		ImGui::Text("Y ");
		ImGui::SameLine();

		float spacing2 = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftY", ImGuiDir_Left))
		{
			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Position.Y += Model_YTranslate;
				App->CL_Vm_Genesis3D->MoveActor();
			}
		}
		ImGui::SameLine(0.0f, spacing2);
		if (ImGui::ArrowButton("##rightY", ImGuiDir_Right))
		{
			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Position.Y -= Model_YTranslate;
				App->CL_Vm_Genesis3D->MoveActor();
			}
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsY[] = { "1", "2", "5", "10", "20" };
		static int XitemY = 1;
		bool ChangedY = ImGui::Combo("Step Y", &XitemY, XitemsY, IM_ARRAYSIZE(XitemsY));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedY == 1)
		{
			Model_YTranslate = (float)atof(XitemsY[XitemY]);
		}

		// ------------------------------------------ Position z
		ImGui::Text("Z ");
		ImGui::SameLine();

		float spacing3 = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##leftZ", ImGuiDir_Left))
		{
			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Position.Z += Model_ZTranslate;
				App->CL_Vm_Genesis3D->MoveActor();
			}
		}
		ImGui::SameLine(0.0f, spacing3);
		if (ImGui::ArrowButton("##rightZ", ImGuiDir_Right))
		{
			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->Actor_Position.Z -= Model_ZTranslate;
				App->CL_Vm_Genesis3D->MoveActor();
			}
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsZ[] = { "1", "2", "5", "10", "20" };
		static int XitemZ = 1;
		bool ChangedZ = ImGui::Combo("Step Z", &XitemZ, XitemsZ, IM_ARRAYSIZE(XitemsZ));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (ChangedZ == 1)
		{
			Model_ZTranslate = (float)atof(XitemsZ[XitemZ]);
		}
	
		ImGui::Spacing();
		ImGui::Indent();
		if (ImGui::Button("Middle of Bounding Box",ImVec2(200,40)))
		{
			App->Cl_Vm_Dimensions->Centre_Model_Mid();
		}

		if (ImGui::Button("Base of Bounding Box", ImVec2(200, 40)))
		{
			App->Cl_Vm_Dimensions->Centre_Model_Base();
		}

		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Scale  Terry Bernie					   *
// *************************************************************************
void VM_ImGui::ImGui_Scale(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Scale", &Show_Scale , ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Text("Scale");
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::SameLine();
		ImGui::Checkbox("Lock Axis", &App->Cl_Dimensions->Set_ScaleLock);
		if (App->Cl_Dimensions->Set_ScaleLock == 1)
		{
			/*Ogre::Vector3 scale = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getScale();
			ImGui::Text("X %.3f Y %.3f Z %.3f", scale.x, scale.y, scale.z);*/
			ImGui::Spacing();

			ImGui::Text("All ");
			ImGui::SameLine();

			float spacingSX = ImGui::GetStyle().ItemInnerSpacing.x;
			ImGui::PushButtonRepeat(true);
			if (ImGui::ArrowButton("##LeftSX", ImGuiDir_Left))
			{
				float Delta = 0.5;// App->Cl_Dimensions->Model_XScale;

				if (App->CL_Vm_Model->Model_Loaded == 1)
				{
					App->CL_Vm_Genesis3D->ScaleActor(Delta, Delta, Delta);
					//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
					//Scale.x += Delta;
					//Scale.y += Delta;
					//Scale.z += Delta;
					//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
					//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

					//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
					//Scale.x += Delta;
					//Scale.y += Delta;
					//Scale.z += Delta;
					//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
					//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					////App->Cl_Dimensions->Set_Physics_Position(index);
					//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
				}
			}
			ImGui::SameLine(0.0f, spacingSX);
			if (ImGui::ArrowButton("##rightSX", ImGuiDir_Right))
			{
				float Delta = 1;// App->Cl_Dimensions->Model_XScale;

				if (App->CL_Vm_Model->Model_Loaded == 1)
				{
					App->CL_Vm_Genesis3D->ScaleActor(Delta, Delta, Delta);
					//Scale.x -= Delta;
					//Scale.y -= Delta;
					//Scale.z -= Delta;
					//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
					//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

					//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
					//Scale.x -= Delta;
					//Scale.y -= Delta;
					//Scale.z -= Delta;
					//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
					//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

					////App->Cl_Dimensions->Set_Physics_Position(index);
					//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
				}
			}
			ImGui::PopButtonRepeat();
		}
		else
		{
			/*Ogre::Vector3 scale = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getScale();
			ImGui::Text("X %.3f Y %.3f Z %.3f", scale.x, scale.y, scale.z);*/
			ImGui::Spacing();

			// Scale X
			ImGui::Text("X ");
			ImGui::SameLine();

			if (ImGui::Button("SX + "))
			{
				//float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.x += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.x += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				//App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}

			ImGui::SameLine();

			if (ImGui::Button("SX - "))
			{
				//float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.x -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.x -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				//App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);

			}

			// Scale Y
			ImGui::Text("Y ");
			ImGui::SameLine();

			if (ImGui::Button("SY + "))
			{
				//float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.y += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.y += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				//App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}

			ImGui::SameLine();

			if (ImGui::Button("SY - "))
			{
				//float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.y -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.y -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				//App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}

			// Scale Z
			ImGui::Text("Z ");
			ImGui::SameLine();

			if (ImGui::Button("SZ + "))
			{
				//float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.z += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.z += Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				//App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}

			ImGui::SameLine();

			if (ImGui::Button("SZ - "))
			{
				//float Delta = 0.2;// App->Cl_Dimensions->Model_XScale;
				//Ogre::Vector3 Scale = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale;
				//Scale.z -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setScale(Scale);

				//Scale = App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale;
				//Scale.z -= Delta;
				//App->Cl_Scene_Data->Cl_Object[index]->Physics_Scale = Scale;
				//App->Cl_Scene_Data->Cl_Object[index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

				//App->Cl_Dimensions->Set_Physics_Position(index);
				//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
			}
		}
		ImGui::End();
	}
}


// *************************************************************************
// *						ImGui_Image  Terry Bernie					   *
// *************************************************************************
void VM_ImGui::ImGui_Image(void)
{
	//ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Image", &Show_Image, ImGuiWindowFlags_NoSavedSettings))
	{
		ImGui::End();
	}
	else
	{
		if (App->CL_Vm_Textures->g_Texture[0] == NULL)
		{

		}
		else
		{
			
			/*int MatIndex = App->CL_Vm_Model->MatIndex_Data[0];
			glBindTexture(GL_TEXTURE_2D, App->CL_Vm_Textures->g_Texture[MatIndex]);

			ImGui::Text("pointer = %p", App->CL_Vm_Textures->g_Texture[MatIndex]);
			ImGui::Text("size = %d x %d", 256, 256);
			ImGui::Image((void*)(intptr_t)App->CL_Vm_Textures->g_Texture[MatIndex], ImVec2(256.0f, 256.0f));
			ImGui::End();*/
		}
	}
}

// *************************************************************************
// *						ImGui_GroupList  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::ImGui_GroupList(void)
{
	static int selected_Players = 0;

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Groups", &Show_Group_List, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		int GroupCount = App->CL_Vm_Model->GroupCount;
		ImGui::Text("Group Count %i", GroupCount);

		ImGui::Separator();
		ImGui::Spacing();

		int Count = 0;
		while (Count < GroupCount)
		{
			ImGui::Bullet();
			if (ImGui::Selectable(App->CL_Vm_Model->S_MeshGroup[Count]->GroupName, selected_Players == Count))
			{
				selected_Players = Count;
				Block = 1;
			}

			Count++;
		}

		if (Block == 1)
		{
			App->CL_Vm_Groups->Update_Groups_Dialog(selected_Players);
			Block = 0;
		}

		if (Reset_Groups == 1)
		{
			selected_Players = 0;
			Reset_Groups = 0;
		}

		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_MotionList  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::ImGui_MotionList(void)
{
	static int selected_Motion = 0;

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Motions", &Show_Motion_List, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		int MotionCount = App->CL_Vm_Model->MotionCount;
		ImGui::Text("Motion Count %i", MotionCount);

		ImGui::Text("Time %f", App->CL_Vm_Motions->Current_EndTime);
		ImGui::Text("Current %f", App->CL_Vm_Genesis3D->m_CurrentPose);

		ImGui::Separator();
		ImGui::Spacing();

		int Count = 0;
		while (Count < MotionCount)
		{
			ImGui::Bullet();
			if (ImGui::Selectable(App->CL_Vm_Model->MotionNames_Data[Count].Name, selected_Motion == Count))
			{
				selected_Motion = Count;
				Block_Motion = 1;
			}

			Count++;
		}

		if (Block_Motion == 1)
		{
			char buff[255];
			strcpy(buff, App->CL_Vm_Model->MotionNames_Data[selected_Motion].Name);

			App->CL_Vm_Genesis3D->GetMotion(buff);

			strcpy(App->CL_Vm_Genesis3D->MotionName, buff);

			App->CL_Vm_Genesis3D->m_CurrentPose = 0;

			Block_Motion = 0;
		}

		ImGui::End();
	}
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



		ImGui::Text("Texture Name: = %s", App->CL_Vm_Model->S_TextureInfo[App->CL_Vm_Groups->SelectedGroup]->MaterialName);
		ImGui::Text("Mat Index: = %i", App->CL_Vm_Model->S_TextureInfo[App->CL_Vm_Groups->SelectedGroup]->ActorMaterialIndex);
		ImGui::Text("Has Bitmap: = %i", App->CL_Vm_Model->S_TextureInfo[App->CL_Vm_Groups->SelectedGroup]->HasGEBitmap);
		
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Text("Width: = %i", App->CL_Vm_Model->S_TextureInfo[App->CL_Vm_Groups->SelectedGroup]->GEWitdth);
		ImGui::Text("Height: = %i", App->CL_Vm_Model->S_TextureInfo[App->CL_Vm_Groups->SelectedGroup]->GEHeight);

		ImGui::Separator();
		ImGui::Spacing();

		ImGui::Text("Red: = %0.3f", App->CL_Vm_Model->S_TextureInfo[App->CL_Vm_Groups->SelectedGroup]->R);
		ImGui::Text("Green: = %0.3f", App->CL_Vm_Model->S_TextureInfo[App->CL_Vm_Groups->SelectedGroup]->G);
		ImGui::Text("Blue: = %0.3f", App->CL_Vm_Model->S_TextureInfo[App->CL_Vm_Groups->SelectedGroup]->B);
		
		App->CL_Vm_Textures->GetFormat(App->CL_Vm_Model->S_TextureInfo[App->CL_Vm_Groups->SelectedGroup]->GEFormat);
		ImGui::Text("Format: = %s", App->CL_Vm_Textures->GEFormatString);

		ImGui::Separator();
		ImGui::Spacing();

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

	ImGui::OpenPopup("Model Data");

	if (!ImGui::BeginPopupModal("Model Data", &Show_Model_Data, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::EndPopup();
	}
	else
	{

		ImGui::Text("Model Name: = %s", App->CL_Vm_Model->JustName);
		ImGui::Text("Model File Name: = %s", App->CL_Vm_Model->FileName);
		ImGui::Text("Model Path: = %s", App->CL_Vm_Model->Model_FolderPath);
		ImGui::Text("Texture Path: = %s", App->CL_Vm_Model->Texture_FolderPath);

		ImGui::Spacing();

		ImGui::Text("Vertices: = %i", App->CL_Vm_Model->VerticeCount);
		ImGui::Text("Faces: = %i", App->CL_Vm_Model->FaceCount);
		ImGui::Text("Normals: = %i", App->CL_Vm_Model->NormalsCount);
		ImGui::Text("UVs: = %i", App->CL_Vm_Model->UVCount);

		ImGui::Spacing();

		ImGui::Text("Textures: = %i", App->CL_Vm_Model->TextureCount);

		// ----------------------------- Textures
		char Header[255];
		int TextureCount = App->CL_Vm_Model->S_Texture[0]->UsedTextureCount;

		sprintf(Header, "%s %i", "Textures", TextureCount);

		if (ImGui::CollapsingHeader(Header))
		{
			int Count = 0;
			while (Count < App->CL_Vm_Model->S_Texture[0]->UsedTextureCount)
			{
				//ImGui::Text("%s", App->CL_Vm_Model->S_TextureInfo[Count]->Text_FileName);
				ImGui::Text("%s", App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName);
				Count++;
			}
		}

		

		ImGui::Spacing();

		// ----------------------------- Motions
		int MotionCount = App->CL_Vm_Model->MotionCount;
		sprintf(Header, "%s %i", "Motions", MotionCount);

		if (ImGui::CollapsingHeader(Header))
		{
			int Count = 0;
			while (Count < MotionCount)
			{
				ImGui::Text("%s", App->CL_Vm_Model->MotionNames_Data[Count].Name);
				Count++;
			}
		}

		ImGui::Spacing();

		// ----------------------------- Bones
		int BoneCount = App->CL_Vm_Model->BoneCount;
		sprintf(Header, "%s %i", "Bones", BoneCount);

		if (ImGui::CollapsingHeader(Header))
		{
			int Count = 0;
			while (Count < BoneCount)
			{
				ImGui::Text("%s", App->CL_Vm_Model->S_Bones[Count]->BoneName);
				Count++;
			}
		}

		// ----------------------------- Groups
		int GroupCount = App->CL_Vm_Model->GroupCount;
		sprintf(Header, "%s %i", "Groups", GroupCount);

		if (ImGui::CollapsingHeader(Header))
		{
			/*int Count = 0;
			while (Count < BoneCount)
			{
			ImGui::Text("%s", App->CL_Vm_Model->S_Bones[Count]->BoneName);
			Count++;
			}*/
		}


		if (ImGui::Button("Close"))
		{
			Show_Model_Data = 0;
		}

		ImGui::EndPopup();
	}
}
