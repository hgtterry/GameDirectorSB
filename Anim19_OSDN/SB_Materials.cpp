#include "stdafx.h"
#include "GD19_App.h"
#include "SB_Materials.h"

SB_Materials::SB_Materials(void)
{
	Show_Material_Editor = 0;
	BaseEntity = nullptr;
}

SB_Materials::~SB_Materials(void)
{
}

// *************************************************************************
// *		 Start_Material_Editor:- Terry and Hazel Flanigan 2023  	   *
// *************************************************************************
void SB_Materials::Start_Material_Editor()
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
	{
		BaseEntity = App->SBC_Scene->B_Area[Index]->Area_Ent;
	}
	else
	{
		BaseEntity = App->SBC_Scene->B_Object[Index]->Object_Ent;
	}

	Show_Material_Editor = 1;
}

// *************************************************************************
// *			Material_Editor_Gui:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Materials::Material_Editor_Gui()
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	//App->SBC_Scene->B_Object[Index]->Object_Ent->getMesh()->getSubMesh(1)->getMaterialName();

	

	ImGui::SetNextWindowPos(ImVec2(250, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(350, 490), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Material_Editor", &Show_Material_Editor, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
		return;
	}

	ImGuiColorEditFlags misc_flags2 = (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(213, 222, 242, 255));

	ImGui::Spacing();
	ImGui::Spacing();

	// ---------------------------------------------------------------- Main Light

	ImGui::Text("Material Editor");
	ImGui::Separator();

	if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
	{
		int NumSubMesh = App->SBC_Scene->B_Area[Index]->Area_Ent->getMesh()->getNumSubMeshes();
		static int item_current_idx = 0;

		ImGui::Text("SubMeshes %i", NumSubMesh);
		if (ImGui::BeginCombo("Materials", App->SBC_Scene->B_Area[Index]->Area_Ent->getMesh()->getSubMesh(item_current_idx)->getMaterialName().c_str()))
		{
			for (int n = 0; n < NumSubMesh; n++)
			{
				Ogre::String text = App->SBC_Scene->B_Area[Index]->Area_Ent->getMesh()->getSubMesh(n)->getMaterialName().c_str();
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(text.c_str(), is_selected))
					item_current_idx = n;

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}



		Ogre::String text = App->SBC_Scene->B_Area[Index]->Area_Ent->getMesh()->getSubMesh(item_current_idx)->getMaterialName().c_str();
		Ogre::MaterialPtr  Mat = static_cast<Ogre::MaterialPtr> (Ogre::MaterialManager::getSingleton().getByName(text));
		ImGui::Text("Texture:-  %s", Mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName().c_str());

		if (ImGui::Button("Change", ImVec2(100, 0)))
		{
			App->SBC_FileIO->OpenTextureFile("Texture", NULL, NULL);

			Mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(App->SBC_FileIO->Texture_FileName);
		}
	}
	else
	{
		int NumSubMesh = BaseEntity->getMesh()->getNumSubMeshes();
		static int item_current_idx = 0;

		ImGui::Text("SubMeshes %i", NumSubMesh);
		if (ImGui::BeginCombo("Materials", BaseEntity->getMesh()->getSubMesh(item_current_idx)->getMaterialName().c_str()))
		{
			for (int n = 0; n < NumSubMesh; n++)
			{
				Ogre::String text = BaseEntity->getMesh()->getSubMesh(n)->getMaterialName().c_str();
				const bool is_selected = (item_current_idx == n);
				if (ImGui::Selectable(text.c_str(), is_selected))
					item_current_idx = n;

				if (is_selected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}


			ImGui::EndCombo();
		}

		Ogre::String text = BaseEntity->getMesh()->getSubMesh(item_current_idx)->getMaterialName().c_str();
		Ogre::MaterialPtr  Mat = static_cast<Ogre::MaterialPtr> (Ogre::MaterialManager::getSingleton().getByName(text));

		ImGui::Text("Texture:-  %s", Mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName().c_str());

		if (ImGui::Button("Change", ImVec2(100, 0)))
		{
			App->SBC_FileIO->OpenTextureFile("Texture", NULL, NULL);

			Mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(App->SBC_FileIO->Texture_FileName);
		}

	}

	if (ImGui::Button("Close", ImVec2(100, 0)))
	{
		//Close_Environment_Editor();
		Show_Material_Editor = 0;
		ImGui::PopStyleColor();
	}

	ImGui::End();
}
