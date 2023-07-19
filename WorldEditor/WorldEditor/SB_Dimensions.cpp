/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Dimensions.h"

SB_Dimensions::SB_Dimensions()
{
	
		Show_Dimensions = 0;

		Show_Position = 0;
		Show_Scale = 0;
		Show_Rotation = 0;

		PosX_Selected = 1;
		PosY_Selected = 0;
		PosZ_Selected = 0;

		ScaleX_Selected = 1;
		ScaleY_Selected = 0;
		ScaleZ_Selected = 0;

		RotationX_Selected = 1;
		RotationY_Selected = 0;
		RotationZ_Selected = 0;

		Model_Pos_Delta = 1;
		Model_Scale_Delta = 0.5;
		Model_Rotation_Delta = 1;

		Scale_Lock = 1;
}

SB_Dimensions::~SB_Dimensions()
{
	

}

// *************************************************************************
// *					Dimesions_Select  Terry Flanigan				   *
// *************************************************************************
void SB_Dimensions::Dimesions_Select(void)
{
	if (Show_Position == 1 || Show_Scale == 1 || Show_Rotation == 1)
	{
		Show_Dimensions = 1;
		App->SBC_Dimensions->ImGui_Dimensions();
	}
	else
	{
		Show_Dimensions = 0;
	}
}

// *************************************************************************
// *						ImGui_Dimensions  Terry Flanigan			   *
// *************************************************************************
void SB_Dimensions::ImGui_Dimensions(void)
{
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);

	ImGuiStyle* style = &ImGui::GetStyle();

	if (!ImGui::Begin("Rotation2", &Show_Dimensions, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		
		ImGui::Indent();
		ImGui::Indent();

		//--------------------------------------- Position
		style->Colors[ImGuiCol_Button] = ImVec4(0.8f, 0.8f, 0.8f, 1);

		if (Show_Position == 1)
		{
			style->Colors[ImGuiCol_Button] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
		}

		if (ImGui::Button("Position"))
		{
			Show_Dimensions = 0;
			Show_Position = 1;
			Show_Scale = 0;
			Show_Rotation = 0;
		}

		style->Colors[ImGuiCol_Button] = ImVec4(0.8f, 0.8f, 0.8f, 1);

		//--------------------------------------- Rotation
		ImGui::SameLine(0.0f);

		if (Show_Rotation == 1)
		{
			style->Colors[ImGuiCol_Button] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
		}

		if (ImGui::Button("Rotation"))
		{
			Show_Dimensions = 0;
			Show_Position = 0;
			Show_Scale = 0;
			Show_Rotation = 1;
		}
		style->Colors[ImGuiCol_Button] = ImVec4(0.8f, 0.8f, 0.8f, 1);

		//--------------------------------------- Scale
		ImGui::SameLine(0.0f);

		if (Show_Scale == 1)
		{
			style->Colors[ImGuiCol_Button] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
		}

		if (ImGui::Button("Scale"))
		{
			Show_Dimensions = 0;
			Show_Position = 0;
			Show_Scale = 1;
			Show_Rotation = 0;

		}

		style->Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	
		ImGui::Unindent();
		ImGui::Unindent();

		if (Show_Position == 1)
		{
			/*if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
			{
				ImGui_Position_Area();
			}
			else*/
			{
				ImGui_Position();
			}
		}

		if (Show_Scale == 1)
		{
			/*if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
			{
				ImGui_Scale_Area();
			}
			else*/
			{
				ImGui_Scale();
			}
		}

		if (Show_Rotation == 1)
		{
			/*if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
			{
				ImGui_Rotation_Area();
			}
			else*/
			{
				ImGui_Rotation();
			}
		}
		
		ImGui::Separator();
		ImGui::Spacing();

		if (ImGui::Button("Close"))
		{
			Show_Dimensions = 0;
			Show_Position = 0;
			Show_Scale = 0;
			Show_Rotation = 0;

		}
		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Position Terry Flanigan				   *
// *************************************************************************
void SB_Dimensions::ImGui_Position(void)
{
	//int Index = App->SBC_Properties->Current_Selected_Object;

	Ogre::Vector3 Pos = Ogre::Vector3(0, 0, 0);

	if (App->CL_Model->Model_Type == Enums::LoadedFile_Assimp)
	{
		Pos.x = App->CL_Model->S_BoundingBox[0]->Centre->x;
		Pos.y = App->CL_Model->S_BoundingBox[0]->Centre->y;
		Pos.z = App->CL_Model->S_BoundingBox[0]->Centre->z;

		App->CL_Ogre->RenderListener->Hair_1PosX = Pos.x;
		App->CL_Ogre->RenderListener->Hair_1PosY = Pos.y;
		App->CL_Ogre->RenderListener->Hair_1PosZ = Pos.z;
	}

	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::Text("Position");
	ImGui::Separator();
	ImGui::Spacing();

	//ImGui::Text("Current Selected Object = %i", App->SBC_Properties->Current_Selected_Object);
	//ImGui::Text("Object Name: = %s", App->SBC_Scene->B_Object[Index]->Mesh_Name);
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	float vec4a[4] = { Pos.x, Pos.y, Pos.z, 0.44f };
	ImGui::InputFloat3("", vec4a, "%.3f", ImGuiInputTextFlags_ReadOnly);
	
	// ----------------------------------------------------------------------------- Pos CheckBox X 
	ImGui::Indent();
	ImGui::Indent();
	
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

	ImGui::Checkbox("PX", &PosX_Selected); 

	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	

	if (PosX_Selected == 1)
	{
		PosY_Selected = 0;
		PosZ_Selected = 0;
	}

	//------------------------------------------------------------------------------- Pos CheckBox Y
	ImGui::SameLine();
	ImGui::Text("        ");
	ImGui::SameLine();

	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.9f, 0.0f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.f, 1.f, 0.f, 1.00f);
	ImGui::Checkbox("PY", &PosY_Selected);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

	if (PosY_Selected)
	{
		PosX_Selected = 0;
		PosZ_Selected = 0;
	}

	//------------------------------------------------------------------------------- Pos CheckBox Z
	ImGui::SameLine();
	ImGui::Text("         ");
	ImGui::SameLine();

	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.9f, 0.0f, 0.0f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(1.f, 0.f, 0.f, 1.00f);
	ImGui::Checkbox("PZ", &PosZ_Selected);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	if (PosZ_Selected)
	{
		
		PosX_Selected = 0;
		PosY_Selected = 0;
	}
	
	ImGui::Indent();

	ImGui::Spacing();
	ImGui::Spacing();

	// ----------------------------------------------------------------------------- Position Do Move 
	float spacingX = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);
	if (ImGui::ArrowButton("##leftXX", ImGuiDir_Left))
	{
		if (App->CL_Model->Model_Loaded == 1)
		{
			if (PosX_Selected == 1)
			{
				Set_Position(Model_Pos_Delta, 0, 0);
			}

			if (PosY_Selected == 1)
			{
				Set_Position(0, Model_Pos_Delta, 0);
			}

			if (PosZ_Selected == 1)
			{
				Set_Position(0, 0, Model_Pos_Delta);
			}
		}
	}

	ImGui::SameLine(0.0f, spacingX);
	if (ImGui::ArrowButton("##rightXX", ImGuiDir_Right))
	{
		if (App->CL_Model->Model_Loaded == 1)
		{
			if (PosX_Selected == 1)
			{
				Set_Position(-Model_Pos_Delta, 0, 0);
			}

			if (PosY_Selected == 1)
			{
				Set_Position(0, -Model_Pos_Delta, 0);
			}

			if (PosZ_Selected == 1)
			{
				Set_Position(0, 0,-Model_Pos_Delta);
			}
		}
	}
	ImGui::PopButtonRepeat();

	// ----------------------------------------------------------------------------- Position Combo Step
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	const char* XitemsPosXX[] = { "0.001","0.01","0.1","1", "2", "5", "10", "20" };
	static int XitemPosXX = 3;
	bool ChangedPosX = ImGui::Combo("Step Pos", &XitemPosXX, XitemsPosXX, IM_ARRAYSIZE(XitemsPosXX));
	if (ChangedPosX == 1)
	{
		Model_Pos_Delta = (float)atof(XitemsPosXX[XitemPosXX]);
	}

	style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

	ImGui::Spacing();
	ImGui::Unindent();
	ImGui::Unindent();
	ImGui::Unindent();
}

