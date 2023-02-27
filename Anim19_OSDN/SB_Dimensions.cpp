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
#include "GD19_App.h"
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
		Model_Scale_Delta = 0.01;
		Model_Rotation_Delta = 1;

		Scale_Lock = 1;

		// -------------------------- Pointers
		pBase_Mesh_Name = NULL;

		pBase_Shape = NULL;

		pBase_Object_Ent = NULL;
		pBase_Object_Node = NULL;
		pBase_Mesh_Pos = NULL;
		pBase_Mesh_Rot = NULL;
		pBase_Mesh_Quat = NULL;

		pBase_Phys_Body = NULL;
		pBase_Physics_Pos = NULL;
		pBase_Physics_Scale = NULL;
		pBase_Physics_Rot = NULL;
		pBase_Physics_Quat = NULL;
}

SB_Dimensions::~SB_Dimensions()
{
	
}


// *************************************************************************
// *						ImGui_Dimensions  Terry Flanigan			   *
// *************************************************************************
void SB_Dimensions::Prepare_Dimensions(void)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
	{
		pBase_Mesh_Name = App->SBC_Scene->B_Area[Index]->Area_Name;

		pBase_Shape = &App->SBC_Scene->B_Area[Index]->Shape;

		pBase_Object_Ent = App->SBC_Scene->B_Area[Index]->Area_Ent;
		pBase_Object_Node = App->SBC_Scene->B_Area[Index]->Area_Node;
		pBase_Mesh_Pos = &App->SBC_Scene->B_Area[Index]->Mesh_Pos;
		pBase_Mesh_Scale = &App->SBC_Scene->B_Area[Index]->Mesh_Scale;
		pBase_Mesh_Rot = &App->SBC_Scene->B_Area[Index]->Mesh_Rot;
		pBase_Mesh_Quat = &App->SBC_Scene->B_Area[Index]->Mesh_Quat;

		pBase_Phys_Body = App->SBC_Scene->B_Area[Index]->Phys_Body;
		pBase_Physics_Pos = &App->SBC_Scene->B_Area[Index]->Physics_Pos;
		pBase_Physics_Scale = &App->SBC_Scene->B_Area[Index]->Physics_Scale;
		pBase_Physics_Rot = &App->SBC_Scene->B_Area[Index]->Physics_Rot;
		pBase_Physics_Quat = &App->SBC_Scene->B_Area[Index]->Physics_Quat;

		//App->Say("Area");
	}
	else
	{
		pBase_Mesh_Name = App->SBC_Scene->B_Object[Index]->Mesh_Name;

		pBase_Shape = &App->SBC_Scene->B_Object[Index]->Shape;

		pBase_Object_Ent = App->SBC_Scene->B_Object[Index]->Object_Ent;
		pBase_Object_Node = App->SBC_Scene->B_Object[Index]->Object_Node;
		pBase_Mesh_Pos  = &App->SBC_Scene->B_Object[Index]->Mesh_Pos;
		pBase_Mesh_Scale = &App->SBC_Scene->B_Object[Index]->Mesh_Scale;
		pBase_Mesh_Rot = &App->SBC_Scene->B_Object[Index]->Mesh_Rot;
		pBase_Mesh_Quat = &App->SBC_Scene->B_Object[Index]->Mesh_Quat;

		pBase_Phys_Body = App->SBC_Scene->B_Object[Index]->Phys_Body;
		pBase_Physics_Pos = &App->SBC_Scene->B_Object[Index]->Physics_Pos;
		pBase_Physics_Scale = &App->SBC_Scene->B_Object[Index]->Physics_Scale;
		pBase_Physics_Rot = &App->SBC_Scene->B_Object[Index]->Physics_Rot;
		pBase_Physics_Quat = &App->SBC_Scene->B_Object[Index]->Physics_Quat;

		//App->Say("Object");
	}
}

