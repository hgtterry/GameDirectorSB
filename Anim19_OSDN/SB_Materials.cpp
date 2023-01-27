#include "stdafx.h"
#include "GD19_App.h"
#include "SB_Materials.h"

SB_Materials::SB_Materials(void)
{
	Show_Material_Editor = 0;
	item_current_idx = 0;
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
	item_current_idx = 0;

	if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
	{
		BaseEntity = App->SBC_Scene->B_Area[Index]->Area_Ent;
	}
	else
	{
		BaseEntity = App->SBC_Scene->B_Object[Index]->Object_Ent;
	}

	Ogre::String text = BaseEntity->getMesh()->getSubMesh(0)->getMaterialName().c_str();
	Ogre::MaterialPtr  Mat = static_cast<Ogre::MaterialPtr> (Ogre::MaterialManager::getSingleton().getByName(text));
	strcpy(Material_FileName, Mat->getOrigin().c_str());

	App->SBC_FileView->Show_FileView(false);

	Show_Material_Editor = 1;
}

// *************************************************************************
// *			Material_Editor_Gui:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Materials::Material_Editor_Gui()
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(350, 300), ImGuiCond_FirstUseEver);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));

	if (!ImGui::Begin("Material_Editor", &Show_Material_Editor, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{

		ImGuiColorEditFlags misc_flags2 = (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8);

		ImGui::Spacing();
		ImGui::Spacing();

		// ---------------------------------------------------------------- Main Light

		ImGui::Text("Material Editor");
		ImGui::Separator();

		int NumSubMesh = BaseEntity->getMesh()->getNumSubMeshes();

		ImGui::Text("SubMeshes %i %s", NumSubMesh, Material_FileName);
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

			//Mat->getTechnique(0)->getPass(0)->setAmbient(0, 0, 1);

			Update_MaterialFile();

		}


		if (ImGui::Button("Close", ImVec2(100, 0)))
		{
			ImGui::PopStyleColor();
			Close_Material_Editor();
			//Show_Material_Editor = 0;
		}

		ImGui::PopStyleColor();
		ImGui::End();
	}
}

// *************************************************************************
// *		 Close_Material_Editor:- Terry and Hazel Flanigan 2023  	   *
// *************************************************************************
void SB_Materials::Close_Material_Editor()
{
	Show_Material_Editor = 0;
	BaseEntity = nullptr;
	item_current_idx = 0;

	App->SBC_FileView->Show_FileView(true);
}

// *************************************************************************
// *			Update_MaterialFile:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Materials::Update_MaterialFile()
{
	int NumSubMesh = BaseEntity->getMesh()->getNumSubMeshes();

	Ogre::MaterialSerializer matSer;

	for (int n = 0; n < NumSubMesh; n++)
	{
		Ogre::MaterialPtr  Mat;

		Ogre::String text = BaseEntity->getMesh()->getSubMesh(n)->getMaterialName().c_str();
		Mat = static_cast<Ogre::MaterialPtr> (Ogre::MaterialManager::getSingleton().getByName(text));

		matSer.queueForExport(Mat);
	}

	matSer.exportQueued(Material_FileName);

}


