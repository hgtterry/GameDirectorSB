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

	// ---------------- Get Material Name
	Ogre::String text = BaseEntity->getMesh()->getSubMesh(0)->getMaterialName().c_str();
	Ogre::MaterialPtr  Mat = static_cast<Ogre::MaterialPtr> (Ogre::MaterialManager::getSingleton().getByName(text));
	strcpy(Material_FileName, Mat->getOrigin().c_str());


	// ---------------- Copy Scripts
	int NumSubMesh = BaseEntity->getMesh()->getNumSubMeshes();
	int Count = 0;
	while (Count < NumSubMesh)
	{
		Ogre::String text = BaseEntity->getMesh()->getSubMesh(Count)->getMaterialName().c_str();
		Ogre::MaterialPtr  Mat = static_cast<Ogre::MaterialPtr> (Ogre::MaterialManager::getSingleton().getByName(text));

		char Name[MAX_PATH] = { 0 };
		char Num[MAX_PATH] = { 0 };
		_itoa(Count, Num, 10);

		strcpy(Name, "Clone_");
		strcat(Name, Num);

		MatClone[Count] = Mat->clone(Name);

		Count++;
	}


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
	ImGui::SetNextWindowSize(ImVec2(350, 250), ImGuiCond_FirstUseEver);

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
			bool test = App->SBC_FileIO->OpenTextureFile("Texture",NULL, NULL);
			if (test == 1)
			{
				Copy_Texture();
				Mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(App->SBC_FileIO->Texture_FileName);
				Mat->getTechnique(0)->getPass(0)->setAmbient(1, 1, 1);
				Update_MaterialFile();
			}

		}

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Button("Close", ImVec2(100, 0)))
		{
			//Update_MaterialFile();
			Show_Material_Editor = 0;
			Close_Material_Editor();
			Show_Material_Editor = 0;
		}

		ImGui::SameLine();

		if (ImGui::Button("Undo All", ImVec2(100, 0)))
		{

			int NumSubMesh = BaseEntity->getMesh()->getNumSubMeshes();
			int Count = 0;
			while (Count < NumSubMesh)
			{
				Ogre::String text = BaseEntity->getMesh()->getSubMesh(Count)->getMaterialName().c_str();
				Ogre::MaterialPtr  Mat = static_cast<Ogre::MaterialPtr> (Ogre::MaterialManager::getSingleton().getByName(text));
				MatClone[Count]->copyDetailsTo(Mat);
				Count++;
			}

			Update_MaterialFile();
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
// *			 Copy_Texture:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Materials::Copy_Texture()
{
	char SourceFile[MAX_PATH] = { 0 };
	char DestinationFile[MAX_PATH] = { 0 };

	strcpy(SourceFile, App->SBC_FileIO->Texture_Path_FileName);

	strcpy(DestinationFile, App->SBC_Project->m_Main_Assets_Path);
	strcat(DestinationFile, App->SBC_FileIO->Texture_FileName);


	//App->Say_Win(SourceFile);
	//App->Say_Win(DestinationFile);

	CopyFile(SourceFile, DestinationFile, false);
}


// *************************************************************************
// *			Update_MaterialFile:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Materials::Update_MaterialFile()
{

	_chdir(App->SBC_Project->m_Main_Assets_Path);

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