// *************************************************************************
// *						Set_Position Terry Flanigan					   *
// *************************************************************************
void SB_Dimensions::Set_Position(float X, float Y, float Z)
{
	if (App->CL_Model->Model_Loaded == 1)
	{
		int Count = 0;
		int VertCount = 0;

		int GroupCount = App->CL_Model->Get_Groupt_Count();

		while (Count < GroupCount)
		{
			VertCount = 0;
			while (VertCount < App->CL_Model->Group[Count]->GroupVertCount)
			{
				App->CL_Model->Group[Count]->vertex_Data[VertCount].x += X;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].y += Y;
				App->CL_Model->Group[Count]->vertex_Data[VertCount].z += Z;
				VertCount++;
			}
			Count++;
		}

		App->CL_Model->Set_BondingBox_Model(0);
	}
}

// *************************************************************************
// *						ImGui_Scale Terry Flanigan					   *
// *************************************************************************
void SB_Dimensions::ImGui_Scale(void)
{

	Ogre::Vector3 Scale = Ogre::Vector3(0,0,0);

	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::Text("Scale");
	ImGui::Separator();
	ImGui::Spacing();

	//ImGui::Text("Current Selected Object = %i", App->SBC_Properties->Current_Selected_Object);
	//ImGui::Text("Object Name: = %s", App->SBC_Scene->B_Object[Index]->Mesh_Name);
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	float vec4a[4] = { Model_Scale_Delta, Scale.y, Scale.z, 0.44f };
	ImGui::InputFloat3("", vec4a, "%.3f", ImGuiInputTextFlags_ReadOnly);

	// ----------------------------------------------------------------------------- Scale Checkbox X
	ImGui::Indent();
	ImGui::Indent();
	
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);

	ImGui::Checkbox("SX", &ScaleX_Selected);
	
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);

	if (ScaleX_Selected == 1)
	{
		if (Scale_Lock == 1)
		{
			/*App->SBC_Markers->Hide_Axis_Marker();
			App->SBC_Markers->Update_Red_Axis_Marker(Index);
			App->SBC_Markers->Update_Green_Axis_Marker(Index);
			App->SBC_Markers->Update_Blue_Axis_Marker(Index);*/
		}
		else
		{
			/*App->SBC_Markers->Hide_Axis_Marker();
			App->SBC_Markers->Update_Blue_Axis_Marker(Index);*/
		}

		ScaleY_Selected = 0;
		ScaleZ_Selected = 0;
	}
	
	//------------------------------------------------------------------------------- Scale Checkbox Y
	ImGui::SameLine();
	ImGui::Text("        ");
	ImGui::SameLine();

	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.9f, 0.0f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.f, 1.f, 0.f, 1.00f);
	ImGui::Checkbox("SY", &ScaleY_Selected);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

	if (ScaleY_Selected)
	{
		if (Scale_Lock == 1)
		{
			/*App->SBC_Markers->Hide_Axis_Marker();
			App->SBC_Markers->Update_Red_Axis_Marker(Index);
			App->SBC_Markers->Update_Green_Axis_Marker(Index);
			App->SBC_Markers->Update_Blue_Axis_Marker(Index);*/
		}
		else
		{
			/*App->SBC_Markers->Hide_Axis_Marker();
			App->SBC_Markers->Update_Green_Axis_Marker(Index);*/
		}

		ScaleX_Selected = 0;
		ScaleZ_Selected = 0;
	}

	//------------------------------------------------------------------------------- Scale Checkbox Z
	ImGui::SameLine();
	ImGui::Text("         ");
	ImGui::SameLine();

	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
	ImGui::Checkbox("SZ", &ScaleZ_Selected);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

	if (ScaleZ_Selected)
	{
		if (Scale_Lock == 1)
		{
			/*App->SBC_Markers->Hide_Axis_Marker();
			App->SBC_Markers->Update_Red_Axis_Marker(Index);
			App->SBC_Markers->Update_Green_Axis_Marker(Index);
			App->SBC_Markers->Update_Blue_Axis_Marker(Index);*/
		}
		else
		{
			/*App->SBC_Markers->Hide_Axis_Marker();
			App->SBC_Markers->Update_Red_Axis_Marker(Index);*/
		}

		ScaleX_Selected = 0;
		ScaleY_Selected = 0;
	}
	
	ImGui::Indent();
	ImGui::Spacing();
	ImGui::Spacing();

	// ----------------------------------------------------------------------------- Scale Do Scale
	float spacingX = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);
	if (ImGui::ArrowButton("##leftSX", ImGuiDir_Left))
	{
		if (App->CL_Model->Model_Loaded == 1)
		{
			if (Scale_Lock == 1)
			{
				Scale.x = Scale.x + Model_Scale_Delta;
				Scale.y = Scale.y + Model_Scale_Delta;
				Scale.z = Scale.z + Model_Scale_Delta;
				
				Set_Scale(1,1,1,1);
			}
			else
			{
				if (ScaleX_Selected == 1)
				{
					//Scale.x = Scale.x + Model_Scale_Delta;
					Set_Scale(1, Model_Scale_Delta * 4, 1, 1);

				}

				if (ScaleY_Selected == 1)
				{
					//Scale.y = Scale.y + Model_Scale_Delta;
					Set_Scale(1, 1, Model_Scale_Delta * 4, 1);

				}

				if (ScaleZ_Selected == 1)
				{
					//Scale.z = Scale.z + Model_Scale_Delta;
					Set_Scale(1, 1, 1, Model_Scale_Delta * 4);
				}
			}
		}
	}

	ImGui::SameLine(0.0f, spacingX);
	if (ImGui::ArrowButton("##rightSX", ImGuiDir_Right))
	{
		if (App->CL_Model->Model_Loaded == 1)
		{
			if (Scale_Lock == 1)
			{
				Scale.x = Scale.x - Model_Scale_Delta;
				Scale.y = Scale.y - Model_Scale_Delta;
				Scale.z = Scale.z - Model_Scale_Delta;

				Set_Scale(0, 1, 1, 1);
			}
			else
			{
				if (ScaleX_Selected == 1)
				{
					//Scale.x = Scale.x - Model_Scale_Delta;

					Set_Scale(0, Model_Scale_Delta, 1, 1);
					
				}

				if (ScaleY_Selected == 1)
				{
					//Scale.y = Scale.y - Model_Scale_Delta;

					Set_Scale(1, 1, Model_Scale_Delta, 1);
				
				}

				if (ScaleZ_Selected == 1)
				{
					Scale.z = Scale.z - Model_Scale_Delta;

					Set_Scale(1, 1, 1, Model_Scale_Delta);
					
				}
			}
		}
	}
	ImGui::PopButtonRepeat();

	// ----------------------------------------------------------------------------- Scale Combo Step
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	const char* XitemsScaleXX[] = { "0.001","0.5","0.1","1", "2", "5", "10", "20" };
	static int XitemScaleXX = 1;
	bool ChangedScaleX = ImGui::Combo("Step Scale", &XitemScaleXX, XitemsScaleXX, IM_ARRAYSIZE(XitemsScaleXX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
	if (ChangedScaleX == 1)
	{
		Model_Scale_Delta = (float)atof(XitemsScaleXX[XitemScaleXX]);
	}

	

	ImGui::Checkbox("Lock Axis", &Scale_Lock);
	{
		
	}

	style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

	ImGui::Spacing();
	ImGui::Unindent();
	ImGui::Unindent();
	ImGui::Unindent();
}

// *************************************************************************
// *						Set_Scale Terry Flanigan					   *
// *************************************************************************
void SB_Dimensions::Set_Scale(bool Mode, float X, float Y, float Z)
{
	if (App->CL_Model->Model_Loaded == 1)
	{
		if (Scale_Lock == 1)
		{
			float Timeser = 1 / Model_Scale_Delta;
			Ogre::Vector3 Scale;

			if (Mode == 1)
			{
				Scale.x = Model_Scale_Delta *4;
				Scale.y = Model_Scale_Delta *4;
				Scale.z = Model_Scale_Delta *4;
			}
			else
			{
				Scale.x = Model_Scale_Delta;
				Scale.y = Model_Scale_Delta;
				Scale.z = Model_Scale_Delta;
			}

			int Count = 0;
			int VertCount = 0;

			int GroupCount = App->CL_Model->Get_Groupt_Count();

			while (Count < GroupCount)
			{
				VertCount = 0;
				while (VertCount < App->CL_Model->Group[Count]->GroupVertCount)
				{
					App->CL_Model->Group[Count]->vertex_Data[VertCount].x *= Scale.x;
					App->CL_Model->Group[Count]->vertex_Data[VertCount].y *= Scale.y;
					App->CL_Model->Group[Count]->vertex_Data[VertCount].z *= Scale.z;
					VertCount++;
				}
				Count++;
			}

			App->CL_Model->Set_BondingBox_Model(0);

		}
		else
		{
			Ogre::Vector3 Scale;

			int Count = 0;
			int VertCount = 0;

			int GroupCount = App->CL_Model->Get_Groupt_Count();

			while (Count < GroupCount)
			{
				VertCount = 0;
				while (VertCount < App->CL_Model->Group[Count]->GroupVertCount)
				{
					App->CL_Model->Group[Count]->vertex_Data[VertCount].x *= X;
					App->CL_Model->Group[Count]->vertex_Data[VertCount].y *= Y;
					App->CL_Model->Group[Count]->vertex_Data[VertCount].z *= Z;
					VertCount++;
				}
				Count++;
			}

			App->CL_Model->Set_BondingBox_Model(0);
		}
	}
}

// *************************************************************************
// *						ImGui_Rotation Terry Flanigan				   *
// *************************************************************************
void SB_Dimensions::ImGui_Rotation(void)
{
	Ogre::Vector3 Pos = Ogre::Vector3(0, 0, 0);

	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::Text("Rotation");
	ImGui::Separator();
	ImGui::Spacing();

	//ImGui::Text("Current Selected Object = %i", App->SBC_Properties->Current_Selected_Object);
	//ImGui::Text("Object Name: = %s", App->SBC_Scene->B_Object[Index]->Mesh_Name);
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	float vec4a[4] = { Pos.x, Pos.y, Pos.z, 0.44f };
	ImGui::InputFloat3("", vec4a, "%.3f", ImGuiInputTextFlags_ReadOnly);

	// ----------------------------------------------------------------------------- Rotation Checkbox X
	ImGui::Indent();
	ImGui::Indent();
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	ImGui::Checkbox("RX", &RotationX_Selected);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);

	if (RotationX_Selected == 1)
	{
		RotationY_Selected = 0;
		RotationZ_Selected = 0;
	}

	//------------------------------------------------------------------------------- Rotation Checkbox Y
	ImGui::SameLine();
	ImGui::Text("        ");
	ImGui::SameLine();

	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.9f, 0.0f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.f, 1.f, 0.f, 1.00f);
	ImGui::Checkbox("RY", &RotationY_Selected);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

	if (RotationY_Selected)
	{
		RotationX_Selected = 0;
		RotationZ_Selected = 0;
	}

	//------------------------------------------------------------------------------- Rotation Checkbox Z
	ImGui::SameLine();
	ImGui::Text("         ");
	ImGui::SameLine();

	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
	ImGui::Checkbox("RZ", &RotationZ_Selected);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	if (RotationZ_Selected)
	{
		RotationX_Selected = 0;
		RotationY_Selected = 0;
	}
	// ----------------------------------------------------------------------------- Rotation 

	ImGui::Indent();

	ImGui::Spacing();
	ImGui::Spacing();

	float spacingX = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);
	if (ImGui::ArrowButton("##leftRX", ImGuiDir_Left))
	{
		if (App->CL_Model->Model_Loaded == 1)
		{

			if (RotationX_Selected == 1)
			{
				App->CL_Dimensions->Rotate_X_Model(Model_Rotation_Delta);
			}

			if (RotationY_Selected == 1)
			{
				App->CL_Dimensions->Rotate_Y_Model(Model_Rotation_Delta);
			}

			if (RotationZ_Selected == 1)
			{
				App->CL_Dimensions->Rotate_Z_Model(Model_Rotation_Delta);
			}

		}
	}

	ImGui::SameLine(0.0f, spacingX);
	if (ImGui::ArrowButton("##rightRX", ImGuiDir_Right))
	{
		if (App->CL_Model->Model_Loaded == 1)
		{
			
				if (RotationX_Selected == 1)
				{
					App->CL_Dimensions->Rotate_X_Model(-Model_Rotation_Delta);
				}

				if (RotationY_Selected == 1)
				{
					App->CL_Dimensions->Rotate_Y_Model(-Model_Rotation_Delta);
				}

				if (RotationZ_Selected == 1)
				{
					App->CL_Dimensions->Rotate_Z_Model(-Model_Rotation_Delta);
				}
			
		}
	}
	ImGui::PopButtonRepeat();

	// ----------------------------------------------------------------------------- Rotation Combo Step
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	const char* XitemsRotXX[] = { "0.001","0.01","0.1","1", "2", "5", "10", "45" };
	static int XitemRotXX = 3;
	bool ChangedRotX = ImGui::Combo("Step Rot", &XitemRotXX, XitemsRotXX, IM_ARRAYSIZE(XitemsRotXX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
	if (ChangedRotX == 1)
	{
		Model_Rotation_Delta = (float)atof(XitemsRotXX[XitemRotXX]);
	}

	
	

	style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

	ImGui::Spacing();
	ImGui::Unindent();
	ImGui::Unindent();
	ImGui::Unindent();
}

// *************************************************************************
// *				UpDate_Physics_And_Visuals Terry Flanigtan		 	   *
// *************************************************************************
void SB_Dimensions::UpDate_Physics_And_Visuals(int Index)
{
	//if (App->SBC_Scene->B_Object[Index]->Shape == Enums::Shape_TriMesh)
	//{

	//}
	//else
	//{
	//	//if (App->SBC_Scene->B_Object[Index]->Physics_Valid == 1)
	//	{
	//		Set_Physics_Position(Index);
	//	}
	//}
	//

	//App->SBC_Visuals->MarkerBB_Addjust(Index);

	//// Needs Looking at
	//App->SBC_Scene->B_Object[Index]->Altered = 1;
	//App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Object[Index]->FileViewItem);
	//App->SBC_Scene->Scene_Modified = 1;
}

// *************************************************************************
// *	  				Set_Physics_Position Terry Flanigan				   *
// *************************************************************************
void SB_Dimensions::Set_Physics_Position(int Index)
{
	/*AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
	worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();
	App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
	App->SBC_Scene->B_Object[Index]->Physics_Pos = Centre;*/
}

// *************************************************************************
// *					ImGui_Position_Area Terry Flanigan				   *
// *************************************************************************
void SB_Dimensions::ImGui_Position_Area(void)
{
	//int Index = App->SBC_Properties->Current_Selected_Object;

	//Ogre::Vector3 Pos = App->SBC_Scene->B_Area[Index]->Mesh_Pos;

	//ImGuiStyle* style = &ImGui::GetStyle();

	//ImGui::Text("Position");
	//ImGui::Separator();
	//ImGui::Spacing();

	//ImGui::Text("Current Selected Area = %i", App->SBC_Properties->Current_Selected_Object);
	//ImGui::Text("Area Name: = %s", App->SBC_Scene->B_Area[Index]->Area_Name);
	//ImGui::Spacing();
	//ImGui::Separator();
	//ImGui::Spacing();

	//ImGui::Indent();
	//ImGui::Indent();
	//ImGui::Text("X %.3f Y %.3f Z %.3f", Pos.x, Pos.y, Pos.z);

	//ImGui::Spacing();

	//// ----------------------------------------------------------------------------- Position

	//float spacingX = ImGui::GetStyle().ItemInnerSpacing.x;
	//ImGui::PushButtonRepeat(true);
	//if (ImGui::ArrowButton("##leftXX", ImGuiDir_Left))
	//{
	//	if (App->SBC_Scene->Scene_Loaded == 1)
	//	{
	//		if (PosX_Selected == 1)
	//		{
	//			Pos.x = Pos.x - Model_Pos_Delta;
	//			App->SBC_Scene->B_Area[Index]->Area_Node->setPosition(Pos);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Pos = Pos;

	//			Ogre::Vector3 Centre = App->SBC_Com_Area->Get_BoundingBox_World_Centre(Index);

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));

	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//		}

	//		if (PosY_Selected == 1)
	//		{
	//			Pos.y = Pos.y + Model_Pos_Delta;
	//			App->SBC_Scene->B_Area[Index]->Area_Node->setPosition(Pos);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Pos = Pos;

	//			Ogre::Vector3 Centre = App->SBC_Com_Area->Get_BoundingBox_World_Centre(Index);

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//		}

	//		if (PosZ_Selected == 1)
	//		{
	//			Pos.z = Pos.z - Model_Pos_Delta;
	//			App->SBC_Scene->B_Area[Index]->Area_Node->setPosition(Pos);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Pos = Pos;

	//			Ogre::Vector3 Centre = App->SBC_Com_Area->Get_BoundingBox_World_Centre(Index);

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//		}
	//	}
	//}

	//ImGui::SameLine(0.0f, spacingX);
	//if (ImGui::ArrowButton("##rightXX", ImGuiDir_Right))
	//{
	//	if (App->SBC_Scene->Scene_Loaded == 1)
	//	{
	//		if (PosX_Selected == 1)
	//		{
	//			Pos.x = Pos.x + Model_Pos_Delta;
	//			App->SBC_Scene->B_Area[Index]->Area_Node->setPosition(Pos);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Pos = Pos;

	//			Ogre::Vector3 Centre = App->SBC_Com_Area->Get_BoundingBox_World_Centre(Index);

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//		}

	//		if (PosY_Selected == 1)
	//		{
	//			Pos.y = Pos.y - Model_Pos_Delta;
	//			App->SBC_Scene->B_Area[Index]->Area_Node->setPosition(Pos);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Pos = Pos;

	//			Ogre::Vector3 Centre = App->SBC_Com_Area->Get_BoundingBox_World_Centre(Index);

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//		}

	//		if (PosZ_Selected == 1)
	//		{
	//			Pos.z = Pos.z + Model_Pos_Delta;
	//			App->SBC_Scene->B_Area[Index]->Area_Node->setPosition(Pos);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Pos = Pos;

	//			Ogre::Vector3 Centre = App->SBC_Com_Area->Get_BoundingBox_World_Centre(Index);

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//		}
	//	}
	//}
	//ImGui::PopButtonRepeat();

	//ImGui::SameLine();
	//ImGui::SetNextItemWidth(100);
	//const char* XitemsPosXX[] = { "0.001","0.01","0.1","1", "2", "5", "10", "20" };
	//static int XitemPosXX = 3;
	//bool ChangedPosX = ImGui::Combo("Step Pos", &XitemPosXX, XitemsPosXX, IM_ARRAYSIZE(XitemsPosXX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
	//if (ChangedPosX == 1)
	//{
	//	Model_Pos_Delta = (float)atof(XitemsPosXX[XitemPosXX]);
	//}

	//// ----------------------------------------------------------------------------- Pos X
	//ImGui::Indent();

	//style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);
	//ImGui::Checkbox("X", &PosX_Selected);
	//if (PosX_Selected == 1)
	//{
	//	App->SBC_Markers->Hide_Axis_Marker();
	//	App->SBC_Markers->Update_Blue_Axis_Marker(Index);

	//	PosY_Selected = 0;
	//	PosZ_Selected = 0;
	//}
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	////------------------------------------------------------------------------------- Pos Y
	//ImGui::SameLine();
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
	//ImGui::Checkbox("Y", &PosY_Selected);
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

	//if (PosY_Selected)
	//{
	//	App->SBC_Markers->Hide_Axis_Marker();
	//	App->SBC_Markers->Update_Green_Axis_Marker(Index);

	//	PosX_Selected = 0;
	//	PosZ_Selected = 0;
	//}

	////------------------------------------------------------------------------------- Pos Z
	//ImGui::SameLine();
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
	//ImGui::Checkbox("Z", &PosZ_Selected);
	//if (PosZ_Selected)
	//{
	//	App->SBC_Markers->Hide_Axis_Marker();
	//	App->SBC_Markers->Update_Red_Axis_Marker(Index);

	//	PosX_Selected = 0;
	//	PosY_Selected = 0;


	//}
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);


	//style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

	//ImGui::Spacing();
	//ImGui::Unindent();

	//ImGui::Unindent();
	//ImGui::Unindent();
}