// *************************************************************************
// *						ImGui_Dimensions  Terry Flanigan			   *
// *************************************************************************
void SB_Dimensions::ImGui_Dimensions(void)
{
	ImGui::SetNextWindowPos(ImVec2(250, 10), ImGuiCond_FirstUseEver);

	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(210, 210, 210, 210));
	

	if (!ImGui::Begin("Rotation2", &Show_Dimensions, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		

		int Index = App->SBC_Properties->Current_Selected_Object;
		
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

			App->SBC_Markers->Hide_Axis_Marker();
			RedrawWindow(App->SBC_Props_Dialog->Dimensions_Dlg_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

		}

		style->Colors[ImGuiCol_Button] = ImVec4(0.8f, 0.8f, 0.8f, 1);

		//--------------------------------------- Rotation
		ImGui::SameLine();

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

			App->SBC_Markers->Hide_Axis_Marker();
			RedrawWindow(App->SBC_Props_Dialog->Dimensions_Dlg_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

		}
		style->Colors[ImGuiCol_Button] = ImVec4(0.8f, 0.8f, 0.8f, 1);

		//--------------------------------------- Scale
		ImGui::SameLine();

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

			App->SBC_Markers->Hide_Axis_Marker();
			RedrawWindow(App->SBC_Props_Dialog->Dimensions_Dlg_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

		}

		style->Colors[ImGuiCol_Button] = ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
	
		ImGui::Unindent();
		ImGui::Unindent();

		if (Show_Position == 1)
		{
			ImGui_Position();
		}

		if (Show_Scale == 1)
		{
			ImGui_Scale();
		}

		if (Show_Rotation == 1)
		{
			ImGui_Rotation();
		}
		
		ImGui::Separator();
		ImGui::Spacing();

		if (ImGui::Button("Close"))
		{
			Show_Dimensions = 0;
			Show_Position = 0;
			Show_Scale = 0;
			Show_Rotation = 0;

			App->SBC_Markers->Hide_Axis_Marker();
			RedrawWindow(App->SBC_Props_Dialog->Dimensions_Dlg_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			//App->CL_Ogre->RenderListener->Show_Crosshair = 0;
		}

		ImGui::PopStyleColor();
		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Position Terry Flanigan				   *
// *************************************************************************
void SB_Dimensions::ImGui_Position(void)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	Ogre::Vector3 Pos = *pBase_Mesh_Pos;// App->SBC_Scene->B_Object[Index]->Mesh_Pos;

	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::Text("Position");
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Text("Object ID = %i", App->SBC_Properties->Current_Selected_Object);
	ImGui::Text("Object Name: = %s", pBase_Mesh_Name);
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
		App->SBC_Markers->Hide_Axis_Marker();
		App->SBC_Markers->Update_Blue_Axis_Marker(Index);

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
		App->SBC_Markers->Hide_Axis_Marker();
		App->SBC_Markers->Update_Green_Axis_Marker(Index);

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
		App->SBC_Markers->Hide_Axis_Marker();
		App->SBC_Markers->Update_Red_Axis_Marker(Index);

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
		if (App->SBC_Scene->Scene_Loaded == 1)
		{
			if (PosX_Selected == 1)
			{
				Pos.x = Pos.x + Model_Pos_Delta;
				Set_Position(Pos);
			}

			if (PosY_Selected == 1)
			{
				Pos.y = Pos.y + Model_Pos_Delta;
				Set_Position(Pos);
			}

			if (PosZ_Selected == 1)
			{
				Pos.z = Pos.z + Model_Pos_Delta;
				Set_Position(Pos);
			}
		}
	}

	ImGui::SameLine();
	if (ImGui::ArrowButton("##rightXX", ImGuiDir_Right))
	{
		if (App->SBC_Scene->Scene_Loaded == 1)
		{
			if (PosX_Selected == 1)
			{
				Pos.x = Pos.x - Model_Pos_Delta;
				Set_Position(Pos);
			}

			if (PosY_Selected == 1)
			{
				Pos.y = Pos.y - Model_Pos_Delta;
				Set_Position(Pos);
			}

			if (PosZ_Selected == 1)
			{
				Pos.z = Pos.z - Model_Pos_Delta;
				Set_Position(Pos);
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
void SB_Dimensions::Set_Position(Ogre::Vector3 Pos)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	pBase_Object_Node->setPosition(Pos);

	pBase_Mesh_Pos->x = Pos.x;
	pBase_Mesh_Pos->y = Pos.y;
	pBase_Mesh_Pos->z = Pos.z;



	if (pBase_Phys_Body)
	{
		
		Ogre::Vector3 Centre = Get_BoundingBox_World_Centre();

		pBase_Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));

		UpDate_Physics_And_Visuals(Index);
	}
	else
	{
		App->SBC_Markers->MarkerBB_Addjust(Index);
	}

	
}

// *************************************************************************
// *						ImGui_Scale Terry Flanigan					   *
// *************************************************************************
void SB_Dimensions::ImGui_Scale(void)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	Ogre::Vector3 Scale = *pBase_Mesh_Scale;

	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::Text("Scale");
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Text("Object ID = %i", App->SBC_Properties->Current_Selected_Object);
	ImGui::Text("Object Name: = %s", pBase_Mesh_Name);
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	float vec4a[4] = { Scale.x, Scale.y, Scale.z, 0.44f };
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
			App->SBC_Markers->Hide_Axis_Marker();
			App->SBC_Markers->Update_Red_Axis_Marker(Index);
			App->SBC_Markers->Update_Green_Axis_Marker(Index);
			App->SBC_Markers->Update_Blue_Axis_Marker(Index);
		}
		else
		{
			App->SBC_Markers->Hide_Axis_Marker();
			App->SBC_Markers->Update_Blue_Axis_Marker(Index);
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
			App->SBC_Markers->Hide_Axis_Marker();
			App->SBC_Markers->Update_Red_Axis_Marker(Index);
			App->SBC_Markers->Update_Green_Axis_Marker(Index);
			App->SBC_Markers->Update_Blue_Axis_Marker(Index);
		}
		else
		{
			App->SBC_Markers->Hide_Axis_Marker();
			App->SBC_Markers->Update_Green_Axis_Marker(Index);
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
			App->SBC_Markers->Hide_Axis_Marker();
			App->SBC_Markers->Update_Red_Axis_Marker(Index);
			App->SBC_Markers->Update_Green_Axis_Marker(Index);
			App->SBC_Markers->Update_Blue_Axis_Marker(Index);
		}
		else
		{
			App->SBC_Markers->Hide_Axis_Marker();
			App->SBC_Markers->Update_Red_Axis_Marker(Index);
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
		if (App->SBC_Scene->Scene_Loaded == 1)
		{
			if (Scale_Lock == 1)
			{
				Scale.x = Scale.x + Model_Scale_Delta;
				Scale.y = Scale.y + Model_Scale_Delta;
				Scale.z = Scale.z + Model_Scale_Delta;

				Set_Scale(Scale);
			}
			else
			{
				if (ScaleX_Selected == 1)
				{
					Scale.x = Scale.x + Model_Scale_Delta;

					Set_Scale(Scale);

				}

				if (ScaleY_Selected == 1)
				{
					Scale.y = Scale.y + Model_Scale_Delta;

					Set_Scale(Scale);

				}

				if (ScaleZ_Selected == 1)
				{
					Scale.z = Scale.z + Model_Scale_Delta;

					Set_Scale(Scale);
				}
			}
		}
	}

	ImGui::SameLine();
	if (ImGui::ArrowButton("##rightSX", ImGuiDir_Right))
	{
		if (App->SBC_Scene->Scene_Loaded == 1)
		{
			if (Scale_Lock == 1)
			{
				Scale.x = Scale.x - Model_Scale_Delta;
				Scale.y = Scale.y - Model_Scale_Delta;
				Scale.z = Scale.z - Model_Scale_Delta;

				Set_Scale(Scale);
			}
			else
			{
				if (ScaleX_Selected == 1)
				{
					Scale.x = Scale.x - Model_Scale_Delta;

					Set_Scale(Scale);
					
				}

				if (ScaleY_Selected == 1)
				{
					Scale.y = Scale.y - Model_Scale_Delta;

					Set_Scale(Scale);
				
				}

				if (ScaleZ_Selected == 1)
				{
					Scale.z = Scale.z - Model_Scale_Delta;

					Set_Scale(Scale);
					
				}
			}
		}
	}
	ImGui::PopButtonRepeat();

	// ----------------------------------------------------------------------------- Scale Combo Step
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	const char* XitemsScaleXX[] = { "0.001","0.01","0.1","1", "2", "5", "10", "20" };
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
void SB_Dimensions::Set_Scale(Ogre::Vector3 Scale)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	pBase_Object_Node->setScale(Scale);

	pBase_Mesh_Scale->x = Scale.x;
	pBase_Mesh_Scale->y = Scale.y;
	pBase_Mesh_Scale->z = Scale.z;

	if (pBase_Phys_Body)
	{
		pBase_Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));
		pBase_Physics_Scale->x = Scale.x;
		pBase_Physics_Scale->y = Scale.y;
		pBase_Physics_Scale->z = Scale.z;

		UpDate_Physics_And_Visuals(Index);
	}

	App->SBC_Markers->MarkerBB_Addjust(Index);
}

