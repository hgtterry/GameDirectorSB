#include "stdafx.h"
#include "GD19_App.h"
#include "VM_ImGui.h"


VM_ImGui::VM_ImGui()
{
	StartPos = 0;
	Show_FPS = 1;
	Show_ImGui_Test = 0;
	Show_Rotation = 0;

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
	if (!ImGui::Begin("Rotation", &Show_Rotation, ImGuiWindowFlags_NoSavedSettings |ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
	}
	else
	{
		
		ImGui::Text("  X    Y    Z");

		ImGui::VSliderFloat("##RotationX", ImVec2(70, 260), &App->CL_Vm_Genesis3D->Actor_Rotation.X, 0.0f, 360.0f, "%.2f\nDeg");
		ImGui::SameLine();
		ImGui::VSliderFloat("##RotationY", ImVec2(70, 260), &App->CL_Vm_Genesis3D->Actor_Rotation.Y, 0.0f, 360.0f, "%.2f\nDeg");
		ImGui::SameLine();
		ImGui::VSliderFloat("##RotationZ", ImVec2(70, 260), &App->CL_Vm_Genesis3D->Actor_Rotation.Z, 0.0f, 360.0f, "%.2f\nDeg");


		App->CL_Vm_Genesis3D->MoveActor();

		ImGui::End();
	}
}