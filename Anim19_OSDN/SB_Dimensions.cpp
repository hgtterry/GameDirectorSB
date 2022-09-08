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
#include "SB_Dimensions.h"

SB_Dimensions::SB_Dimensions()
{
	
		Show_Dimensions = 0;

		PosX_Selected = 1;
		PosY_Selected = 0;
		PosZ_Selected = 0;

		ScaleX_Selected = 1;
		ScaleY_Selected = 0;
		ScaleZ_Selected = 0;

		Model_X_Delta = 1;
	
}

SB_Dimensions::~SB_Dimensions()
{
	

}

// *************************************************************************
// *						ImGui_Dimensions  Terry Bernie				   *
// *************************************************************************
void SB_Dimensions::ImGui_Dimensions(void)
{
	ImGui::SetNextWindowPos(ImVec2(250, 10), ImGuiCond_FirstUseEver);

	ImGuiStyle* style = &ImGui::GetStyle();

	if (!ImGui::Begin("Rotation2", &Show_Dimensions, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		int Index = App->SBC_Properties->Current_Selected_Object;
		//App->CL_Ogre->RenderListener->Show_Crosshair = 1;


		//*************************************************************************************** Rotation
		ImGui_Position();
		ImGui_Scale();

		//ImGui_Rotation();

		if (ImGui::Button("Close"))
		{
			Show_Dimensions = 0;
			//App->CL_Panels->Show_Panels(1);
			//App->CL_TopBar->Toggle_Dimensions_Flag = 0;
			//RedrawWindow(App->CL_TopBar->Model_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			//App->CL_Ogre->RenderListener->Show_Crosshair = 0;
		}

		ImGui::End();
	}
}

// *************************************************************************
// *						ImGui_Position Terry Flanigan				   *
// *************************************************************************
void SB_Dimensions::ImGui_Position(void)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	Ogre::Vector3 Pos = App->SBC_Scene->B_Object[Index]->Object_Node->getPosition();

	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::Text("Position");
	ImGui::Separator();
	ImGui::Spacing();

	if (App->SBC_Scene->Scene_Loaded == 1)
	{
		/*pos.x = App->CL_Model->S_BoundingBox[0]->Centre->x;
		pos.y = App->CL_Model->S_BoundingBox[0]->Centre->y;
		pos.z = App->CL_Model->S_BoundingBox[0]->Centre->z;

		App->CL_Ogre->RenderListener->Hair_1PosX = pos.x;
		App->CL_Ogre->RenderListener->Hair_1PosY = pos.y;
		App->CL_Ogre->RenderListener->Hair_1PosZ = pos.z;*/
	}

	ImGui::Indent();
	ImGui::Indent();
	ImGui::Text("X %.3f Y %.3f Z %.3f", Pos.x, Pos.y, Pos.z);

	ImGui::Spacing();

	// ----------------------------------------------------------------------------- Position

	float spacingX = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);
	if (ImGui::ArrowButton("##leftXX", ImGuiDir_Left))
	{
		if (App->SBC_Scene->Scene_Loaded == 1)
		{
			if (PosX_Selected == 1)
			{
				Pos.x = Pos.x - Model_X_Delta;
				App->SBC_Scene->B_Object[Index]->Object_Node->setPosition(Pos);

				AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
				worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
				Ogre::Vector3 Centre = worldAAB.getCenter();
				App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
			}

			if (PosY_Selected == 1)
			{
				Pos.y = Pos.y + Model_X_Delta;
				App->SBC_Scene->B_Object[Index]->Object_Node->setPosition(Pos);

				AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
				worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
				Ogre::Vector3 Centre = worldAAB.getCenter();
				App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
			}

			if (PosZ_Selected == 1)
			{
				Pos.z = Pos.z - Model_X_Delta;
				App->SBC_Scene->B_Object[Index]->Object_Node->setPosition(Pos);

				AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
				worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
				Ogre::Vector3 Centre = worldAAB.getCenter();
				App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
			}
		}
	}

	ImGui::SameLine(0.0f, spacingX);
	if (ImGui::ArrowButton("##rightXX", ImGuiDir_Right))
	{
		if (App->SBC_Scene->Scene_Loaded == 1)
		{
			if (PosX_Selected == 1)
			{
				Pos.x = Pos.x + Model_X_Delta;
				App->SBC_Scene->B_Object[Index]->Object_Node->setPosition(Pos);

				AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
				worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
				Ogre::Vector3 Centre = worldAAB.getCenter();
				App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
			}

			if (PosY_Selected == 1)
			{
				Pos.y = Pos.y - Model_X_Delta;
				App->SBC_Scene->B_Object[Index]->Object_Node->setPosition(Pos);

				AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
				worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
				Ogre::Vector3 Centre = worldAAB.getCenter();
				App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
			}

			if (PosZ_Selected == 1)
			{
				Pos.z = Pos.z + Model_X_Delta;
				App->SBC_Scene->B_Object[Index]->Object_Node->setPosition(Pos);

				AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
				worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
				Ogre::Vector3 Centre = worldAAB.getCenter();
				App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
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
		Model_X_Delta = (float)atof(XitemsPosXX[XitemPosXX]);
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

	ImGui::Unindent();
	ImGui::Unindent();
}

// *************************************************************************
// *						ImGui_Scale Terry Flanigan					   *
// *************************************************************************
void SB_Dimensions::ImGui_Scale(void)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	Ogre::Vector3 Scale = App->SBC_Scene->B_Object[Index]->Object_Node->getScale();

	ImGuiStyle* style = &ImGui::GetStyle();

	ImGui::Text("Scale");
	ImGui::Separator();
	ImGui::Spacing();

	if (App->SBC_Scene->Scene_Loaded == 1)
	{
		/*pos.x = App->CL_Model->S_BoundingBox[0]->Centre->x;
		pos.y = App->CL_Model->S_BoundingBox[0]->Centre->y;
		pos.z = App->CL_Model->S_BoundingBox[0]->Centre->z;

		App->CL_Ogre->RenderListener->Hair_1PosX = pos.x;
		App->CL_Ogre->RenderListener->Hair_1PosY = pos.y;
		App->CL_Ogre->RenderListener->Hair_1PosZ = pos.z;*/
	}

	ImGui::Indent();
	ImGui::Indent();
	ImGui::Text("X %.3f Y %.3f Z %.3f", Scale.x, Scale.y, Scale.z);

	ImGui::Spacing();

	// ----------------------------------------------------------------------------- Scale

	float spacingX = ImGui::GetStyle().ItemInnerSpacing.x;
	ImGui::PushButtonRepeat(true);
	if (ImGui::ArrowButton("##leftXX", ImGuiDir_Left))
	{
		if (App->SBC_Scene->Scene_Loaded == 1)
		{
			if (ScaleX_Selected == 1)
			{
				Scale.x = Scale.x - 1;
				App->SBC_Scene->B_Object[Index]->Object_Node->setScale(Scale);

				AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
				worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
				Ogre::Vector3 Centre = worldAAB.getCenter();
				App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));

				//App->CL_Dimensions->Translate_Model(-App->CL_Dimensions->Model_X_Position, 0, 0);
			}

			if (ScaleY_Selected == 1)
			{
				Scale.y = Scale.y + 1;
				App->SBC_Scene->B_Object[Index]->Object_Node->setScale(Scale);

				AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
				worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
				Ogre::Vector3 Centre = worldAAB.getCenter();
				App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
				//App->CL_Dimensions->Translate_Model(0, -App->CL_Dimensions->Model_X_Position, 0);
			}

			if (ScaleZ_Selected == 1)
			{
				Scale.z = Scale.z - 1;
				App->SBC_Scene->B_Object[Index]->Object_Node->setScale(Scale);

				AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
				worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
				Ogre::Vector3 Centre = worldAAB.getCenter();
				App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
				//App->Cl_Vm_Dimensions->Translate_Model(0, 0, -App->CL_Dimensions->Model_X_Position);
			}
		}
	}

	ImGui::SameLine(0.0f, spacingX);
	if (ImGui::ArrowButton("##rightXX", ImGuiDir_Right))
	{
		if (App->SBC_Scene->Scene_Loaded == 1)
		{
			if (ScaleX_Selected == 1)
			{
				Scale.x = Scale.x + 1;
				App->SBC_Scene->B_Object[Index]->Object_Node->setScale(Scale);

				AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
				worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
				Ogre::Vector3 Centre = worldAAB.getCenter();
				App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
				//App->CL_Dimensions->Translate_Model(App->CL_Dimensions->Model_X_Position, 0, 0);
			}

			if (ScaleY_Selected == 1)
			{
				Scale.y = Scale.y - 1;
				App->SBC_Scene->B_Object[Index]->Object_Node->setScale(Scale);

				AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
				worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
				Ogre::Vector3 Centre = worldAAB.getCenter();
				App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
				//App->CL_Dimensions->Translate_Model(0, App->CL_Dimensions->Model_X_Position, 0);
			}

			if (ScaleZ_Selected == 1)
			{
				Scale.z = Scale.z + 1;
				App->SBC_Scene->B_Object[Index]->Object_Node->setScale(Scale);

				AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Index]->Object_Ent->getBoundingBox();
				worldAAB.transformAffine(App->SBC_Scene->B_Object[Index]->Object_Node->_getFullTransform());
				Ogre::Vector3 Centre = worldAAB.getCenter();
				App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
				//App->CL_Dimensions->Translate_Model(0, 0, App->CL_Dimensions->Model_X_Position);
			}
		}
	}
	ImGui::PopButtonRepeat();

	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	const char* XitemsScaleXX[] = { "0.001","0.01","0.1","1", "2", "5", "10", "20" };
	static int XitemScaleXX = 3;
	bool ChangedScaleX = ImGui::Combo("Step Scale", &XitemScaleXX, XitemsScaleXX, IM_ARRAYSIZE(XitemsScaleXX));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.
	if (ChangedScaleX == 1)
	{
		//App->CL_Dimensions->Model_X_Position = (float)atof(XitemsPosXX[XitemPosXX]);
	}

	// ----------------------------------------------------------------------------- Pos X
	ImGui::Indent();

	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 0.0f, 1.0f, 1.00f);
	ImGui::Checkbox("X", &ScaleX_Selected);
	if (ScaleX_Selected == 1)
	{
		ScaleY_Selected = 0;
		ScaleZ_Selected = 0;
	}
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);
	//------------------------------------------------------------------------------- Pos Y
	ImGui::SameLine();
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);
	ImGui::Checkbox("Y", &ScaleY_Selected);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);

	if (ScaleY_Selected)
	{
		ScaleX_Selected = 0;
		ScaleZ_Selected = 0;
	}

	//------------------------------------------------------------------------------- Pos Z
	ImGui::SameLine();
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.00f);
	ImGui::Checkbox("Z", &ScaleZ_Selected);
	if (ScaleZ_Selected)
	{
		ScaleX_Selected = 0;
		ScaleY_Selected = 0;
	}
	style->Colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.00f);


	style->Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

	ImGui::Spacing();
	ImGui::Unindent();

	ImGui::Unindent();
	ImGui::Unindent();
}
