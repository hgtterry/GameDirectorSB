#include "stdafx.h"
#include "GD19_App.h"
#include "VM_ImGui.h"


VM_ImGui::VM_ImGui()
{
	StartPos = 0;
	Show_FPS = 1;
	Show_ImGui_Test = 0;
	Show_Rotation = 0;
	Show_Position = 0;

	Test = 180;
}


VM_ImGui::~VM_ImGui()
{
}

// *************************************************************************
// *					Render_ImGui  Terry Bernie						   *
// *************************************************************************
void VM_ImGui::Render_ImGui(void)
{

	if (Show_FPS == 1)
	{
		ImGui_FPS();
	}

	if (Show_ImGui_Test == 1)
	{
		ImGui::ShowDemoWindow();
	}

	if (Show_Rotation == 1)
	{
		ImGui_Rotation();
	}

	if (Show_Position == 1)
	{
		ImGui_Position();
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
		ImGui::Text("FPS average %.1f ms/frame (%.0f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//ImGui::PopFont();

		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Rotation  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::ImGui_Rotation(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Rotation", &Show_Rotation, ImGuiWindowFlags_NoSavedSettings |ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		
		ImGui::Text("  X    Y    Z");

		if (ImGui::Button("X+", ImVec2(70, 0)))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button("Y+", ImVec2(70, 0)))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button("Z+", ImVec2(70, 0)))
		{
		}
		
		ImGui::VSliderFloat("##RotationX", ImVec2(70, 260),  &App->CL_Vm_Genesis3D->Actor_Rotation.X, 0.0f, 360.0f, "%.2f\nDeg");
		ImGui::SameLine();
		ImGui::VSliderFloat("##RotationY", ImVec2(70, 260), &App->CL_Vm_Genesis3D->Actor_Rotation.Y, 0.0f, 360.0f, "%.2f\nDeg");
		ImGui::SameLine();
		ImGui::VSliderFloat("##RotationZ", ImVec2(70, 260), &App->CL_Vm_Genesis3D->Actor_Rotation.Z, 0.0f, 360.0f, "%.2f\nDeg");
		
		if (ImGui::Button("X-", ImVec2(70, 0)))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button("Y-", ImVec2(70, 0)))
		{
		}
		ImGui::SameLine();
		if (ImGui::Button("Z-", ImVec2(70, 0)))
		{
		}

		if (App->CL_Vm_Genesis3D->Actor_Rotation.X > App->CL_Vm_Genesis3D->Actor_Rotation_Old.X || App->CL_Vm_Genesis3D->Actor_Rotation.X < App->CL_Vm_Genesis3D->Actor_Rotation_Old.X)
		{
			App->CL_Vm_Genesis3D->MoveActor();
			App->CL_Vm_Genesis3D->Actor_Rotation_Old.X = App->CL_Vm_Genesis3D->Actor_Rotation.X;
		}

		if (App->CL_Vm_Genesis3D->Actor_Rotation.Y > App->CL_Vm_Genesis3D->Actor_Rotation_Old.Y || App->CL_Vm_Genesis3D->Actor_Rotation.Y < App->CL_Vm_Genesis3D->Actor_Rotation_Old.Y)
		{
			App->CL_Vm_Genesis3D->MoveActor();
			App->CL_Vm_Genesis3D->Actor_Rotation_Old.Y = App->CL_Vm_Genesis3D->Actor_Rotation.Y;
		}

		if (App->CL_Vm_Genesis3D->Actor_Rotation.Z > App->CL_Vm_Genesis3D->Actor_Rotation_Old.Z || App->CL_Vm_Genesis3D->Actor_Rotation.Z < App->CL_Vm_Genesis3D->Actor_Rotation_Old.Z)
		{
			App->CL_Vm_Genesis3D->MoveActor();
			App->CL_Vm_Genesis3D->Actor_Rotation_Old.Z = App->CL_Vm_Genesis3D->Actor_Rotation.Z;
		}
		
		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Position  Terry Bernie				   *
// *************************************************************************
void VM_ImGui::ImGui_Position(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Position", &Show_Position, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{

		/*Ogre::Vector3 pos = App->Cl_Scene_Data->Cl_Object[index]->OgreNode->getPosition();
		ImGui::Text("X %.3f Y %.3f Z %.3f", pos.x, pos.y, pos.z);*/
	
		ImGui::Spacing();

		// ------------------------------------------ Position X
		ImGui::Text("X ");
		ImGui::SameLine();

		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##left", ImGuiDir_Left))
		{
			//Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos;
			//Pos.x += App->Cl_Dimensions->Model_XTranslate;// Delta;
			//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos = Pos;
			//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setPosition(Pos);
			//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
		}
		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right))
		{
			//Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos;
			//Pos.x -= App->Cl_Dimensions->Model_XTranslate;// Delta;
			//App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos = Pos;
			//App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setPosition(Pos);
			////App->Cl_Dimensions->Select_Properties_Update();
			//App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
		}
		ImGui::PopButtonRepeat();

		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		const char* XitemsX[] = { "1", "2", "5", "10", "20" };
		static int XitemX = 1;
		bool Changed = ImGui::Combo("Step X", &XitemX, XitemsX, IM_ARRAYSIZE(XitemsX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		if (Changed == 1)
		{
			App->Cl_Dimensions->Model_XTranslate = (float)atof(XitemsX[XitemX]);
		}

		// ------------------------------------------ Position y
		//ImGui::Text("Y ");
		//ImGui::SameLine();

		//float spacing2 = ImGui::GetStyle().ItemInnerSpacing.x;
		//ImGui::PushButtonRepeat(true);
		//if (ImGui::ArrowButton("##leftY", ImGuiDir_Left))
		//{
		//	Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos;
		//	Pos.y += App->Cl_Dimensions->Model_YTranslate;// Delta;
		//	App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos = Pos;
		//	App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setPosition(Pos);
		//	App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
		//}
		//ImGui::SameLine(0.0f, spacing2);
		//if (ImGui::ArrowButton("##rightY", ImGuiDir_Right))
		//{
		//	Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos;
		//	Pos.y -= App->Cl_Dimensions->Model_YTranslate;// Delta;
		//	App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos = Pos;
		//	App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setPosition(Pos);
		//	
		//	App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
		//}
		//ImGui::PopButtonRepeat();

		//ImGui::SameLine();
		//ImGui::SetNextItemWidth(100);
		//const char* XitemsY[] = { "1", "2", "5", "10", "20" };
		//static int XitemY = 1;
		//bool ChangedY = ImGui::Combo("Step Y", &XitemY, XitemsY, IM_ARRAYSIZE(XitemsY));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		//if (ChangedY == 1)
		//{
		//	App->Cl_Dimensions->Model_YTranslate = (float)atof(XitemsY[XitemY]);
		//}

		//// ------------------------------------------ Position z
		//ImGui::Text("Z ");
		//ImGui::SameLine();

		//float spacing3 = ImGui::GetStyle().ItemInnerSpacing.x;
		//ImGui::PushButtonRepeat(true);
		//if (ImGui::ArrowButton("##leftZ", ImGuiDir_Left))
		//{
		//	Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos;
		//	Pos.z += App->Cl_Dimensions->Model_ZTranslate;// Delta;
		//	App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos = Pos;
		//	App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setPosition(Pos);
		//	App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
		//}
		//ImGui::SameLine(0.0f, spacing3);
		//if (ImGui::ArrowButton("##rightZ", ImGuiDir_Right))
		//{
		//	Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos;
		//	Pos.z -= App->Cl_Dimensions->Model_ZTranslate;// Delta;
		//	App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos = Pos;
		//	App->Cl_Scene_Data->Cl_Object[index]->OgreNode->setPosition(Pos);
		//	
		//	App->Cl_Dimensions->UpDate_Physics_And_Visuals(index);
		//}
		//ImGui::PopButtonRepeat();

		//ImGui::SameLine();
		//ImGui::SetNextItemWidth(100);
		//const char* XitemsZ[] = { "1", "2", "5", "10", "20" };
		//static int XitemZ = 1;
		//bool ChangedZ = ImGui::Combo("Step Z", &XitemZ, XitemsZ, IM_ARRAYSIZE(XitemsZ));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
		//if (ChangedZ == 1)
		//{
		//	App->Cl_Dimensions->Model_ZTranslate = (float)atof(XitemsZ[XitemZ]);
		//}
	
		ImGui::End();
	}
}