// *************************************************************************
// *					ImGui_Rotation_Area Terry Flanigan				   *
// *************************************************************************
void SB_Dimensions::ImGui_Rotation_Area(void)
{
	//int Index = App->SBC_Properties->Current_Selected_Object;

	//Ogre::Vector3 RotD = App->SBC_Scene->B_Area[Index]->Mesh_Rot;

	//ImGuiStyle* style = &ImGui::GetStyle();

	//ImGui::Text("Rotation");
	//ImGui::Separator();
	//ImGui::Spacing();

	//ImGui::Text("Current Selected Object = %i", App->SBC_Properties->Current_Selected_Object);
	//ImGui::Text("Object Name: = %s", App->SBC_Scene->B_Area[Index]->Area_Name);
	//ImGui::Spacing();
	//ImGui::Separator();
	//ImGui::Spacing();

	//float X = 0;

	//ImGui::Indent();
	//ImGui::Indent();
	//ImGui::Text("X %.3f Y %.3f Z %.3f", RotD.x, RotD.y, RotD.z);

	//ImGui::Spacing();

	//// ----------------------------------------------------------------------------- Rotate x

	//float spacingX = ImGui::GetStyle().ItemInnerSpacing.x;
	//ImGui::PushButtonRepeat(true);
	//if (ImGui::ArrowButton("##leftRX", ImGuiDir_Left))
	//{
	//	if (App->SBC_Scene->Scene_Loaded == 1)
	//	{

	//		if (RotationX_Selected == 1)
	//		{
	//			App->SBC_Scene->B_Area[Index]->Area_Node->rotate(Ogre::Quaternion(Ogre::Degree(Model_Rotation_Delta), Ogre::Vector3(1, 0, 0)), Ogre::Node::TransformSpace::TS_LOCAL);

	//			App->SBC_Scene->B_Area[Index]->Mesh_Rot.x += Model_Rotation_Delta;
	//			App->SBC_Scene->B_Area[Index]->Mesh_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	//			App->SBC_Scene->B_Area[Index]->Physics_Rot.x += Model_Rotation_Delta;
	//			App->SBC_Scene->B_Area[Index]->Physics_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	//			float w = App->SBC_Scene->B_Area[Index]->Physics_Quat.w;
	//			float x = App->SBC_Scene->B_Area[Index]->Physics_Quat.x;
	//			float y = App->SBC_Scene->B_Area[Index]->Physics_Quat.y;
	//			float z = App->SBC_Scene->B_Area[Index]->Physics_Quat.z;

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);

	//		}

	//		if (RotationY_Selected == 1)
	//		{
	//			App->SBC_Scene->B_Area[Index]->Area_Node->rotate(Ogre::Quaternion(Ogre::Degree(Model_Rotation_Delta), Ogre::Vector3(0, 1, 0)), Ogre::Node::TransformSpace::TS_LOCAL);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Rot.y += Model_Rotation_Delta;
	//			App->SBC_Scene->B_Area[Index]->Mesh_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	//			App->SBC_Scene->B_Area[Index]->Physics_Rot.y += Model_Rotation_Delta;
	//			App->SBC_Scene->B_Area[Index]->Physics_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	//			float w = App->SBC_Scene->B_Area[Index]->Physics_Quat.w;
	//			float x = App->SBC_Scene->B_Area[Index]->Physics_Quat.x;
	//			float y = App->SBC_Scene->B_Area[Index]->Physics_Quat.y;
	//			float z = App->SBC_Scene->B_Area[Index]->Physics_Quat.z;

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);

	//		}

	//		if (RotationZ_Selected == 1)
	//		{
	//			App->SBC_Scene->B_Area[Index]->Area_Node->rotate(Ogre::Quaternion(Ogre::Degree(Model_Rotation_Delta), Ogre::Vector3(0, 0, 1)), Ogre::Node::TransformSpace::TS_LOCAL);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Rot.z += Model_Rotation_Delta;
	//			App->SBC_Scene->B_Area[Index]->Mesh_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	//			App->SBC_Scene->B_Area[Index]->Physics_Rot.z += Model_Rotation_Delta;
	//			App->SBC_Scene->B_Area[Index]->Physics_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	//			float w = App->SBC_Scene->B_Area[Index]->Physics_Quat.w;
	//			float x = App->SBC_Scene->B_Area[Index]->Physics_Quat.x;
	//			float y = App->SBC_Scene->B_Area[Index]->Physics_Quat.y;
	//			float z = App->SBC_Scene->B_Area[Index]->Physics_Quat.z;

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);

	//		}

	//	}
	//}

	//ImGui::SameLine(0.0f, spacingX);
	//if (ImGui::ArrowButton("##rightRX", ImGuiDir_Right))
	//{
	//	if (App->SBC_Scene->Scene_Loaded == 1)
	//	{

	//		if (RotationX_Selected == 1)
	//		{
	//			App->SBC_Scene->B_Area[Index]->Area_Node->rotate(Ogre::Quaternion(Ogre::Degree(-Model_Rotation_Delta), Ogre::Vector3(1, 0, 0)), Ogre::Node::TransformSpace::TS_LOCAL);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Rot.x -= Model_Rotation_Delta;
	//			App->SBC_Scene->B_Area[Index]->Mesh_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	//			App->SBC_Scene->B_Area[Index]->Physics_Rot.x -= Model_Rotation_Delta;
	//			App->SBC_Scene->B_Area[Index]->Physics_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	//			float w = App->SBC_Scene->B_Area[Index]->Physics_Quat.w;
	//			float x = App->SBC_Scene->B_Area[Index]->Physics_Quat.x;
	//			float y = App->SBC_Scene->B_Area[Index]->Physics_Quat.y;
	//			float z = App->SBC_Scene->B_Area[Index]->Physics_Quat.z;

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);

	//		}

	//		if (RotationY_Selected == 1)
	//		{
	//			App->SBC_Scene->B_Area[Index]->Area_Node->rotate(Ogre::Quaternion(Ogre::Degree(-Model_Rotation_Delta), Ogre::Vector3(0, 1, 0)), Ogre::Node::TransformSpace::TS_LOCAL);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Rot.y -= Model_Rotation_Delta;
	//			App->SBC_Scene->B_Area[Index]->Mesh_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	//			App->SBC_Scene->B_Area[Index]->Physics_Rot.y -= Model_Rotation_Delta;
	//			App->SBC_Scene->B_Area[Index]->Physics_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	//			float w = App->SBC_Scene->B_Area[Index]->Physics_Quat.w;
	//			float x = App->SBC_Scene->B_Area[Index]->Physics_Quat.x;
	//			float y = App->SBC_Scene->B_Area[Index]->Physics_Quat.y;
	//			float z = App->SBC_Scene->B_Area[Index]->Physics_Quat.z;

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);

	//		}

	//		if (RotationZ_Selected == 1)
	//		{
	//			App->SBC_Scene->B_Area[Index]->Area_Node->rotate(Ogre::Quaternion(Ogre::Degree(-Model_Rotation_Delta), Ogre::Vector3(0, 0, 1)), Ogre::Node::TransformSpace::TS_LOCAL);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Rot.z -= Model_Rotation_Delta;
	//			App->SBC_Scene->B_Area[Index]->Mesh_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	//			App->SBC_Scene->B_Area[Index]->Physics_Rot.z -= Model_Rotation_Delta;
	//			App->SBC_Scene->B_Area[Index]->Physics_Quat = App->SBC_Scene->B_Area[Index]->Area_Node->getOrientation();

	//			float w = App->SBC_Scene->B_Area[Index]->Physics_Quat.w;
	//			float x = App->SBC_Scene->B_Area[Index]->Physics_Quat.x;
	//			float y = App->SBC_Scene->B_Area[Index]->Physics_Quat.y;
	//			float z = App->SBC_Scene->B_Area[Index]->Physics_Quat.z;

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);

	//		}

	//	}
	//}

	//ImGui::PopButtonRepeat();
	//ImGui::SameLine();
	//ImGui::SetNextItemWidth(100);
	//const char* XitemsRotXX[] = { "0.001","0.01","0.1","1", "2", "5", "10", "45" };
	//static int XitemRotXX = 3;
	//bool ChangedRotX = ImGui::Combo("Step Rot", &XitemRotXX, XitemsRotXX, IM_ARRAYSIZE(XitemsRotXX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
	//if (ChangedRotX == 1)
	//{
	//	Model_Rotation_Delta = (float)atof(XitemsRotXX[XitemRotXX]);
	//}

	//// ----------------------------------------------------------------------------- Rotation X
	//ImGui::Indent();

	//style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);
	//ImGui::Checkbox("RX", &RotationX_Selected);
	//if (RotationX_Selected == 1)
	//{
	//	RotationY_Selected = 0;
	//	RotationZ_Selected = 0;
	//}
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	////------------------------------------------------------------------------------- Rotation Y
	//ImGui::SameLine();
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
	//ImGui::Checkbox("RY", &RotationY_Selected);
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

	//if (RotationY_Selected)
	//{
	//	RotationX_Selected = 0;
	//	RotationZ_Selected = 0;
	//}

	////------------------------------------------------------------------------------- Rotation Z
	//ImGui::SameLine();
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
	//ImGui::Checkbox("RZ", &RotationZ_Selected);
	//if (RotationZ_Selected)
	//{
	//	RotationX_Selected = 0;
	//	RotationY_Selected = 0;
	//}
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

	//style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

	//ImGui::Spacing();
	//ImGui::Unindent();

	//ImGui::Unindent();
	//ImGui::Unindent();
}