// *************************************************************************
// *						ImGui_Rotation Terry Flanigan				   *
// *************************************************************************
void SB_Dimensions::ImGui_Rotation(void)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	Ogre::Vector3 mRotation = *pBase_Mesh_Rot;

	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::Text("Rotation");
	ImGui::Separator();
	ImGui::Spacing();

	ImGui::Text("Object ID = %i", App->SBC_Properties->Current_Selected_Object);
	ImGui::Text("Object Name: = %s", pBase_Mesh_Name);
	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

	float vec4a[4] = { mRotation.x, mRotation.y, mRotation.z, 0.44f };
	ImGui::InputFloat3("", vec4a, "%.3f", ImGuiInputTextFlags_ReadOnly);

	// ----------------------------------------------------------------------------- Rotation X
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

	//------------------------------------------------------------------------------- Rotation Y
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

	//------------------------------------------------------------------------------- Rotation Z
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
		if (App->SBC_Scene->Scene_Loaded == 1)
		{
			if (RotationX_Selected == 1)
			{
				pBase_Mesh_Rot->x += Model_Rotation_Delta;
				Set_Rotation(Ogre::Vector3(1,0,0), Model_Rotation_Delta);

			}

			if (RotationY_Selected == 1)
			{
				pBase_Mesh_Rot->y += Model_Rotation_Delta;
				Set_Rotation(Ogre::Vector3(0, 1, 0), Model_Rotation_Delta);
			}

			if (RotationZ_Selected == 1)
			{
				pBase_Mesh_Rot->z += Model_Rotation_Delta;
				Set_Rotation(Ogre::Vector3(0, 0, 1), Model_Rotation_Delta);

			}
		}
	}

	ImGui::SameLine();
	if (ImGui::ArrowButton("##rightRX", ImGuiDir_Right))
	{
		if (App->SBC_Scene->Scene_Loaded == 1)
		{
			
				if (RotationX_Selected == 1)
				{
					pBase_Mesh_Rot->x -= Model_Rotation_Delta;
					Set_Rotation(Ogre::Vector3(1, 0, 0), -Model_Rotation_Delta);

				}

				if (RotationY_Selected == 1)
				{
					pBase_Mesh_Rot->y -= Model_Rotation_Delta;
					Set_Rotation(Ogre::Vector3(0, 1, 0), -Model_Rotation_Delta);

				}

				if (RotationZ_Selected == 1)
				{
					pBase_Mesh_Rot->z -= Model_Rotation_Delta;
					Set_Rotation(Ogre::Vector3(0, 0, 1), -Model_Rotation_Delta);

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
// *						Set_Rotation Terry Flanigan					   *
// *************************************************************************
void SB_Dimensions::Set_Rotation(Ogre::Vector3 Rotation,float Delta)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	pBase_Object_Node->rotate(Ogre::Quaternion(Ogre::Degree(Delta), Rotation), Ogre::Node::TransformSpace::TS_LOCAL);

	pBase_Mesh_Quat->w = pBase_Object_Node->getOrientation().w;
	pBase_Mesh_Quat->x = pBase_Object_Node->getOrientation().x;
	pBase_Mesh_Quat->y = pBase_Object_Node->getOrientation().y;
	pBase_Mesh_Quat->z = pBase_Object_Node->getOrientation().z;

	if (pBase_Phys_Body)
	{
		pBase_Physics_Rot->x += Model_Rotation_Delta;

		pBase_Physics_Quat->w = pBase_Object_Node->getOrientation().w;
		pBase_Physics_Quat->x = pBase_Object_Node->getOrientation().x;
		pBase_Physics_Quat->y = pBase_Object_Node->getOrientation().y;
		pBase_Physics_Quat->z = pBase_Object_Node->getOrientation().z;

		pBase_Phys_Body->getWorldTransform().setRotation(btQuaternion(pBase_Physics_Quat->x,
			pBase_Physics_Quat->y, pBase_Physics_Quat->z, pBase_Physics_Quat->w));

		UpDate_Physics_And_Visuals(Index);
	}

	App->SBC_Markers->MarkerBB_Addjust(Index);
}

// *************************************************************************
// *	Get_BoundingBox_World_Centre:- Terry and Hazel Flanigan 2023	   *
// *************************************************************************
Ogre::Vector3 SB_Dimensions::Get_BoundingBox_World_Centre()
{
	
	if (*pBase_Shape == Enums::Shape_TriMesh)
	{
		Ogre::Vector3 Pos = pBase_Object_Node->getPosition();
		return Pos;
	}
	else
	{
		AxisAlignedBox worldAAB = pBase_Object_Ent->getBoundingBox();
		worldAAB.transformAffine(pBase_Object_Node->_getFullTransform());
		Ogre::Vector3 Centre = worldAAB.getCenter();

		return Centre;
	}
}

// *************************************************************************
// *				UpDate_Physics_And_Visuals Terry Flanigan		 	   *
// *************************************************************************
void SB_Dimensions::UpDate_Physics_And_Visuals(int Index)
{
	if (*pBase_Shape == Enums::Shape_TriMesh)
	{

	}
	else
	{
		{
			Set_Physics_Position();
		}
	}


	App->SBC_Markers->MarkerBB_Addjust(Index);

	// Needs Looking at
	App->SBC_Scene->B_Object[Index]->Altered = 1;
	App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Object[Index]->FileViewItem);
	App->SBC_Scene->Scene_Modified = 1;
}

// *************************************************************************
// *	  			Set_Physics_Position Terry Flanigan				   *
// *************************************************************************
void SB_Dimensions::Set_Physics_Position()
{
	AxisAlignedBox worldAAB = pBase_Object_Ent->getBoundingBox();
	worldAAB.transformAffine(pBase_Object_Node->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();
	pBase_Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));

	pBase_Physics_Pos->x = Centre.x;
	pBase_Physics_Pos->y = Centre.y;
	pBase_Physics_Pos->z = Centre.z;
}


