#include "stdafx.h"
#include "GD19_App.h"
#include "SB_Materials.h"

SB_Materials::SB_Materials(void)
{
	Show_Material_Editor = 0;
	Show_Scroll_Editor = 0;
	item_current_idx = 0;
	BaseEntity = nullptr;
	NumSubMesh = 0;
	MatClone.resize(0);
}

SB_Materials::~SB_Materials(void)
{
}

// *************************************************************************
// *		 Start_Material_Editor:- Terry and Hazel Flanigan 2023  	   *
// *************************************************************************
void SB_Materials::Start_Material_Editor()
{
	NumSubMesh = 0;
	MatClone.resize(0);

	int Index = App->SBC_Properties->Current_Selected_Object;
	item_current_idx = 0;

	if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
	{
		BaseEntity = App->SBC_Scene->B_Area[Index]->Area_Ent;
	}
	else
	{
		BaseEntity = App->SBC_Scene->V_Object[Index]->Object_Ent;
	}

	// ---------------- Get Material Name
	Get_Material_Name(BaseEntity);

	// ---------------- Copy Scripts
	NumSubMesh = BaseEntity->getMesh()->getNumSubMeshes();

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

		MatClone.push_back(Mat->clone(Name));

		Count++;
	}


	App->SBC_FileView->Show_FileView(false);

	App->SBC_Panels->Close_Gui_Panels();
	App->SBC_Panels->Enable_All_Panels(false);

	Show_Material_Editor = 1;
}

// *************************************************************************
// *			Material_Editor_Gui:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Materials::Material_Editor_Gui()
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(320, 350), ImGuiCond_FirstUseEver);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));

	if (!ImGui::Begin("Material_Editor", &Show_Material_Editor, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{

		ImGui::Spacing();
		ImGui::Spacing();

		// ---------------------------------------------------------------- Material Editor

		ImGui::Text("Material Editor");
		ImGui::Separator();

		ImGui::Text(Material_FileName);
		ImGui::Text("Sub Materials %i", NumSubMesh);

		if (ImGui::BeginCombo("###MATS", BaseEntity->getMesh()->getSubMesh(item_current_idx)->getMaterialName().c_str()))
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
		MatCurent = static_cast<Ogre::MaterialPtr> (Ogre::MaterialManager::getSingleton().getByName(text));

		//ImGui::Text("Texture:-  %s", Mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName().c_str());

		char Texture[256];

		strcpy(Texture, MatCurent->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName().c_str());

		const char* listbox_items[] = { Texture,"Scroll"};
		static int listbox_item_current = -1;
		
		if (ImGui::ListBox("##L1", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items), 4))
		{
			if (listbox_item_current == 0) // Change Texture
			{
				bool test = App->SBC_FileIO->OpenTextureFile("Texture", NULL, NULL);
				if (test == 1)
				{
					Copy_Texture();
					MatCurent->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureName(App->SBC_FileIO->Texture_FileName);
					MatCurent->getTechnique(0)->getPass(0)->setAmbient(1, 1, 1);
					//MatCurent->getTechnique(0)->getPass(0)->setPolygonMode(Ogre::PolygonMode::PM_POINTS);
					Update_MaterialFile();
				}
			}

			
			if (listbox_item_current == 1) // Scroll
			{
				MatCurent->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setScrollAnimation(0.01, 0.71);
				//Mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureRotate(Ogre::Radian(90));
				//Update_MaterialFile();
			}
		}

		if (listbox_item_current == 1)
		{
			Show_Scroll_Editor = 1;
			Scroll_Gui();
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
// *				Scroll_Gui:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Materials::Scroll_Gui()
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(320, 350), ImGuiCond_FirstUseEver);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));

	if (!ImGui::Begin("Scroll_Editor", &Show_Scroll_Editor, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
	}
	else
	{
		ImGui::Text("Scroll Editor");
		ImGui::Separator();

		ImGui::Text("Poop %f", MatCurent->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureUScroll());
		
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

	App->SBC_Panels->Enable_All_Panels(true);
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

// *************************************************************************
// *			Get_Material_Name:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Materials::Get_Material_Name(Ogre::Entity* mEntity)
{
	Ogre::String text = mEntity->getMesh()->getSubMesh(0)->getMaterialName().c_str();
	Ogre::MaterialPtr  Mat = static_cast<Ogre::MaterialPtr> (Ogre::MaterialManager::getSingleton().getByName(text));

	strcpy(Material_FileName, Mat->getOrigin().c_str());
}