// *************************************************************************
// *					ImGui_Scale_Area Terry Flanigan					   *
// *************************************************************************
void SB_Dimensions::ImGui_Scale_Area(void)
{
	//int Index = App->SBC_Properties->Current_Selected_Object;

	//Ogre::Vector3 Scale = App->SBC_Scene->B_Area[Index]->Mesh_Scale;

	//ImGuiStyle* style = &ImGui::GetStyle();

	//ImGui::Text("Scale");
	//ImGui::Separator();
	//ImGui::Spacing();

	//ImGui::Text("Current Selected Object = %i", App->SBC_Properties->Current_Selected_Object);
	//ImGui::Text("Object Name: = %s", App->SBC_Scene->B_Area[Index]->Area_Name);
	//ImGui::Spacing();
	//ImGui::Separator();
	//ImGui::Spacing();

	//float X = 0;

	//if (App->SBC_Scene->Scene_Loaded == 1)
	//{
	//	/*pos.x = App->CL_Model->S_BoundingBox[0]->Centre->x;
	//	pos.y = App->CL_Model->S_BoundingBox[0]->Centre->y;
	//	pos.z = App->CL_Model->S_BoundingBox[0]->Centre->z;

	//	App->CL_Ogre->RenderListener->Hair_1PosX = pos.x;
	//	App->CL_Ogre->RenderListener->Hair_1PosY = pos.y;
	//	App->CL_Ogre->RenderListener->Hair_1PosZ = pos.z;*/
	//}

	//ImGui::Indent();
	//ImGui::Indent();
	//ImGui::Text("X %.4f Y %.4f Z %.4f", Scale.x, Scale.y, Scale.z);

	//ImGui::Spacing();

	//// ----------------------------------------------------------------------------- Scale

	//float spacingX = ImGui::GetStyle().ItemInnerSpacing.x;
	//ImGui::PushButtonRepeat(true);
	//if (ImGui::ArrowButton("##leftSX", ImGuiDir_Left))
	//{
	//	if (App->SBC_Scene->Scene_Loaded == 1)
	//	{
	//		if (Scale_Lock == 1)
	//		{
	//			Scale.x = Scale.x + Model_Scale_Delta;
	//			Scale.y = Scale.y + Model_Scale_Delta;
	//			Scale.z = Scale.z + Model_Scale_Delta;

	//			App->SBC_Scene->B_Area[Index]->Area_Node->setScale(Scale);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Scale = Scale;


	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));
	//			App->SBC_Scene->B_Area[Index]->Physics_Scale = Scale;

	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//		}
	//		else
	//		{
	//			if (ScaleX_Selected == 1)
	//			{
	//				Scale.x = Scale.x - Model_Scale_Delta;
	//				App->SBC_Scene->B_Area[Index]->Area_Node->setScale(Scale);
	//				App->SBC_Scene->B_Area[Index]->Mesh_Scale = Scale;

	//				App->SBC_Scene->B_Area[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));
	//				App->SBC_Scene->B_Area[Index]->Physics_Scale = Scale;

	//				App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//			}

	//			if (ScaleY_Selected == 1)
	//			{
	//				Scale.y = Scale.y + Model_Scale_Delta;
	//				App->SBC_Scene->B_Area[Index]->Area_Node->setScale(Scale);
	//				App->SBC_Scene->B_Area[Index]->Mesh_Scale = Scale;

	//				App->SBC_Scene->B_Area[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));
	//				App->SBC_Scene->B_Area[Index]->Physics_Scale = Scale;

	//				App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//			}

	//			if (ScaleZ_Selected == 1)
	//			{
	//				Scale.z = Scale.z - Model_Scale_Delta;
	//				App->SBC_Scene->B_Area[Index]->Area_Node->setScale(Scale);
	//				App->SBC_Scene->B_Area[Index]->Mesh_Scale = Scale;

	//				App->SBC_Scene->B_Area[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));
	//				App->SBC_Scene->B_Area[Index]->Physics_Scale = Scale;

	//				App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//			}
	//		}
	//	}
	//}

	//ImGui::SameLine(0.0f, spacingX);
	//if (ImGui::ArrowButton("##rightSX", ImGuiDir_Right))
	//{
	//	if (App->SBC_Scene->Scene_Loaded == 1)
	//	{
	//		if (Scale_Lock == 1)
	//		{
	//			Scale.x = Scale.x - Model_Scale_Delta;
	//			Scale.y = Scale.y - Model_Scale_Delta;
	//			Scale.z = Scale.z - Model_Scale_Delta;

	//			App->SBC_Scene->B_Area[Index]->Area_Node->setScale(Scale);
	//			App->SBC_Scene->B_Area[Index]->Mesh_Scale = Scale;

	//			App->SBC_Scene->B_Area[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));
	//			App->SBC_Scene->B_Area[Index]->Physics_Scale = Scale;

	//			App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//		}
	//		else
	//		{
	//			if (ScaleX_Selected == 1)
	//			{
	//				Scale.x = Scale.x + Model_Scale_Delta;
	//				App->SBC_Scene->B_Area[Index]->Area_Node->setScale(Scale);
	//				App->SBC_Scene->B_Area[Index]->Mesh_Scale = Scale;

	//				App->SBC_Scene->B_Area[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));
	//				App->SBC_Scene->B_Area[Index]->Physics_Scale = Scale;

	//				App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//			}

	//			if (ScaleY_Selected == 1)
	//			{
	//				Scale.y = Scale.y - Model_Scale_Delta;
	//				App->SBC_Scene->B_Area[Index]->Area_Node->setScale(Scale);
	//				App->SBC_Scene->B_Area[Index]->Mesh_Scale = Scale;

	//				App->SBC_Scene->B_Area[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));
	//				App->SBC_Scene->B_Area[Index]->Physics_Scale = Scale;

	//				App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//			}

	//			if (ScaleZ_Selected == 1)
	//			{
	//				Scale.z = Scale.z + Model_Scale_Delta;
	//				App->SBC_Scene->B_Area[Index]->Area_Node->setScale(Scale);
	//				App->SBC_Scene->B_Area[Index]->Mesh_Scale = Scale;

	//				App->SBC_Scene->B_Area[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));
	//				App->SBC_Scene->B_Area[Index]->Physics_Scale = Scale;

	//				App->SBC_Com_Area->UpDate_Physics_And_Visuals(Index);
	//			}
	//		}
	//	}
	//}
	//ImGui::PopButtonRepeat();

	//ImGui::SameLine();
	//ImGui::SetNextItemWidth(100);
	//const char* XitemsScaleXX[] = { "0.001","0.01","0.1","1", "2", "5", "10", "20" };
	//static int XitemScaleXX = 1;
	//bool ChangedScaleX = ImGui::Combo("Step Scale", &XitemScaleXX, XitemsScaleXX, IM_ARRAYSIZE(XitemsScaleXX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
	//if (ChangedScaleX == 1)
	//{
	//	Model_Scale_Delta = (float)atof(XitemsScaleXX[XitemScaleXX]);
	//}

	//// ----------------------------------------------------------------------------- Scale X
	//ImGui::Indent();

	//style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);
	//ImGui::Checkbox("SX", &ScaleX_Selected);
	//if (ScaleX_Selected == 1)
	//{
	//	if (Scale_Lock == 1)
	//	{
	//		App->SBC_Markers->Hide_Axis_Marker();
	//		App->SBC_Markers->Update_Red_Axis_Marker(Index);
	//		App->SBC_Markers->Update_Green_Axis_Marker(Index);
	//		App->SBC_Markers->Update_Blue_Axis_Marker(Index);
	//	}
	//	else
	//	{
	//		App->SBC_Markers->Hide_Axis_Marker();
	//		App->SBC_Markers->Update_Blue_Axis_Marker(Index);
	//	}

	//	ScaleY_Selected = 0;
	//	ScaleZ_Selected = 0;
	//}
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	////------------------------------------------------------------------------------- Scale Y
	//ImGui::SameLine();
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
	//ImGui::Checkbox("SY", &ScaleY_Selected);
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

	//if (ScaleY_Selected)
	//{
	//	if (Scale_Lock == 1)
	//	{
	//		App->SBC_Markers->Hide_Axis_Marker();
	//		App->SBC_Markers->Update_Red_Axis_Marker(Index);
	//		App->SBC_Markers->Update_Green_Axis_Marker(Index);
	//		App->SBC_Markers->Update_Blue_Axis_Marker(Index);
	//	}
	//	else
	//	{
	//		App->SBC_Markers->Hide_Axis_Marker();
	//		App->SBC_Markers->Update_Green_Axis_Marker(Index);
	//	}

	//	ScaleX_Selected = 0;
	//	ScaleZ_Selected = 0;
	//}

	////------------------------------------------------------------------------------- Scale Z
	//ImGui::SameLine();
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
	//ImGui::Checkbox("SZ", &ScaleZ_Selected);
	//if (ScaleZ_Selected)
	//{
	//	if (Scale_Lock == 1)
	//	{
	//		App->SBC_Markers->Hide_Axis_Marker();
	//		App->SBC_Markers->Update_Red_Axis_Marker(Index);
	//		App->SBC_Markers->Update_Green_Axis_Marker(Index);
	//		App->SBC_Markers->Update_Blue_Axis_Marker(Index);
	//	}
	//	else
	//	{
	//		App->SBC_Markers->Hide_Axis_Marker();
	//		App->SBC_Markers->Update_Red_Axis_Marker(Index);
	//	}

	//	ScaleX_Selected = 0;
	//	ScaleY_Selected = 0;
	//}
	//style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

	//ImGui::Checkbox("Lock Axis", &Scale_Lock);
	//{

	//}

	//style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

	//ImGui::Spacing();
	//ImGui::Unindent();

	//ImGui::Unindent();
	//ImGui::Unindent();
}

